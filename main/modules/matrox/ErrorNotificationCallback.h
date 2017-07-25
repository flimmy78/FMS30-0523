#pragma once
#include <mvUnknown.h>
#include <MvFlexAPI.h>
#include <MatroxDSXsdk.h>
namespace caspar {
	namespace matrox {

		class CErrorNotificationCallback : public CMvUnknown,
			public IMvErrorNotificationCallback,
			public IMvSurfacePoolCallback,
			public IMvAudioSamplesPoolCallback,
			public IMvSystemTopologyErrorCallback
		{
		public:
			CErrorNotificationCallback(void);
			CErrorNotificationCallback(SMvResolutionInfo in_sResolution);

			virtual ~CErrorNotificationCallback(void);

			// Interface IMvGenlockNotificationCallback
			virtual HRESULT __stdcall Notify(HRESULT in_hrError);                                              //Asynch error on Matrox Card
			virtual void    __stdcall ReceiveSurface(IMvSurface*  in_pISurface);                               //Asynch error on video surface 
			virtual void    __stdcall ReceiveAudioSamples(IMvAudioSamples* in_pIAudioSamples);                 //Asynch error on audio samples
			virtual HRESULT __stdcall NotifyAsyncError(const SMvAsyncErrorInformation& in_krsAsynErrorInfo);   //Asynch error on system topology


																											   // CMvUnknow implementation
			MVDECLARE_IUNKNOWN;

		protected:

			SMvResolutionInfo m_sResolution;
		};
	}
}


