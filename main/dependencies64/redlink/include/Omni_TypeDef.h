#ifndef _Omn_TYPE_DEF_H
#define _Omn_TYPE_DEF_H
#include "Omni_platform.h"
#include "Omni_VACommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* �忨ϵ������
******************************************/
typedef enum Omn_BOARD_CLASS_E
{
    Omn_BOARDCLASS_UNKNOW = -1,
    Omn_BOARDCLASS_EX0   = 0,
    Omn_BOARDCLASS_EX1   = 1,
    Omn_BOARDCLASS_EX2   = 2,
    Omn_BOARDCLASS_EX3   = 3,
    Omn_BOARDCLASS_EX4   = 4,
    Omn_BOARDCLASS_EX5   = 5
} Omn_BOARD_CLASS;

/******************************************
* �忨����
******************************************/
typedef enum Omn_BOARD_TYPE_E
{
    Omn_BOARDTYPE_UNKNOW    = -1,    
    Omn_BOARDTYPE_CAP500    = 39,   //��Ӧ��CAP-500��
    Omn_BOARDTYPE_CAP600    = 40,   //��Ӧ��CAP-600��
    Omn_BOARDTYPE_EM200     = 41,   //��Ӧ��EditMini-200��
    Omn_BOARDTYPE_CG100     = 42,   //��Ӧ��CG-100��
    Omn_BOARDTYPE_SER400    = 43,   //��Ӧ��Server-400��
    Omn_BOARDTYPE_CAP500K   = 44,   //��Ӧ��CAP-500K��
    Omn_BOARDTYPE_CAP400    = 45,   //��Ӧ��CAP-400��
    Omn_BOARDTYPE_CAP300    = 46,   //��Ӧ��CAP-300��
    Omn_BOARDTYPE_EM100     = 47,   //��Ӧ��EditMini-100��
    Omn_BOARDTYPE_SER400K   = 48,   //��Ӧ��Server-400K��
    Omn_BOARDTYPE_SER100S   = 49,   //��Ӧ��Server-100S��
    Omn_BOARDTYPE_SER100D   = 50,   //��Ӧ��Server-100D��
    Omn_BOARDTYPE_CAP400ASI = 51,   //��Ӧ��CAP-400_A_S_I��
    Omn_BOARDTYPE_EDITPRO   = 52,   //��Ӧ��EditPro��
    //Omn_BOARDTYPE_SER101N   = 53,   //��Ӧ��Server-101N��
    //Omn_BOARDTYPE_CG101     = 54,   //��Ӧ��CG-101��
    Omn_BOARDTYPE_SER400LE  = 55,   //��Ӧ��Server-400LE��
    Omn_BOARDTYPE_SER800    = 56,   //��Ӧ��Server-800��
    //Omn_BOARDTYPE_SER801N   = 57,   //��Ӧ��Server-801N��
    Omn_BOARDTYPE_SER1200   = 58,   //��Ӧ��Server-1200��
    Omn_BOARDTYPE_MAX
} Omn_BOARD_TYPE;

/******************************************
* �ӿ�����
******************************************/
typedef enum Omn_DAUGHTERCARD_TYPE_E
{
    Omn_DAUGHTERCARDTYPE_UNKNOW         = -1,
    Omn_DAUGHTERCARDTYPE_OPAA8180B      = 19,   //��Ӧ��OPAA8180B�ӿ�
    Omn_DAUGHTERCARDTYPE_OPDA8180UTC    = 20,   //��Ӧ��OPDA8180UTC�ӿ�
    Omn_DAUGHTERCARDTYPE_TALLY10        = 21,   //��Ӧ��OPTALLY10�ӿ�
    Omn_DAUGHTERCARDTYPE_OPAA2120       = 22,   //��Ӧ��DEK_OPAA_SUB�ӿ�
    Omn_DAUGHTERCARDTYPE_SER100OPAA     = 23,   //��Ӧ��OPVA0130UH�ӿ�
    Omn_DAUGHTERCARDTYPE_E200OPVA       = 24,   //��Ӧ��EDIT200_OPVA_SUB�ӿ�
    Omn_DAUGHTERCARDTYPE_SER1200SDIOUT  = 25,   //��Ӧ��SER1200_SDIOUT_SUB�ӿ�
    Omn_DAUGHTERCARDTYPE_MAX
} Omn_DAUGHTERCARD_TYPE;

/******************************************
* �����汾��Ϣ
******************************************/
typedef struct SOmnBoardVersionInfo_T
{
    Om_UINT32  dwBiosVersion;     //Firmware�汾��    
    Om_UINT32  dwBoardVersion;    //�忨PCB�汾��
    Om_UINT64  qwBoardSerialNo;   //�忨���к�
    Om_UINT32  dwReseved[9];      //������չ�ã�ȫ0 
} SOmnBoardVersionInfo;

/******************************************
* �ӿ��汾��Ϣ
******************************************/
typedef struct SOmnSubCardInfo_T
{
    Omn_DAUGHTERCARD_TYPE enumCardType;       //�ӿ�����
    Om_UINT32            dwFirmareVersion;   //Firmware�汾��
    Om_UINT32            dwCardVersion;      //�忨PCB�汾��
    Om_UINT64            qwCardSerialNo;     //�忨���к�    
    Om_UINT32            u8Reserved[9];      //������չ�ã�ȫ0
} SOmnSubCardInfo, SOmnDaughterCardInfo;

/******************************************
* �׿���Դ��Ϣ
******************************************/
typedef struct SOmnBoardInfo_T
{
    SOmnBoardVersionInfo  sBoardVersionInfo;         //�����汾��Ϣ
    Omn_BOARD_CLASS       enumBoardClass;            //�忨����
    Omn_BOARD_TYPE        enumBoardType;             //�忨������
    Om_UINT32             dwRecordDataPortNum;       //�ɼ�����ͨ����
    Om_UINT32             dwPlayDataPortNum;         //��������ͨ����
    Om_UINT32             dwInputSignalPortNum;      //�źŲɼ��˿���
    Om_UINT32             dwOutputSignalPortNum;     //�źŲ����˿���
    Om_UINT8              bScalerSupport;            //�忨�Ƿ�֧��Scaler    
    Om_UINT8              u8InterfaceNum;            //�忨֧��Interface����
    Om_UINT8              u8MixerNum;                //�忨֧�ֵ�Ӳ��Mixer����    
    Om_UINT8              u8KeyerNum;                //�忨֧�ֵ�Ӳ��Keyer����
    Om_UINT8              u8Reserved[8];             //������չ�ã�ȫ0
    Om_UINT32             dwDaughterCardNum;         //�ӿ�����
    SOmnSubCardInfo       psDaughterCardInfo[6];     //�ӿ���Ϣ����
} SOmnBoardInfo;

/******************************************
* �������汾��Ϣ
******************************************/
typedef struct SOmnVersionInfo_T
{
    Om_UINT16  wMajorVersion;    //���汾��,��ʮ�����γɽ���UI����
    Om_UINT16  wMinorVersion;    //�ΰ汾��,��ʮ�����γɽ���UI����
    Om_UINT32  dwSvnNo;          //svn��,��ʮ�����γɽ���UI����
    Om_UINT32  dwBuildNo;        //build�汾��,��ʮ�������γɽ���UI����
    Om_UINT32  dwTag;            //�����֧��ǩ
}SOmnVersionInfo;

/******************************************
* SDKȫ����Ϣ
******************************************/
typedef struct SOmnGlobalInfo_T
{
    Om_UINT32        dwBoardNum;         //�忨����
    SOmnBoardInfo     psBoardInfo[4];     //�忨������Ϣ����
    SOmnVersionInfo   sSDKVersion;        //�������汾��Ϣ    
    Om_UINT32        u32Reserved[9];     //������չ�ã�ȫ0
} SOmnGlobalInfo, *PSOmnGlobalInfo;

/******************************************
* ��ѯ�忨֧������ʱ�����Բ�ѯ����
* ����Omn_GetSpecCapInfoʱʹ��
******************************************/
typedef enum Omn_BOARDSPECINFO_TYPE_E
{
    Omn_BOARDSPECINFO_UNKNOW           = -1,
    Omn_BOARDSPECINFO_BOARDNAME        = 0, //�忨��
    Omn_BOARDSPECINFO_VIDEO_STANDARD   = 1, //��Ƶ��ʽ
    Omn_BOARDSPECINFO_GENLOCK          = 2, //����Դ
    Omn_BOARDSPECINFO_VIDEO_SRC        = 3, //��ƵԴ
    Omn_BOARDSPECINFO_AUDIO_SRC        = 4, //��ƵԴ
    Omn_BOARDSPECINFO_COLOR_FMT_INPUT  = 5, //�ɼ���ɫ��ʽ
    Omn_BOARDSPECINFO_COLOR_FMT_OUTPUT = 6, //������ɫ��ʽ
    Omn_BOARDSPECINFO_VIDEO_OUT_TYPE   = 7, //��Ƶ����ź�����
    Omn_BOARDSPECINFO_MAX              = 16 
} Omn_BOARDSPECINFO_TYPE;

/******************************************
* ����Դ����
******************************************/
typedef enum Omn_GENLOCK_SOURCE_E
{
    Omn_GENLOCKSOURCE_UNKNOW          = -1,
    Omn_GENLOCKSOURCE_INTERNAL        = 0, //��ͬ��
    Omn_GENLOCKSOURCE_REFERENCE_IO    = 1, //�������������Reference�ź��ϡ�
                                           //ע�⣬���ô����෽ʽʱ����������ź���Ref�źŲ�ͬ������ѡ��Omn_GENLOCKSOURCE_REFERENCE���෽ʽ������ᵼ�²ɼ������쳣��
    Omn_GENLOCKSOURCE_SDI_IN_0        = 2, //����SDI�����ź�0��
    Omn_GENLOCKSOURCE_SDI_IN_1        = 3, //����SDI�����ź�1��
    Omn_GENLOCKSOURCE_SDI_IN_2        = 4, //����SDI�����ź�2��
    Omn_GENLOCKSOURCE_SDI_IN_3        = 5, //����SDI�����ź�3��
    Omn_GENLOCKSOURCE_ANALOG_IN_0     = 6, //����ģ�������ź�0��
    Omn_GENLOCKSOURCE_REFERENCE       = 7, //�������������Reference�ź��ϣ��������ڸ��Ե������ź���
    Omn_GENLOCKSOURCE_ANALOG_IN_1     = 8, //����ģ�������ź�1��
    Omn_GENLOCKSOURCE_ANALOG_IN_2     = 9, //����ģ�������ź�2��
    Omn_GENLOCKSOURCE_ANALOG_IN_3     = 10, //����ģ�������ź�3��
    Omn_GENLOCKSOURCE_AES_IN_0        = 11, //����AES�����ź�12��
    Omn_GENLOCKSOURCE_AES_IN_1        = 12, //����AES�����ź�34��
    Omn_GENLOCKSOURCE_AES_IN_2        = 13, //����AES�����ź�56��
    Omn_GENLOCKSOURCE_AES_IN_3        = 14, //����AES�����ź�78��
    Omn_GENLOCKSOURCE_AES_IN_0_LOOP   = 15, //����AES�����ź�12��ͬʱ��Ƶ��ͨ
    Omn_GENLOCKSOURCE_CASCADE         = 16  //���ڰ�伶���źſ���
} Omn_GENLOCK_SOURCE;

/******************************************
* ģ���AES/EBU��ʽ��Ƶͨ���ķ���
******************************************/
typedef enum Omn_AES_ANA_CONFIG_E
{
    Omn_AES_ANA_CONFIG_UNKNOW       = -1,
    Omn_AES_ANA_CONFIG_BIND_V0      = 0,  //�źŶ˿�0����ռ��������Ƶ�ӿ�
    Omn_AES_ANA_CONFIG_AUTO         = 1,  //�źŶ˿�ƽ��ռ�������Ƶ�ӿ�
    Omn_AES_ANA_CONFIG_BIND_V1      = 2,  //�źŶ˿�1����ռ��������Ƶ�ӿ�
    Omn_AES_ANA_CONFIG_BIND_V2      = 3,  //�źŶ˿�2����ռ��������Ƶ�ӿ�
    Omn_AES_ANA_CONFIG_BIND_V3      = 4,  //�źŶ˿�3����ռ��������Ƶ�ӿ�
    Omn_AES_ANA_CONFIG_INDEPENDENT  = 16  //��Ƶ��������ͨ��ռ��������Ƶ�˿�
} Omn_AES_ANA_CONFIG;

/******************************************
* ģ����Ƶ�źſ����м���
******************************************/
typedef enum Omn_ANTI_LINE_CRAWL_E
{
    Omn_ANTI_LINE_CRAWL_UNKNOW   = -1,
    Omn_ANTI_LINE_CRAWL_LOW   = 0,        //�ͼ���
    Omn_ANTI_LINE_CRAWL_MIDDLE   = 1,     //�м���
    Omn_ANTI_LINE_CRAWL_HIGH   = 2        //�߼���
} Omn_ANTI_LINE_CRAWL;

/******************************************
* ������ȫ���WatchDog������Ϣ
******************************************/
typedef struct SOmnBoardWatchDogInfo_T
{
    Om_BOOL    EnableHW_Level;  //Ӳ����WatchDog�Ƿ�����
    Om_BOOL    EnableOS_Level;  //OS��WatchDog�Ƿ�����
    Om_BOOL    EnableApp_Level;  //Ӧ�ü�WatchDog�Ƿ�����
} SOmnBoardWatchDogInfo;

/******************************************
* �忨Interface�ӿڷ�������
******************************************/
typedef struct SOmnBoardInterfaceInfo_T
{
    Om_UINT32  InterfaceDirection[32];  //��i��BNC�ӿڵķ���������0�������1
} SOmnBoardInterfaceInfo;

/******************************************
* �忨��������Ϣ
******************************************/
typedef struct SOmnBoardBasePara_T
{    
    Omn_GENLOCK_SOURCE    enmuGenlockSource;   //����Դ    
    Omn_AES_ANA_CONFIG    enmuOutAudioConfig;  //ģ���AES/EBU�������OSP��ģʽ
    Omn_ANTI_LINE_CRAWL   enmuAntiLineCrawl;   //ģ����Ƶ�źſ����м���
    Om_UINT32            dwMonitorCh;         //����ͨ���ţ�0:0~1, 1:2~3, 2:4~5, 3:6~7 ... 7:14~15
    Om_INT32             nMonitorVolume;      //������������-118~9��-118��ʾ����
    Om_UINT32            dwMicVolume;         //��˷�������������0~120��0ΪĬ��ֵ
    SOmnBoardWatchDogInfo sBoardWatchDogInfo;  //�忨/������WatchDog��Ϣ
    Om_UINT32            u32Reserved[9];      //������չ�ã�ȫ0
} SOmnBoardBasePara;

/******************************************
* �忨��������Ϣö��ֵ����Omn_GetBoardParamEx
* ��Omn_SetBoardParamExʱʹ��
******************************************/
typedef enum Omn_BOARDCONFIG_TYPE_E
{
    Omn_BOARDCONFIGTYPE_UNKNOW                      = -1,  
    Omn_BOARDCONFIGTYPE_MAIN_STANDARD			    = 0,	//�ݲ�֧��
    Omn_BOARDCONFIGTYPE_GENLOCK                     = 1,    //GET/SET ����Դ��ʹ��Omn_GENLOCK_SOURCE *���Ͳ���
    Omn_BOARDCONFIGTYPE_IN_AES_ANA_CONFIG		    = 2,	//�ݲ�֧��
    Omn_BOARDCONFIGTYPE_OUT_AES_ANA_CONFIG          = 3,    //GET/SET ģ���AES/EBU����������ͨ����ģʽ��ʹ��Omn_AES_ANA_CONFIG *���Ͳ���
    Omn_BOARDCONFIGTYPE_MONITOR_SELECT              = 4,    //GET/SET ����ͨ���ţ�ʹ��Om_UINT32 *���Ͳ�����0:0~1, 1:2~3, 2:4~5, 3:6~7 ... 7:14~15
    Omn_BOARDCONFIGTYPE_MONITOR_VOLUME              = 5,    //GET/SET ����������ʹ��Om_INT32 *���Ͳ�������-118~0��-118��ʾ����
    Omn_BOARDCONFIGTYPE_MIC_LINEIN_VOLUME           = 6,    //GET/SET ��˷�/LINEIN��������,ʹ��Om_UINT32 *���Ͳ�������Χ��0~120
    Omn_BOARDCONFIGTYPE_ANTI_LINECRAWL              = 7,    //GET/SET �����У�ʹ��Omn_ANTI_LINE_CRAWL *���Ͳ���
    Omn_BOARDCONFIGTYPE_TALLY                       = 8,    //GET/SET Tally��ʹ��SOmnTallyInfo *���Ͳ���
    Omn_BOARDCONFIGTYPE_WATCHDOG                    = 9,    //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_INTERFACE                   = 10,   //GET/SET interface�������,ʹ��SOmnBoardInterfaceInfo *���Ͳ���
    Omn_BOARDCONFIGTYPE_3D_TRANS                    = 11,   //GET/SET 3D��Ƶ�Ĵ��书�ܣ�ʹ��SOmn3DTrans *���Ͳ���
    Omn_BOARDCONFIGTYPE_3G_LEVELB			        = 12,	//�ݲ�֧��
    Omn_BOARDCONFIGTYPE_INPUT_HPHASE                = 13,	//�ݲ�֧��
    Omn_BOARDCONFIGTYPE_VANC_TRANS                  = 14,   //GET/SET ָ��DP�˿ڵ�VANC���书�ܣ�ʹ��SOmn_VANC_TRANS *���Ͳ���
    Omn_BOARDCONFIGTYPE_VANC_INFO_CHECK             = 15,   //GET ָ��DP�˿ڵ�VANC֧�������ʹ��SOmn_VANC_INFO *���Ͳ���    
    Omn_BOARDCONFIGTYPE_SIGNAL_ADAPTATION           = 16,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_MULTICHANNEL_TRANS          = 17,   //GET/SET ��ͬ��ͬ���ɼ�ģʽ��ʹ��SOmnMultiChannelTrans *���Ͳ���    
    Omn_BOARDCONFIGTYPE_HDMI_OUT_SIG_CLR            = 18,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_HDMI_IN_SIG_CLR             = 19,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_LINEIN_OR_MICIN             = 20,   //GET/SET LineIn��MicIn��ʹ��Om_UINT32*���ݲ�����0ΪLineIN��1ΪMicIN
    Omn_BOARDCONFIGTYPE_MIC_VOLUME2                 = 21,   //GET/SET Mic������ʹ��SOmn_MIC_VOLUME*���ݲ���
    Omn_BOARDCONFIGTYPE_MIC_48V                     = 22,   //GET/SET Mic�Ƿ�ʹ��48V�����Դ��ʹ��SOmn_MIC_48V*���ݲ���
    Omn_BOARDCONFIGTYPE_G_OVER_BG_DELAY             = 23,   //GET/SET ���ӱ���ʱ�ı����ӳ�֡��
    Omn_BOARDCONFIGTYPE_SDI_OUT_REF_SWITCH          = 24,   //GET/SET EditPro�����ڲ����ӿ�ʱ��SDI OUT2�����ó�Ref in��ʹ��Om_UINT32 *����
                                                            //������0��ʾSDI Out��1��ʾRef In
    Omn_BOARDCONFIGTYPE_AES_LTC_SWITCH              = 25,   //GET/SET EditPro��������EDIT200_OPVA_SUB�ӿ�AES In/Out 7/8������LTC In/Out��
                                                            //�л�ѡ��ʹ��Om_UINT32 *���Ͳ�����0��ʾΪAES In/Out 7/8������1��ʾΪLTC In/Out
    Omn_BOARDCONFIGTYPE_HP_LINEOUT_SWITCH           = 26,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_APP_PRIVATE_INFO            = 27,   //GET/SET �忨Flash�ϴ洢��Ӧ��˽�м�����Ϣ��ʹ��Om_UINT8[16]���ݲ���
    Omn_BOARDCONFIGTYPE_HDMI_OUT_AUD_CHNS           = 28,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_LTC_OUT_CONFIG              = 29,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_LTC_IN_CONFIG               = 30,   //�ݲ�֧��
    Omn_BOARDCONFIGTYPE_ISP_KEYMODE_CONFIG          = 31,   //GET/SET ����KeyMode�ɼ������ã�ʹ��SOmnKeyModeConfig*���Ͳ���
    Omn_BOARDCONFIGTYPE_OSP_KEYMODE_CONFIG          = 32,   //GET/SET ����KeyMode���������ã�ʹ��SOmnKeyModeConfig*���Ͳ���
    Omn_BOARDCONFIGTYPE_LTC_PLAYSOURCE              = 33,   //GET/SET ����ģ��LTC�����Դ����һ·OSP��ʹ��SOmnLTCPlaySource*���Ͳ���
    Omn_BOARDCONFIGTYPE_PORTPAIR23_OUT_CONFIG       = 34,   //GET/SET ����Server-400K������������KeyMode����ʱ�ڶ���KeyMode��
                                                            //������ݣ�ʹ��Om_UINT32 *���Ͳ�����0�������ǰKeyMode�������ݣ� 1�����
                                                            //һ��KeyMode����������ͬ��2�������һ��KeyMode�������ݵ��±任
    Omn_BOARDCONFIGTYPE_IO_WORK_MODE                = 35,   //GET/SET��ֻ������Server-800_K����ʹ��Omn_IO_WORK_MODE *���Ͳ���
    Omn_BOARDCONFIGTYPE_MAX     
} Omn_BOARDCONFIG_TYPE;

/******************************************
* �忨����Դö��ֵ
******************************************/
typedef enum Omn_ALARM_SOURCE_E
{
    Omn_ALARM_UNKNOWN           = 0,

    Omn_ALARM_REFERENCE_LOST    = (0x01<<0),  //�������źŶ�ʧ
                                  
    Omn_ALARM_INPUT0_LOST       = (0x01<<1),  //�����ź�0���źŶ�ʧ 
    Omn_ALARM_INPUT1_LOST       = (0x01<<2),  //�����ź�1���źŶ�ʧ
    Omn_ALARM_INPUT2_LOST       = (0x01<<3),  //�����ź�2���źŶ�ʧ
    Omn_ALARM_INPUT3_LOST       = (0x01<<4),  //�����ź�3���źŶ�ʧ
    Omn_ALARM_INPUT4_LOST       = (0x01<<5),  //�����ź�4���źŶ�ʧ
    Omn_ALARM_INPUT5_LOST       = (0x01<<6),  //�����ź�5���źŶ�ʧ
    Omn_ALARM_INPUT6_LOST       = (0x01<<7),  //�����ź�6���źŶ�ʧ
    Omn_ALARM_INPUT7_LOST       = (0x01<<8),  //�����ź�7���źŶ�ʧ

    Omn_ALARM_INPUT0_SIGNAL_ERR = (0x01<<9),  //�����ź�0���ź���ʽ���趨���� 
    Omn_ALARM_INPUT1_SIGNAL_ERR = (0x01<<10), //�����ź�1���ź���ʽ���趨����
    Omn_ALARM_INPUT2_SIGNAL_ERR = (0x01<<11), //�����ź�2���ź���ʽ���趨����
    Omn_ALARM_INPUT3_SIGNAL_ERR = (0x01<<12), //�����ź�3���ź���ʽ���趨����
    Omn_ALARM_INPUT4_SIGNAL_ERR = (0x01<<13), //�����ź�4���ź���ʽ���趨����
    Omn_ALARM_INPUT5_SIGNAL_ERR = (0x01<<14), //�����ź�5���ź���ʽ���趨����
    Omn_ALARM_INPUT6_SIGNAL_ERR = (0x01<<15), //�����ź�6���ź���ʽ���趨����
    Omn_ALARM_INPUT7_SIGNAL_ERR = (0x01<<16), //�����ź�7���ź���ʽ���趨����

    Omn_ALARM_CH1_DIE           = (0x01<<17), //�ݲ�֧��
    Omn_ALARM_CH2_DIE           = (0x01<<18), //�ݲ�֧��

    Omn_ALARM_TEMPERAT          = (0x01<<19), //�¶ȳ���85�ȱ���
    Omn_ALARM_VOLTGAGE          = (0x01<<20),  //�ݲ�֧��

    Omn_ALARM_INPUT0_UNSYNC     = (0x01<<21), //�����ź�0�������಻ͬ��
    Omn_ALARM_INPUT1_UNSYNC     = (0x01<<22), //�����ź�1�������಻ͬ��
    Omn_ALARM_INPUT2_UNSYNC     = (0x01<<23), //�����ź�2�������಻ͬ��
    Omn_ALARM_INPUT3_UNSYNC     = (0x01<<24), //�����ź�3�������಻ͬ��

    Omn_ALARM_GENLOCK_CHANGE    = (0x01<<31)  //����״̬����ʽ�ı�
} Omn_ALARM_SOURCE;

#define Omn_ALARM_GENLOCK_LOST Omn_ALARM_REFERENCE_LOST

#define Omn_ALARM_SDI0_LOST    Omn_ALARM_INPUT0_LOST 
#define Omn_ALARM_SDI1_LOST    Omn_ALARM_INPUT1_LOST 
#define Omn_ALARM_SDI2_LOST    Omn_ALARM_INPUT2_LOST 
#define Omn_ALARM_SDI3_LOST    Omn_ALARM_INPUT3_LOST 
#define Omn_ALARM_SDI4_LOST    Omn_ALARM_INPUT4_LOST 
#define Omn_ALARM_SDI5_LOST    Omn_ALARM_INPUT5_LOST 
#define Omn_ALARM_SDI6_LOST    Omn_ALARM_INPUT6_LOST 
#define Omn_ALARM_SDI7_LOST    Omn_ALARM_INPUT7_LOST 

#define Omn_ALARM_SDI0_SIGNAL_ERR  Omn_ALARM_INPUT0_SIGNAL_ERR 
#define Omn_ALARM_SDI1_SIGNAL_ERR  Omn_ALARM_INPUT1_SIGNAL_ERR 
#define Omn_ALARM_SDI2_SIGNAL_ERR  Omn_ALARM_INPUT2_SIGNAL_ERR 
#define Omn_ALARM_SDI3_SIGNAL_ERR  Omn_ALARM_INPUT3_SIGNAL_ERR 
#define Omn_ALARM_SDI4_SIGNAL_ERR  Omn_ALARM_INPUT4_SIGNAL_ERR 
#define Omn_ALARM_SDI5_SIGNAL_ERR  Omn_ALARM_INPUT5_SIGNAL_ERR 
#define Omn_ALARM_SDI6_SIGNAL_ERR  Omn_ALARM_INPUT6_SIGNAL_ERR 
#define Omn_ALARM_SDI7_SIGNAL_ERR  Omn_ALARM_INPUT7_SIGNAL_ERR 

/******************************************
* �忨����Դ״̬ 
******************************************/
typedef enum Omn_GENLOCK_STATUS_E
{
    Omn_GENLOCK_STATUS_UNKNOW     = -1,
    Omn_GENLOCK_STATUS_FREE       = 0, //������״̬
    Omn_GENLOCK_STATUS_LOST       = 1, //����Դ��ʧ
    Omn_GENLOCK_STATUS_LOCKING    = 2, //����Դ��������������
    Omn_GENLOCK_STATUS_LOCKED     = 3, //����Դ��������״̬
    Omn_GENLOCK_STATUS_MAX        = 4 
} Omn_GENLOCK_STATUS;

/******************************************
* �忨�����ص�������Ϣ
******************************************/
typedef struct SOmnAlarmInfo_T 
{
     Om_UINT32              dwAlarmSrcMask;             //���ر���Դ��Ϣ 
     Omn_VIDEO_STANDARD     enumInputVideoStandard[32]; //����4·������Ƶ�źŵ���ʽ��Ϣ
     Omn_GENLOCK_STATUS     enumLastGenLockStatus;      //����״̬�仯ǰ������״̬0:free,1:Lost,2:locking,3:Locked
     Omn_VIDEO_STANDARD     enumLastGenLockStandard;    //����״̬�仯ǰ��������ʽ
     Omn_GENLOCK_STATUS     enumCurrentGenLockStatus;   //��ǰ����״̬�仯�������״̬0:free,1:Lost,2:locking,3:Locked
     Omn_VIDEO_STANDARD     enumCurrentGenLockStandard; //��ǰ����״̬�仯���������ʽ
     Om_UINT32              dwReserved[25];             //������չ�ã�ȫ0
} SOmnAlarmInfo;

/******************************************
* �忨״̬��ѯ���룬��SOmnMonitorInfo�ṹ
* ��dwMonitorMask��Ա��ʹ��
******************************************/
#define Omn_MONITOR_MASK_INPUTVIDEOSTANDARD (0x01)    //��ѯ��ǰ�����źŵ���ʽ��Ϣ
#define Omn_MONITOR_MASK_TEMPERAT           (0x02)    //��ѯ�忨�¶�״̬
#define Omn_MONITOR_MASK_FUNSPEED           (0x04)    //��ѯ�忨����ת�٣���֧��
#define Omn_MONITOR_MASK_TIMETICK           (0x08)    //��ѯ�忨ȫ��ʱ��
#define Omn_MONITOR_MASK_GENLOCKSTATUS      (0x10)    //��ѯ�忨����Դ״̬
#define Omn_MONITOR_MASK_GENLOCKSTANDARD    (0x20)    //��ѯ�忨����Դ��ʽ

/******************************************
* Ӳ��״̬��Ϣ 
******************************************/
typedef struct SOmnMonitorInfo_T 
{
    Om_UINT32            dwMonitorMask;              //��ѯ����
    Omn_VIDEO_STANDARD    enumInputVideoStandard[32]; //��ǰ0-31·�����źŵ���ʽ,����OmnVIDEOSTANDARD_UNKNOW��ʾISPδ�����ź�
    Om_UINT32            dwTemperature;              //�����¶ȵ�λΪ���϶�
    Om_UINT32            dwFunSpeed;                 //���ص�λΪת/���ӣ���֧��
    Om_UINT64            qwHwTimeTicks;              //���ص�λΪ100ns
    Omn_GENLOCK_STATUS   enumGenLockStatus;          //����״̬0:free,1:Lost,2:locking,3:Locked
    Omn_VIDEO_STANDARD   enumGenLockStandard;        //������ʽ���忨�Զ�ʶ��
    Om_UINT32            Reserved[9];                //������չ�ã�ȫ0
} SOmnMonitorInfo,*PSOmnMonitorInfo;

/****************************************** 
* I/O���ù���ģʽ
******************************************/
typedef enum Omn_IO_WORK_MODE_E
{
    Omn_IO_WORKMODE_UNKNOWN         = -1,
    Omn_IO_WORKMODE_8In0Out         = 0, //8��0��
    Omn_IO_WORKMODE_7In1Out         = 1, //7��1��
    Omn_IO_WORKMODE_6In2Out         = 2, //6��2��
    Omn_IO_WORKMODE_5In3Out         = 3, //5��3��
    Omn_IO_WORKMODE_4In4Out         = 4, //4��4��//�������Server-800��
    Omn_IO_WORKMODE_8In4Out         = 5, //8��4��//�������Server-1200��
    Omn_IO_WORKMODE_7In5Out         = 6, //7��5��
    Omn_IO_WORKMODE_6In6Out         = 7, //6��6��
    Omn_IO_WORKMODE_5In7Out         = 8, //5��7��
    Omn_IO_WORKMODE_4In8Out         = 9  //4��8��
}Omn_IO_WORK_MODE;

/****************************************** 
* PORT����
******************************************/
typedef enum Omn_PORT_TYPE_E
{
    Omn_PORTTYPE_UNKNOW           = -1,
    Omn_PORTTYPE_RECORD_DATA      = 0, //�ɼ����ݶ˿ڣ�RDP��
    Omn_PORTTYPE_PLAY_DATA        = 1, //�������ݶ˿ڣ�PDP��
    Omn_PORTTYPE_SIGNAL_INPUT     = 2, //�����źŶ˿ڣ�ISP��
    Omn_PORTTYPE_SIGNAL_OUTPUT    = 3, //����źŶ˿ڣ�OSP��
} Omn_PORT_TYPE;

/****************************************** 
* ������
******************************************/
typedef enum Omn_STREAM_TYPE_E
{
    Omn_STREAM_UNKNOW             = -1,
    Omn_STREAM_RECORD_GRAPHICS    = 0,    //RDP��ͼ����
    Omn_STREAM_RECORD_KEY         = 1,    //RDP��Key��
    Omn_STREAM_PLAY_GRAPHICS      = 2,    //PDP��ͼ����
    Omn_STREAM_PLAY_KEY           = 3,    //PDP��Key��
    Omn_STREAM_SIGNAL_IN          = 4,    //ISP��������
    Omn_STREAM_SIGNAL_OUT         = 6,    //OSP�������
    Omn_STREAM_MIXER_GRAPHICS     = 10,   //Mixer�����ͼ����
    Omn_STREAM_MIXER_KEY          = 11    //Mixer�����Key��
} Omn_STREAM_TYPE;

/****************************************** 
* ��������Ϣ�����ݽṹ
******************************************/
typedef struct SOmnStreamInfo_T
{
    Omn_STREAM_TYPE   enumStreamType;     //������
    Om_UINT32        dwStreamSourceNo;   //�����(�������˿ڱ��һ��)
} SOmnStreamInfo;

/******************************************
* �˿�������Ϣ
******************************************/
typedef struct SOmnPortDesc_T
{
    Omn_PORT_TYPE enumPortType;//�˿�����
    Om_UINT32    dwPortNo;    //�˿ڱ��
}SOmnPortDesc;

/******************************************
* SDI��Ƕ��Ƶ���÷�ʽ
* ��Omn_SetAudioEmbeddedChannel��Omn_SetAudioOutputConfig���
******************************************/
typedef enum Omn_EMBEDDEDAUDIO_CONFIG_E
{
    Omn_EMBEDDEDAUDIO_CONFIG_ALL  = 0, //Audio channel 0-11 will be embedded in the SDI.
    Omn_EMBEDDEDAUDIO_CONFIG_0_11 = 1, //Audio channel 0-11 will be embedded in the SDI.
    Omn_EMBEDDEDAUDIO_CONFIG_0_7  = 2, //Audio channel 0-7 will be embedded in the SDI.
    Omn_EMBEDDEDAUDIO_CONFIG_0_3  = 3, //Audio channel 0-3 will be embedded in the SDI
    Omn_EMBEDDEDAUDIO_CONFIG_NONE = 4, //No audio will be embedded in the SDI.
    Omn_EMBEDDEDAUDIO_CONFIG_MAX
} Omn_EMBEDDEDAUDIO_CONFIG;

/******************************************
* ����NTSC���·����źŻ�����׼�� CAV��Component Analog Video����д
******************************************/
typedef enum Omn_CAV_STANDARD_E
{
    Omn_CAV_STANDARD_UNKNOW           = -1,
    Omn_CAV_STANDARD_SMPTE            = 0, //SMPTE/EBU N10��׼
    Omn_CAV_STANDARD_NTSC_BETACAM     = 1, //BETACAM��׼
    Omn_CAV_STANDARD_MII              = 2  //MII��׼
} Omn_CAV_STANDARD;

/******************************************
* ����NTSC���ºڵ�ƽ�ķ���
******************************************/
typedef enum Omn_VIDEO_BLACK_LEVEL_E
{
    Omn_VIDEO_BLACK_LEVEL_UNKNOW  = -1,
    Omn_VIDEO_PEDESTAL_OFF        = 0, //û��7.5 IRE��̨��
    Omn_VIDEO_PESESTAL_ON         = 1  //��7.5 IRE��̨��
} Omn_VIDEO_BLACK_LEVEL;

/******************************************
* ģ����Ƶ�źŵ�ƽ
******************************************/
typedef enum Omn_AUDIO_FULL_LEVEL_E
{
    Omn_AUDIO_FULL_LEVEL_UNKNOW   = -1,
    Omn_AUDIO_FULL_LEVEL_24DB     = 0, //��Ƶ�����ȵ�ƽΪ24DB
    Omn_AUDIO_FULL_LEVEL_22DB     = 1  //��Ƶ�����ȵ�ƽΪ22DB
} Omn_AUDIO_FULL_LEVEL;

/******************************************
* Scaler������Ϣ
******************************************/
typedef enum  Omn_UPDOWN_CROSS_CONVERT_MODE_E
{
    Omn_UPDOWN_CROSS_CONVERT_MODE_UNKNOWN       = -1,
    Omn_UPDOWN_CROSS_CONVERT_MODE_1080I_TO_PAL  = 0x00,   //1080i50 -> PAL
    Omn_UPDOWN_CROSS_CONVERT_MODE_1080I_TO_NTSC = 0x01,   //1080i59 -> NTSC
    Omn_UPDOWN_CROSS_CONVERT_MODE_1080I_TO_720P = 0x02,   //1080i50 -> 720p50, 1080i59 -> 720p59
    Omn_UPDOWN_CROSS_CONVERT_MODE_720P_TO_PAL   = 0x04,   //720p50 -> PAL
    Omn_UPDOWN_CROSS_CONVERT_MODE_720P_TO_NTSC  = 0x05,   //720p59 -> NTSC
    Omn_UPDOWN_CROSS_CONVERT_MODE_PAL_TO_1080I  = 0x10,   //PAL -> 1080i50
    Omn_UPDOWN_CROSS_CONVERT_MODE_NTSC_TO_1080I = 0x11,   //NTSC -> 1080i59
    Omn_UPDOWN_CROSS_CONVERT_MODE_PAL_TO_720P   = 0x14,   //PAL -> 720p50
    Omn_UPDOWN_CROSS_CONVERT_MODE_NTSC_TO_720P  = 0x15,   //NTSC -> 720p59
    Omn_UPDOWN_CROSS_CONVERT_MODE_USERDEFINE    = 0x1F,   //user define
    Omn_UPDOWN_CROSS_CONVERT_MODE_MAX           = 0x20    //standard max  
} Omn_UPDOWN_CROSS_CONVERT_MODE;

typedef enum  Omn_SCALE_DEINTERLAC_TYPE_E
{
    Omn_SCALE_DEINTERLAC_DISABLE = 0, //����Deinterlacing
    Omn_SCALE_DEINTERLAC_ENABLE = 1   //��Deinterlacing
} Omn_SCALE_DEINTERLAC_TYPE;

typedef struct SOmnUpDownCrossConvertParam_T
{
    OmnVIDEO_SCALE_TYPE      enumScaleType;          //���±任ʹ�õı任���ͣ���ӦOmnVIDEO_SCALE_TYPE�е�ö��ֵ
    Omn_SCALE_DEINTERLAC_TYPE enumDeinterlacType;     //���±仯ʹ��Deinterlace���� 0��������1����
    OmnCOLORSPACE_CONVERT    enumColorSpaceConvert;  //���±仯ʹ����ɫ�ռ�ת������ 0��������ɫ�ռ�ת����1��601->709ת����2��709->601ת��
    Om_UINT32                Reserved[9];            //������չ�ã�ȫ0
} SOmnUpDownCrossConvertParam;

/******************************************
* ISP��������Ϣ
******************************************/
typedef struct SOmnInputSignalPortParam_T
{
    Omn_VIDEO_STANDARD        enumVideoStandard;    //�˿���ʽ
    Om_UINT32                 dwVideoClipFlag;      //��Ƶ�޷���־
    Omn_VIDEO_SIGNAL_TYPE     enumVideoSigType;     //��ƵԴ
    Omn_AUDIO_SIGNAL_TYPE     enumAudioSigType;     //��ƵԴ
    Omn_AUDIO_FULL_LEVEL      enumAudioLevel;       //ģ����Ƶ����ƽ���ã��ݲ�֧��
    Omn_EMBEDDEDAUDIO_CONFIG  enumEmbeddedAudioCfg; //SDI�ź�Ƕ����Ƶ��ͨ�����ã��ݲ�֧��
    Omn_CAV_STANDARD          enumCavStd;           //CAV���ã�Ntsc��ʽ��ʹ�ã��ݲ�֧��
    Omn_VIDEO_BLACK_LEVEL     enumVideoBlackLevel;  //�ڵ�ƽ���ã�Ntsc��ʽ��ʹ�ã��ݲ�֧��
    Om_BOOL                   bEnableDeinterlace;   //�Ƿ�Ը��вɼ��źŽ���ȥ��֯������Server-400K֧��
    Om_BOOL                   bEnableKeyLumaUpscale;//�����ź����ȵķ�Χ��16~235������0~255����Server-400K֧��
    Om_UINT32                 Reserved[7];          //������չ�ã�ȫ0
} SOmnInputSignalPortParam;

/******************************************
* OSP��������Ϣ
******************************************/
typedef struct SOmnOutputSignalPortParam_T
{
    Omn_VIDEO_STANDARD        enumVideoStandard;        //�˿���ʽ
    Om_UINT32                 dwVideoClipFlag;          //��Ƶ�޷���־
    Omn_VIDEO_SIGNAL_TYPE     enumVideoSigType;         //ģ����Ƶ��������ã��ݲ�֧��
    Om_INT32                  dwHrznPhase;              //OSP������λ
    Om_INT32                  dwVrtclPhase;             //OSP�ĳ���λ����
    Om_DOUBLE                 dSubCarrierPhase;         //���ز���λ���ݲ�֧��
    Omn_AUDIO_FULL_LEVEL      enumAudioLevel;           //ģ����Ƶ����ƽ���ã��ݲ�֧��
    Omn_EMBEDDEDAUDIO_CONFIG  enumEmbeddedAudioCfg;     //SDI�ź�Ƕ����Ƶ��ͨ�����ã��ݲ�֧��
    Omn_CAV_STANDARD          enumCavStd;               //CAV���ã�Ntsc��ʽ��ʹ�ã��ݲ�֧��
    Omn_VIDEO_BLACK_LEVEL     enumVideoBlackLevel;      //�ڵ�ƽ���ã�Ntsc��ʽ��ʹ�ã��ݲ�֧��
    SOmnStreamInfo            sExecptionLoopBackSource; //Watchdog����ʱ�Ļ�ͨ���ã��ݲ�֧��
    Om_INT32                  nKeyPhase;                //OSP�ļ���λ��ֻ��Server-400��ʹ��
    Om_BOOL                   bEnableKeyLumaDownscale;  //�����ź����ȵķ�Χ��0~255��С��16~235����Server-400K֧��
    Om_UINT32                 Reserved[7];              //������չ�ã�ȫ0
} SOmnOutputSignalPortParam;

/******************************************
* RDP��������Ϣ
******************************************/
typedef struct SOmnRecordDataPortParam_T
{
    Omn_VIDEO_STANDARD    enumVideoStandard;  //�˿���ʽ
    Omn_COLOR_FORMAT      enumColorFormat;    //��ɫ��ʽ
    SOmnAudioMediaInfo    enumAudioMediaInfo; //��Ƶ������Ϣ���ݲ�֧��
    Om_UINT32             dwFrameBufferAmount;//�ɼ����еĳ���
    Om_UINT32             Reserved[9];        //������չ�ã�ȫ0
} SOmnRecordDataPortParam;

/******************************************
* PDP��������Ϣ
******************************************/
typedef struct SOmnPlayDataPortParam_T
{
    Omn_VIDEO_STANDARD    enumVideoStandard;      //�˿���ʽ
    Omn_COLOR_FORMAT      enumColorFormat;        //��ɫ��ʽ
    SOmnAudioMediaInfo    enumAudioMediaInfo;     //��Ƶ������Ϣ���ݲ�֧��
    Om_UINT32             dwFrameBufferAmount;    //�������еĳ���
    Om_UINT32             Reserved[9];            //������չ�ã�ȫ0
} SOmnPlayDataPortParam;

/******************************************
* Mixer��·������Ƶ֮��Ĺ�ϵ
******************************************/
typedef enum Omn_MIXER_MODE_E
{
    Omn_MIXER_UNKNOWN         = -1,
    Omn_BYPASS_INPUTA         = 0, //ֱͨA·������Ƶ�ź�
    Omn_BYPASS_INPUTB         = 1, //ֱͨB·������Ƶ�ź�
    Omn_BYPASS_BLACK          = 2, //ֱͨ�ڳ���Ƶ�ź�
    Omn_INPUTA_OVER_BLACK     = 3, //A·������Ƶ�źŵ��ںڳ���
    Omn_INPUTB_OVER_BLACK     = 4, //B·������Ƶ�źŵ��ںڳ���
    Omn_INPUTA_OVER_INPUTB    = 5, //A·������Ƶ(ͼ��+Key)����B·��Ƶ(ͼ��)��,���A·����Key�ź�
    Omn_MIXER_MODE_UNKNOWN1   = 6, //δ������
    Omn_INPUTA_MIXER_INPUTB   = 7, //A·������Ƶ(ͼ��+Key)����B·��Ƶ(ͼ��+Key)��,�����·����Ļ��Key�ź�
    Omn_MIXER_MODE_UNKNOWN2   = 8  //δ������
} Omn_MIXER_MODE;

/******************************************
* Mixer��·������Ƶ֮��Ĺ�ϵ
******************************************/
typedef enum Omn_MIXER_AUDIO_MODE_E
{
    Omn_MIXER_AUDIO_UNKNOWN   = -1,
    Omn_BYPASS_AUDIO_INPUTA   = 0, //���InputA��ص���Ƶ
    Omn_BYPASS_AUDIO_INPUTB   = 1, //���InputB��ص���Ƶ
    Omn_MIXER_AUDIO_UNKNOWN2  = 2  //δ������
} Omn_MIXER_AUDIO_MODE;

/******************************************
* Mixer�����ò���
******************************************/
typedef struct SOmnMixerCfg_T
{
    Omn_MIXER_MODE        enumMixerMode;             //��ƵMixerģʽ
    Omn_MIXER_AUDIO_MODE  enumMixerAudioMode;        //��Ƶѡ��ģʽ
    SOmnStreamInfo        sInputAGraphicsSourceInfo; //Mixer����A��ͼ����������Դ
    SOmnStreamInfo        sInputAKeySourceInfo;      //Mixer����A��Key��������Դ
    SOmnStreamInfo        sInputBGraphicsSourceInfo; //Mixer����B��ͼ����������Դ
    SOmnStreamInfo        sInputBKeySourceInfo;      //Mixer����B��Key��������Դ    
} SOmnMixerCfg, SOmnMixerParam;

/******************************************
* �������ò�������ƵԴ�ֱ��Ӧ��ƵMixer���
* ����ƵԴ
******************************************/
typedef struct SOmnAudioMixerCfg_T
{
    Om_BOOL         bEnableAudioMixer;     //�Ƿ�ʹ�ܻ�������
    Om_UINT32       dwInputAVolume[16];    //��ƵMixer����A��Ӧ��Ƶ��������ʹ�õı������ӷ�ΧΪ0~200������0~100Ϊ������100~200Ϊ��������ʱֻ֧��8·
    Om_UINT32       dwInputBVolume[16];    //��ƵMixer����B��Ӧ��Ƶ��������ʹ�õı������ӷ�ΧΪ0~200������0~100Ϊ������100~200Ϊ��������ʱֻ֧��8·
    Om_UINT32       Reserved[32];          //��������չʹ�ã�������Ϊȫ0
}SOmnAudioMixerCfg;

/******************************************
* ����Ƶ����ʱ��Ϣ�����ڻص��������ݲ���
******************************************/
typedef struct SOmn_RunTimeInfo_T
{
    Om_UINT32   dwInterruptCount;    //�źŶ˿ڵ�֡�жϼ���
    Om_UINT32   dwCallBackCount;     //�źŶ˿ڵĻص�����
    Om_UINT32   dwBufferRemainCount; //�źŶ˿ڵ�Buffer������еȴ�����֡��
    Om_UINT32   dwHardwareFrameCount;//�źŶ˿��Ѵ���֡��
    Om_UINT32   dwLostFrameCount;    //�źŶ˿ڵĶ�֡��
    Om_UINT32   InterruptType;       //�ڳ���ʽʱ�����жϵ�����: 0 odd, 1 even, 3 frame
    Om_UINT32   Reserved[9];         //��������չʹ�ã�������Ϊȫ0
} SOmn_RunTimeInfo, *PSOmn_RunTimeInfo;

/******************************************
* ͬ���ύ��ʽ�£�SDK���ݸ��ص���������Ϣ
******************************************/
typedef struct SOmn_SyncVACallbackInfo_T
{
    SOmn_RunTimeInfo sRunTimeInfo;   //����˿�����ʱ��Ϣ
    Om_UINT32   dwAudioSampleCount;  //�źŶ˿���Ҫ�������Ƶ��������
    Om_UINT32   dwGenlockCount;     //Genlockʱ���жϼ�����ֻ�����ڲ���
    Om_UINT32   Reserved[8];         //��������չʹ�ã�������Ϊȫ0
} SOmn_SyncVACallbackInfo, *PSOmn_SyncVACallbackInfo;

/******************************************
* ��������ʱ��SDK���ݸ��ص���������Ϣ
******************************************/
typedef struct SOmn_HLBCallbackInfo_T
{
    Om_UINT_PTR      dwUpdateNo;  //�ύ�������ţ����ڶ�λ����֡��
    Om_UINT8         bNeedPlay;   //�����Ƿ����ڻ���
    Om_UINT8         bReserved[3];//��������չʹ�ã�������Ϊȫ0
    Om_UINT32        Reserved[9]; //��������չʹ�ã�������Ϊȫ0
} SOmn_HLBCallbackInfo, *PSOmn_HLBCallbackInfo;

/******************************************
* �û��ڴ������ṹ
******************************************/
typedef struct SOmnBufferInfo_T
{
    Om_PVOID   pBufferAddr;          //Buffer��ַ��Ҫ���ַ����16�ֽڶ���
    Om_UINT32   dwBufferSize;        //Buffer����
    Om_UINT32   dwBufferLinePitch;   //Buffer�г���,��Ҫ���һЩ����DirectX��ͼ��Buffer��ÿ��֮�䶼�пն�
} SOmnBufferInfo;

/******************************************
* �����ύ����
******************************************/
typedef enum Omn_BUFFERUPDATE_FLAG_E
{
    Omn_BUFUPDATEFLAG_UNKNOW         = -1,
    Omn_BUFUPDATEFLAG_FIRSTFIELD     = 0, //��1��Bufferֻ�ύ��һ��
    Omn_BUFUPDATEFLAG_SECONDFIELD    = 1, //��1��Bufferֻ�ύ�ڶ���
    Omn_BUFUPDATEFLAG_BOTHFIELD      = 2, //��2��Bufferͬʱ�ύ����
    Omn_BUFUPDATEFLAG_FRAME          = 3, //��1��Buffer�ύһ֡
    Omn_BUFUPDATEFLAG_FRAME_SEGMENT  = 4  //�ݲ�֧��
} Omn_BUFFERUPDATE_FLAG;

/******************************************
* ����Omn_UpdateBufferʱ����ָ��SOmnBufUpdataInfo
* �ṹpsBufferArr[]������±�
******************************************/
typedef enum Omn_UPDATE_BUFFER_INDEX_E
{
    Omn_UPDATEBUFFER_INDEX_UNKNOW             = -1,
    Omn_UPDATEBUFFER_INDEX_FRAME              = 0, //֡��ʽ����
    Omn_UPDATEBUFFER_INDEX_FIRSTFIELD         = 0, //����ʽ����
    Omn_UPDATEBUFFER_INDEX_Y_ZONE             = 0, //���ڽ�YUV�ֱ���ʱ��
    Omn_UPDATEBUFFER_INDEX_SECONDFIELD        = 1, //����ʽ����
    Omn_UPDATEBUFFER_INDEX_U_ZONE             = 1, //���ڽ�YUV�ֱ���ʱ��
    Omn_UPDATEBUFFER_INDEX_V_ZONE             = 2, //���ڽ�YUV�ֱ���ʱ��
    Omn_UPDATEBUFFER_INDEX_KEY                = 3, //KEY���������ݲ�֧��
    Omn_UPDATEBUFFER_INDEX_AUDIO              = 4, //��Ƶ��������
    Omn_UPDATEBUFFER_INDEX_VANC_FRAME         = 5, //֡��ʽ�£�һ֡VANC����
    Omn_UPDATEBUFFER_INDEX_VANC_FIRSTFIELD    = 5, //����ʽ�£��泡VANC����
    Omn_UPDATEBUFFER_INDEX_OOB                = 6, //VITC/LTC/AFD�����ݴ洢����
    Omn_UPDATEBUFFER_INDEX_VANC_SECONDFIELD   = 7, //����ʽ�£�ż��VANC����
    Omn_UPDATEBUFFER_INDEX_MAX                = 8
} Omn_UPDATE_BUFFER_INDEX;

/******************************************
* ͬ���ύBufferʱ�����ݽṹ
* ����Omn_UpdateBufferʱʹ��
******************************************/
#define HAS_SUBSEQUENCE_MAGIC 19
typedef struct SOmnBufUpdataInfo_T
{
    Om_UINT32            dwSize;             //SOmnBufUpdataInfo�ṹ�Ĵ�С����λ��Byte    
    Om_UINT_PTR          dwUpdateNo;         //ÿ���ύ���������ţ�����SDKͨ���ص�����֪ͨӦ�ó���    
    Omn_BUFFERUPDATE_FLAG enumBufUpdateFlag;  //�˴��ύ������
    Omn_VIDEOSCAN_MODE    enumVideoScanType;  //��Ƶɨ��֡���������з�ʽ(Omn_BUFUPDATEFLAG_FRAME����Ч)    
    Omn_RECT              sValidRect;         //�ݲ�֧�ִ˲�����������Ϊȫ0
    SOmnBufferInfo        psBufferArr[Omn_UPDATEBUFFER_INDEX_MAX];  //IO Buffer��������
    Om_UINT8             u8HasSub;           //�����ýṹ֮���Ƿ񻹸���һ����ͬ�Ľṹ�����ΪHAS_SUBSEQUENCE_MAGIC�������滹�и��棬�������û�и���
    
    Om_UINT32            dwReserved[17];     //��������չʹ�ã�������Ϊȫ0
    Om_UINT32            dwGenlockIntCount;  //����Server-400K����SDI�ɼ�ʱ����ʾ�ɼ���ǰ֡/��ʱ��Genlock�жϼ���
    Om_UINT32            dwTsLength;         //����ASI�źŲɼ�ʱ�����زɼ�TS�ĳ��ȣ���λ��byte
    Om_UINT32            dwDMAConsumption;   //DMA�������ĵ�ʱ�䣬100nsΪ��λ�����Ϊ0xffffffff,����DMA�����й���
    Om_UINT8             u8IsInterlace;      //����CAP-500��,�ɼ�HDMI�ź�ʱ�����ص�ǰHDMI�����źŵ�ɨ�跽ʽΪ���л��Ǹ���(RDP��)��0�����У�1�����С���������֧�֣�����0xff
    Om_UINT8             u8FrameRate;        //����CAP-500��,�ɼ�HDMI�ź�ʱ�����ص�ǰHDMI�����źŵ�֡��(RDP��)����λ��fps����������֧�֣�����0xff    
    Om_UINT8             u8Reserved[4];      //��������չʹ�ã�������Ϊȫ0
    Om_UINT8             u8IsOdd;            //��Server-400K������ȥ���вɼ�ʱ����ʾ��ǰΪ�泡��ż��ȥ���еõ���1����ʾ�泡ȥ���еõ���֡��0����ʾż��ȥ���еõ���֡
    Om_UINT32            dwTimeStamp;        //ͬ���ύ��ʽ�£�����ʱ���(RDP��)
    Om_UINT64            dwGlobalTimeStamp;  //ͬ���ύ��ʽ�£����ذ忨ȫ��ʱ���(RDP��)�����ڶ�·�ɼ�ʱ��ͬ��
    Omn_RECT              sReturnRect;        //����RDP�����زɼ���Ƶ��RECT��Ϣ��PDP��֧�֣�����ȫ0
} SOmnBufUpdataInfo;

/******************************************
* Դ��Ŀ������ӳ����Ϣ 
******************************************/
typedef struct SOmnRectMap_T
{
    Omn_RECT        sSrcValidRect;  //Դѡȡ�ľ�������PDP��ISPΪԴ��
    Omn_RECT        sDestValidRect; //Ŀ����õľ�������RDP��OSPΪĿ�꣩
    Om_BOOL         bValid;         //ӳ����Ϣ�Ƿ���Ч��Om_FALSE��ʾ��Ч��Om_TRUE��ʾ��Ч
}SOmnRectMap;

/******************************************
* ͬ���ύBuffer�ǵ���չ���ݽṹ
* ����Omn_UpdateBuffer_Ex1ʱʹ��
******************************************/
typedef struct SOmnBufUpdateInfo_Ex1_T
{
    Om_UINT32                   dwSize;             //SOmnBufUpdateInfo_Ex1�ṹ�Ĵ�С
    Om_UINT_PTR                 dwUpdateNo;         //ÿ���ύ���������ţ�����SDKͨ���ص�����֪ͨӦ�ó���
    Omn_BUFFERUPDATE_FLAG       enumBufUpdateFlag;  //�˴��ύ������
    Omn_VIDEOSCAN_MODE          enumVideoScanType;  //��Ƶɨ��֡���������з�ʽ(Omn_BUFUPDATEFLAG_FRAME����Ч)  
    SOmnBufferInfo              psBufferArr[Omn_UPDATEBUFFER_INDEX_MAX]; //IO Buffer��������
    SOmnRectMap                 sMapInfo[8];        //λ��ӳ����Ϣ��ÿһ��Ա��������һ��Դ��Ŀ���λ��ӳ����Ϣ�����������ΪĿ��˿�ID�ţ�Ŀǰ��PDP֧��
    Om_UINT8                    u8HasSub;           //�����ýṹ֮���Ƿ񻹸���һ����ͬ�Ľṹ�����ΪHAS_SUBSEQUENCE_MAGIC�������滹�и��棬�������û�и���

    Om_UINT32                   dwReserved[29];
    Om_UINT32                   dwGenlockIntCount;  //����Server-400K����SDI�ɼ�ʱ����ʾ�ɼ���ǰ֡/��ʱ��Genlock�жϼ���
    Om_UINT32                   dwTsLength;         //����ASI�źŲɼ�ʱ�����زɼ�TS�ĳ��ȣ���λ��byte
    Om_UINT32                   dwDMAConsumption;   //DMA�������ĵ�ʱ�䣬100nsΪ��λ�����Ϊ0xffffffff,����DMA�����й���
    Om_UINT8                    u8IsInterlace;      //����CAP-500��,�ɼ�HDMI�ź�ʱ�����ص�ǰHDMI�����źŵ�ɨ�跽ʽΪ���л��Ǹ���(RDP��)��0�����У�1�����С���������֧�֣�����0xff
    Om_UINT8                    u8FrameRate;        //����CAP-500��,�ɼ�HDMI�ź�ʱ�����ص�ǰHDMI�����źŵ�֡��(RDP��)����λ��fps����������֧�֣�����0xff    
    Om_UINT8                    u8IsOdd;            //��Server-400K������ȥ���вɼ�ʱ����ʾ��ǰΪ�泡��ż��ȥ���еõ���1����ʾ�泡ȥ���еõ���֡��0����ʾż��ȥ���еõ���֡
    Om_UINT32                   dwTimeStamp;        //ͬ���ύ��ʽ�£�����ʱ���(RDP��)    
    Om_UINT64                   dwGlobalTimeStamp;  //ͬ���ύ��ʽ�£����ذ忨ȫ��ʱ���(RDP��)�����ڶ�·�ɼ�ʱ��ͬ��
    SOmnRectMap                 sReturnMapInfo[8];  //��sMapInfoһһ��Ӧ�Ĳ���������Ϣ
}SOmnBufUpdateInfo_Ex1;


/******************************************
* VANC����������Ϣ
******************************************/
typedef struct SOmn_VANC_TRANS_T
{
    Om_UINT32               dwSize;             //�����ݽṹ�Ĵ�С�����ֽ�Ϊ��λ
    Omn_PORT_TYPE            enumDataPortType;   //���ݶ˿����ͣ�ʹ���ĸ����ݶ˿ڵ�VANC����
    Om_UINT32               dwDatePortNo;       //���ݶ˿ںţ�ʹ���ĸ����ݶ˿ڵ�VANC����
    Om_BOOL                 bEnable;            //ʹ�����ݶ˿ڵ�VANC���书��
    Om_UINT32               dwVANCTypeFlag;     //VANC���ݵĴ洢��ʽ��0,Y��UV�������������ڴ洢VANC���ݣ�1,ʹ��Y�����洢VANC���ݣ�2,ʹ��UV�����洢VANC����
}SOmn_VANC_TRANS, *PSOmn_VANC_TRANS;

/******************************************
* VANC��ѯ��Ϣ
******************************************/
typedef struct SOmn_VANC_INFO_T
{
    //��ѯǰ��������Ϣ
    Om_UINT32               dwSize;           //�����ݽṹ�Ĵ�С�����ֽ�Ϊ��λ
    Omn_PORT_TYPE            enumDataPortType; //���ݶ˿����ͣ���ѯ�ĸ����ݶ˿ڵ�VANC֧�����
    Om_UINT32               dwDatePortNo;     //���ݶ˿ںţ���ѯ�ĸ����ݶ˿ڵ�VANC֧�����
    Om_UINT32               dwBufFlag;        //��ѯ�泡��ż����֡��VANC֧����Ϣ����ʾ��ʽ: 0 �泡��1 ż����3 ֡

    //��ѯ�ķ�����Ϣ
    Omn_VIDEO_STANDARD       enumVidStd;       //��ǰ���ݶ˿ڵ���Ƶ��ʽ
    Omn_COLOR_FORMAT         enumVANCBufFmt;   //VANC Bufferʹ�õ���ɫ��ʽ
    Om_UINT32               dwVANCStartLine;  //VANC ��ʼ�У�����
    Om_UINT32               dwVANCEndLine;    //VANC �����У�����
    Om_UINT32               dwVANCBufSize;    //ʹ������Ҫ׼����VANC Buffer�Ĵ�С�����ֽ�Ϊ��λ
    Om_UINT32               dwVANCLinePitch;  //VANC ÿ����ռ�ݵĴ洢�ռ��С�����ֽ�Ϊ��λ
}SOmn_VANC_INFO, *PSOmn_VANC_INFO;

/****************************************** 
* 3D����������Ϣ
******************************************/
typedef struct SOmn3DTrans_T
{
    Omn_PORT_TYPE   enumDataPortType;  //PDP/RDP���ͣ�ʹ���ĸ����ݶ˿ڵ�3D����
    Om_UINT32      dwDatePortNo;      //�˿�ID
    Om_BOOL        bEnable;           //ʹ�ܿ���    
    Om_UINT32      previewSrc;        //�ݲ�֧�֣�ȫ0
}SOmn3DTrans, *PSOmn3DTrans;

/****************************************** 
* ��·ͬ���ɼ���Ϣ
******************************************/
typedef struct SOmnMultiChannelTrans_T 
{
    Omn_PORT_TYPE   enumDataPortType;         //PDP/RDP����
    Om_UINT32      dwDatePortNo;             //�˿�ID
    Om_UINT8       SignalPortSelection[32];  //��i��OSP/ISP��ѡ�������0��ʾ��ѡ��1��ʾѡ��
}SOmnMultiChannelTrans;

/****************************************** 
* 3G LevelB������Ϣ����֧��
******************************************/
typedef struct SOmn3GLevelB_T
{
    Omn_PORT_TYPE enumSignalPortType;  //�źŶ˿����ͣ�ʹ���ĸ��źŶ˿ڵ�3G LevelB
    Om_UINT32      dwDatePortNo;      //�źŶ˿ںţ�ʹ���ĸ��źŶ˿ڵ�3G LevelB
    Om_BOOL        bEnable;           //ʹ�ܿ���
    Om_UINT32      dwStreamCount;     //������������1����������2˫��������
}SOmn3GLevelB, *PSOmn3GLevelB;

/******************************************
* �źŶ˿�����Ӧ������Ϣ����֧��
******************************************/
typedef struct SOmnSignalAdaptation_T
{
    Omn_PORT_TYPE enumSignalPortType;  //�źŶ˿�����
    Om_UINT32      dwSignalPortNo;    //�źŶ˿ں�
    Om_BOOL        bSupported;        //���ڲ�ѯ���źŶ˿��Ƿ�֧���ź�����Ӧ����
    Om_BOOL        bEnable;           //ʹ�ܿ���
}SOmnSignalAdaptation;

/******************************************
* ���ڻ�ȡ������GPIO����Ϣ����֧��
******************************************/
typedef struct SOmnBoardTallyInfo_T
{
    Om_UINT8 u8TallyItfAmt;     //֧�ֵ�Tally�ӿ�������������ֻ����Ŀǰ���֧��6��Tally�ӿڣ���Ӳ���汾�й�
    Om_UINT8 u8TallyEnable;     //Tally�ӿ�ʹ�ܿ��أ�0:Audio,1:Tally
    Om_UINT8 u8TallyIOMask;     //Tally�ӿ�IO�������룬0:Input,1��Output
    Om_UINT8 u8TallyStatusMask; //���û��ȡ����Tally�ӿ�״̬���룬0:��,1:��
    Om_UINT8 u8AudioSelect;     //��Ƶ�ӿ�ѡ��0:AES/EBU, 1:Analog
    Om_UINT8 u8Reserved[3];     //��չ�ã�������Ϊȫ0
    Om_UINT32 Reserved[2];      //��չ�ã�������Ϊȫ0
} SOmnBoardTallyInfo;

/******************************************
* Tally������Ϣ
******************************************/
typedef struct SOmnTallyInfo_T
{
    Om_UINT32				dwTallyAmount;	//Tally������,�����ڲ�ѯ
    Om_UINT32				dwTallyType;	//Tally���ͣ�0:��ƽʽ��1:����ʽ
    Om_UINT32				dwStatusMask;	//���õ����״̬����ƽʽ��0:��1:��������ʽ��0:�Ͽ���1:��ͨ
}SOmnTallyInfo;

/******************************************
* Mic����������Ϣ
******************************************/
typedef struct SOmn_MIC_VOLUME_T
{
    Om_UINT32 u32MicIdx;     //Server������֧������Mic���룬�˱�����������Mic��Id��
    Om_UINT32 u32MicVolume;  //Mic����ֵ��ȡֵ��Χ0~60����λΪdB
}SOmn_MIC_VOLUME;

/******************************************
* Mic48V��Դ������Ϣ
******************************************/
typedef struct SOmn_MIC_48V_T
{
    Om_UINT32 u32MicIdx;     //Server������֧������Mic���룬�˱�����������Mic��Id��
    Om_UINT32 u32Enable48V;  //ʹ��Mic��48V�����Դ, 0:�رգ�1:ʹ��
}SOmn_MIC_48V;

/******************************************
* LTC��ֵ����������SMPTE-12M-1-2008��
* SMPTE-12M-2-2008��SMPTE-309M-1999
******************************************/
typedef struct SOmn_LTC_VALUE_T
{
    Om_UINT32 dwHour; //ʱ
    Om_UINT32 dwMin; //��
    Om_UINT32 dwSec; //��
    Om_UINT32 dwFrm; //֡
    Om_BOOL  bTimeSpecified;//ʱ���Ƿ���ȷ���μ�SMPTE-12M-1-2008
    Om_UINT32 dwYear; //��
    Om_UINT32 dwMon; //��
    Om_UINT32 dwDay; //��
    Om_BOOL  bDateSpecified;//�����Ƿ���ȷ���μ�SMPTE-12M-1-2008
    Om_UINT64 qwOriginLTCVal;//ԭʼLTCֵ,�μ�SMPTE-12M-2-2008
}SOmn_LTC_VALUE;

/******************************************
* LTC�������
******************************************/
typedef struct SOmn_LTC_OUT_CONFIG_T
{
    Om_UINT32 dwOutputNo;//LTC���ͨ��������
    Om_BOOL  bLoopout;//�Ƿ񻷳���ͬ����������LTC���źţ�Om_TRUE:������ͬ����������LTC���źţ�Om_FALSE����������������Ϊ�������
}SOmn_LTC_OUT_CONFIG;

/******************************************
* �ɼ�ʱLTC����Դ��ѡ��
******************************************/
typedef enum Omn_LTC_SOURCE_TYPE_E
{
    Omn_LTCSOURCEYPTE_RESPECTIVE = 0,//���ɼ�ͨ��LTCԴ�Ը��Ե�LTC����
    Omn_LTCSOURCETYPE_IN0   = 1,//���вɼ�ͨ��LTC��Դ��LTC����0
    Omn_LTCSOURCETYPE_IN1   = 2,//���вɼ�ͨ��LTC��Դ��LTC����1
    Omn_LTCSOURCETYPE_IN2   = 3,//���вɼ�ͨ��LTC��Դ��LTC����2
    Omn_LTCSOURCETYPE_IN3   = 4 //���вɼ�ͨ��LTC��Դ��LTC����3
}Omn_LTC_SOURCE_TYPE;

/******************************************
* ����LTC�����Դ��Ϣ
******************************************/
typedef struct SOmnLTCPlaySource_T
{
    Om_UINT32   dwLTCNo; //���LTC���
    Om_UINT32   dwOSPNo; //�ṩLTC�����Դ��OSP������
}SOmnLTCPlaySource;

/******************************************
* ����KeyMode����ģʽʱ��ѡ��Ķ˿����
******************************************/
typedef enum Omn_PORTPAIR_E
{
    Omn_PORTPAIR_Unknown   = 0,
    Omn_PORTPAIR_0_1       = 1, //�˿�0��1���
    Omn_PORTPAIR_2_3       = 2, //�˿�2��3���
    Omn_PORTPAIR_4_5       = 3, //�˿�4��5���
    Omn_PORTPAIR_6_7       = 4, //�˿�6��7���
    Omn_PORTPAIR_Max
}Omn_PORTPAIR;

/******************************************
* ֧��KeyMode�ɼ�������������
******************************************/
typedef struct SOmnKeyModeConfig_T
{
    Omn_PORTPAIR            enumPortPairType;   //KeyMode�˿����
    Om_BOOL                 bEnableKeyMode;     //KeyModeʹ�ܿ���, Om_FALSE:�رգ�Om_TRUE��ʹ��
}SOmnKeyModeConfig;

/******************************************
* Keyer��Դ������Ϣ
******************************************/
typedef struct SOmnKeyProfile_T
{
    Om_UINT32       dwRDPPortNo;    //Ӧ�û�ȡKeyer��������RDP��Դ��    
    Om_UINT32       reserved[4];    //��չ�ã�������Ϊȫ0
}SOmnKeyProfile;

/******************************************
* ��������
******************************************/
typedef enum Omn_BACKGROUND_COLOR_E
{
    Omn_BGCOLOR_Unknown    = 0,
    Omn_BGCOLOR_RED        = 1,  //�챳��
    Omn_BGCOLOR_YELLOW     = 2,  //�Ʊ���
    Omn_BGCOLOR_GREEN      = 3,  //�̱���
    Omn_BGCOLOR_CYAN       = 4,  //�౳��
    Omn_BGCOLOR_BLUE       = 5,  //������
    Omn_BGCOLOR_PINK       = 6,  //Ʒ�챳��
    Omn_BGCOLOR_GRAY       = 7   //�ұ���
} Omn_BACKGROUND_COLOR;

/******************************************
* ɫ��ֵ�������䣬���������ѡȡ������ֵ
* ����õ���SDKʹ���ߵ���Omn_InitKeyerParam()
* ���м��㡣ע�⣺����ֵ���ɸ��ġ�
******************************************/
typedef struct SOmnKeyerBasicParam_T
{      
    Omn_BACKGROUND_COLOR enumBGColor;      //������ɫ��ͨ��Omn_InitKeyerParam()����ó��������û�����
    Om_FLOAT             fHMinLimit;       //ɫ���������ޣ�ͨ��Omn_InitKeyerParam()����ó��������û�����
    Om_FLOAT             fHMaxLimit;       //ɫ���������ޣ�ͨ��Omn_InitKeyerParam()����ó��������û�����
    Om_FLOAT             fHSpillMin;       //��ɫ�����ɫ����Сֵ��ͨ��Omn_InitKeyerParam()����ó��������û�����
    Om_FLOAT             fHSpillMax;       //��ɫ�����ɫ�����ֵ��ͨ��Omn_InitKeyerParam()����ó��������û�����
}SOmnKeyerBasicParam;

/******************************************
* Keyer��������
******************************************/
typedef struct SOmnKeyerBGParam_T
{
    Om_FLOAT             fHMax;             //ɫ�����ֵ��ȡֵ��Χ[fHMinLimit, fHMaxLimit],���û�����
    Om_FLOAT             fHMin;             //ɫ����Сֵ��ȡֵ��Χ[fHMinLimit, fHMaxLimit],���û�����
    Om_UINT32            dwAlphaSLevelMax;  //Alphaͨ��S���ֵ��0~1000��,���û�����
    Om_UINT32            dwAlphaSLevelMin;  //Alphaͨ��V��Сֵ��0~1000��,���û�����
    Om_UINT32            dwAlphaBLevelMax;  //Alphaͨ��V���ֵ��0~1000��,���û�����
    Om_UINT32            dwAlphaBLevelMin;  //Alphaͨ��V��Сֵ��0~1000��,���û�����
}SOmnKeyerBGParam;

/******************************************
* Keyer�������
******************************************/
typedef struct SOmnKeyerPostprocessParam_T
{
    Om_UINT32            dwSpillHLevel;   //��ɫ����ɫ��ƫ�Ƶĳ̶ȣ�0~1000��,���û�����
    Om_UINT32            dwSpillHRange;   //��ɫ����ɫ��ƫ�Ƶķ�Χ��0~1000��,���û�����
    Om_UINT32            dwSpillSLevel;   //��ɫ�����Ͷ�ѹ���ĳ̶ȣ�0~1000��,���û�����
    Om_UINT32            dwSpillSRange;   //��ɫ�����Ͷ�ѹ���ķ�Χ��0~1000��,���û�����

    Om_UINT32            dwDenoiseLevel;  //ǰ������ĳ̶ȣ�0~1000��,���û�����
    Om_UINT32            dwDenoiseRange;  //ǰ������ķ�Χ��0~1000��,���û�����

    Om_INT32             nEdge;           //��Ե����-3~3��,���û�����
    Om_INT32             nBlur;           //ģ������0~3��,���û�����
}SOmnKeyerPostprocessParam;

/******************************************
* Keyer��������
******************************************/
typedef struct SOmnKeyerRect_T
{
    Omn_RECT            sRect1;           //���������1
    Om_BOOL             bRect1Enabled;    //�Ƿ������1���п���
    Omn_RECT            sRect2;           //���������2
    Om_BOOL             bRect2Enabled;    //�Ƿ������2���п���
}SOmnKeyerRect;

/******************************************
* Keyer����
******************************************/
typedef struct SOmnKeyerParam_T
{    
    SOmnKeyerBasicParam         sBasic;             //����������Ϣ�����ݴ������ص����õ��������û�����
    SOmnKeyerBGParam            sBGParam;           //��������,���û�����
    SOmnKeyerPostprocessParam   sPostProcParam;     //�������,���û�����
    SOmnKeyerRect               sRect;              //��������,���û�����
    Om_BOOL                     bDeinterlace;       //�Ը���ɨ����Ƶ����ȥ���д���
    Om_UINT32                   Reserved[3];        //��չ�ã�������Ϊȫ0
} SOmnKeyerParam;


/******************************************
* SDK����ֵ����
******************************************/
typedef enum Omn_RETURN_CODE_E
{
    Omn_ERR_DRV                   = 0xffff0000, //�������ش��󣬵�16bitΪ�������صĴ�����
    Omn_ERR_FAILED                = 0x80000001, //ʧ��
    Omn_ERR_INVALID_PARAM         = 0x80000002, //���������Ч
    Omn_ERR_ACCESS_DENY           = 0x80000003, //�ܾ�����
    Omn_ERR_SYS_MEMORY            = 0x80000004, //ϵͳ�ڴ����ʧ��
    Omn_ERR_BOARD_MEMORY          = 0x80000005, //�忨�ڴ����ʧ��
    Omn_ERR_UNSUPPORTED           = 0x80000006, //SDK��֧�ָù���
    Omn_ERR_VERSION               = 0x80000007, //SDK�汾����
    Omn_ERR_INVALID_STATUS        = 0x80000008, //��ǰSDK����״̬��Ч
    Omn_ERR_NO_ITF                = 0x80000009, //û�иÿ��ýӿ�
    Omn_ERR_OBJ_NOT_FOUND         = 0x8000000a, //δ�ҵ�Ŀ�����
    Omn_ERR_BAD_INTERNAL_INFO     = 0x8000000b, //�ڲ�����
    Omn_ERR_NOT_INIT              = 0x8000000c, //SDKδ��ʼ��
    Omn_ERR_RESOURCE_NOTENOUGH    = 0x8000000d, //SDK��Դ����
    Omn_ERR_ADDR_NOT_ALIGNED      = 0x8000000e,//������������ڴ��ַ�в�����32�ֽڵ�ַ��������
    //�˴���չ������Ϣ

    Omn_SUCCESS                   = 0x00000000, //�ɹ�

    Omn_IMPLICT_RULE              = 0x00000001, //������ʹ�ù���
    Omn_DO_NOTHING                = 0x00000002, //�����κβ�����ֱ�ӷ���
    //�˴���չ������Ϣ
}Omn_RETURN_CODE, Om_HRESULT;
#define Om_OK    Omn_SUCCESS
#define Om_FAIL    Omn_ERR_FAILED

/******************************************
* ����ͨ�ûص���������
******************************************/
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
    typedef   Om_HRESULT  (WINAPIV* Omn_CallBackFuncPtr)(Om_VOID *pSDKInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (WINAPIV* Omn_AlarmCBFuncPtr)(SOmnAlarmInfo *pAlarmInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (WINAPIV* Omn_IoCBFuncPtr)(SOmn_SyncVACallbackInfo *pIoInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (WINAPIV* Omn_HLBCBFuncPtr)(SOmn_HLBCallbackInfo *pHlbInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (WINAPIV* Omn_TimerCBFuncPtr)(Om_UINT64 *pHwTickCountUnitIs100ns, Om_VOID *pContext);
    
#elif defined(_LINUX32) || defined(_LINUX64) 
    typedef   Om_HRESULT  (* Omn_CallBackFuncPtr)(Om_VOID *pSDKInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (* Omn_AlarmCBFuncPtr)(SOmnAlarmInfo *pAlarmInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (* Omn_IoCBFuncPtr)(SOmn_SyncVACallbackInfo *pIoInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (* Omn_HLBCBFuncPtr)(SOmn_HLBCallbackInfo *pHlbInfo, Om_VOID *pContext);
    typedef   Om_HRESULT  (* Omn_TimerCBFuncPtr)(Om_UINT64 *pHwTickCountUnitIs100ns, Om_VOID *pContext);
#endif


#ifdef __cplusplus
}
#endif

#if defined Omn_IMPORTEXPORT
#  undef Omn_IMPORTEXPORT
#endif



/* On pretty much everything else, we can thankfully just ignore this */
#if !defined Omn_IMPORTEXPORT
#  define Omn_IMPORTEXPORT
#endif

#define Omn_EXPORTS Omn_IMPORTEXPORT

#endif

