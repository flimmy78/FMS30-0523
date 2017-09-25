/*========================\
|   �忨��Ϣ��ѯ������    |
\*=======================*/

#ifndef __Omni_API_QUERY_H__
#define __Omni_API_QUERY_H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* �������� Omn_QueryGlobalInfo
* ���ܣ� �õ�SDK�汾�ţ���ǰ�忨���Լ����忨�Ļ�����Ϣ
* ���������
* ���������psRBGlobalInfo:��Ű忨ö����Ϣ��SDK�汾��ָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
*   
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryGlobalInfo(SOmnGlobalInfo *psRBGlobalInfo);

/******************************************
* �������� Omn_QuerySpecInfo()
* ���ܣ� ��ѯ�忨ָ����Ϣ
* ���������dwBoardNo:����
*           enumInfoType:ָ����Ϣ����ö��ֵ
*           pSpecInfo:��ѯ����ʱ��Ҫ��������Ϣ��
*           iIDX:ָ����Ϣϵ��ֵ���������忨����ֻ��һ������ֵΪ0   
* ���������ppName:ָ����Ϣ������
*           pValue:ָ����Ϣ����ö��ֵ
* ����ֵ�� Om_OK:������ ����������
* ˵���� enumInfoTypeֵ��pSpecInfo��pValue�����Ͷ�Ӧ����
|-----------------------------------------|-----------------------------|------------------------------|
|       enumSpecInfoType                  |       pSpecInfo����         |         pValue����           |
|-----------------------------------------|-----------------------------|------------------------------|
|   Omn_BOARDSPECINFO_BOARDNAME         |     Om_NULL               |   Om_NULL                  |
|   Omn_BOARDSPECINFO_GENLOCK           |     Om_NULL               |   Omn_GENLOCK_SOURCE*      |
|   Omn_BOARDSPECINFO_VIDEO_STANDARD    |     SOmnPortDesc* ,ISP/OSP|   Omn_VIDEO_STANDARD*      |
|   Omn_BOARDSPECINFO_VIDEO_SRC         |     SOmnPortDesc* ,ISP    |   Omn_VIDEO_SIGNAL_TYPE*   |
|   Omn_BOARDSPECINFO_AUDIO_SRC         |     SOmnPortDesc* ,ISP    |   Omn_AUDIO_SIGNAL_TYPE*   |
|   Omn_BOARDSPECINFO_COLOR_FMT_INPUT   |     SOmnPortDesc* ,RDP    |   Omn_COLOR_FORMAT*        |
|   Omn_BOARDSPECINFO_COLOR_FMT_OUTPUT  |     SOmnPortDesc* ,PDP    |   Omn_COLOR_FORMAT*        |
|   Omn_BOARDSPECINFO_VIDEO_OUT_TYPE    |     SOmnPortDesc* ,OSP    |   Omn_VIDEO_SIGNAL_TYPE    |
|-----------------------------------------|-----------------------------|------------------------------|
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QuerySpecInfo(Om_UINT32 dwBoardNo, Omn_BOARDSPECINFO_TYPE enumInfoType, Om_PVOID pSpecInfo, Om_INT32 iIDX
                                                , const Om_CHAR** ppName, Om_VOID* pValue);

/******************************************
* �������� Omn_QueryPortActivation
* ���ܣ� ��ѯ�˿��Ƿ����
* ���������dwBoardNo:����
*           enumPortType:SP�˿�����
*           dwPortNo:SP�˿ں�
*           psPortParam:����
* �����������
* ����ֵ�� Omn_SUCCESS �ö˿ڴ��ڼ���̬������
*          Omn_ERR_FAILED �ö˿ڴ��ڷǼ���̬��������
*          Omn_ERR_INVALID_PARAM �ö˿ڵ�������Բ�������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryPortActivation(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo);

/******************************************
* �������� Omn_QueryMonitorInfo
* ���ܣ� ��ȡ�忨�����Ϣ,��Ӳ��ʱ�ӡ��¶ȡ���ѹ��
* ���������dwBoardNo �忨��
* ���������psMonitorInfo �忨״̬��Ϣ
* ����ֵ�� Om_OK���ɹ���������ʧ��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryMonitorInfo(Om_UINT32 dwBoardNo, SOmnMonitorInfo *psMonitorInfo);

/******************************************
* �������� Omn_QueryLTCValue
* ���ܣ� ��ȡ����LTC��ֵ
* ���������dwBoardNo:����
*           dwInputNo:LTC����ͨ����
*           bWaitInterrupt:�ڻ�ȡLTCֵǰ�Ƿ��LTC�����ж�
* ���������pLTCVlaue:�˴���ȡ�õ�LTCֵ
* ����ֵ�� S_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryLTCValue(Om_UINT32 dwBoardNo, Om_UINT32 dwInputNo, Om_BOOL bWaitInterrupt, SOmn_LTC_VALUE *pLTCVlaue);

/******************************************
* �������� Omn_QueryLTCInputStatus
* ���ܣ� ��ѯ��ǰLTC�����źŵ���Ч״̬
* ���������dwBoardNo:����
*           dwInputNo:LTC����ͨ����
* ���������pIsValid:��ǰLTC�����ź��Ƿ���Ч��Om_FALSE:��Ч��Om_TRUE:��Ч
* ����ֵ�� S_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryLTCInputStatus(Om_UINT32 dwBoardNo, Om_UINT32 dwInputNo, Om_BOOL *pIsValid);

/******************************************
* �������� Omn_QueryKeyerProfile()
* ���ܣ� ��ѯKeyer����Դ������Ϣ
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
* ���������psProfile��Keyer��Դ������Ϣ
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryKeyerProfile(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyProfile *psProfile);

/******************************************
* �������� Omn_QueryGenlockStatus()
* ���ܣ� ��ѯGenlockʱ���жϼ���
* ���������dwBoardNo:����
*           dwTimeout���ȴ���ʱʱ�䣬���Ϊ0���򲻵��жϣ�ֱ�ӷ��ص�ǰGenlockʱ���жϼ���,��λ������
* ���������pInterruptCount��Genlockʱ���жϼ���
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryGenlockStatus(Om_UINT32 dwBoardNo, Om_UINT32 *pInterruptCount, Om_UINT32 dwTimeout);

/******************************************
* �������� Omn_QueryInputPhaseDiff()
* ���ܣ� ��ѯ�����ź����������ź�֮�����λ��
* ���������dwBoardNo:����
*           dwIspNo�������źŶ˿ڵ�����
* ���������pPhaseDiff�������ź����������ź�֮�����λ���λ��΢��
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryInputPhaseDiff(Om_UINT32 dwBoardNo, Om_UINT32 dwIspNo, Om_UINT32 *pPhaseDiff);

#ifdef __cplusplus
}
#endif
#endif
