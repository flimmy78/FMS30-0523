#ifndef __Omni_API_COMPATIBLE_H__
#define __Omni_API_COMPATIBLE_H__

#define Omn_EnumGlobalInfo        Omn_QueryGlobalInfo
#define Omn_GetSpecCapInfo_V6     Omn_QuerySpecInfo
#define Omn_IsPortActive          Omn_QueryPortActivation
#define Omn_GetBoardMonitorInfo   Omn_QueryMonitorInfo
#define Omn_GetLTCValue           Omn_QueryLTCValue
#define Omn_GetLTCInputStatus     Omn_QueryLTCInputStatus

#define Omn_BOARDTYPE_C5F Omn_BOARDTYPE_CAP500
#define Omn_BOARDTYPE_C6H Omn_BOARDTYPE_CAP600
#define Omn_BOARDTYPE_DEK Omn_BOARDTYPE_EM200
#define Omn_BOARDTYPE_HG  Omn_BOARDTYPE_CG100
#define Omn_BOARDTYPE_HQ  Omn_BOARDTYPE_SER400
#define Omn_BOARDTYPE_E200 Omn_BOARDTYPE_EDITPRO

#define Omn_AES_ANA_CONFIG_ENTIRELY0 Omn_AES_ANA_CONFIG_BIND_V0
#define Omn_AES_ANA_CONFIG_SOLELY    Omn_AES_ANA_CONFIG_AUTO
#define Omn_AES_ANA_CONFIG_ENTIRELY1 Omn_AES_ANA_CONFIG_BIND_V1
#define Omn_AES_ANA_CONFIG_ENTIRELY2 Omn_AES_ANA_CONFIG_BIND_V2
#define Omn_AES_ANA_CONFIG_ENTIRELY3 Omn_AES_ANA_CONFIG_BIND_V3

#define Omn_INPUTB_OVER_INPUTA  Omn_MIXER_MODE_UNKNOWN1
#define Omn_INPUTB_MIXER_INPUTA Omn_MIXER_MODE_UNKNOWN2

#define Omn_MIXER_AUDIO Omn_MIXER_AUDIO_UNKNOWN2

#endif