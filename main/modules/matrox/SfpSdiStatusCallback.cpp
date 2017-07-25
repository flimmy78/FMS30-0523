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

#include "SfpSdiStatusCallback.h"
namespace caspar {
	namespace matrox {
		// ---------------------------------------------------------------------------------------------------------------------
		CSfpSdiStatusCallback::CSfpSdiStatusCallback()
			: CMvUnknown(L"CSfpSdiStatusCallback", NULL)
			, m_oWaitEvent(false) // Auto reset event
		{
		}


		// ---------------------------------------------------------------------------------------------------------------------
		CSfpSdiStatusCallback::~CSfpSdiStatusCallback(void)
		{
		}


		// ---------------------------------------------------------------------------------------------------------------------
		void CSfpSdiStatusCallback::WaitForEvent()
		{
			m_oWaitEvent.Wait();
		}


		// ---------------------------------------------------------------------------------------------------------------------
		HRESULT CSfpSdiStatusCallback::Notify(IMvSfpSdi * in_pISfpSdi, const SMvSfpSdiStatus & in_krsStatus)
		{
			printf("         %s) ", MV_SFP_LABEL_ENUM_TO_STRING(in_pISfpSdi->GetLabel()));

			if (in_krsStatus.bModulePresent == false)
			{
				printf("Module not present\n");
			}
			else
			{
				printf("Vendor=%s Part=%s S/N=%s",
					in_krsStatus.sSerialId.szVendorName,
					in_krsStatus.sSerialId.szVendorPartNumber,
					in_krsStatus.sSerialId.szVendorSerialNumber);

				if (!in_krsStatus.bSupportedModule)
				{
					printf(" <<=== Unsupported module\n");
				}
				else if (!in_krsStatus.bCorrectModuleDirection)
				{
					printf(" <<=== Invalid direction");
				}

				printf("\n");
			}

			m_oWaitEvent.Set();

			return MV_NOERROR;
		}

	}
}