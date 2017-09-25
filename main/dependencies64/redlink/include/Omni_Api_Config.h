/*======================\
|   �忨���ò���������  |
\*=====================*/

#ifndef __Omni_API_CONFIG_H__
#define __Omni_API_CONFIG_H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* �������� Omn_GetBoardParam
* ���ܣ� �õ���ǰ�忨��Ϣ
* ���������dwBoardNo:����
* ���������pBoardParam:�忨��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetBoardParam(Om_UINT32 dwBoardNo, SOmnBoardBasePara *psBoardBaseParam);

/******************************************
* �������� Omn_SetBoardParam
* ���ܣ� ���ð忨����
* ���������dwBoardNo:����
*           pBoardParam�����ò���ֵָ��
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetBoardParam(Om_UINT32 dwBoardNo, SOmnBoardBasePara *psBoardBaseParam);

/******************************************
* �������� Omn_GetBoardParamEx
* ���ܣ� �õ���ǰ�忨��չ��Ϣ,���Բ�ѯ�忨�������
* ���������dwBoardNo:����
*           enumConfigType�����ò�������
* ���������pConfigData:�忨��Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetBoardParamEx(Om_UINT32 dwBoardNo, Omn_BOARDCONFIG_TYPE enumConfigType, Om_PVOID pConfigData);

/******************************************
* �������� Omn_SetBoardParamEx
* ���ܣ� �������ð忨�������
* ���������dwBoardNo:����
*           enumConfigType�����ò�������
*           pConfigData�����ò���ֵָ��
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetBoardParamEx(Om_UINT32 dwBoardNo, Omn_BOARDCONFIG_TYPE enumConfigType, Om_PVOID pConfigData);

/******************************************
* �������� Omn_SetInSignalPortParam
* ���ܣ� �����ź�����˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
*           psISPParam:ISP����
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetInputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnInputSignalPortParam *psISPParam);

/******************************************
* �������� Omn_GetInSignalPortParam
* ���ܣ� ��ѯ����źŶ˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
* ���������psISPParam:ISP����
* ����ֵ��  Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetInputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnInputSignalPortParam *psISPParam);

/******************************************
* �������� Omn_SetOutputSignalPortParam
* ���ܣ� �����ź�����˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
*           psOSPParam:OSP����
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetOutputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnOutputSignalPortParam *psOSPParam);

/******************************************
* �������� Omn_GetOutSignalPortParam
* ���ܣ� ��ѯ����źŶ˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
* ���������psOSPParam:OSP����
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetOutputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnOutputSignalPortParam *psOSPParam);

/******************************************
* �������� Omn_SetRecordDataPortParam
* ���ܣ� ���òɼ��˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
*           psRDPParam:RDP����
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetRecordDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnRecordDataPortParam *psRDPParam);

/******************************************
* �������� Omn_GetRecordDataPortParam
* ���ܣ� ��ѯ�ɼ��˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
* ���������psRDPParam:RDP����
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetRecordDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnRecordDataPortParam *psRDPParam);

/******************************************
* �������� Omn_SetPlayDataPortParam
* ���ܣ� ���ò����˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
*           psPDPParam:PDP����
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetPlayDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnPlayDataPortParam *psPDPParam);

/******************************************
* �������� Omn_GetPlayDataPortParam
* ���ܣ� ��ѯ�����˿ڵĲ�����Ϣ
* ���������dwBoardNo:����
*           dwPortNo:�˿ں�
* ���������psPDPParam:PDP����
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetPlayDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnPlayDataPortParam *psPDPParam);

/******************************************
* �������� Omn_SetSwitchRoute()
* ���ܣ� ������������������˿ڵ�������Դ��Ϣ
* ���������dwBoardNo:����
*           enumDestStreamType:�����������������
*           dwDestStreamNo:���������������
*           psSourceInfo:����Դ��Ϣ
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� ע�⣬ֻ��OSP��RDP����ص������ǡ�Dest�������򱨴������SDK����ֲᡱ
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetSwitchRoute(Om_UINT32 dwBoardNo, Omn_STREAM_TYPE enumDestStreamType, Om_UINT32 dwDestStreamNo, SOmnStreamInfo *psSourceInfo);

/******************************************
* �������� Omn_GetSwitchRoute()
* ���ܣ� ��ѯ��������������˿ڵ�������Դ��Ϣ
* ���������dwBoardNo:����
*           enumDestStreamType:�����������������
*           dwDestStreamNo:���������������
* ���������psSourceInfo:�������������Դ��Ϣ
* ����ֵ�� Om_OK:������ ����������
* ˵���� ע�⣬ֻ��OSP��RDP����ص������ǡ�Dest�������򱨴������SDK����ֲᡱ
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetSwitchRoute(Om_UINT32 dwBoardNo, Omn_STREAM_TYPE enumDestStreamType, Om_UINT32 dwDestStreamNo, SOmnStreamInfo *psSourceInfo);

/******************************************
* �������� Omn_SetMixerParam()
* ���ܣ� ����Mixer������Ϣ
* ���������dwBoardNo:����
*           dwMixerNo:Mixer��
*           psMixerParam:Mixer������Ϣ
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnMixerParam *psMixerParam);

/******************************************
* �������� Omn_GetMixerParam()
* ���ܣ� ��ѯMixer������Ϣ
* ���������dwBoardNo:����
*           dwMixerNo:Mixer��
* ���������psMixerParam:Mixer������Ϣ
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnMixerParam *psMixerParam);

/******************************************
* �������� Omn_SetAudioMixerParam()
* ���ܣ� ������Ƶ���������Ϣ��Ŀǰֻ֧��Mixer 0����ֻ֧��������뱳�������
* ���������dwBoardNo:����
*           dwMixerNo:Mixer�ţ�����ƵMixer��ͬ
*           psMixerParam:Mixer������Ϣ
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetAudioMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnAudioMixerCfg *psMixerParam);

/******************************************
* �������� Omn_GetAudioMixerParam()
* ���ܣ� ��ѯ��Ƶ���������Ϣ��Ŀǰֻ֧��Mixer 0����ֻ֧��������뱳�������
* ���������dwBoardNo:����
*           dwMixerNo:Mixer�ţ�����ƵMixer��ͬ
* ���������psMixerParam:Mixer������Ϣ
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetAudioMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnAudioMixerCfg *psMixerParam);

/******************************************
* �������� Omn_SetUpDownCrossConvertParam()
* ���ܣ� �������±任������Ϣ
* ���������dwBoardNo:����
*           enumMode:���±任ģʽ
*           psConvertParam:���±任������Ϣָ��
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetUpDownCrossConvertParam(Om_UINT32 dwBoardNo, Omn_UPDOWN_CROSS_CONVERT_MODE enumMode, SOmnUpDownCrossConvertParam *psConvertParam);

/******************************************
* �������� Omn_GetUpDownCrossConvertParam()
* ���ܣ� ��ѯ���±任������Ϣ
* ���������dwBoardNo:����
*           enumMode:���±任ģʽ
* ���������psConvertParam:���±任������Ϣָ��
* ����ֵ�� Om_OK:������ ����������
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetUpDownCrossConvertParam(Om_UINT32 dwBoardNo, Omn_UPDOWN_CROSS_CONVERT_MODE  enumMode, SOmnUpDownCrossConvertParam *psConvertParam);

/******************************************
* �������� Omn_SetKeyerSrc()
* ���ܣ� ����Keyer������Դ���ݲ�֧��
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
*           psPort: Keyer������Դ
* �����������
* ����ֵ�� Om_OK:������ 
*          Omn_ERR_UNSUPPORTED���ݲ�֧�֣�
*          ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetKeyerSrc(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnPortDesc *psPort);

/******************************************
* �������� Omn_GetKeyerSrc()
* ���ܣ� ��ѯKeyer������Դ
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
* ���������psPort��Keyer������Դ
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetKeyerSrc(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnPortDesc *psPort);

/******************************************
* �������� Omn_InitKeyerParam()
* ���ܣ� ����ʰȡ�ı������أ���ʼ��Keyer����
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
*           pPixArr:������������ָ�룬BGRA��ʽ
*           dwPixCount:pPixArr�е�������
* ���������psParam:Keyer��ʼ������
* ����ֵ�� Om_OK:������ ����������
* ˵���� Ӧ�ó���ÿ��ʰȡ�������غ�Ӧ���ñ��������Keyer�����ĳ�ʼ��
******************************************/
Omn_EXPORTS Om_HRESULT Omn_InitKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, Om_UINT32 *pPixArr, Om_UINT32 dwPixCount, SOmnKeyerParam *psParam);

/******************************************
* �������� Omn_SetKeyerParam()
* ���ܣ� ����Keyer����
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
*           psParam��Keyer����
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyerParam *psParam);

/******************************************
* �������� Omn_GetKeyerParam()
* ���ܣ� ��ȡKeyer����
* ���������dwBoardNo:����
*           dwKeyerNo��Keyer������
* ���������psParam��ɫ������
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyerParam *psParam);

/******************************************
* �������� Omn_SetGenlockStandard()
* ���ܣ� ����Genlockʱ����ʽ
* ���������dwBoardNo:����
*           enumVideostandard��Genlockʱ����ʽ
* �����������
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetGenlockStandard(Om_UINT32 dwBoardNo, Omn_VIDEO_STANDARD enumVideostandard);

/******************************************
* �������� Omn_GetGenlockStandard()
* ���ܣ� ��ѯGenlockʱ����ʽ
* ���������dwBoardNo:����
* ���������pEnumVideostandard��Genlockʱ����ʽ
* ����ֵ�� Om_OK:������ ����������
* ˵����
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetGenlockStandard(Om_UINT32 dwBoardNo, Omn_VIDEO_STANDARD *pEnumVideostandard);


Omn_EXPORTS Om_HRESULT Omn_SetSDIInputGain(Om_UINT32 dwBoardNo, Om_UINT32 dwISPNo, Om_FLOAT gain);
Omn_EXPORTS Om_HRESULT Omn_GetSDIInputGain(Om_UINT32 dwBoardNo, Om_UINT32 dwISPNo, Om_FLOAT *gain);
Omn_EXPORTS Om_HRESULT Omn_SetSDIInput3GExMode(Om_UINT32 dwBoardNo, Om_UINT32 dwISPNo, Om_BOOL bEnable);
Omn_EXPORTS Om_HRESULT Omn_GetSDIInput3GExMode(Om_UINT32 dwBoardNo, Om_UINT32 dwISPNo, Om_BOOL *bEnable);
Omn_EXPORTS Om_HRESULT Omn_GetCableLength(Om_UINT32 dwBoardNo, Om_UINT32 dwISPNo, Om_UINT32 *dwLength);
#ifdef __cplusplus
}
#endif
#endif
