#ifndef Omn_VACOMMON_DEF_H_
#define Omn_VACOMMON_DEF_H_

/*******************************************************************************
* Copyright (c) 2016 Beijing Redlink Information Technology Co.,LTD
* 
* Beijing Redlink Information Technology Co.,LTD licenses this software under specific terms and
* conditions.  Use of any of the software or derivatives thereof in any
* product without a Beijing Redlink Information Technology Co.,LTD PCI card is strictly prohibited. 
* 
* Beijing Redlink Information Technology Co.,LTD provides this software AS IS, WITHOUT ANY WARRANTY,
* EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF
* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  Beijing Redlink Information Technology Co.,LTD makes no guarantee
* or representations regarding the use of, or the results of the use of,
* the software and documentation in terms of correctness, accuracy,
* reliability, currentness, or otherwise; and you rely on the software,
* documentation and results solely at your own risk.
* 
* IN NO EVENT SHALL Beijing Redlink Information Technology Co.,LTD BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
* LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
* OF ANY KIND.  IN NO EVENT SHALL Beijing Redlink Information Technology Co.,LTD'S TOTAL LIABILITY EXCEED THE SUM
* PAID TO Beijing Redlink Information Technology Co.,LTD FOR THE PRODUCT LICENSED HEREUNDER.
* 
******************************************************************************/

/******************************************************************************
*
* File Name:
*
*     Omni_VACommonDef.h
*
* Description:
*
*
* 描述:
*
*     .
* Revision:
*
*
******************************************************************************/

#include "Omni_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Omn_VIDEO_STANDARD_E // 视频制式标准
{
    OmnVIDEOSTANDARD_UNKNOW          = 0x00000000, // Unknow type.

    OmnVIDEOSTANDARD_PAL             = 0x00000001, // PAL video type.      //ITU.R-BT656
    OmnVIDEOSTANDARD_NTSC2997        = 0x00000002, // NTSC video type.      //ITU.R-BT656
    OmnVIDEOSTANDARD_NTSC30          = 0x00000004, // 30-frames/second generic type.

    OmnVIDEOSTANDARD_HD1080i_25      = 0x00000010, // HDTV 1920*1080*25 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080i_2997    = 0x00000020, // HDTV 1920*1080*29.97 type.   //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080i_30      = 0x00000040, // HDTV 1920*1080*30 type.    //SMPTE 274M

    OmnVIDEOSTANDARD_HD720p_2398     = 0x00000080, // HDTV 1280*720*23.98 type.   //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_24       = 0x00000200, // HDTV 1280*720*24 type.    //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_25       = 0x00000100, // HDTV 1280*720*25 type.    //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_2997     = 0x00001000, // HDTV 1280*720*29.97 type.   //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_30       = 0x00000008, // HDTV 1280*720*30 type.    //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_50       = 0x00000400, // HDTV 1280*720*50 type.    //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_5994     = 0x00000800, // HDTV 1280*720*59.94 type.   //SMPTE 296M
    OmnVIDEOSTANDARD_HD720p_60       = 0x00040000, // HDTV 1280*720*60 type.    //SMPTE 296M

    OmnVIDEOSTANDARD_HD1080p_2398    = 0x00002000, // HDTV 1920*1080*23.98 type.   //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080p_24      = 0x00004000, // HDTV 1920*1080*24 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080p_25      = 0x00008000, // HDTV 1920*1080*25 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080p_2997    = 0x00010000, // HDTV 1920*1080*29.97 type.   //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080p_30      = 0x00020000, // HDTV 1920*1080*30 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080P_4796    = 0x4E000000, // HDTV 1920*1080*47.96 type.   //     /@@@@/
    OmnVIDEOSTANDARD_HD1080P_48      = 0x4F000000, // HDTV 1920*1080*48 type.    //     /@@@@/
    OmnVIDEOSTANDARD_HD1080P_50      = 0x41000000, // HDTV 1920*1080*50 type.    //SMPTE 274M  /****/
    OmnVIDEOSTANDARD_HD1080P_5994    = 0x42000000, // HDTV 1920*1080*59.94 type.   //SMPTE 274M  /****/
    OmnVIDEOSTANDARD_HD1080P_60      = 0x43000000, // HDTV 1920*1080*60 type.    //SMPTE 274M  /****/

    OmnVIDEOSTANDARD_HD1080psf_2398  = 0x00080000, // HDTV 1920*1080*23.98 type.   //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080psf_24    = 0x00100000, // HDTV 1920*1080*24 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080psf_25    = 0x00200000, // HDTV 1920*1080*25 type.    //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080psf_2997  = 0x00400000, // HDTV 1920*1080*29.97 type.   //SMPTE 274M
    OmnVIDEOSTANDARD_HD1080psf_30    = 0x00800000, // HDTV 1920*1080*30 type.    //SMPTE 274M

    OmnVIDEOSTANDARD_2K1080P_2398    = 0x45000000, // 2K 2048*1080*23.98 type.    //AJA支持   /****/
    OmnVIDEOSTANDARD_2K1080P_24      = 0x46000000, // 2K 2048*1080*24 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080P_25      = 0x22100000, // 2K 2048*1080*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_2997    = 0x22200000, // 2K 2048*1080*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_30      = 0x22300000, // 2K 2048*1080*30 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_4796    = 0x22700000, // 2K 2048*1080*47.96 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_48      = 0x47000000, // 2K 2048*1080*48 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080P_50      = 0x22400000, // 2K 2048*1080*50 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_5994    = 0x22500000, // 2K 2048*1080*59.94 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_60      = 0x22600000, // 2K 2048*1080*60 type.    //     /@@@@/

    OmnVIDEOSTANDARD_2K1080Psf_2398  = 0x81000000, // 2K 2048*1080*23.98 type.    //AJA支持   /****/
    OmnVIDEOSTANDARD_2K1080Psf_24    = 0x82000000, // 2K 2048*1080*24 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080Psf_25    = 0x21100000, // 2K 2048*1080*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080Psf_2997  = 0x21200000, // 2K 2048*1080*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080Psf_30    = 0x21300000, // 2K 2048*1080*30 type.    //     /@@@@/

    OmnVIDEOSTANDARD_2K1556P_2398    = 0x83000000, // 2K 2048*1556*23.98 PLAYBACK.   //AJA支持   /****/
    OmnVIDEOSTANDARD_2K1556P_24      = 0x84000000, // 2K 2048*1556*24 PLAYBACK.   //AJA支持   /****/
    OmnVIDEOSTANDARD_2K1556Psf_2398  = 0x85000000, // 2K 2048*1556*23.98 PLAYBACK.   //AJA支持   /****/
    OmnVIDEOSTANDARD_2K1556Psf_24    = 0x86000000, // 2K 2048*1556*24 PLAYBACK.   //AJA支持   /****/

    OmnVIDEOSTANDARD_4K_3840P_2398   = 0xF1100000, // 4K 3840*2160*23.98 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_24     = 0xF1200000, // 4K 3840*2160*24 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_25     = 0xF1300000, // 4K 3840*2160*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_2997   = 0xF1400000, // 4K 3840*2160*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_30     = 0xF1500000, // 4K 3840*2160*30 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_4796   = 0xF1600000, // 4K 3840*2160*47.96 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_48     = 0xF1700000, // 4K 3840*2160*48 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_50     = 0xF1800000, // 4K 3840*2160*50 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_5994   = 0xF1900000, // 4K 3840*2160*59.94 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840P_60     = 0xF1A00000, // 4K 3840*2160*60 type.    //     /@@@@/

    OmnVIDEOSTANDARD_4K_3840Psf_2398 = 0xF2100000, // 4K 3840*2160*23.98 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840Psf_24   = 0xF2200000, // 4K 3840*2160*24 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840Psf_25   = 0xF2300000, // 4K 3840*2160*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840Psf_2997 = 0xF2400000, // 4K 3840*2160*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_3840Psf_30   = 0xF2500000, // 4K 3840*2160*30 type.    //     /@@@@/

    OmnVIDEOSTANDARD_4K_4096P_2398   = 0xF3100000, // 4K 4096*2160*23.98 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_24     = 0xF3200000, // 4K 4096*2160*24 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_25     = 0xF3300000, // 4K 4096*2160*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_2997   = 0xF3400000, // 4K 4096*2160*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_30     = 0xF3500000, // 4K 4096*2160*30 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_4796   = 0xF3600000, // 4K 4096*2160*47.96 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_48     = 0xF3700000, // 4K 4096*2160*48 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_50     = 0xF3800000, // 4K 4096*2160*50 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_5994   = 0xF3900000, // 4K 4096*2160*59.94 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096P_60     = 0xF3A00000, // 4K 4096*2160*60 type.    //     /@@@@/

    OmnVIDEOSTANDARD_4K_4096Psf_2398 = 0xF4100000, // 4K 4096*2160*23.98 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096Psf_24   = 0xF4200000, // 4K 4096*2160*24 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096Psf_25   = 0xF4300000, // 4K 4096*2160*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096Psf_2997 = 0xF4400000, // 4K 4096*2160*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_4K_4096Psf_30   = 0xF4500000, // 4K 4096*2160*30 type.    //     /@@@@/

    OmnVIDEOSTANDARD_2398_P          = 0x02000000, // Unknow Size 23.98 P type.        /****/
    OmnVIDEOSTANDARD_2398_Psf        = 0x03000000, // Unknow Size 23.98 Psf type.        /****/
    OmnVIDEOSTANDARD_24_P            = 0x04000000, // Unknow Size 24 P type.         /****/
    OmnVIDEOSTANDARD_24_Psf          = 0x05000000, // Unknow Size 24 Psf type.         /****/
    OmnVIDEOSTANDARD_25_I            = 0x08000000, // Unknow Size 25 I type.
    OmnVIDEOSTANDARD_25_P            = 0x06000000, // Unknow Size 25 P type.         /****/
    OmnVIDEOSTANDARD_25_Psf          = 0x07000000, // Unknow Size 25 Psf type.         /****/
    OmnVIDEOSTANDARD_2997_I          = 0x10000000, // Unknow Size 29.97 I type.
    OmnVIDEOSTANDARD_2997_P          = 0xC0000000, // Unknow Size 29.97 P type.        /****/
    OmnVIDEOSTANDARD_2997_Psf        = 0xC1000000, // Unknow Size 29.97 Psf type.        /****/
    OmnVIDEOSTANDARD_30_I            = 0x20000000, // Unknow Size 30 I type.
    OmnVIDEOSTANDARD_30_P            = 0xC2000000, // Unknow Size 30 P type.         /****/
    OmnVIDEOSTANDARD_30_Psf          = 0xC3000000, // Unknow Size 30 Psf type.         /****/
    OmnVIDEOSTANDARD_4796_P          = 0xC8000000, // Unknow Size 48 type.          /@@@@/
    OmnVIDEOSTANDARD_48_P            = 0xC4000000, // Unknow Size 48 type.          /****/
    OmnVIDEOSTANDARD_50_P            = 0xC5000000, // Unknow Size 50 type.          /****/
    OmnVIDEOSTANDARD_5994_P          = 0xC6000000, // Unknow Size 59.94 type.         /****/
    OmnVIDEOSTANDARD_60_P            = 0xC7000000, // Unknow Size 60 type.          /****/
} Omn_VIDEO_STANDARD;

typedef enum Omn_AUDIO_TYPE_E // 音频编解码格式类型
{
    OmnAUDIOTYPE_UNKNOW           = 0x00000000,  // @emem  unknow type.

    OmnAUDIOTYPE_WAVE_PCM         = 0x00000001,  // WAVE PCM 音频压缩方式

    OmnAUDIOTYPE_MP1              = 0x00000004,  // MPEG1 音频 (Layer 1) 压缩方式
    OmnAUDIOTYPE_MP2              = 0x00000008,  // MPEG1 音频 (Layer 2) 压缩方式
    OmnAUDIOTYPE_MP3              = 0x00000010,  // MPEG1 音频 (Layer 3) 压缩方式 
    OmnAUDIOTYPE_MPEG4            = 0x00000002,  // MPEG4 (ACM) 音频压缩WAVE

    OmnAUDIOTYPE_AAC              = 0x00000020,  // AAC 压缩方式。
    OmnAUDIOTYPE_AC3              = 0x00000040,  // Dolby Digital (AC3) 音频压缩方式
    OmnAUDIOTYPE_DTS              = 0x00000080,  // DTS 音频压缩方式
    OmnAUDIOTYPE_DRA              = 0x00080000,  // DRA Audio
    OmnAUDIOTYPE_AVS              = 0x00000800,  // AVS音频压缩方式
    OmnAUDIOTYPE_DolbyE           = 0x00001000,  // Dolby-E 音频压缩方式
    OmnAUDIOTYPE_EAC3             = 0x00002000,  // Dolby Digital Plus (EAC3) 音频压缩方式

    OmnAUDIOTYPE_REAL_MEDIA       = 0x00000100,  // Real media 音频压缩方式
    OmnAUDIOTYPE_WINDOWS_MEDIA    = 0x00000200,  // Windows media 音频压缩方式
    OmnAUDIOTYPE_QUICKTIME_MOV    = 0x00000400,  // Quicktime 音频压缩方式

    OmnAUDIOTYPE_G711             = 0x00004000,  // ITUT的语音压缩标准,分ALaw和ULaw两种模式
    OmnAUDIOTYPE_AMRNB            = 0x00010000,  // AMR-NB for 3GPP or GSM
    OmnAUDIOTYPE_AMRWB            = 0x00020000,  // AMR-NB for 3GPP only
    OmnAUDIOTYPE_SWFFLV           = 0x00040000,  // Flv Audio
    OmnAUDIOTYPE_ACM_COMPRESSED   = 0x01000000,  // Audio compression manager (ACM)压缩格式。
} Omn_AUDIO_TYPE;

typedef enum Omn_COLOR_FORMAT_E // 视频颜色格式
{
    OmnCOLORFORMAT_UNKNOW           = 0x00000000,  // invalid color format.

    OmnCOLORFORMAT_BGRA             = 0x00000001,  //BGRA4444, 8bit, 0xAARRGGBB...4个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量
    OmnCOLORFORMAT_BGR              = 0x00000004,  //BGR444, 8bit, 0xRRGGBB...3个字节排列1个R分量、1个G分量、1个B分量
    
    OmnCOLORFORMAT_VUYT             = 0x00000020,  //VUYT4444, 8bit, 0xTTYYUUVV...4个字节排列1个T分量、1个Y分量、1个U分量和1个V分量
    OmnCOLORFORMAT_YUYV             = 0x00000040,  //YUYV422, 8bit, 0xVVYYUUYY...4个字节排列排列2个图像像素的Y、U、V分量
    OmnCOLORFORMAT_UYVY             = 0x00000080,  //UYVY422, 8bit, 0xYYVVYYUU...4个字节排列排列2个图像像素的Y、U、V分量

    //OmnCOLORFORMAT_YUVP_444       = 0x00000100,  //YUVP444, 8bit, 1个图像像素占3个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
    OmnCOLORFORMAT_NV12             = 0x00000100,  //NV12, 8bit, 2x2宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
    OmnCOLORFORMAT_YUVP_422         = 0x00000200,  //YUVP422, 8bit, 2x1宏像素占4个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
    OmnCOLORFORMAT_YUVP_420         = 0x00000400,  //YUVP420, 8bit, 2x2宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
    OmnCOLORFORMAT_YV12             = 0x00000400,  //YV12, 8bit, 2x2宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
    OmnCOLORFORMAT_YUVP_411         = 0x00000800,  //YUVP411, 8bit, 4x1宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!

    OmnCOLORFORMAT_YUYV_DNXHD_10BIT = 0x00001000,  //YUYV422, 10bit, AVID定义的采样格式, 详细定义见专门文档!
    OmnCOLORFORMAT_BGRA_Omn10b      = 0x00002000,  //BGRA4444, 10bit, 3×1个图像像素, 详细定义见专门文档!
    OmnCOLORFORMAT_BGR_Omn10b       = 0x00004000,  //BGR444, 10bit, 4×1个图像像素, Method A Little Endian(暂时保留,与OmnCOLORFORMAT_BGR_Omn10b_Ma_LE一样)
    OmnCOLORFORMAT_BGR_Omn10b_Ma_LE = 0x00004000,  //BGR444, 10bit, 4×1个图像像素, Method A Little Endian
    OmnCOLORFORMAT_BGR_Omn10b_Ma_BE = 0x00004001,  //BGR444, 10bit, 4×1个图像像素, Method A Big Endian
    OmnCOLORFORMAT_BGR_Omn10b_Mb_LE = 0x00004002,  //BGR444, 10bit, 4×1个图像像素, Method B Little Endian
    OmnCOLORFORMAT_BGR_Omn10b_Mb_BE = 0x00004003,  //BGR444, 10bit, 4×1个图像像素, Method B Big Endian
    OmnCOLORFORMAT_BGRA_Omn16b      = 0x00008000,  //BGRA4444, 16bit, 0xAAAARRRRGGGGBBBB...8个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量    

    OmnCOLORFORMAT_YUYV_V216        = 0x00020000,  //YUYV422, 16bit, Apple定义的采样格式, 详细定义见专门文档!
    OmnCOLORFORMAT_YUYV_V210        = 0x00040000,  //YUYV422, 10bit, Apple定义的采样格式, 详细定义见专门文档!    
    OmnCOLORFORMAT_YUYV_M101        = 0x00080000,  //YUYV422, 8bit, Matrox定义的采样格式, 详细定义见专门文档!

    OmnCOLORFORMAT_YUYV_M101_10BIT  = 0x00100000,  //YUYV422, 10bit, Matrox定义的采样格式, 详细定义见专门文档!
    OmnCOLORFORMAT_BGR_Omn16b       = 0x00200000,  //BGR444, 16bit, 0xRRRRGGGGBBBB...6个字节排列1个R分量、1个G分量、1个B分量
    OmnCOLORFORMAT_VUYT_Omn10b      = 0x00400000,  //VUYT4444, 10bit, 3×1个图像像素, 详细定义见专门文档!
    OmnCOLORFORMAT_YUAYVA4224       = 0x00800000,  //YUAYVA4224,8bit, Matrox定义的8bit带阿尔法通道的颜色格式, 以YUYV为基础，每8个像素为一个单元，详细定义见专门文档!    
    
    OmnCOLORFORMAT_VUY              = 0x02000000,  //VUY444, 8bit, 0xYYUUVV...3个字节排列1个Y分量、1个U分量和1个V分量
    OmnCOLORFORMAT_VUYT_Omn16b      = 0x04000000,  //VUYT4444, 16bit, 0xTTTTYYYYUUUUVVVV...8个字节排列1个T分量、1个Y分量、1个U分量和1个V分量    
    OmnCOLORFORMAT_VUY_Omn10b       = 0x08000000,  //VUY444, 10bit, 4×1个图像像素, 详细定义见专门文档!

    OmnCOLORFORMAT_VUY_Omn16b       = 0x10000000,  //VUY444, 16bit, 0xYYYYUUUUVVVV...6个字节排列1个Y分量、1个U分量和1个V分量    
} Omn_COLOR_FORMAT;

typedef enum Omn_VIDEOSCAN_MODE_E // 视频扫描帧场数据排列方式, 有时间和空间两个概念，场序（First，Second）表示时间概念，奇偶场(Top，Bottom)表示空间（image Buffer)概念
{
    OmnVIDEOSCANMODE_Invalid                  = -1,
    OmnVIDEOSCANMODE_FirstFieldTop            = 0,   // 两场数据交织排列, 首(First)场排列在奇(Top)场位置
    OmnVIDEOSCANMODE_SecondFieldTop           = 1,   // 两场数据交织排列, 第二(Second)场排列在奇(Top)场位置
    OmnVIDEOSCANMODE_Progressive              = 2,   // 帧数据连续排列, 无场序时间概念
    OmnVIDEOSCANMODE_ProgressiveSegmented     = 3,   // 帧数据分割排列, 无场序时间概念, 无奇偶场空间概念
    OmnVIDEOSCANMODE_FirstFieldTopBackToBack  = 4,   // 两场数据分别排列,首(First)场后是第二(Second)场, 无奇偶场空间概念
    OmnVIDEOSCANMODE_SecondFieldTopBackToBack = 5,   // 两场数据分别排列,第二(Second)场后是首(First)场, 无奇偶场空间概念
} Omn_VIDEOSCAN_MODE;

typedef enum Omn_FIELD_E
{
    Omn_ODD_FIELD   = 0,  //奇数场
    Omn_EVEN_FIELD  = 1,  //偶数场
    Omn_BOTH_FIELD  = 2,  //奇偶场
} Omn_FIELD;

typedef enum Omn_AUDIO_CHANNELCONFIGURATION_E // 声道属性枚举定义
{
    OmnAUDIOCFG_UNKNOW             = 0,      // 声道属性未知
    OmnAUDIOCFG_INDEPENDENT        = 1,      // 独立声道
    OmnAUDIOCFG_STEREO             = 2,      // 立体声(左 右)
    OmnAUDIOCFG_5_1                = 3,      // 5.1(左 右 中置 左环绕 右环绕 低音)
    OmnAUDIOCFG_7_1                = 4,      // 7.0(前左 前右 中置 左 右 左环绕 右环绕  低音)

    OmnAUDIOCFG_2_1                = 5,      // 2.1(左 右 低音)
    OmnAUDIOCFG_3_0_C              = 6,      // 3.0(左 右 中置)
    OmnAUDIOCFG_3_0_S              = 7,      // 3.0(左 右 环绕)
    OmnAUDIOCFG_3_1_C_LFE          = 8,      // 3.1(左 右 中置 低音)
    OmnAUDIOCFG_3_1_S_LFE          = 9,      // 3.1(左 右 环绕 低音)
    OmnAUDIOCFG_4_0_C_S            = 10,     // 4.0(左 右 中置 环绕)
    OmnAUDIOCFG_4_0_LS_RS          = 11,     // 4.0(左 右 左环绕 右环绕)
    OmnAUDIOCFG_4_1_C_S_LFE        = 12,     // 4.1(左 右 中置 环绕 低音)
    OmnAUDIOCFG_4_1_LS_RS_LFE      = 13,     // 4.1(左 右 左环绕 右环绕 低音)
    OmnAUDIOCFG_5_0                = 14,     // 5.0(左 右 中置 左环绕 右环绕)
    OmnAUDIOCFG_6_0_LRC_LRSRC      = 15,     // 6.0(左 右 前中置 左环绕 右环绕 后中置)
    OmnAUDIOCFG_6_0_FLFR_LR_LRS    = 16,     // 6.0(前左 前右 左 右 左环绕 右环绕)
    OmnAUDIOCFG_6_1_LRFC_LRSRC_LFE = 17,     // 6.1(左 右 前中置 左环绕  右环绕 后中置 低音)
    OmnAUDIOCFG_6_1_FLR_LRLRS_LFE  = 18,     // 6.1(前左 前右 左 右 左环绕 右环绕 低音)
    OmnAUDIOCFG_7_0                = 19,     // 7.0(前左 前右 中置 左 右 左环绕 右环绕)
} Omn_AUDIO_CHANNELCONFIGURATION;

typedef enum Omn_CHANNELSAMPLE_FORMAT_E //音频声道采样数据格式
{
    OmnCHANNELSAMPLESFORMAT_Unknow        = 0,
    OmnCHANNELSAMPLESFORMAT_Progressive   = 1,   //音频声道采样数据连续排列...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
    OmnCHANNELSAMPLESFORMAT_Segmented     = 2,   //音频声道采样数据分割排列...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
} Omn_CHANNELSAMPLE_FORMAT;

typedef enum Omn_VIDEO_SIGNAL_TYPE_E  // 视频信号传输类型
{
    OmnVIDEOSIGNALTYPE_UNKNOW      = 0x00000000,  // 非法
    OmnVIDEOSIGNALTYPE_Composite   = 0x00000001,  // 复合类型
    OmnVIDEOSIGNALTYPE_YC          = 0x00000002,  // YC分量类型
    OmnVIDEOSIGNALTYPE_Component   = 0x00000004,  // YUV分量类型
    OmnVIDEOSIGNALTYPE_SDI         = 0x00000008,  // 串行传输
    OmnVIDEOSIGNALTYPE_SDTI        = 0x00000010,
    OmnVIDEOSIGNALTYPE_SDTI_CP     = 0x00000020,
    OmnVIDEOSIGNALTYPE_IPNETWORK   = 0x00000040,
    OmnVIDEOSIGNALTYPE_HDMI        = 0x00000100,
    OmnVIDEOSIGNALTYPE_ASI         = 0x00000200,
    OmnVIDEOSIGNALTYPE_DISPLAYPORT = 0x00000400,
    OmnVIDEOSIGNALTYPE_VGA         = 0x00000800,
    OmnVIDEOSIGNALTYPE_DVI         = 0x00001000,
    OmnVIDEOSIGNALTYPE_OPTICAL     = 0x00002000,  //光纤
} Omn_VIDEO_SIGNAL_TYPE;

typedef enum Omn_AUDIO_SIGNAL_TYPE_E  // 音频信号传输类型
{
    OmnAUDIOSIGNALTYPE_UNKNOW      = 0x00000000,
    OmnAUDIOSIGNALTYPE_Analog      = 0x00000001,
    OmnAUDIOSIGNALTYPE_AESEBU      = 0x00000002,
    OmnAUDIOSIGNALTYPE_SDI         = 0x00000004,
    OmnAUDIOSIGNALTYPE_SDTI        = 0x00000008,
    OmnAUDIOSIGNALTYPE_SDTI_CP     = 0x00000010,
    OmnAUDIOSIGNALTYPE_IPNETWORK   = 0x00000020,
    OmnAUDIOSIGNALTYPE_HDMI        = 0x00000100,
    OmnAUDIOSIGNALTYPE_ASI         = 0x00000200,
    OmnAUDIOSIGNALTYPE_DISPLAYPORT = 0x00000400,
    OmnAUDIOSIGNALTYPE_OPTICAL     = 0x00000800,   //光纤
    OmnAUDIOSIGNALTYPE_Mic         = 0x00001000,
    OmnAUDIOSIGNALTYPE_HeadPhone   = 0x00002000,
} Omn_AUDIO_SIGNAL_TYPE;


typedef enum  OmnCOLORSPACE_CONVERT_E    //颜色空间转换矩阵
{
    OmnCOLORSPACE_CONVERT_DISABLE  = 0,    //不作颜色空间的转换
    OmnCOLORSPACE_601_CONVERT_709  = 1,    //从601标准转换到709标准
    OmnCOLORSPACE_709_CONVERT_601  = 2     //从709标准转换到601标准
} OmnCOLORSPACE_CONVERT;

typedef enum OmnVIDEO_SCALE_TYPE_E   //高标清上下变换模式定义
{
    OmnVIDEO_SCALE_TYPE_NONE					= 0,
    OmnVIDEO_SCALE_TYPE_BOX					    = 1,	//信箱 
    OmnVIDEO_SCALE_TYPE_ZOOM					= 2,	//放大	
    OmnVIDEO_SCALE_TYPE_CUT					    = 3,	//切边
    OmnVIDEO_SCALE_TYPE_WINDOW				    = 4,	//窗口
} OmnVIDEO_SCALE_TYPE;

struct Omn_RECT
{
    Om_INT32 x;//矩形左上角x坐标
    Om_INT32 y;//矩形左上角y坐标
    Om_INT32 w;//矩形宽度
    Om_INT32 h;//矩形高度
};
typedef Omn_RECT *Omn_PRECT;

typedef struct SOmnAudioMediaInfo_E // 音频基本属性
{
    Om_UINT32   dwStruSize;   // 结构大小
    Omn_AUDIO_TYPE  enumAudioType;  // 音频编解码类型。
    Om_UINT32   dwAudioSubType;  // 音频编解码的子类型,子类型定义随enumAudioType不同而不同
    Om_UINT32   dwChannels;   // 声道数目
    Om_UINT32   dwBitsPerSample; // 采样位数 
    Om_UINT32   dwSamplesPerSec; // 每秒采样数量 
    Om_UINT32   dwAvgBitsPerSec; // 音频码率 bits
    Om_UINT32   dwBlockAlign;  // 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)

    Omn_AUDIO_CHANNELCONFIGURATION enumAudioCFG;  //声道属性
    Omn_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat; //音频声道采样数据格式
} SOmnAudioMediaInfo;

Om_INLINE void	Omn_GetVidStdPara( Omn_VIDEO_STANDARD enumVideoStandard, Om_UINT32 &dwWidth, Om_UINT32 &dwHigh)
{	
	dwWidth = dwHigh = 0;
	
	switch( enumVideoStandard )
	{
		case OmnVIDEOSTANDARD_PAL:			
			dwWidth = 720;
			dwHigh = 576;			
			break;

		case OmnVIDEOSTANDARD_NTSC2997:
		case OmnVIDEOSTANDARD_NTSC30:
			dwWidth = 720;
			dwHigh = 486;
			break;

		case OmnVIDEOSTANDARD_HD1080i_25:
		case OmnVIDEOSTANDARD_HD1080i_2997:
		case OmnVIDEOSTANDARD_HD1080i_30:
		case OmnVIDEOSTANDARD_HD1080p_2398:
		case OmnVIDEOSTANDARD_HD1080p_24:
		case OmnVIDEOSTANDARD_HD1080p_25:
		case OmnVIDEOSTANDARD_HD1080p_2997:
		case OmnVIDEOSTANDARD_HD1080p_30:
		case OmnVIDEOSTANDARD_HD1080P_4796:
		case OmnVIDEOSTANDARD_HD1080P_48:
		case OmnVIDEOSTANDARD_HD1080P_50:
		case OmnVIDEOSTANDARD_HD1080P_5994:
		case OmnVIDEOSTANDARD_HD1080P_60:
		case OmnVIDEOSTANDARD_HD1080psf_2398:
		case OmnVIDEOSTANDARD_HD1080psf_24:
		case OmnVIDEOSTANDARD_HD1080psf_25:
		case OmnVIDEOSTANDARD_HD1080psf_2997:
		case OmnVIDEOSTANDARD_HD1080psf_30:
			dwWidth = 1920;
			dwHigh = 1080;
			break;	
		
		case OmnVIDEOSTANDARD_HD720p_2398:
		case OmnVIDEOSTANDARD_HD720p_24:
		case OmnVIDEOSTANDARD_HD720p_25:
		case OmnVIDEOSTANDARD_HD720p_2997:
		case OmnVIDEOSTANDARD_HD720p_30:
		case OmnVIDEOSTANDARD_HD720p_50:
		case OmnVIDEOSTANDARD_HD720p_5994:
		case OmnVIDEOSTANDARD_HD720p_60:
			dwWidth = 1280;
			dwHigh = 720;
			break;
		
		case OmnVIDEOSTANDARD_2K1080P_2398:
		case OmnVIDEOSTANDARD_2K1080P_24:
		case OmnVIDEOSTANDARD_2K1080P_25:
		case OmnVIDEOSTANDARD_2K1080P_2997:
		case OmnVIDEOSTANDARD_2K1080P_30:
		case OmnVIDEOSTANDARD_2K1080P_4796:
		case OmnVIDEOSTANDARD_2K1080P_48:
		case OmnVIDEOSTANDARD_2K1080P_50:
		case OmnVIDEOSTANDARD_2K1080P_5994:
		case OmnVIDEOSTANDARD_2K1080P_60:
		case OmnVIDEOSTANDARD_2K1080Psf_2398:
		case OmnVIDEOSTANDARD_2K1080Psf_24:
		case OmnVIDEOSTANDARD_2K1080Psf_25:
		case OmnVIDEOSTANDARD_2K1080Psf_2997:
		case OmnVIDEOSTANDARD_2K1080Psf_30:
			dwWidth = 2048;
			dwHigh = 1080;			
			break;

		case OmnVIDEOSTANDARD_2K1556P_2398:
		case OmnVIDEOSTANDARD_2K1556P_24:
		case OmnVIDEOSTANDARD_2K1556Psf_2398:
		case OmnVIDEOSTANDARD_2K1556Psf_24:
			dwWidth = 2048;
			dwHigh = 1556;
			break;

		case OmnVIDEOSTANDARD_4K_3840P_2398:
		case OmnVIDEOSTANDARD_4K_3840P_24:
		case OmnVIDEOSTANDARD_4K_3840P_25:
		case OmnVIDEOSTANDARD_4K_3840P_2997:
		case OmnVIDEOSTANDARD_4K_3840P_30:
		case OmnVIDEOSTANDARD_4K_3840P_4796:
		case OmnVIDEOSTANDARD_4K_3840P_48:
		case OmnVIDEOSTANDARD_4K_3840P_50:
		case OmnVIDEOSTANDARD_4K_3840P_5994:
		case OmnVIDEOSTANDARD_4K_3840P_60:
		case OmnVIDEOSTANDARD_4K_3840Psf_2398:
		case OmnVIDEOSTANDARD_4K_3840Psf_24:
		case OmnVIDEOSTANDARD_4K_3840Psf_25:
		case OmnVIDEOSTANDARD_4K_3840Psf_2997:
		case OmnVIDEOSTANDARD_4K_3840Psf_30:
			dwWidth = 3840;
			dwHigh = 2160;
			break;

		case OmnVIDEOSTANDARD_4K_4096P_2398:
		case OmnVIDEOSTANDARD_4K_4096P_24:
		case OmnVIDEOSTANDARD_4K_4096P_25:
		case OmnVIDEOSTANDARD_4K_4096P_2997:
		case OmnVIDEOSTANDARD_4K_4096P_30:
		case OmnVIDEOSTANDARD_4K_4096P_4796:
		case OmnVIDEOSTANDARD_4K_4096P_48:
		case OmnVIDEOSTANDARD_4K_4096P_50:
		case OmnVIDEOSTANDARD_4K_4096P_5994:
		case OmnVIDEOSTANDARD_4K_4096P_60:
		case OmnVIDEOSTANDARD_4K_4096Psf_2398:
		case OmnVIDEOSTANDARD_4K_4096Psf_24:
		case OmnVIDEOSTANDARD_4K_4096Psf_25:
		case OmnVIDEOSTANDARD_4K_4096Psf_2997:
		case OmnVIDEOSTANDARD_4K_4096Psf_30:
			dwWidth = 4096;
			dwHigh = 2160;
			break;
	}
};

typedef enum Omn_SIGNAL_SCAN_MODE_E
{
    OmnSIGNAL_SCAN_UNKNOWN          = 0,   //未知
    OmnSIGNAL_SCAN_INTERLACED       = 1,    //隔行扫描
    OmnSIGNAL_SCAN_PROGRESSIVE      = 2     //逐行扫描
}Omn_SIGNAL_SCAN_MODE;

typedef struct SOmnResolution_T
{
    Om_UINT32 dwWidth;          //宽度，1像素为单位
    Om_UINT32 dwHeight;         //高度，1像素为单位
    Om_UINT32 dwReserved[2];    //保留扩展用，全0
}SOmnResolution;

typedef struct SOmnFrequency_T
{
    Om_UINT32 dwNumerator;      //分子
    Om_UINT32 dwDenominator;    //分母
}SOmnFrequency;

typedef struct SOmnVideoSignalInfo_T
{   
    Om_BOOL              bValid;        //视频信号信息有效标记
    SOmnResolution       sRes;          //视频信号分辨率
    SOmnFrequency        sFreq;         //视频信号帧频
    Omn_SIGNAL_SCAN_MODE enumScanMode;  //视频信号扫描方式
}SOmnVideoSignalInfo;

//在Buf中按4字节设置值
Om_INLINE Om_VOID	OmnDMemset( Om_VOID *pBuf, Om_INT32 value, Om_INT32 num )
{
	Om_INT32 * pTempBuf = (Om_INT32 *)pBuf;
	for(Om_INT32 i = 0; i < num; i++)
	{
		*pTempBuf = value;
		pTempBuf++;
	}
};

#ifdef __cplusplus
}
#endif


#endif//Omn_VACOMMON_DEF_H_