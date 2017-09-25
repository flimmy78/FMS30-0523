/*
* Copyright (c) 2011 Sveriges Television AB <info@casparcg.com>
*
* This file is part of CasparCG (www.casparcg.com).
*
* CasparCG is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CasparCG is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Robert Nagy, ronag89@gmail.com
*/

#include "matrox_producer.h"
#include "../../ffmpeg/producer/filter/filter.h"
#include "../../ffmpeg/producer/util/util.h"
#include "../../ffmpeg/producer/muxer/frame_muxer.h"
#include "../../ffmpeg/producer/muxer/display_mode.h"
#include <common/executor.h>
#include <common/diagnostics/graph.h>
#include <common/except.h>
#include <common/log.h>
#include <common/param.h>
#include <common/timer.h>
#include <common/memcpy.h>
//
#include <core/frame/audio_channel_layout.h>
#include <core/frame/frame.h>
#include <core/frame/draw_frame.h>
#include <core/frame/frame_transform.h>
#include <core/frame/frame_factory.h>
#include <core/producer/frame_producer.h>
#include <core/producer/framerate/framerate_producer.h>
#include <core/monitor/monitor.h>
#include <core/diagnostics/call_context.h>
#include <core/mixer/audio/audio_mixer.h>
#include <core/help/help_repository.h>
#include <core/help/help_sink.h>


#include <tbb/concurrent_queue.h>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/range/adaptor/transformed.hpp>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
	#define __STDC_CONSTANT_MACROS
	#define __STDC_LIMIT_MACROS
	#include <libavcodec/avcodec.h>
	#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

#include <functional>

#include "../common.h"
#include "../matrox_sdi_capture.h"
#include "../matrox_2022_capture.h"
namespace caspar {
	namespace matrox {

	core::audio_channel_layout get_adjusted_channel_layout(core::audio_channel_layout layout)
	{
		if (layout.num_channels <= 2)
			layout.num_channels = 2;
		else if (layout.num_channels <= 8)
			layout.num_channels = 8;
		else
			layout.num_channels = 16;

		return layout;
	}

	template <typename T>
	std::wstring to_string(const T& cadence)
	{
		return boost::join(cadence | boost::adaptors::transformed([](size_t i) { return boost::lexical_cast<std::wstring>(i); }), L", ");
	}

	ffmpeg::audio_input_pad create_input_pad(const core::video_format_desc& in_format, int num_channels)
	{
		return ffmpeg::audio_input_pad(
			boost::rational<int>(1, in_format.audio_sample_rate),
			in_format.audio_sample_rate,
			AVSampleFormat::AV_SAMPLE_FMT_S32,
			av_get_default_channel_layout(num_channels));
	}

class matrox_producer : boost::noncopyable
{
	producer_need									need_;
	std::shared_ptr<matrox_sdi_capture>				pjsdicap_;
	std::shared_ptr<matrox_2022_capture>			pj2022cap_;
	core::monitor::subject							monitor_subject_;
	spl::shared_ptr<diagnostics::graph>				graph_;
	caspar::timer									tick_timer_;

	const std::wstring								filter_;

	core::video_format_desc							in_format_desc_;
	std::vector<int>								audio_cadence_ = in_format_desc_.audio_cadence;
	
	spl::shared_ptr<core::frame_factory>			frame_factory_;
	core::audio_channel_layout						channel_layout_;
	ffmpeg::frame_muxer								muxer_{
		in_format_desc_.framerate,
		{create_input_pad(in_format_desc_, channel_layout_.num_channels)},
		frame_factory_,
		in_format_desc_,
		channel_layout_,
		filter_,
		ffmpeg::filter::is_deinterlacing(filter_)
	};
	std::shared_ptr<SwrContext>				swr_;
	core::constraints								constraints_{ in_format_desc_.width, in_format_desc_.height };

	tbb::concurrent_bounded_queue<core::draw_frame>	frame_buffer_;
	core::draw_frame								last_frame_ = core::draw_frame::empty();

	std::exception_ptr								exception_;

	tbb::atomic<bool>								is_running_;
	boost::thread									thread_;
	
public:
	matrox_producer(
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& in_format_desc,
		const core::audio_channel_layout& channel_layout,
		const std::wstring& filter,
		producer_need need)
		:filter_(filter)
		, in_format_desc_(in_format_desc)
		, frame_factory_(frame_factory)
		, channel_layout_(get_adjusted_channel_layout(channel_layout))
		,need_(need)
	{		
		if (need.type==type_mid::SDI_TYPE)
		{
			pjsdicap_ = std::make_shared<matrox_sdi_capture>(in_format_desc_.format, channel_layout.num_channels, need);
		}
		else if(need.type == type_mid::IP_TYPE)
		{
			pj2022cap_ = std::make_shared<matrox_2022_capture>(in_format_desc_.format, channel_layout.num_channels, need);
		}

		frame_buffer_.set_capacity(4);

		graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
		graph_->set_color("late-frame", diagnostics::color(0.6f, 0.3f, 0.3f));
		graph_->set_color("frame-time", diagnostics::color(1.0f, 0.0f, 0.0f));
		graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
		graph_->set_color("output-buffer", diagnostics::color(0.0f, 1.0f, 0.0f));
		graph_->set_text(print());
		diagnostics::register_graph(graph_);
		if (!swr_)
		{
			int outchannel = (int)av_get_default_channel_layout(channel_layout_.num_channels);
			int intchannel = outchannel;
			swr_ = {
				swr_alloc_set_opts(
					nullptr,
					intchannel,
					AV_SAMPLE_FMT_S32,// 需要配置的
					in_format_desc_.audio_sample_rate,//需要
					outchannel,
					AV_SAMPLE_FMT_S32,
					48000,//48000hz是matrox默认的暂时只支持这个
					0,
					nullptr),
				[](SwrContext* p)
			{
				swr_free(&p);
			}
			};
			swr_init(swr_.get());
		}

		is_running_ = true;
		thread_ = boost::thread([this] {run(); });
	}

	~matrox_producer()
	{
		is_running_ = false;
		thread_.join();
	}

	//收到Meta之后开始收视音频 
	void run()
	{
		while (is_running_)
		{			
			//输入的逻辑需要参数
			auto video_frame = ffmpeg::create_frame();
			FrameforProducer mframe;
			if (need_.type == type_mid::SDI_TYPE)
			{
				if (!pjsdicap_->get_frame(mframe))
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
					continue;
				}
			}
			else if (need_.type == type_mid::IP_TYPE)
			{
				if (!pj2022cap_->get_frame(mframe))
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
					continue;
				}
			}
			
			video_frame->data[0] = reinterpret_cast<uint8_t*>((uint8_t*)mframe.pvideo.get());
			video_frame->linesize[0] = mframe.width*2;				
			video_frame->format = AV_PIX_FMT_YUYV422;
			video_frame->width = mframe.width;
			video_frame->height = mframe.height;
			video_frame->interlaced_frame = mframe.interlaced_frame==1 ? true:false;
			video_frame->top_field_first = mframe.top_field_first==1?true:false;
			video_frame->key_frame = 1;
			
			muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));
			
			//audio
			std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;
			uint32_t *buffer_ = (uint32_t *)malloc(mframe.usample * channel_layout_.num_channels * sizeof(int32_t));
			uint8_t * p = mframe.paudio.get();
			const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)& p);
			uint8_t *out[] = { reinterpret_cast<uint8_t*>(buffer_) };
			
			
			const auto channel_samples = swr_convert(
				swr_.get(),
				out,
				1920 * channel_layout_.num_channels * sizeof(int32_t),
				in,
				mframe.usample);
			//	
			auto audio_data = reinterpret_cast<int32_t*>((int32_t*)buffer_);
			audio_buffer = std::make_shared<core::mutable_audio_buffer>(
				audio_data,
				audio_data + channel_samples * channel_layout_.num_channels);
			free(buffer_);

			muxer_.push({ audio_buffer });

			for (auto frame = muxer_.poll(); frame != core::draw_frame::empty(); frame = muxer_.poll())
			{
				if (!frame_buffer_.try_push(frame))
				{
					auto dummy = core::draw_frame::empty();
					frame_buffer_.try_pop(dummy);

					frame_buffer_.try_push(frame);

					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				}
			}
		}
	}
	
	core::constraints& pixel_constraints()
	{
		return constraints_;
	}

	core::draw_frame get_frame()
	{

		core::draw_frame frame = last_frame_;

		if (!frame_buffer_.try_pop(frame))
			graph_->set_tag(diagnostics::tag_severity::WARNING, "late-frame");
		else
			last_frame_ = frame;

		graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));

		return frame;
	}

	std::wstring print() const
	{
		std::wstring str;
		if (need_.sdi!=-1)
		{
			str = boost::lexical_cast<std::wstring>(need_.sdi);
		}
		if (!need_.addr.empty())
		{
			str += L"|";
			str += need_.addr;
			str += L":";
			str	+= boost::lexical_cast<std::wstring>(need_.port);
		}
		return L" [" + str + L"|" + in_format_desc_.name + L"]";
	}

	boost::rational<int> get_out_framerate() const
	{
		return muxer_.out_framerate();
	}
	core::monitor::subject& monitor_output()
	{
		return monitor_subject_;
	}
};

class matrox_producer_proxy : public core::frame_producer_base
{
	std::unique_ptr<matrox_producer>	producer_;
	executor							executor_;
public:
	explicit matrox_producer_proxy( 
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& in_format_desc,
		const core::audio_channel_layout& channel_layout,
		const std::wstring& filter_str,
		producer_need need)
		: executor_(L"matrox_producer[" + boost::lexical_cast<std::wstring>(need.card)+ L"-" + boost::lexical_cast<std::wstring>(need.sdi) + L"]")
	{
		auto ctx = core::diagnostics::call_context::for_thread();
		executor_.invoke([=]
		{
			core::diagnostics::call_context::for_thread() = ctx;
			producer_.reset(new matrox_producer(frame_factory, in_format_desc, channel_layout, filter_str, need));
		});
	}

	~matrox_producer_proxy()
	{
		executor_.invoke([=]
		{
			producer_.reset();
		});
	}

	core::monitor::subject& monitor_output()
	{
		return producer_->monitor_output();
	}

	// frame_producer

	core::draw_frame receive_impl() override
	{
		return producer_->get_frame();
	}

	int producer_type()
	{
		return FFMPEG_Resource::FFMPEG_FILE;
	}

	core::constraints& pixel_constraints() override
	{
		return producer_->pixel_constraints();
	}

	std::wstring print() const override
	{
		return producer_->print();
	}

	std::wstring name() const override
	{
		return L"matrox";
	}

	boost::property_tree::wptree info() const override
	{
		boost::property_tree::wptree info;
		info.add(L"type", L"matrox");
		return info;
	}

	boost::rational<int> get_out_framerate() const
	{
		return producer_->get_out_framerate();
	}
};

void describe_producer(core::help_sink& sink, const core::help_repository& repo)
{
	sink.short_description(L"Allows video sources to be input from Matrox cards.");
	sink.syntax(L"matrox card x sdi y 2022 udp://238.0.0.1:10004 ratio 16:9 format 1080i5000 channel_layout stereo");
	sink.para()->text(L"Allows video sources to be input from Matrox cards. Parameters:");
	sink.definitions()
		->item(L"source", L"The matrox source to stream the input from.");
	sink.para()->text(L"Examples:");
	sink.example(L">> play 1-10 matrox card 0 sdi 0 2022 udp://238.0.0.1:10004 ratio 16:9 format 1080i5000", L"Play using matrox card 0 sdi 0 expecting the video signal to have the same video format as the channel.");
}

spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params)
{	
	if(params.empty()|| !boost::iequals(boost::to_upper_copy(params.at(0)), L"MATROX"))
	{
		return core::frame_producer::empty();
	}

	producer_need need;
	if (contains_param(L"card", params))
		need.card = boost::lexical_cast<int>(get_param(L"card", params));
	if (contains_param(L"sdi", params))
		need.sdi = boost::lexical_cast<int>(get_param(L"sdi", params));
	if (contains_param(L"ratio", params))
		need.ratio = get_param(L"ratio", params);
    
	//2022
	std::wstring url2022 = get_param(L"2022", params);
	if (!url2022.empty())
	{
		need.type = type_mid::IP_TYPE;
		auto urlstr = boost::to_upper_copy(url2022);
		std::wstring addr = L"";
		std::wstring port = L"";

		int pos1 = urlstr.find(L"UDP://", 0);
		int pos2 = urlstr.find(L":", 6);

		if (pos1 == std::wstring::npos || pos2 == std::wstring::npos)
			return core::frame_producer::empty();

		addr = urlstr.substr(pos1 + 6, pos2 - 6 - pos1);
		port = urlstr.substr(pos2 + 1, pos2 - 1);
		if (addr.empty() || port.empty())
			return core::frame_producer::empty();
		need.port = boost::lexical_cast<int>(port);
		need.addr = addr;
	}
	else
	{
		//参数 板卡索引 一个卡默认0
		need.type = type_mid::SDI_TYPE;
	}

	auto filter_str = get_param(L"FILTER", params);
	auto length = get_param(L"LENGTH", params, (std::numeric_limits<uint32_t>::max)());
	auto in_format_desc = core::video_format_desc(get_param(L"FORMAT", params, L"INVALID"));//指定输入信号格式
	if (in_format_desc.format == core::video_format::invalid)
		in_format_desc = dependencies.format_desc;

	auto channel_layout_spec = get_param(L"CHANNEL_LAYOUT", params);
	auto channel_layout = *core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");
	if (!channel_layout_spec.empty())
	{
		auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout_spec);
		if (!found_layout)
			CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout not found."));
		channel_layout = *found_layout;
	}

	boost::ireplace_all(filter_str, L"DEINTERLACE_BOB", L"YADIF=1:-1");
	boost::ireplace_all(filter_str, L"DEINTERLACE_LQ", L"SEPARATEFIELDS");
	boost::ireplace_all(filter_str, L"DEINTERLACE", L"YADIF=0:-1");

	auto producer = spl::make_shared<matrox_producer_proxy>(
		dependencies.frame_factory,
		in_format_desc,
		channel_layout,
		filter_str,
		need);

	auto get_source_framerate = [=] { return producer->get_out_framerate(); };
	auto target_framerate = dependencies.format_desc.framerate;

	return core::create_destroy_proxy(core::create_framerate_producer(
		producer,
		get_source_framerate,
		target_framerate,
		dependencies.format_desc.field_mode,
		dependencies.format_desc.audio_cadence));
}
}}
