#ifndef __Omn_TOOLS_H__
#define __Omn_TOOLS_H__


#include "Omni_TypeDef.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* AFD信息
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
* LTC、VITC信息
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
* 用户时码信息，包括模拟LTC、内嵌LTC和VITC
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
* 函数名： Omn_GetOOBBufferSize
* 功能： 查询所用OOB buffer大小的最小值
* 输入参数：无
* 输出参数：无
* 返回值： OOB buffer大小的最小值
* 说明： 
******************************************/
Omn_EXPORTS Om_UINT32 Omn_GetOOBBufferSize();

/******************************************
* 函数名： Omn_EncodeOOBAFD
* 功能： AFD编码
* 输入参数：pAfd：待编码的AFD数据
* 输出参数：pOOBBuffer：已编入AFD信息的OOB数据buffer
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeOOBAFD(SOmn_AFD *pAfd, Om_PVOID pOOBBuffer);

/******************************************
* 函数名： Omn_DecodeOOBAFD
* 功能： AFD解码
* 输入参数：pOOBBuffer：包含待解码AFD数据的OOB数据buffer
* 输出参数：pAfd：解码得到的AFD数据
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeOOBAFD(SOmn_AFD *pAfd, Om_PVOID pOOBBuffer);

/******************************************
* 函数名： Omn_EncodeOOBTimecode
* 功能： 时码（包含模拟LTC、内嵌LTC和VITC）编码
* 输入参数：enumStandard：视频制式
*           pTc：待编码的时码信息
* 输出参数：pOOBBuffer：已编入时码信息的OOB数据buffer
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_EncodeOOBTimecode(Omn_VIDEO_STANDARD enumStandard, SOmn_TIMECODE *pTc, Om_PVOID pOOBBuffer);

/******************************************
* 函数名： Omn_DecodeOOBTimecode
* 功能： 时码（包含模拟LTC、内嵌LTC和VITC）解码
* 输入参数：enumStandard：视频制式
*           pOOBBuffer：包含待解码时码信息的OOB数据buffer
* 输出参数：pTc：解码得到的时码数据
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_DecodeOOBTimecode(Omn_VIDEO_STANDARD enumStandard, SOmn_TIMECODE *pTc, Om_PVOID pOOBBuffer);


//////////////////////////////////////////////////////////////////////////

/******************************************
* VANC数据包嵌入方式
******************************************/
typedef enum Omn_VANC_EMBED_TYPE_E
{
    VANC_EMBED_TYPE_UNKNOW  = -1,
    VANC_EMBED_TYPE_Y   = 0,    //只在分量Y上嵌入VANC包
    VANC_EMBED_TYPE_YUV   = 1,  //分量Y、U、V上均嵌入VANC包
} Omn_VANC_EMBED_TYPE,*POmn_VANC_EMBED_TYPE;

/******************************************
* 函数名： Omn_InitVANCBuffer
* 功能： 初始化VANC buffer
* 输入参数：pVancInfo：VANC支持信息
*           dwStartLineNo：VANC数据buffer需要初始化的起始行
*           dwEndLineNo：VANC数据buffer需要初始化的结束行
* 输出参数：pVancBuffer：VANC数据buffer
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_InitVANCBuffer(/*[OUT]*/ Om_PVOID pVancBuffer
                               , /*[IN]*/ SOmn_VANC_INFO* pVancInfo
                               , /*[IN]*/ Om_UINT32 dwStartLineNo
                               , /*[IN]*/ Om_UINT32 dwEndLineNo);

/******************************************
* 函数名： Omn_EncodeVANCOnLine
* 功能： 在指定行上编入VANC数据包
* 输入参数：pVancInfo：VANC支持信息
*           enumVancEmbedType：VANC数据嵌入类型
*           nDID：VANC包的DID
*           nSDID_DBN：VANC包的SDID/DBN
*           pUDWBuffer：待编码的用户数据字信息
*           dwUDWLength：待编码的用户数据字信息长度，不能超过255
*           dwLineNo：VANC包编入的指定行
* 输出参数：pVancBuffer：已编码的VANC数据buffer
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 对于[ADF][DID][SDID][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[50h,5Fh]区间，SDID取值须在[01h,FFh]区间。
*        对于[ADF][DID][DBN][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[C0h,CFh]区间，DBN取值须在[01h,FFh]区间。
*        编码后的VANC数据包ADF为000h 3FFh 3FFh。
*        上述说明及编码依据SMPTE-291M-2006
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
* 函数名： Omn_EncodeVANC
* 功能： 编入VANC数据包，从起始行开始写入
* 输入参数：pVancInfo：VANC支持信息
*           enumVancEmbedType：VANC数据嵌入类型
*           nDID：VANC包的DID
*           nSDID_DBN：VANC包的SDID/DBN
*           pUDWBuffer：待编码的用户数据字信息
*           dwUDWLength：待编码的用户数据字信息长度，不能超过255
* 输出参数：pVancBuffer：已编码的VANC数据buffer
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 对于[ADF][DID][SDID][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[50h,5Fh]区间，SDID取值须在[01h,FFh]区间。
*        对于[ADF][DID][DBN][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[C0h,CFh]区间，DBN取值须在[01h,FFh]区间。
*        编码后的VANC数据包ADF为000h 3FFh 3FFh。
*        上述说明及编码依据SMPTE-291M-2006
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
* 函数名： Omn_DecodeVANCOnLine
* 功能： 从指定行解析VANC数据包
* 输入参数：
* 输出参数：
* 返回值：
* 说明： 暂不支持该功能
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
* 函数名： Omn_DecodeVANC
* 功能： 功能1：从VANC数据buffer中查找解析指定DID/SDID/DBN的数据包的用户数据字（UDW），可指定要得到第几个这样的数据包的用户数据字。
*        功能2: 从VANC数据buffer中遍历解析所有的数据包，通过指定索引取得指定的数据包，注意此时DID/SDID/DBN应为0。
* 输入参数：nDID：VANC包的DID
*           nSDID_DBN：VANC包的SDID/DBN
*           pVancBuffer：待解码的VANC数据buffer
*           pVancInfo：VANC支持信息
*           enumVancEmbedType：VANC数据嵌入类型
*           dwPackageIndex：要解析得到的VANC数据包的索引
* 输出参数：pUDWBuffer：解码得到的VANC包的用户数据字
*           pUDWLength：解码得到的用户数据字长度
*           pDID：解析得到的当前VANC包的DID
*           nSDID_DBN：解析得到的当前VANC包的SDID/DBN
* 返回值： Om_OK: 成功, 其它: 错误
* 说明： 对于[ADF][DID][SDID][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[50h,5Fh]区间，SDID取值须在[01h,FFh]区间。
*        对于[ADF][DID][DBN][DC][UDW][CS]编码格式的VANC包，用户DID取值须在[C0h,CFh]区间，DBN取值须在[01h,FFh]区间。
*        解码只支持ADF为000h 3FFh 3FFh的VANC数据包。
*        上述说明及解析依据SMPTE-291M-2006
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

