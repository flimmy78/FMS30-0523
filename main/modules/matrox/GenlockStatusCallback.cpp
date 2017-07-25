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

#include "MatroxDSXsdk.h"
#include "GenlockStatusCallback.h"

namespace caspar {
	namespace matrox {
		// ---------------------------------------------------------------------------------------------------------------------
		CGenlockStatusCallback::CGenlockStatusCallback(IMvSystemClock * in_pIClock,
			const SMvResolutionInfo & in_krsResolution,
			bool in_bVerbose)
			: CMvUnknown(L"CGenlockStatusCallback", NULL)
			, m_pJClock(in_pIClock)
			, m_sResolution(in_krsResolution)
			, m_bVerbose(in_bVerbose)
		{
		}


		// ---------------------------------------------------------------------------------------------------------------------
		CGenlockStatusCallback::~CGenlockStatusCallback(void)
		{
		}


		// ---------------------------------------------------------------------------------------------------------------------
		HRESULT CGenlockStatusCallback::Notify(SMvGenlockInputStatus& in_rsGenlockStatus)
		{
			if (m_bVerbose)
			{
				printf("At sample time %" PRIu64 ", genlock status is now \"%s\"\n",
					MvGetSampleForNanoTime(m_pJClock->GetTime(), m_sResolution),
					MV_GENLOCK_STATE_ENUM_TO_STRING(in_rsGenlockStatus.eGenlockState));
			}

			if (in_rsGenlockStatus.eGenlockState == keGenlockStateFreeRunning)
			{
				m_oGenlockEvent.Set();
			}

			return MV_NOERROR;
		}


		// ---------------------------------------------------------------------------------------------------------------------
		bool CGenlockStatusCallback::Wait(unsigned long in_ulTimeOut /*In milliseconds*/)
		{
			return m_oGenlockEvent.Wait(in_ulTimeOut);
		}

	}
}
