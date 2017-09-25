/*======================\
|   板卡配置操作函数集  |
\*=====================*/

#ifndef __Omni_API_CONFIG_H__
#define __Omni_API_CONFIG_H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* 函数名： Omn_GetBoardParam
* 功能： 得到当前板卡信息
* 输入参数：dwBoardNo:卡号
* 输出参数：pBoardParam:板卡信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetBoardParam(Om_UINT32 dwBoardNo, SOmnBoardBasePara *psBoardBaseParam);

/******************************************
* 函数名： Omn_SetBoardParam
* 功能： 设置板卡参数
* 输入参数：dwBoardNo:卡号
*           pBoardParam：设置参数值指针
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetBoardParam(Om_UINT32 dwBoardNo, SOmnBoardBasePara *psBoardBaseParam);

/******************************************
* 函数名： Omn_GetBoardParamEx
* 功能： 得到当前板卡扩展信息,可以查询板卡单项参数
* 输入参数：dwBoardNo:卡号
*           enumConfigType：设置参数类型
* 输出参数：pConfigData:板卡信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetBoardParamEx(Om_UINT32 dwBoardNo, Omn_BOARDCONFIG_TYPE enumConfigType, Om_PVOID pConfigData);

/******************************************
* 函数名： Omn_SetBoardParamEx
* 功能： 可以设置板卡单项参数
* 输入参数：dwBoardNo:卡号
*           enumConfigType：设置参数类型
*           pConfigData：设置参数值指针
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetBoardParamEx(Om_UINT32 dwBoardNo, Omn_BOARDCONFIG_TYPE enumConfigType, Om_PVOID pConfigData);

/******************************************
* 函数名： Omn_SetInSignalPortParam
* 功能： 设置信号输入端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
*           psISPParam:ISP参数
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetInputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnInputSignalPortParam *psISPParam);

/******************************************
* 函数名： Omn_GetInSignalPortParam
* 功能： 查询输出信号端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
* 输出参数：psISPParam:ISP参数
* 返回值：  Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetInputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnInputSignalPortParam *psISPParam);

/******************************************
* 函数名： Omn_SetOutputSignalPortParam
* 功能： 设置信号输入端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
*           psOSPParam:OSP参数
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetOutputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnOutputSignalPortParam *psOSPParam);

/******************************************
* 函数名： Omn_GetOutSignalPortParam
* 功能： 查询输出信号端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
* 输出参数：psOSPParam:OSP参数
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetOutputSignalPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnOutputSignalPortParam *psOSPParam);

/******************************************
* 函数名： Omn_SetRecordDataPortParam
* 功能： 设置采集端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
*           psRDPParam:RDP参数
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetRecordDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnRecordDataPortParam *psRDPParam);

/******************************************
* 函数名： Omn_GetRecordDataPortParam
* 功能： 查询采集端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
* 输出参数：psRDPParam:RDP参数
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetRecordDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnRecordDataPortParam *psRDPParam);

/******************************************
* 函数名： Omn_SetPlayDataPortParam
* 功能： 设置播出端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
*           psPDPParam:PDP参数
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetPlayDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnPlayDataPortParam *psPDPParam);

/******************************************
* 函数名： Omn_GetPlayDataPortParam
* 功能： 查询播出端口的参数信息
* 输入参数：dwBoardNo:卡号
*           dwPortNo:端口号
* 输出参数：psPDPParam:PDP参数
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetPlayDataPortParam(Om_UINT32 dwBoardNo, Om_UINT32 dwPortNo, SOmnPlayDataPortParam *psPDPParam);

/******************************************
* 函数名： Omn_SetSwitchRoute()
* 功能： 设置主交换矩阵输出端口的数据来源信息
* 输入参数：dwBoardNo:卡号
*           enumDestStreamType:交换矩阵输出流类型
*           dwDestStreamNo:交换矩阵输出流号
*           psSourceInfo:流来源信息
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 注意，只有OSP和RDP上相关的流才是“Dest”，否则报错。详见“SDK编程手册”
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetSwitchRoute(Om_UINT32 dwBoardNo, Omn_STREAM_TYPE enumDestStreamType, Om_UINT32 dwDestStreamNo, SOmnStreamInfo *psSourceInfo);

/******************************************
* 函数名： Omn_GetSwitchRoute()
* 功能： 查询主交换矩阵输出端口的数据来源信息
* 输入参数：dwBoardNo:卡号
*           enumDestStreamType:交换矩阵输出流类型
*           dwDestStreamNo:交换矩阵输出流号
* 输出参数：psSourceInfo:输出流的输入来源信息
* 返回值： Om_OK:正常， 其它：错误
* 说明： 注意，只有OSP和RDP上相关的流才是“Dest”，否则报错。详见“SDK编程手册”
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetSwitchRoute(Om_UINT32 dwBoardNo, Omn_STREAM_TYPE enumDestStreamType, Om_UINT32 dwDestStreamNo, SOmnStreamInfo *psSourceInfo);

/******************************************
* 函数名： Omn_SetMixerParam()
* 功能： 设置Mixer配置信息
* 输入参数：dwBoardNo:卡号
*           dwMixerNo:Mixer号
*           psMixerParam:Mixer配置信息
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnMixerParam *psMixerParam);

/******************************************
* 函数名： Omn_GetMixerParam()
* 功能： 查询Mixer配置信息
* 输入参数：dwBoardNo:卡号
*           dwMixerNo:Mixer号
* 输出参数：psMixerParam:Mixer配置信息
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnMixerParam *psMixerParam);

/******************************************
* 函数名： Omn_SetAudioMixerParam()
* 功能： 设置音频混叠配置信息。目前只支持Mixer 0，且只支持主输出与背景音混叠
* 输入参数：dwBoardNo:卡号
*           dwMixerNo:Mixer号，与视频Mixer相同
*           psMixerParam:Mixer配置信息
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetAudioMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnAudioMixerCfg *psMixerParam);

/******************************************
* 函数名： Omn_GetAudioMixerParam()
* 功能： 查询音频混叠配置信息。目前只支持Mixer 0，且只支持主输出与背景音混叠
* 输入参数：dwBoardNo:卡号
*           dwMixerNo:Mixer号，与视频Mixer相同
* 输出参数：psMixerParam:Mixer配置信息
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetAudioMixerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwMixerNo, SOmnAudioMixerCfg *psMixerParam);

/******************************************
* 函数名： Omn_SetUpDownCrossConvertParam()
* 功能： 设置上下变换配置信息
* 输入参数：dwBoardNo:卡号
*           enumMode:上下变换模式
*           psConvertParam:上下变换配置信息指针
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetUpDownCrossConvertParam(Om_UINT32 dwBoardNo, Omn_UPDOWN_CROSS_CONVERT_MODE enumMode, SOmnUpDownCrossConvertParam *psConvertParam);

/******************************************
* 函数名： Omn_GetUpDownCrossConvertParam()
* 功能： 查询上下变换配置信息
* 输入参数：dwBoardNo:卡号
*           enumMode:上下变换模式
* 输出参数：psConvertParam:上下变换配置信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetUpDownCrossConvertParam(Om_UINT32 dwBoardNo, Omn_UPDOWN_CROSS_CONVERT_MODE  enumMode, SOmnUpDownCrossConvertParam *psConvertParam);

/******************************************
* 函数名： Omn_SetKeyerSrc()
* 功能： 设置Keyer数据来源。暂不支持
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
*           psPort: Keyer数据来源
* 输出参数：无
* 返回值： Om_OK:正常， 
*          Omn_ERR_UNSUPPORTED：暂不支持，
*          其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetKeyerSrc(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnPortDesc *psPort);

/******************************************
* 函数名： Omn_GetKeyerSrc()
* 功能： 查询Keyer数据来源
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
* 输出参数：psPort：Keyer数据来源
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetKeyerSrc(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnPortDesc *psPort);

/******************************************
* 函数名： Omn_InitKeyerParam()
* 功能： 基于拾取的背景像素，初始化Keyer参数
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
*           pPixArr:背景像素数组指针，BGRA格式
*           dwPixCount:pPixArr中的像素数
* 输出参数：psParam:Keyer初始化参数
* 返回值： Om_OK:正常， 其它：错误
* 说明： 应用程序每次拾取背景像素后，应调用本函数完成Keyer参数的初始化
******************************************/
Omn_EXPORTS Om_HRESULT Omn_InitKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, Om_UINT32 *pPixArr, Om_UINT32 dwPixCount, SOmnKeyerParam *psParam);

/******************************************
* 函数名： Omn_SetKeyerParam()
* 功能： 设置Keyer参数
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
*           psParam：Keyer参数
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyerParam *psParam);

/******************************************
* 函数名： Omn_GetKeyerParam()
* 功能： 获取Keyer参数
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
* 输出参数：psParam：色键参数
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_GetKeyerParam(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyerParam *psParam);

/******************************************
* 函数名： Omn_SetGenlockStandard()
* 功能： 设置Genlock时钟制式
* 输入参数：dwBoardNo:卡号
*           enumVideostandard：Genlock时钟制式
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_SetGenlockStandard(Om_UINT32 dwBoardNo, Omn_VIDEO_STANDARD enumVideostandard);

/******************************************
* 函数名： Omn_GetGenlockStandard()
* 功能： 查询Genlock时钟制式
* 输入参数：dwBoardNo:卡号
* 输出参数：pEnumVideostandard：Genlock时钟制式
* 返回值： Om_OK:正常， 其它：错误
* 说明：
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
