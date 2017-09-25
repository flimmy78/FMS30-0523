/**
@file: dd_def.h
@brief Header file for Dolby Digital definitions and constants

@verbatim
File: dd_def.h
Desc: Header file for Dolby Digital definitions and constants

       Manufactured under license from Dolby Laboratories
       Dolby and the double-D symbol are trademarks of Dolby Laboratories

 Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.

@endverbatim
**/

#ifndef _DD_DEF_H_
#define _DD_DEF_H_

/**
* @def AC3_AUDIO
* @name DD audio type, for compatibility with other SDK's
* @{
**/
#define AC3_AUDIO                     5 /**< @brief Dolby digital */
/** @}*/

/**
* @def DD_OPT
* @name Option parameters to the ddXXXOutAudioNew functions
* @{
**/

#define DD_OPT_SI_PCM_SAMPLES         0x00000000 /**< @brief The audio samples being input to the encoder are 16-bit short int's, the endian of the samples match the platform (default) */

#define DD_OPT_SI_SWAP_PCM_SAMPLES    0x00000001 /**< @brief The audio samples being input to the encoder are 16-bit short int's, the endian of the samples are opposite of the platform */

#define DD_OPT_FP_PCM_SAMPLES         0x00000002 /**< @brief The audio samples being input to the encoder are 32 bit IEEE floating point values */

#define DD_OPT_DFP_PCM_SAMPLES        0x00000004 /**< @brief The audio samples being input to the encoder are 64 bit floating point values */

#define DD_OPT_24B_PCM_SAMPLES        0x00000008 /**< @brief The audio samples being input to the encoder are 24 bit int's */

#define DD_OPT_32B_PCM_SAMPLES        0x00000010 /**< @brief The audio samples being input to the encoder are 32 bit int's */
/** @}*/

#define DD_DEFVAL_IN_CODING_MODE      (-2) /**< @brief Default values for the parameters of @ref dd_pp_settings */

/**
* @def CHECK
* @name Options for the XXXChkSettings functions
* @{
**/

#define CHECK_DD_ONLY                 0x00000001  /**< @brief Only do Dolby Digital checks, do not check for format compliance */
#define CHECK_ALL                     0x00000002  /**< @brief Do all checks, normally the check functions return after the */ 
/** @}*/

/**
* @def DD_FREQ
* @name Frequencies
* @{
**/
#define DD_FREQ_48                    0
#define DD_FREQ_44_1                  1
#define DD_FREQ_32                    2
/** @}*/

/**
* @def DD_ENC_MODE
* @name Encoder modes
* @{
**/
#define DD_ENC_MODE_DDP              0 /**< @brief  Dolby Digital Plus (bsid 16)                          */
#define DD_ENC_MODE_DD               1 /**< @brief  Dolby Digital (bsid 6)                                */
#define DD_ENC_MODE_BLURAY_PRIMARY   3 /**< @brief  BD-compliant primary stream (I0: bsid 6, D0: bsid 16) */
#define DD_ENC_MODE_DD_LEGACY        7 /**< @brief  Dolby Digital Legacy Mode (bsid 8)                    */
/** @}*/

/**
* @def DD_CHANNEL
* @name Channel table index order
* @{
**/
#define DD_CHANNEL_LEFT               0
#define DD_CHANNEL_CENTER             1
#define DD_CHANNEL_RIGHT              2
#define DD_CHANNEL_LEFT_SUR           3
#define DD_CHANNEL_RIGHT_SUR          4
#define DD_CHANNEL_LFE                5
#define DD_CHANNEL_EXT1               6    /**< @brief Lb for 3/4 mode or Cs for 3/3 mode */
#define DD_CHANNEL_EXT2               7    /**< @brief Rb for 3/4 mode */
#define DD_CHANNEL_COUNT              8
/** @}*/

/**
* @def DD_CHANNEL
* @name Channel routing mode presets
* @{
**/
#define DD_CHANNEL_MODE_DEFAULT       0    /**< @brief  use default routing */
#define DD_CHANNEL_MODE_CUSTOM        1    /**< @brief  use the custom channel table */
#define DD_CHANNEL_MODE_1             2    /**< @brief  L,  R, Ls,  Rs,   C,  LFE, EXT1, EXT2 */
#define DD_CHANNEL_MODE_2             3    /**< @brief  L,  C,  R,  Ls,  Rs,  LFE, EXT1, EXT2 */
#define DD_CHANNEL_MODE_3             4    /**< @brief  L, Ls,  C,  Rs,   R,  LFE, EXT1, EXT2 */
#define DD_CHANNEL_MODE_4             5    /**< @brief  L,  R,  C, LFE,  Ls,   Rs, EXT1, EXT2 */
#define DD_CHANNEL_MODE_5             6    /**< @brief  L,  C, Rs,   R,  Ls,  LFE, EXT1, EXT2 */
#define DD_CHANNEL_MODE_6             7    /**< @brief  C,  L,  R,  Ls,  Rs,  LFE, EXT1, EXT2 */
#define DD_CHANNEL_MODE_COUNT         8
/** @}*/

/**
* @def DD_AUDIOMODE
* @name Coding modes
* @{
**/
#define DD_AUDIOMODE_DSC              0    /**< @brief   Dolby Surround compatible (Lt,Rt)   */
#define DD_AUDIOMODE_1_1              0    /**< @brief   (L,R)              2 channels total */
#define DD_AUDIOMODE_1_0              1    /**< @brief   (C)                1 channel total  */
#define DD_AUDIOMODE_2_0              2    /**< @brief   (L,R)              2 channels total */
#define DD_AUDIOMODE_3_0              3    /**< @brief   (L,C,R)            3 channels total */
#define DD_AUDIOMODE_2_1              4    /**< @brief   (L,R,l)            3 channels total */
#define DD_AUDIOMODE_3_1              5    /**< @brief   (L,C,R,l)          4 channels total */
#define DD_AUDIOMODE_2_2              6    /**< @brief   (L,R,l,r)          4 channels total */
#define DD_AUDIOMODE_3_2              7    /**< @brief   (L,C,R,l,r)        5 channels total */
#define DD_AUDIOMODE_3_4             21    /**< @brief   (L,C,R,l,r,Lb,Rb)  7 channels total */
#define DD_AUDIOMODE_3_3             24    /**< @brief   (L,C,R,l,r,Cs)     6 channels total */
#define DD_AUDIOMODE_COUNT           25
/** @}*/

/**
* @def DD_BITRATE
* @name Bitrates
* @{
**/
#define DD_BITRATE_32                 32
#define DD_BITRATE_40                 40
#define DD_BITRATE_48                 48
#define DD_BITRATE_56                 56
#define DD_BITRATE_64                 64
#define DD_BITRATE_72                 72
#define DD_BITRATE_80                 80
#define DD_BITRATE_88                 88
#define DD_BITRATE_96                 96
#define DD_BITRATE_104                104
#define DD_BITRATE_112                112
#define DD_BITRATE_120                120
#define DD_BITRATE_128                128
#define DD_BITRATE_144                144
#define DD_BITRATE_160                160
#define DD_BITRATE_176                176
#define DD_BITRATE_192                192
#define DD_BITRATE_200                200
#define DD_BITRATE_208                208
#define DD_BITRATE_216                216
#define DD_BITRATE_224                224
#define DD_BITRATE_232                232
#define DD_BITRATE_240                240
#define DD_BITRATE_248                248
#define DD_BITRATE_256                256
#define DD_BITRATE_272                272
#define DD_BITRATE_288                288
#define DD_BITRATE_300                300
#define DD_BITRATE_304                304
#define DD_BITRATE_320                320
#define DD_BITRATE_336                336
#define DD_BITRATE_352                352
#define DD_BITRATE_368                368
#define DD_BITRATE_384                384
#define DD_BITRATE_400                400
#define DD_BITRATE_448                448
#define DD_BITRATE_512                512
#define DD_BITRATE_576                576
#define DD_BITRATE_640                640
#define DD_BITRATE_704                704
#define DD_BITRATE_768                768
#define DD_BITRATE_832                832
#define DD_BITRATE_896                896
#define DD_BITRATE_960                960
#define DD_BITRATE_1008               1008
#define DD_BITRATE_1024               1024
/** @}*/

/**
* @def INV_DD
* @name Defines for Dolby Digital audio conformance check errors
* @{
**/
#define INV_DD_ERRORS                       0x00120000
#define INV_DD_AUDIO_UNKNOWN                INV_DD_ERRORS + 0
#define INV_DD_SAMPLE_RATE                  INV_DD_ERRORS + 1
#define INV_DD_AUDIO_TYPE                   INV_DD_ERRORS + 2
#define INV_DD_AUDIO_CHANNELS               INV_DD_ERRORS + 3
#define INV_DD_AUDIO_BITRATE                INV_DD_ERRORS + 4
#define INV_DD_AUDIO_CMODE                  INV_DD_ERRORS + 5
#define INV_DD_AUDIO_COMP                   INV_DD_ERRORS + 6
#define INV_DD_AUDIO_SECCOMP                INV_DD_ERRORS + 7
#define INV_DD_NOT_INSTALLED                INV_DD_ERRORS + 8
#define INV_DD_AUDIO_LFEENA                 INV_DD_ERRORS + 9
#define INV_DD_AUDIO_LFEFILT                INV_DD_ERRORS + 10
#define INV_DD_AUDIO_DELAYSUR               INV_DD_ERRORS + 11
#define INV_DD_AUDIO_INCHAN                 INV_DD_ERRORS + 12
#define INV_DD_AUDIO_CHAN_ROUTING           INV_DD_ERRORS + 13
#define INV_DD_AUDIO_BE_OUTPUT              INV_DD_ERRORS + 14
#define INV_DD_AUDIO_BUFWDTH                INV_DD_ERRORS + 15
#define INV_DD_AUDIO_SRMOD                  INV_DD_ERRORS + 16
#define INV_DD_AUDIO_AUXDATL                INV_DD_ERRORS + 17
#define INV_DD_AUDIO_BWLOWCPL               INV_DD_ERRORS + 18
#define INV_DD_AUDIO_CHBWCOD                INV_DD_ERRORS + 19
#define INV_DD_AUDIO_PHSCORE                INV_DD_ERRORS + 20
#define INV_DD_AUDIO_LFEHALF                INV_DD_ERRORS + 21
#define INV_DD_AUDIO_BWSPX                  INV_DD_ERRORS + 22
#define INV_DD_AUDIO_BWHIGH                 INV_DD_ERRORS + 23
#define INV_DD_AUDIO_CPL_ECPL_ENABL         INV_DD_ERRORS + 24
#define INV_DD_AUDIO_DIALNORM               INV_DD_ERRORS + 25
#define INV_DD_AUDIO_DCFILTERFLAG           INV_DD_ERRORS + 26
#define INV_DD_AUDIO_COMPR_PROFILE          INV_DD_ERRORS + 27
#define INV_DD_AUDIO_COMPR2_PROFILE         INV_DD_ERRORS + 28
#define INV_DD_AUDIO_DYNRNG_PROFILE         INV_DD_ERRORS + 29
#define INV_DD_AUDIO_DYNRNG2_PROFILE        INV_DD_ERRORS + 30
#define INV_DD_AUDIO_DIGDEEMPH_MODE         INV_DD_ERRORS + 31
#define INV_DD_AUDIO_ENC51_ENCODING_MODE    INV_DD_ERRORS + 32
#define INV_DD_AUDIO_BWFILTERFLAG           INV_DD_ERRORS + 33
#define INV_DD_AUDIO_PH90FILTERFLAG         INV_DD_ERRORS + 34
#define INV_DD_AUDIO_SURATTFLAG             INV_DD_ERRORS + 35
#define INV_DD_AUDIO_DMIXMOD                INV_DD_ERRORS + 36
#define INV_DD_AUDIO_LTRTCMIXLEV            INV_DD_ERRORS + 37
#define INV_DD_AUDIO_LTRTSURMIXLEV          INV_DD_ERRORS + 38
#define INV_DD_AUDIO_LOROCMIXLEV            INV_DD_ERRORS + 39
#define INV_DD_AUDIO_LOROSURMIXLEV          INV_DD_ERRORS + 40
#define INV_DD_AUDIO_DSUREXMOD              INV_DD_ERRORS + 41
#define INV_DD_AUDIO_DHEADPHONMOD           INV_DD_ERRORS + 42
#define INV_DD_AUDIO_ADCONVTYP              INV_DD_ERRORS + 43
#define INV_DD_AUDIO_MIXLEVEL               INV_DD_ERRORS + 44
#define INV_DD_AUDIO_COPYRIGHTB             INV_DD_ERRORS + 45
#define INV_DD_AUDIO_ORIGBS                 INV_DD_ERRORS + 46
#define INV_DD_AUDIO_BSMOD                  INV_DD_ERRORS + 47
#define INV_DD_AUDIO_ROOMTYP                INV_DD_ERRORS + 48
#define INV_DD_AUDIO_DSURMOD                INV_DD_ERRORS + 49
#define INV_DD_AUDIO_AUTOSETUPPROFILE       INV_DD_ERRORS + 50
#define INV_DD_AUDIO_SUBSTREAMID            INV_DD_ERRORS + 51
#define INV_DD_AUDIO_BSTYPE                 INV_DD_ERRORS + 52
#define INV_DD_AUDIO_PGMSCL                 INV_DD_ERRORS + 53
#define INV_DD_AUDIO_EXTPGMSCL              INV_DD_ERRORS + 54
#define INV_DD_AUDIO_TC_FLAG                INV_DD_ERRORS + 55
#define INV_DD_AUDIO_TC_FRAMERATECODE       INV_DD_ERRORS + 56
#define INV_DD_AUDIO_TC_ISDROPFRAME         INV_DD_ERRORS + 57
#define INV_DD_AUDIO_TC_OFFSET              INV_DD_ERRORS + 58
#define INV_DD_AUDIO_ENF_ENABL              INV_DD_ERRORS + 59
#define INV_DD_AUDIO_USE_CHAN_TBL           INV_DD_ERRORS + 60
#define INV_DD_AUDIO_2X_FLAG                INV_DD_ERRORS + 61
#define INV_DD_AUDIO_ALT_BITSTREAM          INV_DD_ERRORS + 62
#define INV_DD_AUDIO_RF_OVERMOD             INV_DD_ERRORS + 63
#define INV_DD_AUDIO_CMIXLEVEL              INV_DD_ERRORS + 64
#define INV_DD_AUDIO_SMIXLEVEL              INV_DD_ERRORS + 65
#define INV_DD_AUDIO_AUX_DATA_LENGTH        INV_DD_ERRORS + 66
#define INV_DD_AUDIO_DEC_OUTPUT_CONFIG      INV_DD_ERRORS + 67
#define INV_DD_AUDIO_PRODUCTION_INFO        INV_DD_ERRORS + 68
#define INV_DD_AUDIO_GLOBAL_DRC_PROFILE     INV_DD_ERRORS + 69
#define INV_DD_AUDIO_SURMIXLEV              INV_DD_ERRORS + 70
#define INV_DD_AUDIO_CMIXLEV                INV_DD_ERRORS + 71
#define INV_DD_AUDIO_COMPRASSION_MODE       INV_DD_ERRORS + 72
#define INV_DD_AUDIO_STEREO_OUTPUT_MODE     INV_DD_ERRORS + 73
#define INV_DD_AUDIO_DYNRNG_SCALE_LOW       INV_DD_ERRORS + 74
#define INV_DD_AUDIO_DYNRNG_SCALE_HIGH      INV_DD_ERRORS + 75
#define INV_DD_AUDIO_IN_OUT_NUM_CHANS       INV_DD_ERRORS + 76
#define INV_DD_AUDIO_CONCEALMENT_MODE       INV_DD_ERRORS + 77
#define INV_DD_AUDIO_IN_CODING_MODE         INV_DD_ERRORS + 78
#define INV_DD_ENCODER_MODE                 INV_DD_ERRORS + 79
/** @}*/

#endif // _DD_DEF_H_
