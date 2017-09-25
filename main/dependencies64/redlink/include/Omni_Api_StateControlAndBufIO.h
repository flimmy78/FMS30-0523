/*================================================\
|   板卡采集/播出状态控制函数集以及buffer IO函数  |
\*===============================================*/

#ifndef __Omni_API_STATE_CTRL_AND_BUFFER_IO_H__
#define __Omni_API_STATE_CTRL_AND_BUFFER_IO__H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* 函数名： Omn_PreRecord
* 功能： 注册采集回调函数
* 输入参数：dwBoardNo:卡号
*           dwRDPNo:RDP端口号
*           bISAsync:扩展用，须为Om_FALSE
*           pIoCBFun:用于端口视音频数据Buffer交互回调函数指针
*           pMsgCBFun:扩展用，须为Om_NULL
*           pContext:回调时的应用程序上下文
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
*   
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PreRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, Om_BOOL bISAsync
    , Omn_IoCBFuncPtr pIoCBFun, Omn_CallBackFuncPtr pMsgCBFun, Om_PVOID pContext);


/******************************************
* 函数名： Omn_StartRecord
* 功能： 开始/重启动采集
* 输入参数：dwBoardNo:卡号
*           dwRDPNo:采集数据端口号
* 输出参数：psRecordInfo:运行时信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StartRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, SOmn_RunTimeInfo *psRecordInfo);

/******************************************
* 函数名： Omn_StopRecord
* 功能： 停止采集
* 输入参数：dwBoardNo:卡号
*           dwRDPNo:采集数据端口号
* 输出参数：psRecordInfo:运行时信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo, SOmn_RunTimeInfo *psRecordInfo);


/******************************************
* 函数名： Omn_CloseRecord
* 功能： 关闭通道，并取消注册函数
* 输入参数：dwBoardNo:卡号
*           dwRDPNo:采集数据端口号
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
*   -1:卡号不存在，-2:该通道没有被占用
* 说明： 释放通道资源。
******************************************/
Omn_EXPORTS Om_HRESULT Omn_CloseRecord(Om_UINT32 dwBoardNo, Om_UINT32 dwRDPNo);

/******************************************
* 函数名： Omn_PrePlay
* 功能： 注册播放回调函数
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
*           bISAsync:扩展用，须为Om_FALSE
*           pIoCBFun:用于端口视音频数据Buffer交互回调函数指针
*           pMsgCBFun:扩展用，须为Om_NULL
*           pHLBCBFun:扩展用，须为Om_NULL
*           pContext:回调时的应用程序上下文
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 因为每块板卡支持多个播出通道，每个通道都可注册回调函数
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PrePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, Om_BOOL bISAsync
    , Omn_IoCBFuncPtr pIoCBFun, Omn_CallBackFuncPtr pMsgCBFun, Omn_HLBCBFuncPtr pHLBCBFun, Om_PVOID pContext);

/******************************************
* 函数名： Omn_StartPlay
* 功能： 开始播放
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
* 输出参数：psPlayInfo:运行时信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 每块卡每路都可以单独播放
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StartPlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo  *psPlayInfo);

/******************************************
* 函数名： Omn_StopPlay
* 功能： 停止播放
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
* 输出参数：psPlayInfo:运行时信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 每块卡每路都可以单独停止，停止表示卡停止回调，但板卡上的Buffer还要播完，
*   并停留在最后一帧。
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopPlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* 函数名： Omn_StopPlayImmediately
* 功能： 立即停止播出通道的播出
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
* 输出参数：psPlayInfo:运行时信息指针
* 返回值： Om_OK，成功；其它，失败
* 说明：    Omn_StopPlay与Omn_StopPlayImmediately的区别在于，前者会等到板卡播出队列中的所有Buffer都播出完毕后才停
*           止播出；而后者会立即停止播出。
******************************************/
Omn_EXPORTS Om_HRESULT Omn_StopPlayImmediately(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* 函数名： Omn_PausePlay
* 功能： 暂停播放
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
* 输出参数：psPlayInfo:运行时信息指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 各卡各路可以单独暂停。暂停时，底层立即停止回调，同时板卡上的Buffer停留当前硬件播出帧。
*        硬件播出队列中已经打入的Buffer内容还继续保留，下次Start时可继续从当前硬件播出帧位置启动。
******************************************/
Omn_EXPORTS Om_HRESULT Omn_PausePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmn_RunTimeInfo *psPlayInfo);

/******************************************
* 函数名： Omn_Seek
* 功能： Seek视频画面
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
*           psUpdateInfo：Seek画面Buf信息
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 各卡各路都可以单独SEEK，同时Seek永远都是同步的
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Seek(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo, SOmnBufUpdataInfo *psUpdateInfo);

/******************************************
* 函数名： Omn_ClosePlay
* 功能： 关闭通道，并取消注册函数
* 输入参数：dwBoardNo:卡号
*           dwPDPNo:播放数据端口号
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
*   -1:卡号不存在，-2:该通道没有被占用
* 说明： 释放通道资源。
******************************************/
Omn_EXPORTS Om_HRESULT Omn_ClosePlay(Om_UINT32 dwBoardNo, Om_UINT32 dwPDPNo);

/******************************************
* 函数名： Omn_UpdateBuffer
* 功能  ： 对于播出通道来说，该函数告诉板卡该Buffer中数据用于播出 
*          对于采集通道来说，该函数告诉板卡采集的数据传到该Buffer
* 输入参数：dwBoardNo:卡号
*           enumPortType:数据端口类型，表明是RDP还是PDP
*           dwPortNo:端口号
*           psUpdateInfo:要Update的视频/音频信息
* 输出参数：
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_UpdateBuffer(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, SOmnBufUpdataInfo *psUpdateInfo);

/******************************************
* 函数名： Omn_UpdateBuffer_Ex1
* 功能  ： 对于播出通道来说，该函数告诉板卡该Buffer中数据用于播出 
*          对于采集通道来说，该函数告诉板卡采集的数据传到该Buffer
* 输入参数：dwBoardNo:卡号
*           enumPortType:数据端口类型，表明是RDP还是PDP
*           dwPortNo:端口号
*           psUpdateInfo:要Update的视频/音频信息
* 输出参数：
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_UpdateBuffer_Ex1(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, SOmnBufUpdateInfo_Ex1 *psUpdateInfo);


#ifdef __cplusplus
}
#endif

#endif
