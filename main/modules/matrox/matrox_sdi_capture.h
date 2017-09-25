#pragma once

#include <core/video_format.h>

#include <common/forward.h>
#include <common/memory.h>
#include <common/cache_aligned_vector.h>
#include <common/array.h>

#include <core/frame/frame_visitor.h>
#include <core/monitor/monitor.h>
#include <tbb/concurrent_queue.h>
#include <vector>
#include <cstdint>
#include "common.h"

#include "cardinfo.h"
namespace caspar {
	namespace matrox {
		
		class matrox_sdi_capture
		{
		public:
			matrox_sdi_capture(core::video_format format,int NeedAChannel,	producer_need need);
			~matrox_sdi_capture();
			bool get_frame(FrameforProducer & frame);
			int _GetChannels();
		private:
			struct impl;
			TMvSmartPtr<impl> impl_;
		};

		struct matrox_sdi_capture::impl :  public IMvNodeNotificationCallback,public CMvUnknown
		{
			//COM的对象接口参数，记为系统对象
			TMvSmartPtr<IMvSystemConfiguration>				m_IMvSystemConfiguration_ ;
			//板卡数量记录
			std::vector<SdiCardInfo>						m_CardConfigs;
			producer_need									m_need;
			unsigned int									m_preset_channel_;
			//锁相
			TMvSmartPtr<IMvSystemClock>						m_pJClock ;
			//拓扑对象
			TMvSmartPtr<IMvSystemTopology>					m_pJSystemTopology;

			//node
			TMvSmartPtr<IMvNode>							m_pJIOCardNodeForCapture ;
			TMvSmartPtr<IMvHostNode>						m_pJHostNode;
			TMvSmartPtr<IMvTransferStream>					m_pJTransferStream;
			TMvSmartPtr<IMvInputStream>						m_pJSdiVideoInputStream;

			uint32_t										m_ui32WriteToReadDelayInFrame ;
			uint32_t										m_ui32DepthInFrame;

			SMvResolutionInfo								m_in_Resolution;
			core::video_format								m_format_;

			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	m_oOutputBuffersQueue;
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	BuffersQueue;
			tbb::cache_aligned_allocator<uint8_t>			cc_memory_pool;
			uint32_t										m_ui32AudioConnectorCount;
			IMvAudioInputConnector *						apIAudioInputConnectors[16];

			bool											m_bInput4K;

		public:
			impl(core::video_format format, int NeedAChannel, producer_need need);
			virtual ~impl();
			CMvHResult Stop();
			MVDECLARE_IUNKNOWN;

			inline bool _IsFieldBased(SMvResolutionInfo &in_sResInfo)
			{
				return in_sResInfo.eScanMode == keMvScanModeFirstFieldTop || in_sResInfo.eScanMode == keMvScanModeSecondFieldTop;
			}

			bool get_frame(FrameforProducer& frame);
			int  _GetChannels();
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters);

		private:
			CMvHResult _SysConfiguration();
			void _GetResolution(SMvResolutionInfo *in_pResInfo);
			CMvHResult _EnumerateCards();
			CMvHResult _FillConnectors(SdiCardInfo & io_rsCardInfo);
			CMvHResult _ValidateAndDisplayCardTemperature(SdiCardInfo & in_krsCardInfo);
			CMvHResult _AVCheck();
			
			CMvHResult _BuildTopology();
			CMvHResult _CleanTopology();
			CMvHResult _RetrieveGenlockClock();
			CMvHResult _SetupGenlock();
			CMvHResult _BuildMainTopology();

			void _InitNodeSettings(SMvNodeSettings      &out_sNodeSettings,
				SMvNodeSettingsVideo &out_sNodeSettingsVideo,
				SMvNodeSettingsAudio &out_sNodeSettingsAudio);
		
			void _InitInputStreamSettings(SMvInputStreamSettings& sInStreamSettings);

			HRESULT _GetEmbeddedAudioInputConnectors(IMvSdiVideoInputConnector * in_pISdivideoInputConnector,
				IMvAudioInputConnector   ** out_apIAudioInputConnectors,
				uint32_t                  & io_rui32Count);

			bool get_interlace_frame(FrameforProducer& frame);
			bool get_progressive_frame(FrameforProducer& frame);
		};

	}
}