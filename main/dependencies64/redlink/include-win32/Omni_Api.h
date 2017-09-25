/*======================================================\
|   Welcome using Ultralink IO Cards. The application |
|   programming interface starts from here              |
\*=====================================================*/

#ifndef _Omn_API_H
#define _Omn_API_H

#include <Omni_TypeDef.h>
#ifdef __cplusplus
extern "C" {
#endif
/******************************************
* 函数名： Omn_Initialize
* 功能： SDK初始化函数
* 输入参数：无
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 应该在调用SDK所有其他函数前必须调用该函数，否则其他函数将报错
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Initialize();

/******************************************
* 函数名： Omn_Release
* 功能： SDK释放函数
* 输入参数：无
* 输出参数：无
* 返回值： Om_OK:正常， 其它：错误
* 说明： 当前进程不使用SDK包时，调用此函数释放SDK占用系统资源
******************************************/
Omn_EXPORTS Om_HRESULT Omn_Release();
#ifdef __cplusplus
}
#endif 

#include "Omni_Api_Config.h"
#include "Omni_Api_Notify.h"
#include "Omni_Api_Query.h"
#include "Omni_Api_StateControlAndBufIO.h"
#include "Omni_Api_Compatible.h"

#endif //_Omn_API_H

