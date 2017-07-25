/*

(c) Copyright Matrox Electronic Systems Ltd., 2013-2015. All rights reserved. 

This code and information is provided "as is" without warranty of any kind,
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

#pragma once
namespace caspar {
	namespace matrox {
		class CGenlockStatusCallback : public CMvUnknown, public IMvGenlockNotificationCallback
		{
		public:
			CGenlockStatusCallback(IMvSystemClock * in_pIClock,
				const SMvResolutionInfo & in_krsResolution,
				bool in_bVerbose);
			virtual ~CGenlockStatusCallback(void);

			// Interface IMvGenlockNotificationCallback
			virtual HRESULT __stdcall Notify(SMvGenlockInputStatus& in_rsGenlockStatus);

			// CMvUnknow implementation
			MVDECLARE_IUNKNOWN;

			// Public methods
			bool Wait(unsigned long in_ulTimeOut /*In milliseconds*/);

		protected:
			CMvEvent m_oGenlockEvent;
			TMvSmartPtr<IMvSystemClock> m_pJClock;
			SMvResolutionInfo m_sResolution;
			bool m_bVerbose;
		};
	}
}
