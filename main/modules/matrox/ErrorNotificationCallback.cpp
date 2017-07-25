#include "ErrorNotificationCallback.h"
#include <common/log.h>
namespace caspar {
	namespace matrox {
		// ---------------------------------------------------------------------------------------------------------------------
		CErrorNotificationCallback::CErrorNotificationCallback()
			: CMvUnknown(L"CErrorNotificationCallback", NULL)
		{
		}

		// ---------------------------------------------------------------------------------------------------------------------
		CErrorNotificationCallback::CErrorNotificationCallback(SMvResolutionInfo in_sResolution)
			: CMvUnknown(L"CErrorNotificationCallback", NULL)
		{
			m_sResolution = in_sResolution;
		}


		// ---------------------------------------------------------------------------------------------------------------------
		CErrorNotificationCallback::~CErrorNotificationCallback(void)
		{
		}


		// ---------------------------------------------------------------------------------------------------------------------
		HRESULT CErrorNotificationCallback::Notify(HRESULT in_hrError)
		{
			CASPAR_LOG(error) << L"CErrorNotificationCallback " << mvErrorToString(in_hrError);

			return MV_NOERROR;
		}

		// ---------------------------------------------------------------------------------------------------------------------
		void CErrorNotificationCallback::ReceiveSurface(IMvSurface*  in_pISurface)                 //Asynch error on video surface 
		{
			CMvHResult  hr = MV_NOERROR;
			CMvHResult  hr_error;

			hr = in_pISurface->GetLastError(&hr_error);

			if (hr_error != MV_NOERROR)
			{
				CASPAR_LOG(error) << L"Video surface has asynch error: mvErrorToString(hr_error)";
			}
		}


		// ---------------------------------------------------------------------------------------------------------------------
		void CErrorNotificationCallback::ReceiveAudioSamples(IMvAudioSamples* in_pIAudioSamples)  //Asynch error on audio samples
		{

			CMvHResult  hr = MV_NOERROR;
			CMvHResult  hr_error;

			hr = in_pIAudioSamples->GetLastError(&hr_error);

			if (hr_error != MV_NOERROR)
			{
				CASPAR_LOG(error) << L"Audio samples has asynch error:  mvErrorToString(hr_error)";
			}
		}

		// ---------------------------------------------------------------------------------------------------------------------
		HRESULT CErrorNotificationCallback::NotifyAsyncError(const SMvAsyncErrorInformation& in_krsAsynErrorInfo)
		{
			// Get error code only from the error string.
			const wchar_t * wszErrorString = mvErrorToString(in_krsAsynErrorInfo.hError);
			const wchar_t * wszColon = wcschr(wszErrorString, L':');

			wchar_t wszErrorCode[128];
			wcsncpy_s(wszErrorCode, _countof(wszErrorCode), wszErrorString, wszColon - wszErrorString);

			// Get name of the element that failed
			char szName[32];
			switch (in_krsAsynErrorInfo.eType)
			{
			case keMvAsyncErrorTypeNode:
				in_krsAsynErrorInfo.uInfo.sNode.pINode->GetName(szName, _countof(szName));
				break;
			case keMvAsyncErrorTypeTransferStream:
				in_krsAsynErrorInfo.uInfo.sTransfer.pITransferStream->GetName(szName, _countof(szName));
				break;
			default:
				CASPAR_LOG(warning)<<L"in_krsAsynErrorInfo.eType Unknown type."; // This should not happen
			}

			// Display error message
			if (in_krsAsynErrorInfo.ui64Duration == 0)
			{
				CASPAR_LOG(error) << L"Error from <" <<szName << L"> at sample time" << 
					MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Timestamp, m_sResolution) <<wszErrorCode;
			}
			else
			{
				CASPAR_LOG(error) << L"Error from <" << szName << L"> at sample time " << MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Timestamp, m_sResolution)
					<< L" during " << MvGetSampleForNanoTime(in_krsAsynErrorInfo.ui64Duration, m_sResolution)<< L" video units: " << wszErrorCode;
			}

			return MV_NOERROR;
		}
	}
}