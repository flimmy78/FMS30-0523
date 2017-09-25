/*======================================================\
|   Welcome using Ultralink IO Cards. The application |
|   programming interface starts from here              |
\*=====================================================*/

#ifndef _Omn_API_H
#define _Omn_API_H

#include <Omni_TypeDef.h>
#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* �������� Omn_Initialize
* ���ܣ� SDK��ʼ������
* �����������
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� Ӧ���ڵ���SDK������������ǰ������øú�����������������������
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Initialize();

/******************************************
* �������� Omn_Release
* ���ܣ� SDK�ͷź���
* �����������
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� ��ǰ���̲�ʹ��SDK��ʱ�����ô˺����ͷ�SDKռ��ϵͳ��Դ
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Release();
#ifdef __cplusplus
}
#endif 

#include "Omni_Api_Config.h"
#include "Omni_Api_Notify.h"
#include "Omni_Api_Query.h"
#include "Omni_Api_StateControlAndBufIO.h"
#include "Omni_Api_Compatible.h"

#endif //_Omn_API_H

