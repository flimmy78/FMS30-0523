/*

(c) Copyright Matrox Electronic Systems Ltd., 2013-2016. All rights reserved.

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
#include "MatroxDSXsdk.h"
namespace caspar {
	namespace matrox {
		class CSfpSdiStatusCallback : public CMvUnknown, public IMvSfpSdiNotificationCallback
		{
		public:
			CSfpSdiStatusCallback();
			virtual ~CSfpSdiStatusCallback(void);

			// Interface IMvSfpSdiNotificationCallback
			virtual HRESULT __stdcall Notify(IMvSfpSdi * in_pISfpSdi, const SMvSfpSdiStatus & in_krsStatus);

			// CMvUnknow implementation
			MVDECLARE_IUNKNOWN;

			// Public methods
			void WaitForEvent();

		private:
			CMvEvent m_oWaitEvent;
		};
	}
}

