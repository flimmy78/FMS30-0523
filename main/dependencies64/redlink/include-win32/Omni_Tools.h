#ifndef __Omn_TOOLS_H__
#define __Omn_TOOLS_H__


#include "Omni_TypeDef.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* AFD��Ϣ
******************************************/
typedef struct SOmn_AFD_T
{
    Om_UINT8    ar;
    Om_UINT8    a0;
    Om_UINT8    a1;
    Om_UINT8    a2;
    Om_UINT8    a3;

    Om_UINT8    top_flag;
    Om_UINT8    left_flag;
    Om_UINT8    bottom_flag;
    Om_UINT8    right_flag;

    Om_UINT16   bar_value1;
    Om_UINT16   bar_value2;
}SOmn_AFD, *PSOmn_AFD;

/******************************************
* LTC��VITC��Ϣ
******************************************/
typedef struct SOmn_LTC_VITC_T
{
    Om_UINT32 frame_unit         :4;
    Om_UINT32 frame_ten          :2;
    Om_UINT32 second_unit        :4;
    Om_UINT32 second_ten         :3;
    Om_UINT32 minute_unit        :4;
    Om_UINT32 minute_ten         :3;
    Om_UINT32 hour_unit          :4;
    Om_UINT32 hour_ten           :2;

    Om_UINT32 dropframe_flag     :1;
    Om_UINT32 colorframe_flag    :1;
    Om_UINT32 polaritycorr_flag  :1;
    Om_UINT32 bg0_flag           :1;
    Om_UINT32 bg1_flag           :1;
    Om_UINT32 bg2_flag           :1;

    Om_UINT32 binary_group1      :4;
    Om_UINT32 binary_group2      :4;
    Om_UINT32 binary_group3      :4;
    Om_UINT32 binary_group4      :4;
    Om_UINT32 binary_group5      :4;
    Om_UINT32 binary_group6      :4;
    Om_UINT32 binary_group7      :4;
    Om_UINT32 binary_group8      :4;
}SOmn_LTC_VITC, *PSOmn_LTC_VITC, SOmn_LTC, *PSOmn_LTC, SOmn_VITC, *PSOmn_VITC;

/******************************************
* �û�ʱ����Ϣ������ģ��LTC����ǶLTC��VITC
******************************************/
typedef struct SOmn_TIMECODE_T
{
    Om_UINT32        size;

    Om_UINT64        embLtcTime_Value;
    Om_UINT8         embLtcValid;
    Om_UINT64        VitcTime_Value;
    Om_UINT8         VitcValid;
    Om_UINT64        anaLtcTime_Value;
    Om_UINT8         anaLtcValid;

    Om_UINT32        reserved32;
    Om_UINT8         reserved8;
}SOmn_TIMECODE, *PSOmn_TIMECODE;

/******************************************
* �������� Omn_GetOOBBufferSize
* ���ܣ� ��ѯ����OOB buffer��С����Сֵ
* �����������
* �����������
* ����ֵ�� OOB buffer��С����Сֵ
* ˵���� 
******************************************/
Omn_EXPORTS Om_UINT32 Omn_GetOOBBufferSize();

/******************************************
* �������� Omn_EncodeOOBAFD
* ���ܣ� AFD����
* ���������pAfd���������AFD����
* ���������pOOBBuffer���ѱ���AFD��Ϣ��OOB����buffer
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeOOBAFD(SOmn_AFD *pAfd, Om_PVOID pOOBBuffer);

/******************************************
* �������� Omn_DecodeOOBAFD
* ���ܣ� AFD����
* ���������pOOBBuffer������������AFD���ݵ�OOB����buffer
* ���������pAfd������õ���AFD����
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeOOBAFD(SOmn_AFD *pAfd, Om_PVOID pOOBBuffer);

/******************************************
* �������� Omn_EncodeOOBTimecode
* ���ܣ� ʱ�루����ģ��LTC����ǶLTC��VITC������
* ���������enumStandard����Ƶ��ʽ
*           pTc���������ʱ����Ϣ
* ���������pOOBBuffer���ѱ���ʱ����Ϣ��OOB����buffer
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeOOBTimecode(Omn_VIDEO_STANDARD enumStandard, SOmn_TIMECODE *pTc, Om_PVOID pOOBBuffer);

/******************************************
* �������� Omn_DecodeOOBTimecode
* ���ܣ� ʱ�루����ģ��LTC����ǶLTC��VITC������
* ���������enumStandard����Ƶ��ʽ
*           pOOBBuffer������������ʱ����Ϣ��OOB����buffer
* ���������pTc������õ���ʱ������
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeOOBTimecode(Omn_VIDEO_STANDARD enumStandard, SOmn_TIMECODE *pTc, Om_PVOID pOOBBuffer);


//////////////////////////////////////////////////////////////////////////

/******************************************
* VANC���ݰ�Ƕ�뷽ʽ
******************************************/
typedef enum Omn_VANC_EMBED_TYPE_E
{
    VANC_EMBED_TYPE_UNKNOW  = -1,
    VANC_EMBED_TYPE_Y   = 0,    //ֻ�ڷ���Y��Ƕ��VANC��
    VANC_EMBED_TYPE_YUV   = 1,  //����Y��U��V�Ͼ�Ƕ��VANC��
} Omn_VANC_EMBED_TYPE,*POmn_VANC_EMBED_TYPE;

/******************************************
* �������� Omn_InitVANCBuffer
* ���ܣ� ��ʼ��VANC buffer
* ���������pVancInfo��VANC֧����Ϣ
*           dwStartLineNo��VANC����buffer��Ҫ��ʼ������ʼ��
*           dwEndLineNo��VANC����buffer��Ҫ��ʼ���Ľ�����
* ���������pVancBuffer��VANC����buffer
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_InitVANCBuffer(/*[OUT]*/ Om_PVOID pVancBuffer
                               , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                               , /*[IN]*/ Om_UINT32 dwStartLineNo
                               , /*[IN]*/ Om_UINT32 dwEndLineNo);

/******************************************
* �������� Omn_EncodeVANCOnLine
* ���ܣ� ��ָ�����ϱ���VANC���ݰ�
* ���������pVancInfo��VANC֧����Ϣ
*           enumVancEmbedType��VANC����Ƕ������
*           nDID��VANC����DID
*           nSDID_DBN��VANC����SDID/DBN
*           pUDWBuffer����������û���������Ϣ
*           dwUDWLength����������û���������Ϣ���ȣ����ܳ���255
*           dwLineNo��VANC�������ָ����
* ���������pVancBuffer���ѱ����VANC����buffer
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� ����[ADF][DID][SDID][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[50h,5Fh]���䣬SDIDȡֵ����[01h,FFh]���䡣
*        ����[ADF][DID][DBN][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[C0h,CFh]���䣬DBNȡֵ����[01h,FFh]���䡣
*        ������VANC���ݰ�ADFΪ000h 3FFh 3FFh��
*        ����˵������������SMPTE-291M-2006
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeVANCOnLine (/*[OUT]*/ Om_PVOID pVancBuffer
                                , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                                , /*[IN]*/ Omn_VANC_EMBED_TYPE enumVancEmbedType
                                , /*[IN]*/ Om_UINT8 nDID
                                , /*[IN]*/ Om_UINT8 nSDID_DBN
                                , /*[IN]*/ Om_PVOID pUDWBuffer
                                , /*[IN]*/ Om_UINT32 dwUDWLength
                                , /*[IN]*/ Om_UINT32 dwLineNo
                                );

/******************************************
* �������� Omn_EncodeVANC
* ���ܣ� ����VANC���ݰ�������ʼ�п�ʼд��
* ���������pVancInfo��VANC֧����Ϣ
*           enumVancEmbedType��VANC����Ƕ������
*           nDID��VANC����DID
*           nSDID_DBN��VANC����SDID/DBN
*           pUDWBuffer����������û���������Ϣ
*           dwUDWLength����������û���������Ϣ���ȣ����ܳ���255
* ���������pVancBuffer���ѱ����VANC����buffer
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� ����[ADF][DID][SDID][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[50h,5Fh]���䣬SDIDȡֵ����[01h,FFh]���䡣
*        ����[ADF][DID][DBN][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[C0h,CFh]���䣬DBNȡֵ����[01h,FFh]���䡣
*        ������VANC���ݰ�ADFΪ000h 3FFh 3FFh��
*        ����˵������������SMPTE-291M-2006
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeVANC (/*[OUT]*/ Om_PVOID pVancBuffer
                            , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                            , /*[IN]*/ Omn_VANC_EMBED_TYPE enumVancEmbedType
                            , /*[IN]*/ Om_UINT8 nDID
                            , /*[IN]*/ Om_UINT8 nSDID_DBN
                            , /*[IN]*/ Om_PVOID pUDWBuffer
                            , /*[IN]*/ Om_UINT32 dwUDWLength
                            );

/******************************************
* �������� Omn_DecodeVANCOnLine
* ���ܣ� ��ָ���н���VANC���ݰ�
* ���������
* ���������
* ����ֵ��
* ˵���� �ݲ�֧�ָù���
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeVANCOnLine (/*[OUT]*/ Om_PVOID pUDWBuffer
                                , /*[OUT]*/ Om_UINT32 *pUDWLength
                                , /*[IN] [OUT]*/ Om_UINT8 *pDID
                                , /*[IN] [OUT]*/ Om_UINT8 *pSDID_DBN
                                , /*[IN]*/ Om_PVOID pVancBuffer
                                , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                                , /*[IN]*/ Omn_VANC_EMBED_TYPE enumVancEmbedType
                                , /*[IN]*/ Om_UINT32 dwLineNo
                                , /*[IN]*/ Om_UINT32 dwPackageIndex
                                );

/******************************************
* �������� Omn_DecodeVANC
* ���ܣ� ����1����VANC����buffer�в��ҽ���ָ��DID/SDID/DBN�����ݰ����û������֣�UDW������ָ��Ҫ�õ��ڼ������������ݰ����û������֡�
*        ����2: ��VANC����buffer�б����������е����ݰ���ͨ��ָ������ȡ��ָ�������ݰ���ע���ʱDID/SDID/DBNӦΪ0��
* ���������nDID��VANC����DID
*           nSDID_DBN��VANC����SDID/DBN
*           pVancBuffer���������VANC����buffer
*           pVancInfo��VANC֧����Ϣ
*           enumVancEmbedType��VANC����Ƕ������
*           dwPackageIndex��Ҫ�����õ���VANC���ݰ�������
* ���������pUDWBuffer������õ���VANC�����û�������
*           pUDWLength������õ����û������ֳ���
*           pDID�������õ��ĵ�ǰVANC����DID
*           nSDID_DBN�������õ��ĵ�ǰVANC����SDID/DBN
* ����ֵ�� Om_OK: �ɹ�, ����: ����
* ˵���� ����[ADF][DID][SDID][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[50h,5Fh]���䣬SDIDȡֵ����[01h,FFh]���䡣
*        ����[ADF][DID][DBN][DC][UDW][CS]�����ʽ��VANC�����û�DIDȡֵ����[C0h,CFh]���䣬DBNȡֵ����[01h,FFh]���䡣
*        ����ֻ֧��ADFΪ000h 3FFh 3FFh��VANC���ݰ���
*        ����˵������������SMPTE-291M-2006
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeVANC (/*[OUT]*/ Om_PVOID pUDWBuffer
                            , /*[OUT]*/ Om_UINT32 *pUDWLength
                            , /*[IN] [OUT]*/ Om_UINT8 *pDID
                            , /*[IN] [OUT]*/ Om_UINT8 *pSDID_DBN
                            , /*[IN]*/ Om_PVOID pVancBuffer
                            , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                            , /*[IN]*/ Omn_VANC_EMBED_TYPE enumVancEmbedType
                            , /*[IN]*/ Om_UINT32 dwPackageIndex
                            );

#ifdef __cplusplus
}
#endif

#endif // __Omn_TOOLS_H__

