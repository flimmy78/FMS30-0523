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
* ����:
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

typedef enum Omn_VIDEO_STANDARD_E // ��Ƶ��ʽ��׼
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

    OmnVIDEOSTANDARD_2K1080P_2398    = 0x45000000, // 2K 2048*1080*23.98 type.    //AJA֧��   /****/
    OmnVIDEOSTANDARD_2K1080P_24      = 0x46000000, // 2K 2048*1080*24 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080P_25      = 0x22100000, // 2K 2048*1080*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_2997    = 0x22200000, // 2K 2048*1080*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_30      = 0x22300000, // 2K 2048*1080*30 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_4796    = 0x22700000, // 2K 2048*1080*47.96 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_48      = 0x47000000, // 2K 2048*1080*48 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080P_50      = 0x22400000, // 2K 2048*1080*50 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_5994    = 0x22500000, // 2K 2048*1080*59.94 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080P_60      = 0x22600000, // 2K 2048*1080*60 type.    //     /@@@@/

    OmnVIDEOSTANDARD_2K1080Psf_2398  = 0x81000000, // 2K 2048*1080*23.98 type.    //AJA֧��   /****/
    OmnVIDEOSTANDARD_2K1080Psf_24    = 0x82000000, // 2K 2048*1080*24 type.    //SMPTE 428-1  /****/
    OmnVIDEOSTANDARD_2K1080Psf_25    = 0x21100000, // 2K 2048*1080*25 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080Psf_2997  = 0x21200000, // 2K 2048*1080*29.97 type.    //     /@@@@/
    OmnVIDEOSTANDARD_2K1080Psf_30    = 0x21300000, // 2K 2048*1080*30 type.    //     /@@@@/

    OmnVIDEOSTANDARD_2K1556P_2398    = 0x83000000, // 2K 2048*1556*23.98 PLAYBACK.   //AJA֧��   /****/
    OmnVIDEOSTANDARD_2K1556P_24      = 0x84000000, // 2K 2048*1556*24 PLAYBACK.   //AJA֧��   /****/
    OmnVIDEOSTANDARD_2K1556Psf_2398  = 0x85000000, // 2K 2048*1556*23.98 PLAYBACK.   //AJA֧��   /****/
    OmnVIDEOSTANDARD_2K1556Psf_24    = 0x86000000, // 2K 2048*1556*24 PLAYBACK.   //AJA֧��   /****/

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

typedef enum Omn_AUDIO_TYPE_E // ��Ƶ������ʽ����
{
    OmnAUDIOTYPE_UNKNOW           = 0x00000000,  // @emem  unknow type.

    OmnAUDIOTYPE_WAVE_PCM         = 0x00000001,  // WAVE PCM ��Ƶѹ����ʽ

    OmnAUDIOTYPE_MP1              = 0x00000004,  // MPEG1 ��Ƶ (Layer 1) ѹ����ʽ
    OmnAUDIOTYPE_MP2              = 0x00000008,  // MPEG1 ��Ƶ (Layer 2) ѹ����ʽ
    OmnAUDIOTYPE_MP3              = 0x00000010,  // MPEG1 ��Ƶ (Layer 3) ѹ����ʽ 
    OmnAUDIOTYPE_MPEG4            = 0x00000002,  // MPEG4 (ACM) ��Ƶѹ��WAVE

    OmnAUDIOTYPE_AAC              = 0x00000020,  // AAC ѹ����ʽ��
    OmnAUDIOTYPE_AC3              = 0x00000040,  // Dolby Digital (AC3) ��Ƶѹ����ʽ
    OmnAUDIOTYPE_DTS              = 0x00000080,  // DTS ��Ƶѹ����ʽ
    OmnAUDIOTYPE_DRA              = 0x00080000,  // DRA Audio
    OmnAUDIOTYPE_AVS              = 0x00000800,  // AVS��Ƶѹ����ʽ
    OmnAUDIOTYPE_DolbyE           = 0x00001000,  // Dolby-E ��Ƶѹ����ʽ
    OmnAUDIOTYPE_EAC3             = 0x00002000,  // Dolby Digital Plus (EAC3) ��Ƶѹ����ʽ

    OmnAUDIOTYPE_REAL_MEDIA       = 0x00000100,  // Real media ��Ƶѹ����ʽ
    OmnAUDIOTYPE_WINDOWS_MEDIA    = 0x00000200,  // Windows media ��Ƶѹ����ʽ
    OmnAUDIOTYPE_QUICKTIME_MOV    = 0x00000400,  // Quicktime ��Ƶѹ����ʽ

    OmnAUDIOTYPE_G711             = 0x00004000,  // ITUT������ѹ����׼,��ALaw��ULaw����ģʽ
    OmnAUDIOTYPE_AMRNB            = 0x00010000,  // AMR-NB for 3GPP or GSM
    OmnAUDIOTYPE_AMRWB            = 0x00020000,  // AMR-NB for 3GPP only
    OmnAUDIOTYPE_SWFFLV           = 0x00040000,  // Flv Audio
    OmnAUDIOTYPE_ACM_COMPRESSED   = 0x01000000,  // Audio compression manager (ACM)ѹ����ʽ��
} Omn_AUDIO_TYPE;

typedef enum Omn_COLOR_FORMAT_E // ��Ƶ��ɫ��ʽ
{
    OmnCOLORFORMAT_UNKNOW           = 0x00000000,  // invalid color format.

    OmnCOLORFORMAT_BGRA             = 0x00000001,  //BGRA4444, 8bit, 0xAARRGGBB...4���ֽ�����1����ͨ������A��1��R������1��G������1��B����
    OmnCOLORFORMAT_BGR              = 0x00000004,  //BGR444, 8bit, 0xRRGGBB...3���ֽ�����1��R������1��G������1��B����
    
    OmnCOLORFORMAT_VUYT             = 0x00000020,  //VUYT4444, 8bit, 0xTTYYUUVV...4���ֽ�����1��T������1��Y������1��U������1��V����
    OmnCOLORFORMAT_YUYV             = 0x00000040,  //YUYV422, 8bit, 0xVVYYUUYY...4���ֽ���������2��ͼ�����ص�Y��U��V����
    OmnCOLORFORMAT_UYVY             = 0x00000080,  //UYVY422, 8bit, 0xYYVVYYUU...4���ֽ���������2��ͼ�����ص�Y��U��V����

    //OmnCOLORFORMAT_YUVP_444       = 0x00000100,  //YUVP444, 8bit, 1��ͼ������ռ3���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_NV12             = 0x00000100,  //NV12, 8bit, 2x2������ռ6���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YUVP_422         = 0x00000200,  //YUVP422, 8bit, 2x1������ռ4���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YUVP_420         = 0x00000400,  //YUVP420, 8bit, 2x2������ռ6���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YV12             = 0x00000400,  //YV12, 8bit, 2x2������ռ6���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YUVP_411         = 0x00000800,  //YUVP411, 8bit, 4x1������ռ6���ֽ�,Y��U��V�����ֱ𱣴������黺������, ��ϸ�����ר���ĵ�!

    OmnCOLORFORMAT_YUYV_DNXHD_10BIT = 0x00001000,  //YUYV422, 10bit, AVID����Ĳ�����ʽ, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_BGRA_Omn10b      = 0x00002000,  //BGRA4444, 10bit, 3��1��ͼ������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_BGR_Omn10b       = 0x00004000,  //BGR444, 10bit, 4��1��ͼ������, Method A Little Endian(��ʱ����,��OmnCOLORFORMAT_BGR_Omn10b_Ma_LEһ��)
    OmnCOLORFORMAT_BGR_Omn10b_Ma_LE = 0x00004000,  //BGR444, 10bit, 4��1��ͼ������, Method A Little Endian
    OmnCOLORFORMAT_BGR_Omn10b_Ma_BE = 0x00004001,  //BGR444, 10bit, 4��1��ͼ������, Method A Big Endian
    OmnCOLORFORMAT_BGR_Omn10b_Mb_LE = 0x00004002,  //BGR444, 10bit, 4��1��ͼ������, Method B Little Endian
    OmnCOLORFORMAT_BGR_Omn10b_Mb_BE = 0x00004003,  //BGR444, 10bit, 4��1��ͼ������, Method B Big Endian
    OmnCOLORFORMAT_BGRA_Omn16b      = 0x00008000,  //BGRA4444, 16bit, 0xAAAARRRRGGGGBBBB...8���ֽ�����1����ͨ������A��1��R������1��G������1��B����    

    OmnCOLORFORMAT_YUYV_V216        = 0x00020000,  //YUYV422, 16bit, Apple����Ĳ�����ʽ, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YUYV_V210        = 0x00040000,  //YUYV422, 10bit, Apple����Ĳ�����ʽ, ��ϸ�����ר���ĵ�!    
    OmnCOLORFORMAT_YUYV_M101        = 0x00080000,  //YUYV422, 8bit, Matrox����Ĳ�����ʽ, ��ϸ�����ר���ĵ�!

    OmnCOLORFORMAT_YUYV_M101_10BIT  = 0x00100000,  //YUYV422, 10bit, Matrox����Ĳ�����ʽ, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_BGR_Omn16b       = 0x00200000,  //BGR444, 16bit, 0xRRRRGGGGBBBB...6���ֽ�����1��R������1��G������1��B����
    OmnCOLORFORMAT_VUYT_Omn10b      = 0x00400000,  //VUYT4444, 10bit, 3��1��ͼ������, ��ϸ�����ר���ĵ�!
    OmnCOLORFORMAT_YUAYVA4224       = 0x00800000,  //YUAYVA4224,8bit, Matrox�����8bit��������ͨ������ɫ��ʽ, ��YUYVΪ������ÿ8������Ϊһ����Ԫ����ϸ�����ר���ĵ�!    
    
    OmnCOLORFORMAT_VUY              = 0x02000000,  //VUY444, 8bit, 0xYYUUVV...3���ֽ�����1��Y������1��U������1��V����
    OmnCOLORFORMAT_VUYT_Omn16b      = 0x04000000,  //VUYT4444, 16bit, 0xTTTTYYYYUUUUVVVV...8���ֽ�����1��T������1��Y������1��U������1��V����    
    OmnCOLORFORMAT_VUY_Omn10b       = 0x08000000,  //VUY444, 10bit, 4��1��ͼ������, ��ϸ�����ר���ĵ�!

    OmnCOLORFORMAT_VUY_Omn16b       = 0x10000000,  //VUY444, 16bit, 0xYYYYUUUUVVVV...6���ֽ�����1��Y������1��U������1��V����    
} Omn_COLOR_FORMAT;

typedef enum Omn_VIDEOSCAN_MODE_E // ��Ƶɨ��֡���������з�ʽ, ��ʱ��Ϳռ������������First��Second����ʾʱ������ż��(Top��Bottom)��ʾ�ռ䣨image Buffer)����
{
    OmnVIDEOSCANMODE_Invalid                  = -1,
    OmnVIDEOSCANMODE_FirstFieldTop            = 0,   // �������ݽ�֯����, ��(First)����������(Top)��λ��
    OmnVIDEOSCANMODE_SecondFieldTop           = 1,   // �������ݽ�֯����, �ڶ�(Second)����������(Top)��λ��
    OmnVIDEOSCANMODE_Progressive              = 2,   // ֡������������, �޳���ʱ�����
    OmnVIDEOSCANMODE_ProgressiveSegmented     = 3,   // ֡���ݷָ�����, �޳���ʱ�����, ����ż���ռ����
    OmnVIDEOSCANMODE_FirstFieldTopBackToBack  = 4,   // �������ݷֱ�����,��(First)�����ǵڶ�(Second)��, ����ż���ռ����
    OmnVIDEOSCANMODE_SecondFieldTopBackToBack = 5,   // �������ݷֱ�����,�ڶ�(Second)��������(First)��, ����ż���ռ����
} Omn_VIDEOSCAN_MODE;

typedef enum Omn_FIELD_E
{
    Omn_ODD_FIELD   = 0,  //������
    Omn_EVEN_FIELD  = 1,  //ż����
    Omn_BOTH_FIELD  = 2,  //��ż��
} Omn_FIELD;

typedef enum Omn_AUDIO_CHANNELCONFIGURATION_E // ��������ö�ٶ���
{
    OmnAUDIOCFG_UNKNOW             = 0,      // ��������δ֪
    OmnAUDIOCFG_INDEPENDENT        = 1,      // ��������
    OmnAUDIOCFG_STEREO             = 2,      // ������(�� ��)
    OmnAUDIOCFG_5_1                = 3,      // 5.1(�� �� ���� ���� �һ��� ����)
    OmnAUDIOCFG_7_1                = 4,      // 7.0(ǰ�� ǰ�� ���� �� �� ���� �һ���  ����)

    OmnAUDIOCFG_2_1                = 5,      // 2.1(�� �� ����)
    OmnAUDIOCFG_3_0_C              = 6,      // 3.0(�� �� ����)
    OmnAUDIOCFG_3_0_S              = 7,      // 3.0(�� �� ����)
    OmnAUDIOCFG_3_1_C_LFE          = 8,      // 3.1(�� �� ���� ����)
    OmnAUDIOCFG_3_1_S_LFE          = 9,      // 3.1(�� �� ���� ����)
    OmnAUDIOCFG_4_0_C_S            = 10,     // 4.0(�� �� ���� ����)
    OmnAUDIOCFG_4_0_LS_RS          = 11,     // 4.0(�� �� ���� �һ���)
    OmnAUDIOCFG_4_1_C_S_LFE        = 12,     // 4.1(�� �� ���� ���� ����)
    OmnAUDIOCFG_4_1_LS_RS_LFE      = 13,     // 4.1(�� �� ���� �һ��� ����)
    OmnAUDIOCFG_5_0                = 14,     // 5.0(�� �� ���� ���� �һ���)
    OmnAUDIOCFG_6_0_LRC_LRSRC      = 15,     // 6.0(�� �� ǰ���� ���� �һ��� ������)
    OmnAUDIOCFG_6_0_FLFR_LR_LRS    = 16,     // 6.0(ǰ�� ǰ�� �� �� ���� �һ���)
    OmnAUDIOCFG_6_1_LRFC_LRSRC_LFE = 17,     // 6.1(�� �� ǰ���� ����  �һ��� ������ ����)
    OmnAUDIOCFG_6_1_FLR_LRLRS_LFE  = 18,     // 6.1(ǰ�� ǰ�� �� �� ���� �һ��� ����)
    OmnAUDIOCFG_7_0                = 19,     // 7.0(ǰ�� ǰ�� ���� �� �� ���� �һ���)
} Omn_AUDIO_CHANNELCONFIGURATION;

typedef enum Omn_CHANNELSAMPLE_FORMAT_E //��Ƶ�����������ݸ�ʽ
{
    OmnCHANNELSAMPLESFORMAT_Unknow        = 0,
    OmnCHANNELSAMPLESFORMAT_Progressive   = 1,   //��Ƶ��������������������...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
    OmnCHANNELSAMPLESFORMAT_Segmented     = 2,   //��Ƶ�����������ݷָ�����...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
} Omn_CHANNELSAMPLE_FORMAT;

typedef enum Omn_VIDEO_SIGNAL_TYPE_E  // ��Ƶ�źŴ�������
{
    OmnVIDEOSIGNALTYPE_UNKNOW      = 0x00000000,  // �Ƿ�
    OmnVIDEOSIGNALTYPE_Composite   = 0x00000001,  // ��������
    OmnVIDEOSIGNALTYPE_YC          = 0x00000002,  // YC��������
    OmnVIDEOSIGNALTYPE_Component   = 0x00000004,  // YUV��������
    OmnVIDEOSIGNALTYPE_SDI         = 0x00000008,  // ���д���
    OmnVIDEOSIGNALTYPE_SDTI        = 0x00000010,
    OmnVIDEOSIGNALTYPE_SDTI_CP     = 0x00000020,
    OmnVIDEOSIGNALTYPE_IPNETWORK   = 0x00000040,
    OmnVIDEOSIGNALTYPE_HDMI        = 0x00000100,
    OmnVIDEOSIGNALTYPE_ASI         = 0x00000200,
    OmnVIDEOSIGNALTYPE_DISPLAYPORT = 0x00000400,
    OmnVIDEOSIGNALTYPE_VGA         = 0x00000800,
    OmnVIDEOSIGNALTYPE_DVI         = 0x00001000,
    OmnVIDEOSIGNALTYPE_OPTICAL     = 0x00002000,  //����
} Omn_VIDEO_SIGNAL_TYPE;

typedef enum Omn_AUDIO_SIGNAL_TYPE_E  // ��Ƶ�źŴ�������
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
    OmnAUDIOSIGNALTYPE_OPTICAL     = 0x00000800,   //����
    OmnAUDIOSIGNALTYPE_Mic         = 0x00001000,
    OmnAUDIOSIGNALTYPE_HeadPhone   = 0x00002000,
} Omn_AUDIO_SIGNAL_TYPE;


typedef enum  OmnCOLORSPACE_CONVERT_E    //��ɫ�ռ�ת������
{
    OmnCOLORSPACE_CONVERT_DISABLE  = 0,    //������ɫ�ռ��ת��
    OmnCOLORSPACE_601_CONVERT_709  = 1,    //��601��׼ת����709��׼
    OmnCOLORSPACE_709_CONVERT_601  = 2     //��709��׼ת����601��׼
} OmnCOLORSPACE_CONVERT;

typedef enum OmnVIDEO_SCALE_TYPE_E   //�߱������±任ģʽ����
{
    OmnVIDEO_SCALE_TYPE_NONE					= 0,
    OmnVIDEO_SCALE_TYPE_BOX					    = 1,	//���� 
    OmnVIDEO_SCALE_TYPE_ZOOM					= 2,	//�Ŵ�	
    OmnVIDEO_SCALE_TYPE_CUT					    = 3,	//�б�
    OmnVIDEO_SCALE_TYPE_WINDOW				    = 4,	//����
} OmnVIDEO_SCALE_TYPE;

struct Omn_RECT
{
    Om_INT32 x;//�������Ͻ�x����
    Om_INT32 y;//�������Ͻ�y����
    Om_INT32 w;//���ο��
    Om_INT32 h;//���θ߶�
};
typedef Omn_RECT *Omn_PRECT;

typedef struct SOmnAudioMediaInfo_E // ��Ƶ��������
{
    Om_UINT32   dwStruSize;   // �ṹ��С
    Omn_AUDIO_TYPE  enumAudioType;  // ��Ƶ��������͡�
    Om_UINT32   dwAudioSubType;  // ��Ƶ������������,�����Ͷ�����enumAudioType��ͬ����ͬ
    Om_UINT32   dwChannels;   // ������Ŀ
    Om_UINT32   dwBitsPerSample; // ����λ�� 
    Om_UINT32   dwSamplesPerSec; // ÿ��������� 
    Om_UINT32   dwAvgBitsPerSec; // ��Ƶ���� bits
    Om_UINT32   dwBlockAlign;  // ���ݿ���뵥λ(ÿ������������Ҫ���ֽ���), ������*������/8, ������(16,20?,24,32...)

    Omn_AUDIO_CHANNELCONFIGURATION enumAudioCFG;  //��������
    Omn_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat; //��Ƶ�����������ݸ�ʽ
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
    OmnSIGNAL_SCAN_UNKNOWN          = 0,   //δ֪
    OmnSIGNAL_SCAN_INTERLACED       = 1,    //����ɨ��
    OmnSIGNAL_SCAN_PROGRESSIVE      = 2     //����ɨ��
}Omn_SIGNAL_SCAN_MODE;

typedef struct SOmnResolution_T
{
    Om_UINT32 dwWidth;          //��ȣ�1����Ϊ��λ
    Om_UINT32 dwHeight;         //�߶ȣ�1����Ϊ��λ
    Om_UINT32 dwReserved[2];    //������չ�ã�ȫ0
}SOmnResolution;

typedef struct SOmnFrequency_T
{
    Om_UINT32 dwNumerator;      //����
    Om_UINT32 dwDenominator;    //��ĸ
}SOmnFrequency;

typedef struct SOmnVideoSignalInfo_T
{   
    Om_BOOL              bValid;        //��Ƶ�ź���Ϣ��Ч���
    SOmnResolution       sRes;          //��Ƶ�źŷֱ���
    SOmnFrequency        sFreq;         //��Ƶ�ź�֡Ƶ
    Omn_SIGNAL_SCAN_MODE enumScanMode;  //��Ƶ�ź�ɨ�跽ʽ
}SOmnVideoSignalInfo;

//��Buf�а�4�ֽ�����ֵ
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