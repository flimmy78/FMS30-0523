#ifndef _Omn_TYPE_DEF_H
#define _Omn_TYPE_DEF_H
#include "Omni_platform.h"
#include "Omni_VACommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************
* 板卡系列类型
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
* 板卡类型
******************************************/
typedef enum Omn_BOARD_TYPE_E
{
    Omn_BOARDTYPE_UNKNOW    = -1,    
    Omn_BOARDTYPE_CAP500    = 39,   //对应于CAP-500卡
    Omn_BOARDTYPE_CAP600    = 40,   //对应于CAP-600卡
    Omn_BOARDTYPE_EM200     = 41,   //对应于EditMini-200卡
    Omn_BOARDTYPE_CG100     = 42,   //对应于CG-100卡
    Omn_BOARDTYPE_SER400    = 43,   //对应于Server-400卡
    Omn_BOARDTYPE_CAP500K   = 44,   //对应于CAP-500K卡
    Omn_BOARDTYPE_CAP400    = 45,   //对应于CAP-400卡
    Omn_BOARDTYPE_CAP300    = 46,   //对应于CAP-300卡
    Omn_BOARDTYPE_EM100     = 47,   //对应于EditMini-100卡
    Omn_BOARDTYPE_SER400K   = 48,   //对应于Server-400K卡
    Omn_BOARDTYPE_SER100S   = 49,   //对应于Server-100S卡
    Omn_BOARDTYPE_SER100D   = 50,   //对应于Server-100D卡
    Omn_BOARDTYPE_CAP400ASI = 51,   //对应于CAP-400_A_S_I卡
    Omn_BOARDTYPE_EDITPRO   = 52,   //对应于EditPro卡
    //Omn_BOARDTYPE_SER101N   = 53,   //对应于Server-101N卡
    //Omn_BOARDTYPE_CG101     = 54,   //对应于CG-101卡
    Omn_BOARDTYPE_SER400LE  = 55,   //对应于Server-400LE卡
    Omn_BOARDTYPE_SER800    = 56,   //对应于Server-800卡
    //Omn_BOARDTYPE_SER801N   = 57,   //对应于Server-801N卡
    Omn_BOARDTYPE_SER1200   = 58,   //对应于Server-1200卡
    Omn_BOARDTYPE_MAX
} Omn_BOARD_TYPE;

/******************************************
* 子卡类型
******************************************/
typedef enum Omn_DAUGHTERCARD_TYPE_E
{
    Omn_DAUGHTERCARDTYPE_UNKNOW         = -1,
    Omn_DAUGHTERCARDTYPE_OPAA8180B      = 19,   //对应于OPAA8180B子卡
    Omn_DAUGHTERCARDTYPE_OPDA8180UTC    = 20,   //对应于OPDA8180UTC子卡
    Omn_DAUGHTERCARDTYPE_TALLY10        = 21,   //对应于OPTALLY10子卡
    Omn_DAUGHTERCARDTYPE_OPAA2120       = 22,   //对应于DEK_OPAA_SUB子卡
    Omn_DAUGHTERCARDTYPE_SER100OPAA     = 23,   //对应于OPVA0130UH子卡
    Omn_DAUGHTERCARDTYPE_E200OPVA       = 24,   //对应于EDIT200_OPVA_SUB子卡
    Omn_DAUGHTERCARDTYPE_SER1200SDIOUT  = 25,   //对应于SER1200_SDIOUT_SUB子卡
    Omn_DAUGHTERCARDTYPE_MAX
} Omn_DAUGHTERCARD_TYPE;

/******************************************
* 主卡版本信息
******************************************/
typedef struct SOmnBoardVersionInfo_T
{
    Om_UINT32  dwBiosVersion;     //Firmware版本号    
    Om_UINT32  dwBoardVersion;    //板卡PCB版本号
    Om_UINT64  qwBoardSerialNo;   //板卡序列号
    Om_UINT32  dwReseved[9];      //保留扩展用，全0 
} SOmnBoardVersionInfo;

/******************************************
* 子卡版本信息
******************************************/
typedef struct SOmnSubCardInfo_T
{
    Omn_DAUGHTERCARD_TYPE enumCardType;       //子卡类型
    Om_UINT32            dwFirmareVersion;   //Firmware版本号
    Om_UINT32            dwCardVersion;      //板卡PCB版本号
    Om_UINT64            qwCardSerialNo;     //板卡序列号    
    Om_UINT32            u8Reserved[9];      //保留扩展用，全0
} SOmnSubCardInfo, SOmnDaughterCardInfo;

/******************************************
* 套卡资源信息
******************************************/
typedef struct SOmnBoardInfo_T
{
    SOmnBoardVersionInfo  sBoardVersionInfo;         //主卡版本信息
    Omn_BOARD_CLASS       enumBoardClass;            //板卡类型
    Omn_BOARD_TYPE        enumBoardType;             //板卡子类型
    Om_UINT32             dwRecordDataPortNum;       //采集数据通道数
    Om_UINT32             dwPlayDataPortNum;         //播出数据通道数
    Om_UINT32             dwInputSignalPortNum;      //信号采集端口数
    Om_UINT32             dwOutputSignalPortNum;     //信号播出端口数
    Om_UINT8              bScalerSupport;            //板卡是否支持Scaler    
    Om_UINT8              u8InterfaceNum;            //板卡支持Interface数量
    Om_UINT8              u8MixerNum;                //板卡支持的硬件Mixer数量    
    Om_UINT8              u8KeyerNum;                //板卡支持的硬件Keyer数量
    Om_UINT8              u8Reserved[8];             //保留扩展用，全0
    Om_UINT32             dwDaughterCardNum;         //子卡数量
    SOmnSubCardInfo       psDaughterCardInfo[6];     //子卡信息数组
} SOmnBoardInfo;

/******************************************
* 发布包版本信息
******************************************/
typedef struct SOmnVersionInfo_T
{
    Om_UINT16  wMajorVersion;    //主版本号,以十进制形成进行UI呈现
    Om_UINT16  wMinorVersion;    //次版本号,以十进制形成进行UI呈现
    Om_UINT32  dwSvnNo;          //svn号,以十进制形成进行UI呈现
    Om_UINT32  dwBuildNo;        //build版本号,以十六进制形成进行UI呈现
    Om_UINT32  dwTag;            //软件分支标签
}SOmnVersionInfo;

/******************************************
* SDK全局信息
******************************************/
typedef struct SOmnGlobalInfo_T
{
    Om_UINT32        dwBoardNum;         //板卡数量
    SOmnBoardInfo     psBoardInfo[4];     //板卡配置信息数组
    SOmnVersionInfo   sSDKVersion;        //发布包版本信息    
    Om_UINT32        u32Reserved[9];     //保留扩展用，全0
} SOmnGlobalInfo, *PSOmnGlobalInfo;

/******************************************
* 查询板卡支持属性时的属性查询类型
* 调用Omn_GetSpecCapInfo时使用
******************************************/
typedef enum Omn_BOARDSPECINFO_TYPE_E
{
    Omn_BOARDSPECINFO_UNKNOW           = -1,
    Omn_BOARDSPECINFO_BOARDNAME        = 0, //板卡名
    Omn_BOARDSPECINFO_VIDEO_STANDARD   = 1, //视频制式
    Omn_BOARDSPECINFO_GENLOCK          = 2, //锁相源
    Omn_BOARDSPECINFO_VIDEO_SRC        = 3, //视频源
    Omn_BOARDSPECINFO_AUDIO_SRC        = 4, //音频源
    Omn_BOARDSPECINFO_COLOR_FMT_INPUT  = 5, //采集颜色格式
    Omn_BOARDSPECINFO_COLOR_FMT_OUTPUT = 6, //播出颜色格式
    Omn_BOARDSPECINFO_VIDEO_OUT_TYPE   = 7, //视频输出信号类型
    Omn_BOARDSPECINFO_MAX              = 16 
} Omn_BOARDSPECINFO_TYPE;

/******************************************
* 锁相源类型
******************************************/
typedef enum Omn_GENLOCK_SOURCE_E
{
    Omn_GENLOCKSOURCE_UNKNOW          = -1,
    Omn_GENLOCKSOURCE_INTERNAL        = 0, //内同步
    Omn_GENLOCKSOURCE_REFERENCE_IO    = 1, //输入输出都锁在Reference信号上。
                                           //注意，设置此锁相方式时，如果输入信号与Ref信号不同步，请选择Omn_GENLOCKSOURCE_REFERENCE锁相方式，否则会导致采集画面异常。
    Omn_GENLOCKSOURCE_SDI_IN_0        = 2, //锁在SDI输入信号0上
    Omn_GENLOCKSOURCE_SDI_IN_1        = 3, //锁在SDI输入信号1上
    Omn_GENLOCKSOURCE_SDI_IN_2        = 4, //锁在SDI输入信号2上
    Omn_GENLOCKSOURCE_SDI_IN_3        = 5, //锁在SDI输入信号3上
    Omn_GENLOCKSOURCE_ANALOG_IN_0     = 6, //锁在模拟输入信号0上
    Omn_GENLOCKSOURCE_REFERENCE       = 7, //仅输出锁在锁在Reference信号上，输入锁在各自的输入信号上
    Omn_GENLOCKSOURCE_ANALOG_IN_1     = 8, //锁在模拟输入信号1上
    Omn_GENLOCKSOURCE_ANALOG_IN_2     = 9, //锁在模拟输入信号2上
    Omn_GENLOCKSOURCE_ANALOG_IN_3     = 10, //锁在模拟输入信号3上
    Omn_GENLOCKSOURCE_AES_IN_0        = 11, //锁在AES输入信号12上
    Omn_GENLOCKSOURCE_AES_IN_1        = 12, //锁在AES输入信号34上
    Omn_GENLOCKSOURCE_AES_IN_2        = 13, //锁在AES输入信号56上
    Omn_GENLOCKSOURCE_AES_IN_3        = 14, //锁在AES输入信号78上
    Omn_GENLOCKSOURCE_AES_IN_0_LOOP   = 15, //锁在AES输入信号12上同时音频环通
    Omn_GENLOCKSOURCE_CASCADE         = 16  //锁在板间级联信号口上
} Omn_GENLOCK_SOURCE;

/******************************************
* 模拟或AES/EBU方式音频通道的分配
******************************************/
typedef enum Omn_AES_ANA_CONFIG_E
{
    Omn_AES_ANA_CONFIG_UNKNOW       = -1,
    Omn_AES_ANA_CONFIG_BIND_V0      = 0,  //信号端口0独自占用所有音频接口
    Omn_AES_ANA_CONFIG_AUTO         = 1,  //信号端口平均占用输出音频接口
    Omn_AES_ANA_CONFIG_BIND_V1      = 2,  //信号端口1独自占用所有音频接口
    Omn_AES_ANA_CONFIG_BIND_V2      = 3,  //信号端口2独自占用所有音频接口
    Omn_AES_ANA_CONFIG_BIND_V3      = 4,  //信号端口3独自占用所有音频接口
    Omn_AES_ANA_CONFIG_INDEPENDENT  = 16  //音频独立播出通道占用所有音频端口
} Omn_AES_ANA_CONFIG;

/******************************************
* 模拟视频信号抗爬行级别
******************************************/
typedef enum Omn_ANTI_LINE_CRAWL_E
{
    Omn_ANTI_LINE_CRAWL_UNKNOW   = -1,
    Omn_ANTI_LINE_CRAWL_LOW   = 0,        //低级别
    Omn_ANTI_LINE_CRAWL_MIDDLE   = 1,     //中级别
    Omn_ANTI_LINE_CRAWL_HIGH   = 2        //高级别
} Omn_ANTI_LINE_CRAWL;

/******************************************
* 三级安全检测WatchDog配置信息
******************************************/
typedef struct SOmnBoardWatchDogInfo_T
{
    Om_BOOL    EnableHW_Level;  //硬件级WatchDog是否启用
    Om_BOOL    EnableOS_Level;  //OS级WatchDog是否启用
    Om_BOOL    EnableApp_Level;  //应用级WatchDog是否启用
} SOmnBoardWatchDogInfo;

/******************************************
* 板卡Interface接口方向设置
******************************************/
typedef struct SOmnBoardInterfaceInfo_T
{
    Om_UINT32  InterfaceDirection[32];  //第i个BNC接口的方向，输入是0，输出是1
} SOmnBoardInterfaceInfo;

/******************************************
* 板卡级参数信息
******************************************/
typedef struct SOmnBoardBasePara_T
{    
    Omn_GENLOCK_SOURCE    enmuGenlockSource;   //锁相源    
    Omn_AES_ANA_CONFIG    enmuOutAudioConfig;  //模拟和AES/EBU分配给各OSP的模式
    Omn_ANTI_LINE_CRAWL   enmuAntiLineCrawl;   //模拟视频信号抗爬行级别
    Om_UINT32            dwMonitorCh;         //监听通道号，0:0~1, 1:2~3, 2:4~5, 3:6~7 ... 7:14~15
    Om_INT32             nMonitorVolume;      //监听音量，从-118~9，-118表示静音
    Om_UINT32            dwMicVolume;         //麦克风输入音量，从0~120，0为默认值
    SOmnBoardWatchDogInfo sBoardWatchDogInfo;  //板卡/驱动级WatchDog信息
    Om_UINT32            u32Reserved[9];      //保留扩展用，全0
} SOmnBoardBasePara;

/******************************************
* 板卡级参数信息枚举值，在Omn_GetBoardParamEx
* 和Omn_SetBoardParamEx时使用
******************************************/
typedef enum Omn_BOARDCONFIG_TYPE_E
{
    Omn_BOARDCONFIGTYPE_UNKNOW                      = -1,  
    Omn_BOARDCONFIGTYPE_MAIN_STANDARD			    = 0,	//暂不支持
    Omn_BOARDCONFIGTYPE_GENLOCK                     = 1,    //GET/SET 锁相源，使用Omn_GENLOCK_SOURCE *类型参数
    Omn_BOARDCONFIGTYPE_IN_AES_ANA_CONFIG		    = 2,	//暂不支持
    Omn_BOARDCONFIGTYPE_OUT_AES_ANA_CONFIG          = 3,    //GET/SET 模拟和AES/EBU分配给各输出通道的模式，使用Omn_AES_ANA_CONFIG *类型参数
    Omn_BOARDCONFIGTYPE_MONITOR_SELECT              = 4,    //GET/SET 监听通道号，使用Om_UINT32 *类型参数，0:0~1, 1:2~3, 2:4~5, 3:6~7 ... 7:14~15
    Omn_BOARDCONFIGTYPE_MONITOR_VOLUME              = 5,    //GET/SET 监听音量，使用Om_INT32 *类型参数，从-118~0，-118表示静音
    Omn_BOARDCONFIGTYPE_MIC_LINEIN_VOLUME           = 6,    //GET/SET 麦克风/LINEIN输入音量,使用Om_UINT32 *类型参数，范围：0~120
    Omn_BOARDCONFIGTYPE_ANTI_LINECRAWL              = 7,    //GET/SET 抗爬行，使用Omn_ANTI_LINE_CRAWL *类型参数
    Omn_BOARDCONFIGTYPE_TALLY                       = 8,    //GET/SET Tally，使用SOmnTallyInfo *类型参数
    Omn_BOARDCONFIGTYPE_WATCHDOG                    = 9,    //暂不支持
    Omn_BOARDCONFIGTYPE_INTERFACE                   = 10,   //GET/SET interface入出属性,使用SOmnBoardInterfaceInfo *类型参数
    Omn_BOARDCONFIGTYPE_3D_TRANS                    = 11,   //GET/SET 3D视频的传输功能，使用SOmn3DTrans *类型参数
    Omn_BOARDCONFIGTYPE_3G_LEVELB			        = 12,	//暂不支持
    Omn_BOARDCONFIGTYPE_INPUT_HPHASE                = 13,	//暂不支持
    Omn_BOARDCONFIGTYPE_VANC_TRANS                  = 14,   //GET/SET 指定DP端口的VANC传输功能，使用SOmn_VANC_TRANS *类型参数
    Omn_BOARDCONFIGTYPE_VANC_INFO_CHECK             = 15,   //GET 指定DP端口的VANC支持情况，使用SOmn_VANC_INFO *类型参数    
    Omn_BOARDCONFIGTYPE_SIGNAL_ADAPTATION           = 16,   //暂不支持
    Omn_BOARDCONFIGTYPE_MULTICHANNEL_TRANS          = 17,   //GET/SET 多同道同步采集模式，使用SOmnMultiChannelTrans *类型参数    
    Omn_BOARDCONFIGTYPE_HDMI_OUT_SIG_CLR            = 18,   //暂不支持
    Omn_BOARDCONFIGTYPE_HDMI_IN_SIG_CLR             = 19,   //暂不支持
    Omn_BOARDCONFIGTYPE_LINEIN_OR_MICIN             = 20,   //GET/SET LineIn或MicIn。使用Om_UINT32*传递参数，0为LineIN，1为MicIN
    Omn_BOARDCONFIGTYPE_MIC_VOLUME2                 = 21,   //GET/SET Mic音量，使用SOmn_MIC_VOLUME*传递参数
    Omn_BOARDCONFIGTYPE_MIC_48V                     = 22,   //GET/SET Mic是否使能48V幻象电源，使用SOmn_MIC_48V*传递参数
    Omn_BOARDCONFIGTYPE_G_OVER_BG_DELAY             = 23,   //GET/SET 叠加背景时的背景延迟帧数
    Omn_BOARDCONFIGTYPE_SDI_OUT_REF_SWITCH          = 24,   //GET/SET EditPro主卡在不插子卡时，SDI OUT2可配置成Ref in，使用Om_UINT32 *类型
                                                            //参数，0表示SDI Out，1表示Ref In
    Omn_BOARDCONFIGTYPE_AES_LTC_SWITCH              = 25,   //GET/SET EditPro主卡卡的EDIT200_OPVA_SUB子卡AES In/Out 7/8声道与LTC In/Out的
                                                            //切换选择，使用Om_UINT32 *类型参数，0表示为AES In/Out 7/8声道，1表示为LTC In/Out
    Omn_BOARDCONFIGTYPE_HP_LINEOUT_SWITCH           = 26,   //暂不支持
    Omn_BOARDCONFIGTYPE_APP_PRIVATE_INFO            = 27,   //GET/SET 板卡Flash上存储的应用私有加密信息，使用Om_UINT8[16]传递参数
    Omn_BOARDCONFIGTYPE_HDMI_OUT_AUD_CHNS           = 28,   //暂不支持
    Omn_BOARDCONFIGTYPE_LTC_OUT_CONFIG              = 29,   //暂不支持
    Omn_BOARDCONFIGTYPE_LTC_IN_CONFIG               = 30,   //暂不支持
    Omn_BOARDCONFIGTYPE_ISP_KEYMODE_CONFIG          = 31,   //GET/SET 进行KeyMode采集的配置，使用SOmnKeyModeConfig*类型参数
    Omn_BOARDCONFIGTYPE_OSP_KEYMODE_CONFIG          = 32,   //GET/SET 进行KeyMode播出的配置，使用SOmnKeyModeConfig*类型参数
    Omn_BOARDCONFIGTYPE_LTC_PLAYSOURCE              = 33,   //GET/SET 配置模拟LTC输出来源于哪一路OSP。使用SOmnLTCPlaySource*类型参数
    Omn_BOARDCONFIGTYPE_PORTPAIR23_OUT_CONFIG       = 34,   //GET/SET 对于Server-400K卡，配置两组KeyMode播出时第二组KeyMode的
                                                            //输出内容，使用Om_UINT32 *类型参数，0：输出当前KeyMode播出内容， 1：与第
                                                            //一组KeyMode播出内容相同，2：输出第一组KeyMode播出内容的下变换
    Omn_BOARDCONFIGTYPE_IO_WORK_MODE                = 35,   //GET/SET，只适用于Server-800_K卡，使用Omn_IO_WORK_MODE *类型参数
    Omn_BOARDCONFIGTYPE_MAX     
} Omn_BOARDCONFIG_TYPE;

/******************************************
* 板卡警报源枚举值
******************************************/
typedef enum Omn_ALARM_SOURCE_E
{
    Omn_ALARM_UNKNOWN           = 0,

    Omn_ALARM_REFERENCE_LOST    = (0x01<<0),  //外锁相信号丢失
                                  
    Omn_ALARM_INPUT0_LOST       = (0x01<<1),  //输入信号0的信号丢失 
    Omn_ALARM_INPUT1_LOST       = (0x01<<2),  //输入信号1的信号丢失
    Omn_ALARM_INPUT2_LOST       = (0x01<<3),  //输入信号2的信号丢失
    Omn_ALARM_INPUT3_LOST       = (0x01<<4),  //输入信号3的信号丢失
    Omn_ALARM_INPUT4_LOST       = (0x01<<5),  //输入信号4的信号丢失
    Omn_ALARM_INPUT5_LOST       = (0x01<<6),  //输入信号5的信号丢失
    Omn_ALARM_INPUT6_LOST       = (0x01<<7),  //输入信号6的信号丢失
    Omn_ALARM_INPUT7_LOST       = (0x01<<8),  //输入信号7的信号丢失

    Omn_ALARM_INPUT0_SIGNAL_ERR = (0x01<<9),  //输入信号0的信号制式与设定不符 
    Omn_ALARM_INPUT1_SIGNAL_ERR = (0x01<<10), //输入信号1的信号制式与设定不符
    Omn_ALARM_INPUT2_SIGNAL_ERR = (0x01<<11), //输入信号2的信号制式与设定不符
    Omn_ALARM_INPUT3_SIGNAL_ERR = (0x01<<12), //输入信号3的信号制式与设定不符
    Omn_ALARM_INPUT4_SIGNAL_ERR = (0x01<<13), //输入信号4的信号制式与设定不符
    Omn_ALARM_INPUT5_SIGNAL_ERR = (0x01<<14), //输入信号5的信号制式与设定不符
    Omn_ALARM_INPUT6_SIGNAL_ERR = (0x01<<15), //输入信号6的信号制式与设定不符
    Omn_ALARM_INPUT7_SIGNAL_ERR = (0x01<<16), //输入信号7的信号制式与设定不符

    Omn_ALARM_CH1_DIE           = (0x01<<17), //暂不支持
    Omn_ALARM_CH2_DIE           = (0x01<<18), //暂不支持

    Omn_ALARM_TEMPERAT          = (0x01<<19), //温度超过85度报警
    Omn_ALARM_VOLTGAGE          = (0x01<<20),  //暂不支持

    Omn_ALARM_INPUT0_UNSYNC     = (0x01<<21), //输入信号0与外锁相不同步
    Omn_ALARM_INPUT1_UNSYNC     = (0x01<<22), //输入信号1与外锁相不同步
    Omn_ALARM_INPUT2_UNSYNC     = (0x01<<23), //输入信号2与外锁相不同步
    Omn_ALARM_INPUT3_UNSYNC     = (0x01<<24), //输入信号3与外锁相不同步

    Omn_ALARM_GENLOCK_CHANGE    = (0x01<<31)  //锁相状态或制式改变
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
* 板卡锁相源状态 
******************************************/
typedef enum Omn_GENLOCK_STATUS_E
{
    Omn_GENLOCK_STATUS_UNKNOW     = -1,
    Omn_GENLOCK_STATUS_FREE       = 0, //内锁相状态
    Omn_GENLOCK_STATUS_LOST       = 1, //锁相源丢失
    Omn_GENLOCK_STATUS_LOCKING    = 2, //锁相源正在锁定过程中
    Omn_GENLOCK_STATUS_LOCKED     = 3, //锁相源处于锁定状态
    Omn_GENLOCK_STATUS_MAX        = 4 
} Omn_GENLOCK_STATUS;

/******************************************
* 板卡报警回调函数信息
******************************************/
typedef struct SOmnAlarmInfo_T 
{
     Om_UINT32              dwAlarmSrcMask;             //返回报警源信息 
     Omn_VIDEO_STANDARD     enumInputVideoStandard[32]; //返回4路输入视频信号的制式信息
     Omn_GENLOCK_STATUS     enumLastGenLockStatus;      //锁相状态变化前的锁相状态0:free,1:Lost,2:locking,3:Locked
     Omn_VIDEO_STANDARD     enumLastGenLockStandard;    //锁相状态变化前的锁相制式
     Omn_GENLOCK_STATUS     enumCurrentGenLockStatus;   //当前锁相状态变化后的锁相状态0:free,1:Lost,2:locking,3:Locked
     Omn_VIDEO_STANDARD     enumCurrentGenLockStandard; //当前锁相状态变化后的锁相制式
     Om_UINT32              dwReserved[25];             //保留扩展用，全0
} SOmnAlarmInfo;

/******************************************
* 板卡状态查询掩码，在SOmnMonitorInfo结构
* 的dwMonitorMask成员处使用
******************************************/
#define Omn_MONITOR_MASK_INPUTVIDEOSTANDARD (0x01)    //查询当前输入信号的制式信息
#define Omn_MONITOR_MASK_TEMPERAT           (0x02)    //查询板卡温度状态
#define Omn_MONITOR_MASK_FUNSPEED           (0x04)    //查询板卡风扇转速，不支持
#define Omn_MONITOR_MASK_TIMETICK           (0x08)    //查询板卡全局时间
#define Omn_MONITOR_MASK_GENLOCKSTATUS      (0x10)    //查询板卡锁相源状态
#define Omn_MONITOR_MASK_GENLOCKSTANDARD    (0x20)    //查询板卡锁相源制式

/******************************************
* 硬件状态信息 
******************************************/
typedef struct SOmnMonitorInfo_T 
{
    Om_UINT32            dwMonitorMask;              //查询掩码
    Omn_VIDEO_STANDARD    enumInputVideoStandard[32]; //当前0-31路输入信号的制式,返回OmnVIDEOSTANDARD_UNKNOW表示ISP未接入信号
    Om_UINT32            dwTemperature;              //返回温度单位为摄氏度
    Om_UINT32            dwFunSpeed;                 //返回单位为转/分钟，不支持
    Om_UINT64            qwHwTimeTicks;              //返回单位为100ns
    Omn_GENLOCK_STATUS   enumGenLockStatus;          //锁相状态0:free,1:Lost,2:locking,3:Locked
    Omn_VIDEO_STANDARD   enumGenLockStandard;        //锁相制式，板卡自动识别
    Om_UINT32            Reserved[9];                //保留扩展用，全0
} SOmnMonitorInfo,*PSOmnMonitorInfo;

/****************************************** 
* I/O配置工作模式
******************************************/
typedef enum Omn_IO_WORK_MODE_E
{
    Omn_IO_WORKMODE_UNKNOWN         = -1,
    Omn_IO_WORKMODE_8In0Out         = 0, //8入0出
    Omn_IO_WORKMODE_7In1Out         = 1, //7入1出
    Omn_IO_WORKMODE_6In2Out         = 2, //6入2出
    Omn_IO_WORKMODE_5In3Out         = 3, //5入3出
    Omn_IO_WORKMODE_4In4Out         = 4, //4入4出//以上针对Server-800卡
    Omn_IO_WORKMODE_8In4Out         = 5, //8入4出//以下针对Server-1200卡
    Omn_IO_WORKMODE_7In5Out         = 6, //7入5出
    Omn_IO_WORKMODE_6In6Out         = 7, //6入6出
    Omn_IO_WORKMODE_5In7Out         = 8, //5入7出
    Omn_IO_WORKMODE_4In8Out         = 9  //4入8出
}Omn_IO_WORK_MODE;

/****************************************** 
* PORT类型
******************************************/
typedef enum Omn_PORT_TYPE_E
{
    Omn_PORTTYPE_UNKNOW           = -1,
    Omn_PORTTYPE_RECORD_DATA      = 0, //采集数据端口（RDP）
    Omn_PORTTYPE_PLAY_DATA        = 1, //播出数据端口（PDP）
    Omn_PORTTYPE_SIGNAL_INPUT     = 2, //输入信号端口（ISP）
    Omn_PORTTYPE_SIGNAL_OUTPUT    = 3, //输出信号端口（OSP）
} Omn_PORT_TYPE;

/****************************************** 
* 流类型
******************************************/
typedef enum Omn_STREAM_TYPE_E
{
    Omn_STREAM_UNKNOW             = -1,
    Omn_STREAM_RECORD_GRAPHICS    = 0,    //RDP的图文流
    Omn_STREAM_RECORD_KEY         = 1,    //RDP的Key流
    Omn_STREAM_PLAY_GRAPHICS      = 2,    //PDP的图文流
    Omn_STREAM_PLAY_KEY           = 3,    //PDP的Key流
    Omn_STREAM_SIGNAL_IN          = 4,    //ISP的输入流
    Omn_STREAM_SIGNAL_OUT         = 6,    //OSP的输出流
    Omn_STREAM_MIXER_GRAPHICS     = 10,   //Mixer输出的图文流
    Omn_STREAM_MIXER_KEY          = 11    //Mixer输出的Key流
} Omn_STREAM_TYPE;

/****************************************** 
* 描述流信息的数据结构
******************************************/
typedef struct SOmnStreamInfo_T
{
    Omn_STREAM_TYPE   enumStreamType;     //流类型
    Om_UINT32        dwStreamSourceNo;   //流编号(与相连端口编号一致)
} SOmnStreamInfo;

/******************************************
* 端口描述信息
******************************************/
typedef struct SOmnPortDesc_T
{
    Omn_PORT_TYPE enumPortType;//端口类型
    Om_UINT32    dwPortNo;    //端口编号
}SOmnPortDesc;

/******************************************
* SDI内嵌音频配置方式
* 与Omn_SetAudioEmbeddedChannel和Omn_SetAudioOutputConfig相关
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
* 定义NTSC制下分量信号互联标准， CAV是Component Analog Video的缩写
******************************************/
typedef enum Omn_CAV_STANDARD_E
{
    Omn_CAV_STANDARD_UNKNOW           = -1,
    Omn_CAV_STANDARD_SMPTE            = 0, //SMPTE/EBU N10标准
    Omn_CAV_STANDARD_NTSC_BETACAM     = 1, //BETACAM标准
    Omn_CAV_STANDARD_MII              = 2  //MII标准
} Omn_CAV_STANDARD;

/******************************************
* 定义NTSC制下黑电平的幅度
******************************************/
typedef enum Omn_VIDEO_BLACK_LEVEL_E
{
    Omn_VIDEO_BLACK_LEVEL_UNKNOW  = -1,
    Omn_VIDEO_PEDESTAL_OFF        = 0, //没有7.5 IRE的台阶
    Omn_VIDEO_PESESTAL_ON         = 1  //有7.5 IRE的台阶
} Omn_VIDEO_BLACK_LEVEL;

/******************************************
* 模拟音频信号电平
******************************************/
typedef enum Omn_AUDIO_FULL_LEVEL_E
{
    Omn_AUDIO_FULL_LEVEL_UNKNOW   = -1,
    Omn_AUDIO_FULL_LEVEL_24DB     = 0, //音频满幅度电平为24DB
    Omn_AUDIO_FULL_LEVEL_22DB     = 1  //音频满幅度电平为22DB
} Omn_AUDIO_FULL_LEVEL;

/******************************************
* Scaler配置信息
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
    Omn_SCALE_DEINTERLAC_DISABLE = 0, //不带Deinterlacing
    Omn_SCALE_DEINTERLAC_ENABLE = 1   //带Deinterlacing
} Omn_SCALE_DEINTERLAC_TYPE;

typedef struct SOmnUpDownCrossConvertParam_T
{
    OmnVIDEO_SCALE_TYPE      enumScaleType;          //上下变换使用的变换类型，对应OmnVIDEO_SCALE_TYPE中的枚举值
    Omn_SCALE_DEINTERLAC_TYPE enumDeinterlacType;     //上下变化使用Deinterlace类型 0：不带，1：带
    OmnCOLORSPACE_CONVERT    enumColorSpaceConvert;  //上下变化使用颜色空间转换类型 0：不做颜色空间转换，1：601->709转换，2：709->601转换
    Om_UINT32                Reserved[9];            //保留扩展用，全0
} SOmnUpDownCrossConvertParam;

/******************************************
* ISP的配置信息
******************************************/
typedef struct SOmnInputSignalPortParam_T
{
    Omn_VIDEO_STANDARD        enumVideoStandard;    //端口制式
    Om_UINT32                 dwVideoClipFlag;      //视频限幅标志
    Omn_VIDEO_SIGNAL_TYPE     enumVideoSigType;     //视频源
    Omn_AUDIO_SIGNAL_TYPE     enumAudioSigType;     //音频源
    Omn_AUDIO_FULL_LEVEL      enumAudioLevel;       //模拟音频满电平设置，暂不支持
    Omn_EMBEDDEDAUDIO_CONFIG  enumEmbeddedAudioCfg; //SDI信号嵌入音频的通道配置，暂不支持
    Omn_CAV_STANDARD          enumCavStd;           //CAV设置，Ntsc制式下使用，暂不支持
    Omn_VIDEO_BLACK_LEVEL     enumVideoBlackLevel;  //黑电平设置，Ntsc制式下使用，暂不支持
    Om_BOOL                   bEnableDeinterlace;   //是否对隔行采集信号进行去交织处理，仅Server-400K支持
    Om_BOOL                   bEnableKeyLumaUpscale;//将键信号亮度的范围由16~235扩大至0~255，仅Server-400K支持
    Om_UINT32                 Reserved[7];          //保留扩展用，全0
} SOmnInputSignalPortParam;

/******************************************
* OSP的配置信息
******************************************/
typedef struct SOmnOutputSignalPortParam_T
{
    Omn_VIDEO_STANDARD        enumVideoStandard;        //端口制式
    Om_UINT32                 dwVideoClipFlag;          //视频限幅标志
    Omn_VIDEO_SIGNAL_TYPE     enumVideoSigType;         //模拟视频的输出配置，暂不支持
    Om_INT32                  dwHrznPhase;              //OSP的行相位
    Om_INT32                  dwVrtclPhase;             //OSP的场相位设置
    Om_DOUBLE                 dSubCarrierPhase;         //附载波相位，暂不支持
    Omn_AUDIO_FULL_LEVEL      enumAudioLevel;           //模拟音频满电平设置，暂不支持
    Omn_EMBEDDEDAUDIO_CONFIG  enumEmbeddedAudioCfg;     //SDI信号嵌入音频的通道配置，暂不支持
    Omn_CAV_STANDARD          enumCavStd;               //CAV设置，Ntsc制式下使用，暂不支持
    Omn_VIDEO_BLACK_LEVEL     enumVideoBlackLevel;      //黑电平设置，Ntsc制式下使用，暂不支持
    SOmnStreamInfo            sExecptionLoopBackSource; //Watchdog触发时的环通设置，暂不支持
    Om_INT32                  nKeyPhase;                //OSP的键相位，只限Server-400卡使用
    Om_BOOL                   bEnableKeyLumaDownscale;  //将键信号亮度的范围由0~255缩小至16~235，仅Server-400K支持
    Om_UINT32                 Reserved[7];              //保留扩展用，全0
} SOmnOutputSignalPortParam;

/******************************************
* RDP的配置信息
******************************************/
typedef struct SOmnRecordDataPortParam_T
{
    Omn_VIDEO_STANDARD    enumVideoStandard;  //端口制式
    Omn_COLOR_FORMAT      enumColorFormat;    //颜色格式
    SOmnAudioMediaInfo    enumAudioMediaInfo; //音频属性信息，暂不支持
    Om_UINT32             dwFrameBufferAmount;//采集队列的长度
    Om_UINT32             Reserved[9];        //保留扩展用，全0
} SOmnRecordDataPortParam;

/******************************************
* PDP的配置信息
******************************************/
typedef struct SOmnPlayDataPortParam_T
{
    Omn_VIDEO_STANDARD    enumVideoStandard;      //端口制式
    Omn_COLOR_FORMAT      enumColorFormat;        //颜色格式
    SOmnAudioMediaInfo    enumAudioMediaInfo;     //音频属性信息，暂不支持
    Om_UINT32             dwFrameBufferAmount;    //播出队列的长度
    Om_UINT32             Reserved[9];            //保留扩展用，全0
} SOmnPlayDataPortParam;

/******************************************
* Mixer两路输入视频之间的关系
******************************************/
typedef enum Omn_MIXER_MODE_E
{
    Omn_MIXER_UNKNOWN         = -1,
    Omn_BYPASS_INPUTA         = 0, //直通A路输入视频信号
    Omn_BYPASS_INPUTB         = 1, //直通B路输入视频信号
    Omn_BYPASS_BLACK          = 2, //直通黑场视频信号
    Omn_INPUTA_OVER_BLACK     = 3, //A路输入视频信号叠在黑场上
    Omn_INPUTB_OVER_BLACK     = 4, //B路输入视频信号叠在黑场上
    Omn_INPUTA_OVER_INPUTB    = 5, //A路输入视频(图文+Key)叠在B路视频(图文)上,输出A路输入Key信号
    Omn_MIXER_MODE_UNKNOWN1   = 6, //未定义项
    Omn_INPUTA_MIXER_INPUTB   = 7, //A路输入视频(图文+Key)叠在B路视频(图文+Key)上,输出两路输入的混合Key信号
    Omn_MIXER_MODE_UNKNOWN2   = 8  //未定义项
} Omn_MIXER_MODE;

/******************************************
* Mixer两路输入音频之间的关系
******************************************/
typedef enum Omn_MIXER_AUDIO_MODE_E
{
    Omn_MIXER_AUDIO_UNKNOWN   = -1,
    Omn_BYPASS_AUDIO_INPUTA   = 0, //输出InputA相关的音频
    Omn_BYPASS_AUDIO_INPUTB   = 1, //输出InputB相关的音频
    Omn_MIXER_AUDIO_UNKNOWN2  = 2  //未定义项
} Omn_MIXER_AUDIO_MODE;

/******************************************
* Mixer的配置参数
******************************************/
typedef struct SOmnMixerCfg_T
{
    Omn_MIXER_MODE        enumMixerMode;             //视频Mixer模式
    Omn_MIXER_AUDIO_MODE  enumMixerAudioMode;        //音频选择模式
    SOmnStreamInfo        sInputAGraphicsSourceInfo; //Mixer输入A的图文数据流来源
    SOmnStreamInfo        sInputAKeySourceInfo;      //Mixer输入A的Key数据流来源
    SOmnStreamInfo        sInputBGraphicsSourceInfo; //Mixer输入B的图文数据流来源
    SOmnStreamInfo        sInputBKeySourceInfo;      //Mixer输入B的Key数据流来源    
} SOmnMixerCfg, SOmnMixerParam;

/******************************************
* 混音配置参数，音频源分别对应视频Mixer混叠
* 的视频源
******************************************/
typedef struct SOmnAudioMixerCfg_T
{
    Om_BOOL         bEnableAudioMixer;     //是否使能混音功能
    Om_UINT32       dwInputAVolume[16];    //视频Mixer输入A对应音频的音量，使用的倍增因子范围为0~200，其中0~100为降音，100~200为扩音。暂时只支持8路
    Om_UINT32       dwInputBVolume[16];    //视频Mixer输入B对应音频的音量，使用的倍增因子范围为0~200，其中0~100为降音，100~200为扩音，暂时只支持8路
    Om_UINT32       Reserved[32];          //保留供扩展使用，必须设为全0
}SOmnAudioMixerCfg;

/******************************************
* 视音频运行时信息，用于回调函数传递参数
******************************************/
typedef struct SOmn_RunTimeInfo_T
{
    Om_UINT32   dwInterruptCount;    //信号端口的帧中断计数
    Om_UINT32   dwCallBackCount;     //信号端口的回调计数
    Om_UINT32   dwBufferRemainCount; //信号端口的Buffer缓存队列等待处理帧数
    Om_UINT32   dwHardwareFrameCount;//信号端口已处理帧数
    Om_UINT32   dwLostFrameCount;    //信号端口的丢帧数
    Om_UINT32   InterruptType;       //在场方式时描述中断的类型: 0 odd, 1 even, 3 frame
    Om_UINT32   Reserved[9];         //保留供扩展使用，必须设为全0
} SOmn_RunTimeInfo, *PSOmn_RunTimeInfo;

/******************************************
* 同步提交方式下，SDK传递给回调函数的信息
******************************************/
typedef struct SOmn_SyncVACallbackInfo_T
{
    SOmn_RunTimeInfo sRunTimeInfo;   //报告端口运行时信息
    Om_UINT32   dwAudioSampleCount;  //信号端口需要处理的音频采样点数
    Om_UINT32   dwGenlockCount;     //Genlock时钟中断计数，只适用于播出
    Om_UINT32   Reserved[8];         //保留供扩展使用，必须设为全0
} SOmn_SyncVACallbackInfo, *PSOmn_SyncVACallbackInfo;

/******************************************
* 播出回显时，SDK传递给回调函数的信息
******************************************/
typedef struct SOmn_HLBCallbackInfo_T
{
    Om_UINT_PTR      dwUpdateNo;  //提交的索引号，用于定位回显帧数
    Om_UINT8         bNeedPlay;   //表明是否用于回显
    Om_UINT8         bReserved[3];//保留供扩展使用，必须设为全0
    Om_UINT32        Reserved[9]; //保留供扩展使用，必须设为全0
} SOmn_HLBCallbackInfo, *PSOmn_HLBCallbackInfo;

/******************************************
* 用户内存描述结构
******************************************/
typedef struct SOmnBufferInfo_T
{
    Om_PVOID   pBufferAddr;          //Buffer地址，要求地址满足16字节对齐
    Om_UINT32   dwBufferSize;        //Buffer长度
    Om_UINT32   dwBufferLinePitch;   //Buffer行长度,主要针对一些来自DirectX的图像Buffer，每行之间都有空洞
} SOmnBufferInfo;

/******************************************
* 数据提交类型
******************************************/
typedef enum Omn_BUFFERUPDATE_FLAG_E
{
    Omn_BUFUPDATEFLAG_UNKNOW         = -1,
    Omn_BUFUPDATEFLAG_FIRSTFIELD     = 0, //用1个Buffer只提交第一场
    Omn_BUFUPDATEFLAG_SECONDFIELD    = 1, //用1个Buffer只提交第二场
    Omn_BUFUPDATEFLAG_BOTHFIELD      = 2, //用2个Buffer同时提交两场
    Omn_BUFUPDATEFLAG_FRAME          = 3, //用1个Buffer提交一帧
    Omn_BUFUPDATEFLAG_FRAME_SEGMENT  = 4  //暂不支持
} Omn_BUFFERUPDATE_FLAG;

/******************************************
* 调用Omn_UpdateBuffer时用于指定SOmnBufUpdataInfo
* 结构psBufferArr[]数组的下标
******************************************/
typedef enum Omn_UPDATE_BUFFER_INDEX_E
{
    Omn_UPDATEBUFFER_INDEX_UNKNOW             = -1,
    Omn_UPDATEBUFFER_INDEX_FRAME              = 0, //帧方式下用
    Omn_UPDATEBUFFER_INDEX_FIRSTFIELD         = 0, //场方式下用
    Omn_UPDATEBUFFER_INDEX_Y_ZONE             = 0, //用于将YUV分别存放时用
    Omn_UPDATEBUFFER_INDEX_SECONDFIELD        = 1, //场方式下用
    Omn_UPDATEBUFFER_INDEX_U_ZONE             = 1, //用于将YUV分别存放时用
    Omn_UPDATEBUFFER_INDEX_V_ZONE             = 2, //用于将YUV分别存放时用
    Omn_UPDATEBUFFER_INDEX_KEY                = 3, //KEY数据区域，暂不支持
    Omn_UPDATEBUFFER_INDEX_AUDIO              = 4, //音频数据区域
    Omn_UPDATEBUFFER_INDEX_VANC_FRAME         = 5, //帧方式下，一帧VANC数据
    Omn_UPDATEBUFFER_INDEX_VANC_FIRSTFIELD    = 5, //场方式下，奇场VANC数据
    Omn_UPDATEBUFFER_INDEX_OOB                = 6, //VITC/LTC/AFD的数据存储区域
    Omn_UPDATEBUFFER_INDEX_VANC_SECONDFIELD   = 7, //场方式下，偶场VANC数据
    Omn_UPDATEBUFFER_INDEX_MAX                = 8
} Omn_UPDATE_BUFFER_INDEX;

/******************************************
* 同步提交Buffer时的数据结构
* 调用Omn_UpdateBuffer时使用
******************************************/
#define HAS_SUBSEQUENCE_MAGIC 19
typedef struct SOmnBufUpdataInfo_T
{
    Om_UINT32            dwSize;             //SOmnBufUpdataInfo结构的大小，单位是Byte    
    Om_UINT_PTR          dwUpdateNo;         //每次提交都有索引号，便于SDK通过回调函数通知应用程序    
    Omn_BUFFERUPDATE_FLAG enumBufUpdateFlag;  //此次提交的类型
    Omn_VIDEOSCAN_MODE    enumVideoScanType;  //视频扫描帧场数据排列方式(Omn_BUFUPDATEFLAG_FRAME才有效)    
    Omn_RECT              sValidRect;         //暂不支持此参数，必须设为全0
    SOmnBufferInfo        psBufferArr[Omn_UPDATEBUFFER_INDEX_MAX];  //IO Buffer描述数组
    Om_UINT8             u8HasSub;           //描述该结构之后是否还跟随一个相同的结构，如果为HAS_SUBSEQUENCE_MAGIC表明后面还有跟随，否则后面没有跟随
    
    Om_UINT32            dwReserved[17];     //保留供扩展使用，必须设为全0
    Om_UINT32            dwGenlockIntCount;  //对于Server-400K卡，SDI采集时，表示采集当前帧/场时的Genlock中断计数
    Om_UINT32            dwTsLength;         //进行ASI信号采集时，返回采集TS的长度，单位是byte
    Om_UINT32            dwDMAConsumption;   //DMA传输消耗的时间，100ns为单位，如果为0xffffffff,表明DMA传输有故障
    Om_UINT8             u8IsInterlace;      //对于CAP-500卡,采集HDMI信号时，返回当前HDMI输入信号的扫描方式为逐行还是隔行(RDP用)，0：逐行，1：隔行。其它卡不支持，返回0xff
    Om_UINT8             u8FrameRate;        //对于CAP-500卡,采集HDMI信号时，返回当前HDMI输入信号的帧率(RDP用)，单位是fps。其它卡不支持，返回0xff    
    Om_UINT8             u8Reserved[4];      //保留供扩展使用，必须设为全0
    Om_UINT8             u8IsOdd;            //在Server-400K卡进行去隔行采集时，表示当前为奇场或偶场去隔行得到，1：表示奇场去隔行得到的帧，0：表示偶场去隔行得到的帧
    Om_UINT32            dwTimeStamp;        //同步提交方式下，返回时间戳(RDP用)
    Om_UINT64            dwGlobalTimeStamp;  //同步提交方式下，返回板卡全局时间戳(RDP用)，用于多路采集时的同步
    Omn_RECT              sReturnRect;        //对于RDP，返回采集视频的RECT信息；PDP不支持，返回全0
} SOmnBufUpdataInfo;

/******************************************
* 源、目标区域映射信息 
******************************************/
typedef struct SOmnRectMap_T
{
    Omn_RECT        sSrcValidRect;  //源选取的矩形区域（PDP、ISP为源）
    Omn_RECT        sDestValidRect; //目标放置的矩形区域（RDP、OSP为目标）
    Om_BOOL         bValid;         //映射信息是否有效，Om_FALSE表示无效，Om_TRUE表示有效
}SOmnRectMap;

/******************************************
* 同步提交Buffer是的扩展数据结构
* 调用Omn_UpdateBuffer_Ex1时使用
******************************************/
typedef struct SOmnBufUpdateInfo_Ex1_T
{
    Om_UINT32                   dwSize;             //SOmnBufUpdateInfo_Ex1结构的大小
    Om_UINT_PTR                 dwUpdateNo;         //每次提交都有索引号，便于SDK通过回调函数通知应用程序
    Omn_BUFFERUPDATE_FLAG       enumBufUpdateFlag;  //此次提交的类型
    Omn_VIDEOSCAN_MODE          enumVideoScanType;  //视频扫描帧场数据排列方式(Omn_BUFUPDATEFLAG_FRAME才有效)  
    SOmnBufferInfo              psBufferArr[Omn_UPDATEBUFFER_INDEX_MAX]; //IO Buffer描述数组
    SOmnRectMap                 sMapInfo[8];        //位块映射信息，每一成员组描述了一对源到目标的位块映射信息，数组的索引为目标端口ID号，目前仅PDP支持
    Om_UINT8                    u8HasSub;           //描述该结构之后是否还跟随一个相同的结构，如果为HAS_SUBSEQUENCE_MAGIC表明后面还有跟随，否则后面没有跟随

    Om_UINT32                   dwReserved[29];
    Om_UINT32                   dwGenlockIntCount;  //对于Server-400K卡，SDI采集时，表示采集当前帧/场时的Genlock中断计数
    Om_UINT32                   dwTsLength;         //进行ASI信号采集时，返回采集TS的长度，单位是byte
    Om_UINT32                   dwDMAConsumption;   //DMA传输消耗的时间，100ns为单位，如果为0xffffffff,表明DMA传输有故障
    Om_UINT8                    u8IsInterlace;      //对于CAP-500卡,采集HDMI信号时，返回当前HDMI输入信号的扫描方式为逐行还是隔行(RDP用)，0：逐行，1：隔行。其它卡不支持，返回0xff
    Om_UINT8                    u8FrameRate;        //对于CAP-500卡,采集HDMI信号时，返回当前HDMI输入信号的帧率(RDP用)，单位是fps。其它卡不支持，返回0xff    
    Om_UINT8                    u8IsOdd;            //在Server-400K卡进行去隔行采集时，表示当前为奇场或偶场去隔行得到，1：表示奇场去隔行得到的帧，0：表示偶场去隔行得到的帧
    Om_UINT32                   dwTimeStamp;        //同步提交方式下，返回时间戳(RDP用)    
    Om_UINT64                   dwGlobalTimeStamp;  //同步提交方式下，返回板卡全局时间戳(RDP用)，用于多路采集时的同步
    SOmnRectMap                 sReturnMapInfo[8];  //与sMapInfo一一对应的操作返回信息
}SOmnBufUpdateInfo_Ex1;


/******************************************
* VANC传输配置信息
******************************************/
typedef struct SOmn_VANC_TRANS_T
{
    Om_UINT32               dwSize;             //此数据结构的大小，以字节为单位
    Omn_PORT_TYPE            enumDataPortType;   //数据端口类型，使能哪个数据端口的VANC功能
    Om_UINT32               dwDatePortNo;       //数据端口号，使能哪个数据端口的VANC功能
    Om_BOOL                 bEnable;            //使能数据端口的VANC传输功能
    Om_UINT32               dwVANCTypeFlag;     //VANC数据的存储方式：0,Y、UV各个分量都用于存储VANC数据；1,使用Y分量存储VANC数据；2,使用UV分量存储VANC数据
}SOmn_VANC_TRANS, *PSOmn_VANC_TRANS;

/******************************************
* VANC查询信息
******************************************/
typedef struct SOmn_VANC_INFO_T
{
    //查询前的输入信息
    Om_UINT32               dwSize;           //此数据结构的大小，以字节为单位
    Omn_PORT_TYPE            enumDataPortType; //数据端口类型，查询哪个数据端口的VANC支持情况
    Om_UINT32               dwDatePortNo;     //数据端口号，查询哪个数据端口的VANC支持情况
    Om_UINT32               dwBufFlag;        //查询奇场、偶场、帧的VANC支持信息，表示方式: 0 奇场；1 偶场；3 帧

    //查询的返回信息
    Omn_VIDEO_STANDARD       enumVidStd;       //当前数据端口的视频制式
    Omn_COLOR_FORMAT         enumVANCBufFmt;   //VANC Buffer使用的颜色格式
    Om_UINT32               dwVANCStartLine;  //VANC 起始行（含）
    Om_UINT32               dwVANCEndLine;    //VANC 结束行（含）
    Om_UINT32               dwVANCBufSize;    //使用者需要准备的VANC Buffer的大小，以字节为单位
    Om_UINT32               dwVANCLinePitch;  //VANC 每行所占据的存储空间大小，以字节为单位
}SOmn_VANC_INFO, *PSOmn_VANC_INFO;

/****************************************** 
* 3D播出配置信息
******************************************/
typedef struct SOmn3DTrans_T
{
    Omn_PORT_TYPE   enumDataPortType;  //PDP/RDP类型，使能哪个数据端口的3D功能
    Om_UINT32      dwDatePortNo;      //端口ID
    Om_BOOL        bEnable;           //使能开关    
    Om_UINT32      previewSrc;        //暂不支持，全0
}SOmn3DTrans, *PSOmn3DTrans;

/****************************************** 
* 多路同步采集信息
******************************************/
typedef struct SOmnMultiChannelTrans_T 
{
    Omn_PORT_TYPE   enumDataPortType;         //PDP/RDP类型
    Om_UINT32      dwDatePortNo;             //端口ID
    Om_UINT8       SignalPortSelection[32];  //第i个OSP/ISP的选择情况，0表示不选，1表示选择
}SOmnMultiChannelTrans;

/****************************************** 
* 3G LevelB配置信息，不支持
******************************************/
typedef struct SOmn3GLevelB_T
{
    Omn_PORT_TYPE enumSignalPortType;  //信号端口类型，使能哪个信号端口的3G LevelB
    Om_UINT32      dwDatePortNo;      //信号端口号，使能哪个信号端口的3G LevelB
    Om_BOOL        bEnable;           //使能开关
    Om_UINT32      dwStreamCount;     //数据流数量（1单内容流，2双内容流）
}SOmn3GLevelB, *PSOmn3GLevelB;

/******************************************
* 信号端口自适应配置信息，不支持
******************************************/
typedef struct SOmnSignalAdaptation_T
{
    Omn_PORT_TYPE enumSignalPortType;  //信号端口类型
    Om_UINT32      dwSignalPortNo;    //信号端口号
    Om_BOOL        bSupported;        //用于查询该信号端口是否支持信号自适应功能
    Om_BOOL        bEnable;           //使能开关
}SOmnSignalAdaptation;

/******************************************
* 用于获取或设置GPIO的信息，不支持
******************************************/
typedef struct SOmnBoardTallyInfo_T
{
    Om_UINT8 u8TallyItfAmt;     //支持的Tally接口数量，调用者只读，目前最多支持6个Tally接口，和硬件版本有关
    Om_UINT8 u8TallyEnable;     //Tally接口使能开关，0:Audio,1:Tally
    Om_UINT8 u8TallyIOMask;     //Tally接口IO属性掩码，0:Input,1：Output
    Om_UINT8 u8TallyStatusMask; //设置或获取到的Tally接口状态掩码，0:灭,1:亮
    Om_UINT8 u8AudioSelect;     //音频接口选择，0:AES/EBU, 1:Analog
    Om_UINT8 u8Reserved[3];     //扩展用，必须设为全0
    Om_UINT32 Reserved[2];      //扩展用，必须设为全0
} SOmnBoardTallyInfo;

/******************************************
* Tally配置信息
******************************************/
typedef struct SOmnTallyInfo_T
{
    Om_UINT32				dwTallyAmount;	//Tally的数量,可用于查询
    Om_UINT32				dwTallyType;	//Tally类型，0:电平式，1:开关式
    Om_UINT32				dwStatusMask;	//设置的输出状态，电平式：0:灭，1:亮；开关式：0:断开，1:接通
}SOmnTallyInfo;

/******************************************
* Mic音量配置信息
******************************************/
typedef struct SOmn_MIC_VOLUME_T
{
    Om_UINT32 u32MicIdx;     //Server卡可以支持两个Mic输入，此变量用于描述Mic的Id号
    Om_UINT32 u32MicVolume;  //Mic音量值，取值范围0~60，单位为dB
}SOmn_MIC_VOLUME;

/******************************************
* Mic48V电源配置信息
******************************************/
typedef struct SOmn_MIC_48V_T
{
    Om_UINT32 u32MicIdx;     //Server卡可以支持两个Mic输入，此变量用于描述Mic的Id号
    Om_UINT32 u32Enable48V;  //使能Mic的48V幻象电源, 0:关闭，1:使能
}SOmn_MIC_48V;

/******************************************
* LTC数值，解析依据SMPTE-12M-1-2008，
* SMPTE-12M-2-2008和SMPTE-309M-1999
******************************************/
typedef struct SOmn_LTC_VALUE_T
{
    Om_UINT32 dwHour; //时
    Om_UINT32 dwMin; //分
    Om_UINT32 dwSec; //秒
    Om_UINT32 dwFrm; //帧
    Om_BOOL  bTimeSpecified;//时间是否明确，参见SMPTE-12M-1-2008
    Om_UINT32 dwYear; //年
    Om_UINT32 dwMon; //月
    Om_UINT32 dwDay; //日
    Om_BOOL  bDateSpecified;//日期是否明确，参见SMPTE-12M-1-2008
    Om_UINT64 qwOriginLTCVal;//原始LTC值,参见SMPTE-12M-2-2008
}SOmn_LTC_VALUE;

/******************************************
* LTC输出配置
******************************************/
typedef struct SOmn_LTC_OUT_CONFIG_T
{
    Om_UINT32 dwOutputNo;//LTC输出通道索引号
    Om_BOOL  bLoopout;//是否环出相同索引号输入LTC的信号，Om_TRUE:环出相同索引号输入LTC的信号，Om_FALSE：不环出，而是作为独立输出
}SOmn_LTC_OUT_CONFIG;

/******************************************
* 采集时LTC输入源的选择
******************************************/
typedef enum Omn_LTC_SOURCE_TYPE_E
{
    Omn_LTCSOURCEYPTE_RESPECTIVE = 0,//各采集通道LTC源自各自的LTC输入
    Omn_LTCSOURCETYPE_IN0   = 1,//所有采集通道LTC都源自LTC输入0
    Omn_LTCSOURCETYPE_IN1   = 2,//所有采集通道LTC都源自LTC输入1
    Omn_LTCSOURCETYPE_IN2   = 3,//所有采集通道LTC都源自LTC输入2
    Omn_LTCSOURCETYPE_IN3   = 4 //所有采集通道LTC都源自LTC输入3
}Omn_LTC_SOURCE_TYPE;

/******************************************
* 外置LTC输出来源信息
******************************************/
typedef struct SOmnLTCPlaySource_T
{
    Om_UINT32   dwLTCNo; //输出LTC编号
    Om_UINT32   dwOSPNo; //提供LTC输出来源的OSP索引号
}SOmnLTCPlaySource;

/******************************************
* 配置KeyMode工作模式时，选择的端口组合
******************************************/
typedef enum Omn_PORTPAIR_E
{
    Omn_PORTPAIR_Unknown   = 0,
    Omn_PORTPAIR_0_1       = 1, //端口0、1组合
    Omn_PORTPAIR_2_3       = 2, //端口2、3组合
    Omn_PORTPAIR_4_5       = 3, //端口4、5组合
    Omn_PORTPAIR_6_7       = 4, //端口6、7组合
    Omn_PORTPAIR_Max
}Omn_PORTPAIR;

/******************************************
* 支持KeyMode采集、播出的配置
******************************************/
typedef struct SOmnKeyModeConfig_T
{
    Omn_PORTPAIR            enumPortPairType;   //KeyMode端口组合
    Om_BOOL                 bEnableKeyMode;     //KeyMode使能开关, Om_FALSE:关闭，Om_TRUE：使能
}SOmnKeyModeConfig;

/******************************************
* Keyer资源属性信息
******************************************/
typedef struct SOmnKeyProfile_T
{
    Om_UINT32       dwRDPPortNo;    //应用获取Keyer抠像结果的RDP资源号    
    Om_UINT32       reserved[4];    //扩展用，必须设为全0
}SOmnKeyProfile;

/******************************************
* 背景类型
******************************************/
typedef enum Omn_BACKGROUND_COLOR_E
{
    Omn_BGCOLOR_Unknown    = 0,
    Omn_BGCOLOR_RED        = 1,  //红背景
    Omn_BGCOLOR_YELLOW     = 2,  //黄背景
    Omn_BGCOLOR_GREEN      = 3,  //绿背景
    Omn_BGCOLOR_CYAN       = 4,  //青背景
    Omn_BGCOLOR_BLUE       = 5,  //蓝背景
    Omn_BGCOLOR_PINK       = 6,  //品红背景
    Omn_BGCOLOR_GRAY       = 7   //灰背景
} Omn_BACKGROUND_COLOR;

/******************************************
* 色度值处理区间，该区间根据选取的像素值
* 计算得到，SDK使用者调用Omn_InitKeyerParam()
* 进行计算。注意：该组值不可更改。
******************************************/
typedef struct SOmnKeyerBasicParam_T
{      
    Omn_BACKGROUND_COLOR enumBGColor;      //背景颜色，通过Omn_InitKeyerParam()计算得出，不可用户调整
    Om_FLOAT             fHMinLimit;       //色度区间下限，通过Omn_InitKeyerParam()计算得出，不可用户调整
    Om_FLOAT             fHMaxLimit;       //色度区间上限，通过Omn_InitKeyerParam()计算得出，不可用户调整
    Om_FLOAT             fHSpillMin;       //溢色处理的色度最小值，通过Omn_InitKeyerParam()计算得出，不可用户调整
    Om_FLOAT             fHSpillMax;       //溢色处理的色度最大值，通过Omn_InitKeyerParam()计算得出，不可用户调整
}SOmnKeyerBasicParam;

/******************************************
* Keyer背景参数
******************************************/
typedef struct SOmnKeyerBGParam_T
{
    Om_FLOAT             fHMax;             //色度最大值，取值范围[fHMinLimit, fHMaxLimit],可用户调整
    Om_FLOAT             fHMin;             //色度最小值，取值范围[fHMinLimit, fHMaxLimit],可用户调整
    Om_UINT32            dwAlphaSLevelMax;  //Alpha通道S最大值（0~1000）,可用户调整
    Om_UINT32            dwAlphaSLevelMin;  //Alpha通道V最小值（0~1000）,可用户调整
    Om_UINT32            dwAlphaBLevelMax;  //Alpha通道V最大值（0~1000）,可用户调整
    Om_UINT32            dwAlphaBLevelMin;  //Alpha通道V最小值（0~1000）,可用户调整
}SOmnKeyerBGParam;

/******************************************
* Keyer后处理参数
******************************************/
typedef struct SOmnKeyerPostprocessParam_T
{
    Om_UINT32            dwSpillHLevel;   //溢色处理色度偏移的程度（0~1000）,可用户调整
    Om_UINT32            dwSpillHRange;   //溢色处理色度偏移的范围（0~1000）,可用户调整
    Om_UINT32            dwSpillSLevel;   //溢色处理饱和度压缩的程度（0~1000）,可用户调整
    Om_UINT32            dwSpillSRange;   //溢色处理饱和度压缩的范围（0~1000）,可用户调整

    Om_UINT32            dwDenoiseLevel;  //前景降噪的程度（0~1000）,可用户调整
    Om_UINT32            dwDenoiseRange;  //前景降噪的范围（0~1000）,可用户调整

    Om_INT32             nEdge;           //边缘处理（-3~3）,可用户调整
    Om_INT32             nBlur;           //模糊处理（0~3）,可用户调整
}SOmnKeyerPostprocessParam;

/******************************************
* Keyer抠像区域
******************************************/
typedef struct SOmnKeyerRect_T
{
    Omn_RECT            sRect1;           //抠像的区域1
    Om_BOOL             bRect1Enabled;    //是否对区域1进行抠像
    Omn_RECT            sRect2;           //抠像的区域2
    Om_BOOL             bRect2Enabled;    //是否对区域2进行抠像
}SOmnKeyerRect;

/******************************************
* Keyer参数
******************************************/
typedef struct SOmnKeyerParam_T
{    
    SOmnKeyerBasicParam         sBasic;             //基本抠像信息，根据传入像素点计算得到，不可用户调整
    SOmnKeyerBGParam            sBGParam;           //背景参数,可用户调整
    SOmnKeyerPostprocessParam   sPostProcParam;     //后处理参数,可用户调整
    SOmnKeyerRect               sRect;              //抠像区域,可用户调整
    Om_BOOL                     bDeinterlace;       //对隔行扫描视频进行去隔行处理
    Om_UINT32                   Reserved[3];        //扩展用，必须设为全0
} SOmnKeyerParam;


/******************************************
* SDK返回值类型
******************************************/
typedef enum Omn_RETURN_CODE_E
{
    Omn_ERR_DRV                   = 0xffff0000, //驱动返回错误，低16bit为驱动返回的错误码
    Omn_ERR_FAILED                = 0x80000001, //失败
    Omn_ERR_INVALID_PARAM         = 0x80000002, //传入参数无效
    Omn_ERR_ACCESS_DENY           = 0x80000003, //拒绝访问
    Omn_ERR_SYS_MEMORY            = 0x80000004, //系统内存操作失败
    Omn_ERR_BOARD_MEMORY          = 0x80000005, //板卡内存操作失败
    Omn_ERR_UNSUPPORTED           = 0x80000006, //SDK不支持该功能
    Omn_ERR_VERSION               = 0x80000007, //SDK版本错误
    Omn_ERR_INVALID_STATUS        = 0x80000008, //当前SDK运行状态无效
    Omn_ERR_NO_ITF                = 0x80000009, //没有该可用接口
    Omn_ERR_OBJ_NOT_FOUND         = 0x8000000a, //未找到目标对象
    Omn_ERR_BAD_INTERNAL_INFO     = 0x8000000b, //内部错误
    Omn_ERR_NOT_INIT              = 0x8000000c, //SDK未初始化
    Omn_ERR_RESOURCE_NOTENOUGH    = 0x8000000d, //SDK资源不足
    Omn_ERR_ADDR_NOT_ALIGNED      = 0x8000000e,//传入各类数据内存地址有不满足32字节地址对齐的情况
    //此处扩展错误信息

    Omn_SUCCESS                   = 0x00000000, //成功

    Omn_IMPLICT_RULE              = 0x00000001, //不符合使用规则
    Omn_DO_NOTHING                = 0x00000002, //不做任何操作，直接返回
    //此处扩展警告信息
}Omn_RETURN_CODE, Om_HRESULT;
#define Om_OK    Omn_SUCCESS
#define Om_FAIL    Omn_ERR_FAILED

/******************************************
* 定义通用回调函数类型
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

