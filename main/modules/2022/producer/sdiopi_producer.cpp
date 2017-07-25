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

#include "sdiopi_producer.h"
#include "../sdiopi_impl.h"
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
namespace caspar { namespace sdiopi_20226 {
	struct producer_need {

		std::wstring   host = L"127.0.0.1";//������Ϣ
		std::wstring   addr = L"235.0.0.1";//��ַ
		unsigned short port = 10001;
	};

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

class sdi2022_producer : boost::noncopyable
{
	
	core::monitor::subject							monitor_subject_;
	spl::shared_ptr<diagnostics::graph>				graph_;
	sdiopi_interface_20226							*pttl_ = nullptr;
	const std::wstring								filter_;

	core::video_format_desc							format_desc_;
	std::vector<int>								audio_cadence_ = format_desc_.audio_cadence;
	
	spl::shared_ptr<core::frame_factory>			frame_factory_;
	core::audio_channel_layout						channel_layout_;
	ffmpeg::frame_muxer								muxer_{
		format_desc_.framerate,
		{ create_input_pad(format_desc_, channel_layout_.num_channels) },
		frame_factory_,
		format_desc_,
		channel_layout_,
		filter_,
		ffmpeg::filter::is_deinterlacing(filter_)
	};
	std::shared_ptr<SwrContext>				swr_;
	core::constraints								constraints_{ format_desc_.width, format_desc_.height };

	tbb::concurrent_bounded_queue<core::draw_frame>	frame_buffer_;
	core::draw_frame								last_frame_ = core::draw_frame::empty();

	std::exception_ptr								exception_;

	tbb::atomic<bool>									is_running_;
	boost::thread										thread_;
	int 												buffer_[1920 * 20];
	producer_need										needs_;
	caspar::timer										tick_timer;
public:
	
	sdi2022_producer(
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& format_desc,
		const core::audio_channel_layout& channel_layout,
		const std::wstring& filter,
		producer_need needs)
		:filter_(filter)
		, format_desc_(format_desc)
		, frame_factory_(frame_factory)
		, channel_layout_(channel_layout)
		, needs_(needs)
	{		
		frame_buffer_.set_capacity(4);
		SdiOpineed		opineed_;
		opineed_.host = u8(needs.host);
		opineed_.addr = u8(needs.addr);
		opineed_.port = needs.port;
		opineed_.channel = channel_layout_.num_channels;
		opineed_.format = format_desc.format;
		opineed_.width = format_desc.width;
		opineed_.higth = format_desc.height;
		
		
		pttl_ = new sdiopi_interface_20226 (opineed_);
		graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
		graph_->set_color("late-frame", diagnostics::color(0.6f, 0.3f, 0.3f));
		graph_->set_color("frame-time", diagnostics::color(1.0f, 0.0f, 0.0f));
		graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
		graph_->set_color("output-buffer", diagnostics::color(0.0f, 1.0f, 0.0f));
		graph_->set_text(print());
		diagnostics::register_graph(graph_);
		is_running_ = true;
		thread_ = boost::thread([this] {run(); });
	}

	~sdi2022_producer()
	{
		release();
	}
	void release()
	{
		is_running_ = false;
		thread_.join();
		if (pttl_)
		{
			delete pttl_;
		}
		CASPAR_LOG(info) << L" sdi2022 producer released.";
	}
	//�յ�Meta֮��ʼ������Ƶ 
	void run()
	{
		caspar::timer			frame_timer;
		
		while (is_running_)
		{	
			//
			
			auto video_frame = ffmpeg::create_frame();
			auto sdiframe =std::make_shared<Sdi2022Frame>();
			if (!pttl_->get_frame(sdiframe))
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				continue;
			}
			if (sdiframe == nullptr)
			{
				//��֡ ����
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				continue;
			}
			
			video_frame->data[0] = reinterpret_cast<uint8_t*>((uint8_t*)sdiframe->pvideo.get());

			video_frame->linesize[0] = format_desc_.width * 2;

			video_frame->format = AV_PIX_FMT_UYVY422;

			video_frame->width = format_desc_.width;
			video_frame->height = format_desc_.height;
			video_frame->interlaced_frame = true;
			video_frame->top_field_first = true;
			video_frame->key_frame = 1;

			muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));

			//audio

			std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;
			auto audio_data = reinterpret_cast<int32_t*>((int32_t*)sdiframe->paudio.get());
			audio_buffer = std::make_shared<core::mutable_audio_buffer>(
				audio_data,
				audio_data + 1920 * channel_layout_.num_channels);

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
			graph_->set_value("frame-time", frame_timer.elapsed()*format_desc_.fps*0.5);
			graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));
			frame_timer.restart();
		}
		
	}
	core::constraints& pixel_constraints()
	{
		return constraints_;
	}

	core::draw_frame get_frame()
	{
		graph_->set_value("tick-time", tick_timer.elapsed() * format_desc_.fps * 0.5);
		tick_timer.restart();
		core::draw_frame frame = last_frame_;

		if (!frame_buffer_.try_pop(frame))
			graph_->set_tag(diagnostics::tag_severity::WARNING, "late-frame");
		else
			last_frame_ = frame;

		//////------------------------------------------
		//thread_ = boost::thread([this] {
		//caspar::timer			frame_timer;
		//auto video_frame = ffmpeg::create_frame();
		//auto sdiframe = std::make_shared<Sdi2022Frame>();
		//if (pttl_->get_frame(sdiframe) && sdiframe != nullptr)
		//{
		//	video_frame->data[0] = reinterpret_cast<uint8_t*>((uint8_t*)sdiframe->pvideo.get());

		//	video_frame->linesize[0] = format_desc_.width * 2;

		//	video_frame->format = AV_PIX_FMT_UYVY422;

		//	video_frame->width = format_desc_.width;
		//	video_frame->height = format_desc_.height;
		//	video_frame->interlaced_frame = true;
		//	video_frame->top_field_first = true;
		//	video_frame->key_frame = 1;

		//	muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));

		//	//audio

		//	std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;
		//	auto audio_data = reinterpret_cast<int32_t*>((int32_t*)sdiframe->paudio.get());
		//	audio_buffer = std::make_shared<core::mutable_audio_buffer>(
		//		audio_data,
		//		audio_data + 1920 * channel_layout_.num_channels);

		//	muxer_.push({ audio_buffer });
		//	for (auto frame = muxer_.poll(); frame != core::draw_frame::empty(); frame = muxer_.poll())
		//	{
		//		if (!frame_buffer_.try_push(frame))
		//		{
		//			auto dummy = core::draw_frame::empty();
		//			frame_buffer_.try_pop(dummy);

		//			frame_buffer_.try_push(frame);
		//			graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");

		//		}
		//	}
		//	graph_->set_value("frame-time", frame_timer.elapsed()*format_desc_.fps*0.5);
		//	graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));
		//	frame_timer.restart();
		//}
		//});

		/*if (!frame_buffer_.try_pop(frame))
			graph_->set_tag(diagnostics::tag_severity::WARNING, "late-frame");
		else
			last_frame_ = frame;*/
		
		//----------------------------------------------

		graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));

		return frame;
	}

	std::wstring print() const
	{
		return L"2022 producer [" +needs_.addr+ L":"+ boost::lexical_cast<std::wstring>(needs_.port) + L"|" + format_desc_.name + L"]";
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

class sdi2022_producer_proxy : public core::frame_producer_base
{
	std::unique_ptr<sdi2022_producer>	producer_;
	const uint32_t						length_;
	executor							executor_;
	producer_need						needs_;

public:
	explicit sdi2022_producer_proxy(
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& format_desc,
		const core::audio_channel_layout& channel_layout,
		const std::wstring& filter_str,
		uint32_t length,
		producer_need needs)
		:executor_(L"sdi2022_producer[" + needs.addr + needs.host + L"]")
		, length_(length)
		,needs_(needs)
	{
		auto ctx = core::diagnostics::call_context::for_thread();
		executor_.invoke([=]
		{
			core::diagnostics::call_context::for_thread() = ctx;
			producer_.reset(new sdi2022_producer(frame_factory, format_desc, channel_layout, filter_str, needs));
		});
	}

	~sdi2022_producer_proxy()
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
		return FFMPEG_Resource::FFMPEG_STREAM;
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
		return L"2022-6";
	}

	boost::property_tree::wptree info() const override
	{
		boost::property_tree::wptree info;
		info.add(L"type", L"2022-6");
		return info;
	}

	boost::rational<int> get_out_framerate() const
	{
		return producer_->get_out_framerate();
	}
};
//��Ҫ�ĵ�����
void describe_producer(core::help_sink& sink, const core::help_repository& repo)
{
	sink.short_description(L"Allows video sources to be input from SDI2022-6");
	sink.syntax(L"SDI2022-6 udp://host:port?localaddr=localhost");
	sink.para()->text(L"Allows video sources to be input from SDI2022-6. Parameters:");
	sink.definitions()
		->item(L"udp://host:port?localaddr=localhost", L"multicast udp  host:port  localaddr is local host");
	sink.para()->text(L"Examples:");
	sink.example(L">> PLAY 1-10 2022-6 udp://235.1.1.1:10000?localaddr=192.168.1.100", L"yv yu  yvu422 formats");
}

spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params)
{
	if (params.empty() || !boost::iequals(boost::to_upper_copy(params.at(0)), L"2022-6"))
		return core::frame_producer::empty();

	if (params.empty() || !boost::iequals(params.at(0), "2022-6"))
		return core::frame_producer::empty();

	producer_need needs;
	if (params.size()<2)
	{
		return core::frame_producer::empty();
	}
	auto urlstr = boost::to_upper_copy(params.at(1));
	std::wstring host = L"";
	std::wstring addr = L"";
	std::wstring port = L"";

	int pos1 = urlstr.find(L"?LOCALADDR=", 0);
	int pos2 = urlstr.find(L"UDP://", 0);
	int pos3 = urlstr.find(L":", 6);

	if (pos1 == std::wstring::npos|| pos2 == std::wstring::npos|| pos3 == std::wstring::npos)
		return core::frame_producer::empty();
	
	host = urlstr.substr(pos1 + 11, urlstr.size() - pos1 - 11);
	addr = urlstr.substr(pos2 + 6, pos3 -6-pos2);
	port = urlstr.substr(pos3 + 1, pos1 - pos3-1);
	if (host.empty()|| addr.empty()|| port.empty())
		return core::frame_producer::empty();


	needs.port = boost::lexical_cast<int>(port);
	needs.addr = addr;
	needs.host = host;


	auto filter_str = get_param(L"FILTER", params);
	auto length = get_param(L"LENGTH", params, std::numeric_limits<uint32_t>::max());
	
	auto in_format_desc = core::video_format_desc(get_param(L"FORMAT", params, L"INVALID"));

	if (in_format_desc.format == core::video_format::invalid)
		in_format_desc = dependencies.format_desc;

		auto channel_layout_spec = get_param(L"CHANNEL_LAYOUT", params);
		auto channel_layout = *core::audio_channel_layout_repository::get_default()->get_layout(L"8ch");

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

	auto producer = spl::make_shared<sdi2022_producer_proxy>(
		dependencies.frame_factory,
		in_format_desc,
		channel_layout,
		filter_str,
		length,
		needs);

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
