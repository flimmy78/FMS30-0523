/**
@file: enc_ddpp.h
@brief DDPP Encoder API

@verbatim
File: enc_ddpp.h
Desc: Dolby Digital Plus Professional audio encoder API declaration

      Manufactured under license from Dolby Laboratories
      Dolby and the double-D symbol are trademarks of Dolby Laboratories
 
 Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.

@endverbatim
 **/

#ifndef _ENC_DDPP_H_
#define _ENC_DDPP_H_

#include "bufstrm.h"
#include "mcapiext.h"
#include "mcdefs.h"
#include "dd_def.h"

#define MC_ENCDDPP_NUM_SAMPLES              (1536)      /**< @brief Samples per frame   */

typedef struct dd_pp_encoder ddppaenc_tt;  /**< @brief Audio encoder object */


#ifdef __GNUC__
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif


struct dd_pp_settings
{

/**
 * @name Common settings
 * @{
 * These settings are common for both Dolby Digital and Dolby Digital Plus encoding
 **/
    uint8_t  encoder_mode;                       /**< @brief  Encoder mode */
    uint8_t  coding_mode;                        /**< @brief  Audio coding mode */
    int32_t  in_coding_mode;                     /**< @brief  Input audio coding mode */
    uint16_t data_rate;                          /**< @brief  Contains the desired bitrate in kbps */
    uint8_t  lfe_enabled;                        /**< @brief  Low frequency effects channel flag */
    uint8_t  lfe_filter_flag;                    /**< @brief  LFE filter flag, only used if lfe_enabled = 1 */
    uint8_t  num_input_channels;                 /**< @brief  The number of input channels */
    uint8_t  use_channel_table;                  /**< @brief  Channel routing mode */
    uint8_t  channel_table[8];                   /**< @brief  Custom channel routing table */
    uint8_t  reserved_channel_table[8];          /**< @brief  Reserved for later usage if it will be necessary */
    uint8_t  le_output;                          /**< @brief  Little endian output flag */
    uint8_t  dialnorm;                           /**< @brief  Dialog normalization (default = 24) */
    uint8_t  dc_filter_flag;                     /**< @brief  DC filter flag */
    uint8_t  line_mode_profile;                  /**< @brief  Line mode 'dynrng' profile */
    uint8_t  rf_mode_profile;                    /**< @brief  RF mode 'compr' profile */
    uint8_t  line_mode_profile2;                 /**< @brief  Line mode 'dynrng2' profile */
    uint8_t  rf_mode_profile2;                   /**< @brief  RF mode 'compr2' profile */
    uint8_t  digital_deemphasis_flag;            /**< @brief  Is not supported */
    uint8_t  sample_rate_code;                   /**< @brief  This parameter is fixed at 0 (48 kHz), and is therefore not configurable */
    uint8_t  bandwidth_filter_flag;              /**< @brief  Is not supported */
    uint8_t  surround_phase_shift_flag;          /**< @brief  90 deg phase shift surrounds */
    uint8_t  surround_attenuation_flag;          /**< @brief  Enable 3 dB surround attenuation */
    uint8_t  stereo_downmix_mode;                /**< @brief  Preferred stereo downmix mode */
    uint8_t  Lt_Rt_center_mix_level;             /**< @brief  Lt/Rt center mix level */
    uint8_t  Lt_Rt_surround_mix_level;           /**< @brief  Lt/Rt surround mix level */
    uint8_t  Lo_Ro_center_mix_level;             /**< @brief  Lo/Ro center mix level */
    uint8_t  Lo_Ro_surround_mix_level;           /**< @brief  Lo/Ro surround mix level */
    uint8_t  surround_ex_mode;                   /**< @brief  Dolby surround EX mode */
    uint8_t  headphone_mode;                     /**< @brief  Dolby headphone mode */
    uint8_t  ad_converter_type;                  /**< @brief  A/D converter type */
    uint8_t  copyright_flag;                     /**< @brief  Copyright flag */
    uint8_t  original_flag;                      /**< @brief  Original bitstream flag */
    uint8_t  bitstream_mode;                     /**< @brief  Bitstream mode */
    uint8_t  audio_mixing_level;                 /**< @brief  Audio production mixing level (default = 25) */
    uint8_t  audio_room_type;                    /**< @brief  Audio production room type */
    uint8_t  surround_mode;                      /**< @brief  Dolby surround mode */
/** @} */

/**
 * @name Dolby Digital Plus settings
 * @{
 * The settings below this point are only used when encoding Dolby Digital Plus
 */
    uint8_t  tc_flag;                            /**< @brief  Timecode flag. Is not supported currently, should be 0 */
    uint8_t  tc_frame_rate_code;                 /**< @brief  Timecode frame rate code */
    uint8_t  tc_drop_frame_flag;                 /**< @brief  Drop-frame timecode flag */
    uint32_t tc_start_offset;                    /**< @brief  Timecode start sample offset from midnight (default = 0) */
    uint8_t  auto_settings_profile;              /**< @brief  Automatic settings profile, deprecated */
    uint8_t  encinfo_flag;                       /**< @brief  Encinfo transmission flag */
    uint8_t  stream_creation_time_flag;          /**< @brief  Stream creation time/date flag */
    uint32_t stream_creation_time;               /**< @brief  Stream creation time/date */
    uint32_t user_data;                          /**< @brief  User data for encinfo, range is 0x0000 .. 0xFFFF (default = 0) */
    uint8_t  substream_id;                       /**< @brief  Substream ID, range is 0 .. 7 (default = 0) */
    uint8_t  program_attenuation;                /**< @brief  Program attenuation */
    uint8_t  ext_program_attenuation;            /**< @brief  External program attenuation */
    uint8_t  bitstream_type;                     /**< @brief  The bitstream type control has been removed */
    int64_t  pts_offset;                         /**< @brief  Pts of the start of the stream */
    int32_t  pts_units;                          /**< @brief  The units of the pts_offset field */
    uint8_t  global_drc_profile;                 /**< @brief  Global DRC profile, can be overridden by other DRC profiles */
    uint8_t  center_mix_level;                   /**< @brief  Center downmix level */
    uint8_t  surround_mix_level;                 /**< @brief  Surround downmix level */
/** @} */

    uint8_t enc_reserved[482];

 /**
  * @name Transcoding mode flag
  * @{
  */
    uint8_t transcoding_flag;                    /**< @brief  Enables/disables transcoding mode */
 /** @} */

 /**
 * @name Transcoding auto parameters flags
 * @{
 * These flags indicates whether appropriate transcoding parameter should be taken from the input DD stream
 * or user defined value should be taken. If flag is set to 0, than value from settings will be used for an appropriate parameter,
 * otherwise encoder will use value from input stream.
 */
    uint8_t trans_encoder_mode_auto;
    uint8_t trans_coding_mode_auto;
    uint8_t trans_data_rate_auto;
    uint8_t trans_lfe_enabled_auto;
    uint8_t trans_lfe_filter_flag_auto;
    uint8_t trans_dialnorm_auto;
    uint8_t trans_dc_filter_flag_auto;
    uint8_t trans_line_mode_profile_auto;
    uint8_t trans_rf_mode_profile_auto;
    uint8_t trans_line_mode_profile2_auto;
    uint8_t trans_rf_mode_profile2_auto;
    uint8_t trans_surround_phase_shift_flag_auto;
    uint8_t trans_surround_attenuation_flag_auto;
    uint8_t trans_stereo_downmix_mode_auto;
    uint8_t trans_Lt_Rt_center_mix_level_auto;
    uint8_t trans_Lt_Rt_surround_mix_level_auto;
    uint8_t trans_Lo_Ro_center_mix_level_auto;
    uint8_t trans_Lo_Ro_surround_mix_level_auto;
    uint8_t trans_surround_ex_mode_auto;
    uint8_t trans_headphone_mode_auto;
    uint8_t trans_ad_converter_type_auto;
    uint8_t trans_copyright_flag_auto;
    uint8_t trans_original_flag_auto;
    uint8_t trans_bitstream_mode_auto;
    uint8_t trans_audio_mixing_level_auto;
    uint8_t trans_audio_room_type_auto;
    uint8_t trans_surround_mode_auto;
    uint8_t trans_substream_id_auto;
    uint8_t trans_ext_program_attenuation_auto;
    uint8_t trans_center_mix_level_auto;
    uint8_t trans_surround_mix_level_auto;
 /** @} */

    uint8_t trans_reserved1[64];

 /**
  * @name Transcoding configuration settings 
  * @{
  * These parameters are used only in transcoding mode
  */
    uint32_t trans_max_delay;    /**< @brief Maximum Delay that can be expected in the system =  Max Decoder Delay + Max PCM Processing Delay + Max Encoder Delay*/

    uint8_t trans_reserved2[351];
 /** @} */

};
#pragma pack(pop)



#ifdef __cplusplus
extern "C" {
#endif

 /**
 * @{
 **/

/**
*  @brief Call to fill a dd_pp_settings structure with defaults values based on one of the MCPROFILE profile values
*  @param[in] set - pointer to an dd_pp_settings structure
*  @param[in] profileID - one of the MCPROFILE_* constants

* @param[out] set - modified dd_pp_settings structure
* @return Returns profile description if valid else NULL
*/

char* MC_EXPORT_API ddppOutAudioDefaults(struct dd_pp_settings *set,
                                         int32_t profileID);


/**
*  @brief Call to fill a dd_pp_settings structure with defaults values based on one of the MCPROFILE profile values and set default encoder mode
*  @param[in] set - pointer to an dd_pp_settings structure
*  @param[in] profileID - one of the MCPROFILE_* constants
*  @param[in] defaultEncoderMode - default encoder mode

* @param[out] set - modified dd_pp_settings structure
* @return Returns profile description if valid else NULL
*/
char* MC_EXPORT_API ddppOutAudioDefaultsEx(dd_pp_settings *set, 
                                           int32_t profileID, 
                                           uint8_t defaultEncoderMode);


/**
*  @brief Call to create an audio encoder object
*  @param[in] get_rc - pointer to a get resource function 
*  @param[in] set - pointer to a filled in dd_pp_settings structure
*  @param[in] options - one of the DD_OPT_ defined in @ref dd_def.h
*  @param[in] serialNumber - serial number issued by MainConcept

* @return Pointer to a @ref ddppaenc_tt object if succesful, NULL if unsuccesful

* @note In case of transcoding mode only 32 bit int's audio samples are supported.
*/
        
ddppaenc_tt* MC_EXPORT_API ddppOutAudioNew(void *(*get_rc)(const char* name),
                                           const struct dd_pp_settings *set,
                                           uint32_t options,
                                           char* serialNumber,
                                           int32_t reserved);

/**
*  @brief Call to free an audio encoder object
*  @param[in] a_enc - audio encoder object to free

* @return None
*/

void MC_EXPORT_API ddppOutAudioFree(ddppaenc_tt *a_enc);


/**
*  @brief Call to initialize the audio encoder for an encoding (or transcoding if transcode mode was enables) session, this 
*         function must be called before the PutBytes function is called
*  @param[in] a_enc - pointer to an audio encoder object
*  @param[in] audiobs - pointer to a bufstream_tt object for the compressed data

* @return 0 if successful, non-zero if not
*/

int32_t MC_EXPORT_API ddppOutAudioInit(ddppaenc_tt *a_enc,
                                       bufstream_tt *audiobs);

/**
*  @brief Call to transfer metadata from decoder in trancoding mode
*  @param[in] a_enc - pointer to an audio encoder object
*  @param[in] audioBuffer - pointer to metadata info; 
* @return 0 if successful, non-zero if not
*/
int32_t MC_EXPORT_API ddppOutAudioPutMetadata(ddppaenc_tt *a_enc, 
                                              dd_metadata_info_tt *metadata_info);

/**
*  @brief Call to process some audio samples
*  @param[in] a_enc - pointer to an audio encoder object
*  @param[in] audioBuffer - pointer to a buffer of PCM audio samples; 
*                           in transcode mode it is a pointer to a buffer of ac3 (or ec3) audio stream
*  @param[in] numAudioBytes - number of bytes of data in the audio buffer
*
*  @param[out] audioBuffer - encoded samples to the audiobs object
*
* @return 0 if successful, non-zero if not
*/

int32_t MC_EXPORT_API ddppOutAudioPutBytes(ddppaenc_tt *a_enc,
                                           uint8_t *audioBuffer,
                                           uint32_t numAudioBytes);


/**
*  @brief Call to finish encoding (or transcoding) session, set abort non-zero if encoding (or transcoding) is being aborted.
*  @param[in] a_enc - pointer to an audio encoder object
*  @param[in] abort - set to 0 to finish any leftover audio and clean up,
*
* @return 0 if successful, non-zero if not
*/

int32_t MC_EXPORT_API ddppOutAudioDone(ddppaenc_tt *a_enc,
                                       int32_t abort);


/**
*  @brief call to get the setting errors/warnings in a dd_pp_settings structure
*         use the get_rc callback to provide an err_printf callback to get error
*         messages that can be localized.
*         The general Dolby Digital Plus compliance checks are done first and then the Format checks are done (if the ProfileID
*         is one of those types). Use @ref CHECK_DD_ONLY flag in the options parameter to turn off the Format compliance checks 
*         (only do the general AC-3 compliance checks).
*         If the options parameter doesn't contain @ref CHECK_ALL, the function returns error when the first non-compliant value is found
*         (the remainder of the settings are not checked). If the options parameter does contain @ref CHECK_ALL, all checks are performed,
*         an error message is sent to the err_printf callback for every error found and the error code of the first error found
*         is returned.

* @param[in] get_rc - pointer to a get_rc function
* @param[in] set - pointer to an dd_pp_settings structure
* @param[in] profileID - one of the MCPROFILE_* constants to check the audio conformance
*                        for a particular format, use 0 for no format conformance checks
* @param[in] options - check options, one or more of the CHECK_* defines in @ref dd_def.h
* @param[in] blocks_per_frame - calculated blocks per frame for the settings
*
* @return 0 if no errors found, one of the INV_DD_* error codes defined in @ref dd_def.h if an error is found
*/

int32_t MC_EXPORT_API ddppOutAudioChkSettings(void *(*get_rc)(const char *name),
                                              const struct dd_pp_settings *set,
                                              int32_t profileID,
                                              uint32_t options,
                                              int32_t *blocks_per_frame);

/**
* @brief Provides access to extended module API.
* @param[in] func - Identifier of module extended function
* @return Pointer to requested function or NULL
*/
APIEXTFUNC MC_EXPORT_API ddppOutAudioGetAPIExt(uint32_t func);

/**
 * @}
**/

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------

#endif // _ENC_DDPP_H_
