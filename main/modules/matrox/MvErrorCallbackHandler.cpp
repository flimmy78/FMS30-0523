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

#include "MvErrorCallbackHandler.h"

namespace caspar {
	namespace matrox {
		CMvErrorCallbackHandler::CMvErrorCallbackHandler(const SMvResolutionInfo & in_rsResolution)
			: CMvUnknown(L"CMvErrorCallbackHandler", NULL)
			, m_sResolution(in_rsResolution)
		{
		}


		CMvErrorCallbackHandler::~CMvErrorCallbackHandler(void)
		{
		}

		// ----------------------------------------------------------------------------
		HRESULT CMvErrorCallbackHandler::NotifyAsyncError(const SMvAsyncErrorInformation& in_krsAsynErrorInfo)
		{
			// Get error code only from the error string.
			const wchar_t * wszErrorString = mvErrorToString(in_krsAsynErrorInfo.hError);
			const wchar_t * wszColon = wcschr(wszErrorString, L':');

			wchar_t wszErrorCode[128];
			wcsncpy_s(wszErrorCode, _countof(wszErrorCode), wszErrorString, wszColon - wszErrorString);

			char szName[32];

			// Get name of the element that failed
			switch (in_krsAsynErrorInfo.eType)
			{
			case keMvAsyncErrorTypeNode:
				in_krsAsynErrorInfo.uInfo.sNode.pINode->GetName(szName, _countof(szName));
				break;
			case keMvAsyncErrorTypeTransferStream:
				in_krsAsynErrorInfo.uInfo.sTransfer.pITransferStream->GetName(szName, _countof(szName));
				break;
			default:
				printf("Unknown type.\n"); // This should not happen
			}

			// Display error message
			if (in_krsAsynErrorInfo.ui64Duration == 0)
			{
				printf("Error from <%s> at sample time %" PRIu64 ": %ls\n",
					szName,
					MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Timestamp, m_sResolution),
					wszErrorCode);
			}
			else
			{
				printf("Error from <%s> at sample time %" PRIu64 " during %" PRIu64 " video units: %ls\n",
					szName,
					MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Timestamp, m_sResolution),
					MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Duration, m_sResolution),
					wszErrorCode);
			}

			return MV_NOERROR;
		}
	}
}