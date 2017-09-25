#pragma once
#include <core/video_format.h>

#include <common/forward.h>
#include <common/memory.h>
#include <common/cache_aligned_vector.h>
#include <common/array.h>

#include <core/frame/frame_visitor.h>
#include <core/monitor/monitor.h>
#include "common.h"

#include <tbb/concurrent_queue.h>

#include "cardinfo.h"
namespace caspar {
	namespace matrox {
		class matrox_sdi_playback
		{
		public:
			matrox_sdi_playback(consumer_need need,core::video_format format, int channels, std::map<std::string, std::string>& ops);
			~matrox_sdi_playback();
			void send(void *pvideo,void * pvideo1,void * paudio, void * paudio1);
			bool _IsFieldBased();
		private:
			struct impl;
			TMvSmartPtr<impl> impl_;
		};

		struct matrox_sdi_playback::impl : public IMvNodeNotificationCallback, public CMvUnknown
		{
			//matrox  分辨率需要的参数
			SMvResolutionInfo								m_Out_Resolution;
			//COM的对象接口参数，记为系统对象
			TMvSmartPtr<IMvSystemConfiguration>				m_IMvSystemConfiguration_ ;
			//锁相
			TMvSmartPtr<IMvSystemClock>						m_pJClock;
			//拓扑对象
			TMvSmartPtr<IMvSystemTopology>					m_pJSystemTopology;

			//node
			TMvSmartPtr<IMvNode>							m_pJIOCardNodeForPlayback;
			TMvSmartPtr<IMvHostNode>						m_pJHostNode;
			TMvSmartPtr<IMvTransferStream>					m_pJTransferStream;
			TMvSmartPtr<IMvOutputStream>					m_pJSdiOutputStream;
			//node 参数
			uint32_t										m_ui32WriteToReadDelayInFrame;
			uint32_t										m_ui32DepthInFrame;

			//板卡参数集合接口
			std::vector<SdiCardInfo>						m_CardConfigs;

			//fms
			core::video_format								m_format_;


			//外来参数
			consumer_need									m_need_;
			std::map<std::string, std::string>				args_options_;

			uint32_t										m_preset_channel_;

			tbb::concurrent_bounded_queue<FrameForConsumer>	bufferqueue;

			bool											m_bOutput4K;
			bool                                            m_isplaying;
		    
		public:
			impl(consumer_need need, core::video_format format, uint32_t channels, std::map<std::string, std::string>& ops);
			virtual ~impl();
			CMvHResult Stop();
			void Play();

			MVDECLARE_IUNKNOWN

		public:				
			void send(void *pvideo, void * pvideo1, void * paudio, void * paudio1);
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters);
			inline bool _IsFieldBased()
			{
				return m_Out_Resolution.eScanMode == keMvScanModeFirstFieldTop || m_Out_Resolution.eScanMode == keMvScanModeSecondFieldTop;
			}

		private:
			CMvHResult _SysConfiguration();
			void _GetResolution(SMvResolutionInfo *out_pResInfo);
			CMvHResult _EnumerateCards();
			CMvHResult _FillConnectors(SdiCardInfo & io_rsCardInfo);
			CMvHResult _ValidateAndDisplayCardTemperature(SdiCardInfo & in_krsCardInfo);

			CMvHResult _BuildTopology();
			CMvHResult _CleanTopology();
			CMvHResult _RetrieveGenlockClock();
			CMvHResult _SetupGenlock();
			CMvHResult _BuildMainTopology();
			void _InitNodeSettings(SMvNodeSettings &out_sNodeSettings,
				SMvNodeSettingsVideo &out_sNodeSettingsVideo,
				SMvNodeSettingsAudio &out_sNodeSettingsAudio,
				SMvNodeSettingsVanc	 &out_sNodeSettingsVanc);

			void _InitOutputStreamSettings(SMvOutputStreamSettings &out_rsStreamSettings);
		};

	}
}