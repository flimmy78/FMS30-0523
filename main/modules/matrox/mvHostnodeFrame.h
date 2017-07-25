//
// Created by zibj 2016/10/25.
//

#pragma once
#include <MatroxDSXsdk.h>
namespace caspar {
	namespace matrox {
		class CMvHostNodeFrameCounter : public CMvUnknown, public IMvNodeNotificationCallback
		{
		public:
			CMvHostNodeFrameCounter(bool in_bVerbose, uint64_t in_ui64Count, bool in_bIsInterlaced);
			virtual ~CMvHostNodeFrameCounter();

			MVDECLARE_IUNKNOWN

				// IMvNodeNotificationCallback implementation
				virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters);

			// Public methods
			void    WaitCompleted();

		private:
			bool       m_bVerbose;
			uint64_t   m_ui64Count;
			bool       m_bIsInterlaced;
			CMvEvent   m_oEndEvent;
		};
	}
}