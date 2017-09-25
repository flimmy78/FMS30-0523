/*========================\
|   板卡信息查询函数集    |
\*=======================*/

#ifndef __Omni_API_QUERY_H__
#define __Omni_API_QUERY_H__
#include "Omni_TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* 函数名： Omn_QueryGlobalInfo
* 功能： 得到SDK版本号，当前板卡数以及各板卡的基本信息
* 输入参数：
* 输出参数：psRBGlobalInfo:存放板卡枚举信息和SDK版本号指针
* 返回值： Om_OK:正常， 其它：错误
* 说明： 
*   
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryGlobalInfo(SOmnGlobalInfo *psRBGlobalInfo);

/******************************************
* 函数名： Omn_QuerySpecInfo()
* 功能： 查询板卡指定信息
* 输入参数：dwBoardNo:卡号
*           enumInfoType:指定信息类型枚举值
*           pSpecInfo:查询参数时需要的其他信息。
*           iIDX:指定信息系列值的索引。板卡名称只有一个，该值为0   
* 输出参数：ppName:指定信息的名称
*           pValue:指定信息类型枚举值
* 返回值： Om_OK:正常， 其它：错误
* 说明： enumInfoType值与pSpecInfo、pValue的类型对应如下
|-----------------------------------------|-----------------------------|------------------------------|
|       enumSpecInfoType                  |       pSpecInfo类型         |         pValue类型           |
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
* 函数名： Omn_QueryPortActivation
* 功能： 查询端口是否可用
* 输入参数：dwBoardNo:卡号
*           enumPortType:SP端口类型
*           dwPortNo:SP端口号
*           psPortParam:参数
* 输出参数：无
* 返回值： Omn_SUCCESS 该端口处于激活态，可用
*          Omn_ERR_FAILED 该端口处于非激活态，不可用
*          Omn_ERR_INVALID_PARAM 该端口的入出属性不可配置
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryPortActivation(Om_UINT32 dwBoardNo, Omn_PORT_TYPE enumPortType, Om_UINT32 dwPortNo);

/******************************************
* 函数名： Omn_QueryMonitorInfo
* 功能： 获取板卡监控信息,如硬件时钟、温度、电压等
* 输入参数：dwBoardNo 板卡号
* 输出参数：psMonitorInfo 板卡状态信息
* 返回值： Om_OK，成功；其它，失败
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryMonitorInfo(Om_UINT32 dwBoardNo, SOmnMonitorInfo *psMonitorInfo);

/******************************************
* 函数名： Omn_QueryLTCValue
* 功能： 获取输入LTC的值
* 输入参数：dwBoardNo:卡号
*           dwInputNo:LTC输入通道号
*           bWaitInterrupt:在获取LTC值前是否等LTC产生中断
* 输出参数：pLTCVlaue:此次所取得的LTC值
* 返回值： S_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryLTCValue(Om_UINT32 dwBoardNo, Om_UINT32 dwInputNo, Om_BOOL bWaitInterrupt, SOmn_LTC_VALUE *pLTCVlaue);

/******************************************
* 函数名： Omn_QueryLTCInputStatus
* 功能： 查询当前LTC输入信号的有效状态
* 输入参数：dwBoardNo:卡号
*           dwInputNo:LTC输入通道号
* 输出参数：pIsValid:当前LTC输入信号是否有效，Om_FALSE:无效，Om_TRUE:有效
* 返回值： S_OK:正常， 其它：错误
* 说明： 
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryLTCInputStatus(Om_UINT32 dwBoardNo, Om_UINT32 dwInputNo, Om_BOOL *pIsValid);

/******************************************
* 函数名： Omn_QueryKeyerProfile()
* 功能： 查询Keyer的资源属性信息
* 输入参数：dwBoardNo:卡号
*           dwKeyerNo：Keyer索引号
* 输出参数：psProfile：Keyer资源属性信息
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryKeyerProfile(Om_UINT32 dwBoardNo, Om_UINT32 dwKeyerNo, SOmnKeyProfile *psProfile);

/******************************************
* 函数名： Omn_QueryGenlockStatus()
* 功能： 查询Genlock时钟中断计数
* 输入参数：dwBoardNo:卡号
*           dwTimeout：等待超时时间，如果为0，则不等中断，直接返回当前Genlock时钟中断计数,单位：毫秒
* 输出参数：pInterruptCount：Genlock时钟中断计数
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryGenlockStatus(Om_UINT32 dwBoardNo, Om_UINT32 *pInterruptCount, Om_UINT32 dwTimeout);

/******************************************
* 函数名： Omn_QueryInputPhaseDiff()
* 功能： 查询输入信号与外锁相信号之间的相位差
* 输入参数：dwBoardNo:卡号
*           dwIspNo：输入信号端口的索引
* 输出参数：pPhaseDiff：输入信号与外锁相信号之间的相位差，单位：微秒
* 返回值： Om_OK:正常， 其它：错误
* 说明：
******************************************/
Omn_EXPORTS Om_HRESULT Omn_QueryInputPhaseDiff(Om_UINT32 dwBoardNo, Om_UINT32 dwIspNo, Om_UINT32 *pPhaseDiff);

#ifdef __cplusplus
}
#endif
#endif
