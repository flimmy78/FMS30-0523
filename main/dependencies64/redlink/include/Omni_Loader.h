#ifndef __Omn_LOADER_H__
#define __Omn_LOADER_H__


#include "Omni_TypeDef.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum OMN_LOADER_RET_E
{
    LOADER_SUCCESS = 0,             //�ɹ�
    LOADER_NO_BOARD,                //δ�ҵ��忨
    LOADER_FILE_CHECKSUM_ERROR,     //�̼��ļ�����У��ʧ��    
    LOADER_FILE_MISMATCH,           //�̼��ļ���忨��ƥ��    

    LOADER_OPER_ERASE_ERROR,        //�̼����£�����ʧ��
    LOADER_OPER_WRITE_ERROR,        //�̼����£�д��ʧ��
    LOADER_OPER_CHECK_ERROR,        //�̼����£�У��ʧ��

    LOADER_RET_MAX
}OMN_LOADER_RET;

typedef enum OMN_LOADER_STAGE_E
{    
    LOADER_IDLE         = 0,    //����
    LOADER_ERASING      = 1,    //�����׶�
    LOADER_WRITING      = 2,    //д��׶�
    LOADER_CHECKING     = 3,    //У��׶�
}OMN_LOADER_STAGE;

typedef struct OMN_LOADER_PROGRESS_T
{
    OMN_LOADER_STAGE stage; //loader�����׶�
    Om_UINT32 dwProgress;   //loader�����׶��µĽ��ȣ���Χ��0-10000
}OMN_LOADER_PROGRESS;

typedef struct OMN_LOADER_FILE_INFO_T
{
    Omn_BOARD_TYPE destType;        //Ŀ��忨����
    Om_UINT32 dwDestBoardVersion;   //Ŀ��忨PCB�汾�ţ�(major<<24)|(minor<<16)|(revision<<8)
    Om_UINT32 dwFirmwareVersion;    //�̼��ļ��汾��(year<<24)|(month<<16)|(date<<8)|(revision��
}OMN_LOADER_FILE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderParseFile�������̼��ļ�
//���������
//in_pFileBuf���̼������ļ�����
//in_dwFileSize���ļ����ݴ�С����λ��Byte
//���������
//out_pFileInfo�����ع̼������ļ���Ϣ
//����ֵ��
//LOADER_SUCCESS���ļ������ɹ�
//LOADER_FILE_CHECKSUM_ERROR���ļ�У��ʧ��
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderParseFile(Om_VOID* in_pFileBuf, Om_UINT32 in_dwFileSize, OMN_LOADER_FILE_INFO* out_pFileInfo);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderInit����ʼ���忨�̼�����ģ��
//���������
//in_dwBoardId����0��ʼ�İ忨ID��
//���������
//��
//����ֵ��
//LOADER_SUCCESS���ɹ�
//LOADER_NO_BOARD��δ�ҵ��忨
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderInit(Om_UINT32 in_dwBoardId);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderStart�������̼��������˺������ûἤ�������ڲ��Ĺ̼������̣߳������첽���ء�֮��
//ͨ��Omn_LoaderCheckProgress������ѯ�̼��������е�״̬������
//���������
//in_dwBoardId����0��ʼ�İ忨ID��
//in_pFileBuf���̼������ļ�����
//in_dwFileSize���ļ����ݴ�С����λ��Byte
//���������
//��
//����ֵ��
//LOADER_SUCCESS���ɹ�
//LOADER_NO_BOARD��δ�ҵ��忨
//LOADER_FILE_CHECKSUM_ERROR���ļ�У��ʧ��
//LOADER_FILE_MISMATCH���ļ���Ŀ��治ƥ�䣬����忨���Ͳ�ƥ�� ���� PCB�汾�Ų�ƥ��
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderStart(Om_UINT32 in_dwBoardId, Om_VOID* in_pFileBuf, Om_UINT32 in_dwFileSize);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderCheckProgress������ѯ�̼��������е�״̬������
//���������
//in_dwBoardId����0��ʼ�İ忨ID��
//���������
//out_pProgress���̼���������
//����ֵ��
//LOADER_SUCCESS���ɹ�
//LOADER_NO_BOARD��δ�ҵ��忨
//LOADER_OPER_ERASE_ERROR����ö�ٶ���
//LOADER_OPER_WRITE_ERROR����ö�ٶ���
//LOADER_OPER_CHECK_ERROR����ö�ٶ���
////////////////////////////////////////////////////////////////////////////////////////////////
Omn_EXPORTS OMN_LOADER_RET Omn_LoaderCheckProgress(Om_UINT32 in_dwBoardId, OMN_LOADER_PROGRESS* out_pProgress);

////////////////////////////////////////////////////////////////////////////////////////////////
//Omn_LoaderCheckProgress���ͷŹ̼�����ģ��
//���������
//in_dwBoardId����0��ʼ�İ忨ID��
//���������
//��
//����ֵ��
//LOADER_SUCCESS���ɹ�
//LOADER_NO_BOARD��δ�ҵ��忨
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

