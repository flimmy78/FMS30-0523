/*=======================\
|   板卡事件通知函数集   |
\*======================*/

#ifndef __Omni_API_NOTIFY_H__
#define __Omni_API_NOTIFY_H__
#include <Omni_TypeDef.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* 函数名： Omn_RegisterAlarmCallback
* 功能： 等板卡的警报中断
* 输入参数：dwBoardNo  板卡号
*           pCallBackFun:出现报警时回调函数指针
*           pContext:出现报警时传给回调函数的应用数据指针
* 输出参数：无
* 返回值： Om_OK，成功；其它，失败
******************************************/
Omn_EXPORTS Om_HRESULT Omn_RegisterAlarmCallback(Om_UINT32 dwBoardNo, Omn_AlarmCBFuncPtr pCallBackFun, Om_PVOID pContext);

/******************************************
* 函数名： Omn_RegisterTimerCallback
* 功能： 硬件定时器回调注册函数。RB6暂不支持
* 输入参数：dwBoardNo  板卡号
*           dwTimeDuration 等待的时间间隔，以ms为单位
*           pCallBackFun 定时器时间到时SDK回调的函数指针，设为空表示不用
*           pContext:传给回调函数的应用数据指针
* 输出参数：无
* 返回值： Om_OK，成功；其它，失败
* 说明：    板卡定时器的时钟精度是10ms
******************************************/
Omn_EXPORTS Om_HRESULT Omn_RegisterTimerCallback(Om_UINT32 dwBoardNo, Om_INT32 iTimeDuration, Omn_TimerCBFuncPtr pCallBackFun, Om_PVOID pContext);

/******************************************
* 函数名： Omn_WaitFrameFieldInterrupt
* 功能： 等待帧/场中断到来
* 输入参数：dwBoardNo:卡号
*           enumPortType:SP端口类型类型，表明是ISP还是OSP
*           dwPortNo:SP端口号
*           bFrameInt:要等待的场/帧类型,根据通道的制式而定
*           dwTimeout:等待超时时间,单位是ms,如果为0则立即返回当前场/帧中断计数
* 输出参数：pRetFieldType:当前场的奇偶性
*           pFrameFieldCount:当前帧/场的中断计数
* 返回值： S_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_WaitFrameFieldInterrupt(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo, Om_BOOL bFrameInt
    , Omn_FIELD *pRetFieldType, Om_UINT32 *pFrameFieldCount, Om_UINT32 dwTimeout);
#ifdef __cplusplus
}
#endif
#endif