#ifndef __Omn_LOADER_H__
#define __Omn_LOADER_H__


#include "Omni_TypeDef.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum OMN_LOADER_RET_E
{
    LOADER_SUCCESS = 0,             //成功
    LOADER_NO_BOARD,                //未找到板卡
    LOADER_FILE_CHECKSUM_ERROR,     //固件文件内容校验失败    
    LOADER_FILE_MISMATCH,           //固件文件与板卡不匹配    

    LOADER_OPER_ERASE_ERROR,        //固件更新，擦除失败
    LOADER_OPER_WRITE_ERROR,        //固件更新，写入失败
    LOADER_OPER_CHECK_ERROR,        //固件更新，校验失败

    LOADER_RET_MAX
}OMN_LOADER_RET;

typedef enum OMN_LOADER_STAGE_E
{    
    LOADER_IDLE         = 0,    //闲置
    LOADER_ERASING      = 1,    //擦除阶段
    LOADER_WRITING      = 2,    //写入阶段
    LOADER_CHECKING     = 3,    //校验阶段
}OMN_LOADER_STAGE;

typedef struct OMN_LOADER_PROGRESS_T
{
    OMN_LOADER_STAGE stage; //loader所处阶段
    Om_UINT32 dwProgress;   //loader所处阶段下的进度，范围：0-10000
}OMN_LOADER_PROGRESS;

typedef struct OMN_LOADER_FILE_INFO_T
{
    Omn_BOARD_TYPE destType;        //目标板卡类型
    Om_UINT32 dwDestBoardVersion;   //目标板卡PCB版本号：(major<<24)|(minor<<16)|(revision<<8)
    Om_UINT32 dwFirmwareVersion;    //固件文件版本：(year<<24)|(month<<16)|(date<<8)|(revision）
}OMN_LOADER_FILE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderParseFile：解析固件文件
//输入参数：
//in_pFileBuf，固件升级文件内容
//in_dwFileSize，文件内容大小，单位是Byte
//输出参数：
//out_pFileInfo，返回固件升级文件信息
//返回值：
//LOADER_SUCCESS，文件解析成功
//LOADER_FILE_CHECKSUM_ERROR，文件校验失败
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderParseFile(Om_VOID* in_pFileBuf, Om_UINT32 in_dwFileSize, OMN_LOADER_FILE_INFO* out_pFileInfo);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderInit：初始化板卡固件升级模块
//输入参数：
//in_dwBoardId，从0开始的板卡ID号
//输出参数：
//无
//返回值：
//LOADER_SUCCESS，成功
//LOADER_NO_BOARD，未找到板卡
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderInit(Om_UINT32 in_dwBoardId);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderStart：启动固件升级。此函数调用会激活驱动内部的固件升级线程，并且异步返回。之后，
//通过Omn_LoaderCheckProgress，可轮询固件升级进行的状态、进度
//输入参数：
//in_dwBoardId，从0开始的板卡ID号
//in_pFileBuf，固件升级文件内容
//in_dwFileSize，文件内容大小，单位是Byte
//输出参数：
//无
//返回值：
//LOADER_SUCCESS，成功
//LOADER_NO_BOARD，未找到板卡
//LOADER_FILE_CHECKSUM_ERROR，文件校验失败
//LOADER_FILE_MISMATCH，文件与目标版不匹配，比如板卡类型不匹配 或者 PCB版本号不匹配
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderStart(Om_UINT32 in_dwBoardId, Om_VOID* in_pFileBuf, Om_UINT32 in_dwFileSize);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderCheckProgress：可轮询固件升级进行的状态、进度
//输入参数：
//in_dwBoardId，从0开始的板卡ID号
//输出参数：
//out_pProgress，固件升级进度
//返回值：
//LOADER_SUCCESS，成功
//LOADER_NO_BOARD，未找到板卡
//LOADER_OPER_ERASE_ERROR，见枚举定义
//LOADER_OPER_WRITE_ERROR，见枚举定义
//LOADER_OPER_CHECK_ERROR，见枚举定义
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderCheckProgress(Om_UINT32 in_dwBoardId, OMN_LOADER_PROGRESS* out_pProgress);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderCheckProgress：释放固件升级模块
//输入参数：
//in_dwBoardId，从0开始的板卡ID号
//输出参数：
//无
//返回值：
//LOADER_SUCCESS，成功
//LOADER_NO_BOARD，未找到板卡
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderRelease(Om_UINT32 in_dwBoardId);


#if defined _MSC_VER 
#    if !defined Omni_SDK_EXPORTS    
#        ifndef _NO_Om_PATH_
#            ifdef _WIN64
#                pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win64\\Omni_Loader_Lib.lib")
#            else
#                pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win32\\Omni_Loader_Lib.lib")
#            endif
#        endif
#    endif
#endif

#ifdef __cplusplus
}
#endif

#endif // __Omn_TOOLS_H__

