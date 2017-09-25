/*=======================\
|   �忨�¼�֪ͨ������   |
\*======================*/

#ifndef __Omni_API_NOTIFY_H__
#define __Omni_API_NOTIFY_H__
#include <Omni_TypeDef.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* �������� Omn_RegisterAlarmCallback
* ���ܣ� �Ȱ忨�ľ����ж�
* ���������dwBoardNo  �忨��
*           pCallBackFun:���ֱ���ʱ�ص�����ָ��
*           pContext:���ֱ���ʱ�����ص�������Ӧ������ָ��
* �����������
* ����ֵ�� Om_OK���ɹ���������ʧ��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_RegisterAlarmCallback(Om_UINT32 dwBoardNo, Omn_AlarmCBFuncPtr pCallBackFun, Om_PVOID pContext);

/******************************************
* �������� Omn_RegisterTimerCallback
* ���ܣ� Ӳ����ʱ���ص�ע�ắ����RB6�ݲ�֧��
* ���������dwBoardNo  �忨��
*           dwTimeDuration �ȴ���ʱ��������msΪ��λ
*           pCallBackFun ��ʱ��ʱ�䵽ʱSDK�ص��ĺ���ָ�룬��Ϊ�ձ�ʾ����
*           pContext:�����ص�������Ӧ������ָ��
* �����������
* ����ֵ�� Om_OK���ɹ���������ʧ��
* ˵����    �忨��ʱ����ʱ�Ӿ�����10ms
******************************************/
Omn_EXPORTS Om_HRESULT Omn_RegisterTimerCallback(Om_UINT32 dwBoardNo, Om_INT32 iTimeDuration, Omn_TimerCBFuncPtr pCallBackFun, Om_PVOID pContext);

/******************************************
* �������� Omn_WaitFrameFieldInterrupt
* ���ܣ� �ȴ�֡/���жϵ���
* ���������dwBoardNo:����
*           enumPortType:SP�˿��������ͣ�������ISP����OSP
*           dwPortNo:SP�˿ں�
*           bFrameInt:Ҫ�ȴ��ĳ�/֡����,����ͨ������ʽ����
*           dwTimeout:�ȴ���ʱʱ��,��λ��ms,���Ϊ0���������ص�ǰ��/֡�жϼ���
* ���������pRetFieldType:��ǰ������ż��
*           pFrameFieldCount:��ǰ֡/�����жϼ���
* ����ֵ�� S_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_WaitFrameFieldInterrupt(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, Om_BOOL bFrameInt
    , Omn_FIELD *pRetFieldType, Om_UINT32 *pFrameFieldCount, Om_UINT32 dwTimeout);
#ifdef __cplusplus
}
#endif
#endif