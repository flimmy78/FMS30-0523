/*================================================\
|   �忨�ɼ�/����״̬���ƺ������Լ�buffer IO����  |
\*===============================================*/

#ifndef __Omni_API_STATE_CTRL_AND_BUFFER_IO_H__
#define __Omni_API_STATE_CTRL_AND_BUFFER_IO__H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* �������� Omn_PreRecord
* ���ܣ� ע��ɼ��ص�����
* ���������dwBoardNo:����
*           dwRDPNo:RDP�˿ں�
*           bISAsync:��չ�ã���ΪOm_FALSE
*           pIoCBFun:���ڶ˿�����Ƶ����Buffer�����ص�����ָ��
*           pMsgCBFun:��չ�ã���ΪOm_NULL
*           pContext:�ص�ʱ��Ӧ�ó���������
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
*   
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PreRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, Om_BOOL bISAsync
    , Omn_IoCBFuncPtr pIoCBFun, Omn_CallBackFuncPtr pMsgCBFun, Om_PVOID pContext);


/******************************************
* �������� Omn_StartRecord
* ���ܣ� ��ʼ/�������ɼ�
* ���������dwBoardNo:����
*           dwRDPNo:�ɼ����ݶ˿ں�
* ���������psRecordInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StartRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, SOmn_RunTimeInfo *psRecordInfo);

/******************************************
* �������� Omn_StopRecord
* ���ܣ� ֹͣ�ɼ�
* ���������dwBoardNo:����
*           dwRDPNo:�ɼ����ݶ˿ں�
* ���������psRecordInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, SOmn_RunTimeInfo *psRecordInfo);


/******************************************
* �������� Omn_CloseRecord
* ���ܣ� �ر�ͨ������ȡ��ע�ắ��
* ���������dwBoardNo:����
*           dwRDPNo:�ɼ����ݶ˿ں�
* �����������
* ����ֵ�� Om_OK:������ ����������
*   -1:���Ų����ڣ�-2:��ͨ��û�б�ռ��
* ˵���� �ͷ�ͨ����Դ��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_CloseRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo);

/******************************************
* �������� Omn_PrePlay
* ���ܣ� ע�Ქ�Żص�����
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
*           bISAsync:��չ�ã���ΪOm_FALSE
*           pIoCBFun:���ڶ˿�����Ƶ����Buffer�����ص�����ָ��
*           pMsgCBFun:��չ�ã���ΪOm_NULL
*           pHLBCBFun:��չ�ã���ΪOm_NULL
*           pContext:�ص�ʱ��Ӧ�ó���������
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� ��Ϊÿ��忨֧�ֶ������ͨ����ÿ��ͨ������ע��ص�����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PrePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, Om_BOOL bISAsync
    , Omn_IoCBFuncPtr pIoCBFun, Omn_CallBackFuncPtr pMsgCBFun, Omn_HLBCBFuncPtr pHLBCBFun, Om_PVOID pContext);

/******************************************
* �������� Omn_StartPlay
* ���ܣ� ��ʼ����
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
* ���������psPlayInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� ÿ�鿨ÿ·�����Ե�������
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StartPlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo  *psPlayInfo);

/******************************************
* �������� Omn_StopPlay
* ���ܣ� ֹͣ����
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
* ���������psPlayInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� ÿ�鿨ÿ·�����Ե���ֹͣ��ֹͣ��ʾ��ֹͣ�ص������忨�ϵ�Buffer��Ҫ���꣬
*   ��ͣ�������һ֡��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopPlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* �������� Omn_StopPlayImmediately
* ���ܣ� ����ֹͣ����ͨ���Ĳ���
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
* ���������psPlayInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK���ɹ���������ʧ��
* ˵����    Omn_StopPlay��Omn_StopPlayImmediately���������ڣ�ǰ�߻�ȵ��忨���������е�����Buffer��������Ϻ��ͣ
*           ֹ�����������߻�����ֹͣ������
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopPlayImmediately(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* �������� Omn_PausePlay
* ���ܣ� ��ͣ����
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
* ���������psPlayInfo:����ʱ��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� ������·���Ե�����ͣ����ͣʱ���ײ�����ֹͣ�ص���ͬʱ�忨�ϵ�Bufferͣ����ǰӲ������֡��
*        Ӳ�������������Ѿ������Buffer���ݻ������������´�Startʱ�ɼ����ӵ�ǰӲ������֡λ��������
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PausePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* �������� Omn_Seek
* ���ܣ� Seek��Ƶ����
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
*           psUpdateInfo��Seek����Buf��Ϣ
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� ������·�����Ե���SEEK��ͬʱSeek��Զ����ͬ����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Seek(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmnBufUpdataInfo *psUpdateInfo);

/******************************************
* �������� Omn_ClosePlay
* ���ܣ� �ر�ͨ������ȡ��ע�ắ��
* ���������dwBoardNo:����
*           dwPDPNo:�������ݶ˿ں�
* �����������
* ����ֵ�� Om_OK:������ ����������
*   -1:���Ų����ڣ�-2:��ͨ��û�б�ռ��
* ˵���� �ͷ�ͨ����Դ��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_ClosePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo);

/******************************************
* �������� Omn_UpdateBuffer
* ����  �� ���ڲ���ͨ����˵���ú������߰忨��Buffer���������ڲ��� 
*          ���ڲɼ�ͨ����˵���ú������߰忨�ɼ������ݴ�����Buffer
* ���������dwBoardNo:����
*           enumPortType:���ݶ˿����ͣ�������RDP����PDP
*           dwPortNo:�˿ں�
*           psUpdateInfo:ҪUpdate����Ƶ/��Ƶ��Ϣ
* ���������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_UpdateBuffer(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, SOmnBufUpdataInfo *psUpdateInfo);

/******************************************
* �������� Omn_UpdateBuffer_Ex1
* ����  �� ���ڲ���ͨ����˵���ú������߰忨��Buffer���������ڲ��� 
*          ���ڲɼ�ͨ����˵���ú������߰忨�ɼ������ݴ�����Buffer
* ���������dwBoardNo:����
*           enumPortType:���ݶ˿����ͣ�������RDP����PDP
*           dwPortNo:�˿ں�
*           psUpdateInfo:ҪUpdate����Ƶ/��Ƶ��Ϣ
* ���������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_UpdateBuffer_Ex1(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, SOmnBufUpdateInfo_Ex1 *psUpdateInfo);


#ifdef __cplusplus
}
#endif

#endif
