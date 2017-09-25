///////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2001-2017. All rights reserved. 
//
//  This software code is subject to the terms and conditions outlined 
//  in the non-disclosure agreement between Matrox and your company. 
//  By accessing this code or using it in any way, you indicate your 
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind, 
//  either expressed or implied, including but not limited to the implied 
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
//  changes in specifications and code at any time and without notice. 
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for 
//  its use; nor for any infringements of patents or other rights of 
//  third parties resulting from its use. No license is granted under 
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "mvTypes.h"
#include "mvIODefinitions.h"
//#include <initializer_list>

//*************************************************************************************//
//**                 KEEP THIS HEADER FILE IN ALPHEBATICAL ORDER                     **//
//*************************************************************************************//


//*************************************************************************************//
//**                          CONSTANTS                                              **//
//*************************************************************************************//

const uint32_t     kulMvMaxThreadPool  = 4;

// *****************************************************************************//
// **                             G L O B A L   M A C R O							**// 
// *****************************************************************************//

#ifdef LINUX_PLATFORM

   // Naked doesn't exist on gcc, but the Linux Intel Compiler undestands it as is
   // (and cpp's with "naked" directive must be compiled by Intel compiler on Linux)
   #define MV_DECLSPEC_NAKED    __declspec(naked)
   #define MV_DECLSPEC_NAKED_64 __declspec(naked) // Only x64 Linux is supported

   #ifdef __INTEL_COMPILER
      // Intel compiler understands the Windows version __declspec(align(x))
      #define MV_DECLSPEC_ALIGN(a)  __declspec(align(a))
   // #else
      // #define MV_DECLSPEC_ALIGN(a)  __attribute__((aligned(a)))
      /* There is a problem with using __attribute__((aligned(a))) in GCC because
         it's supposed to come after the type and/or name of the variable (depending 
         on the version used), which is not the same as Windows nor the Intel compiler.
         Moreover, GCC might even ignore the attribute without reporting an error.
         Therefore for now, use Intel compiler in Linux whenever declspec(align()) is needed */
   #endif

   #define MV_DECLSPEC_DEPRECATED __attribute__((deprecated))
   
   // The following do not exist in Linux
   #define MV_DECLSPEC_DLLEXPORT 
   #define MV_DECLSPEC_DLLIMPORT 
   #define MV_DECLSPEC_NOVTABLE 

#else // WINDOWS

   #define MV_DECLSPEC_NAKED      __declspec(naked)
   #define MV_DECLSPEC_ALIGN(a)   __declspec(align(a))
   #define MV_DECLSPEC_DLLEXPORT  __declspec(dllexport)
   #define MV_DECLSPEC_DLLIMPORT  __declspec(dllimport)
   #define MV_DECLSPEC_NOVTABLE   __declspec(novtable)
   #define MV_DECLSPEC_DEPRECATED __declspec(deprecated)

   #ifdef _WIN64
      #define MV_DECLSPEC_NAKED_64 __declspec(naked)
   #else
      #define MV_DECLSPEC_NAKED_64 
   #endif

#endif

//*************************************************************************************//
//**                          ENUMERATIONS                                           **//
//*************************************************************************************//

//
// Summary:
//    Indicates the position in the 3:2 pulldown sequence of a frame.
//
enum EMv32Sequence
{
   ke32SequenceInvalid,   // Invalid value.
   ke32SequenceDetect,    //
   ke32SequenceReset,     // 
   ke32SequenceA,         //
   ke32SequenceB,         //
   ke32SequenceC,			  //					
   ke32SequenceD,         //
   ke32SequenceNone,      //
   ke32SequenceLast       // End of list indicator.
};

//
// Summary:
//    This macro is used to get the string corresponding to the EMv32Sequence enum value.
//
#define MV_32SEQUENCE_TO_STRING(e)                                      \
   (e == ke32SequenceInvalid)             ? "ke32SequenceInvalid" :     \
   (e == ke32SequenceDetect)              ? "ke32SequenceDetect" :      \
   (e == ke32SequenceReset)               ? "ke32SequenceReset" :       \
   (e == ke32SequenceA)                   ? "ke32SequenceA" :           \
   (e == ke32SequenceB)                   ? "ke32SequenceB" :           \
   (e == ke32SequenceC)                   ? "ke32SequenceC" :           \
   (e == ke32SequenceD)                   ? "ke32SequenceD" :           \
   (e == ke32SequenceNone)                ? "ke32SequenceNone" :        \
   (e == ke32SequenceLast)                ? "ke32SequenceLast" :        \
   "???"

//
// Summary:
//    Represents an AES/EBU channel at the input and/or output. An AES/EBU I/O channel represents a digital audio 
//    stereo pair (2 mono tracks).
//
enum EMvAesEbuAudioIOChannel
{
   keAesEbuAudioIOChannelInvalid,     // Invalid value.
   keAesEbuAudioIOChannelA = 0x0001,  //
   keAesEbuAudioIOChannelB = 0x0002,  //
   keAesEbuAudioIOChannelC = 0x0004,  //
   keAesEbuAudioIOChannelD = 0x0008,  //
   keAesEbuAudioIOChannelE = 0x0010,  //
   keAesEbuAudioIOChannelF = 0x0020,  //
   keAesEbuAudioIOChannelG = 0x0040,  //
   keAesEbuAudioIOChannelH = 0x0080,  //
   keAesEbuAudioIOChannelI = 0x0100,  //
   keAesEbuAudioIOChannelJ = 0x0200,  //
   keAesEbuAudioIOChannelK = 0x0400,  //
   keAesEbuAudioIOChannelL = 0x0800,  //
   keAesEbuAudioIOChannelM = 0x1000,  //
   keAesEbuAudioIOChannelN = 0x2000,  //
   keAesEbuAudioIOChannelO = 0x4000,  //
   keAesEbuAudioIOChannelP = 0x8000,  //
   keAesEbuAudioIOChannelLast         // End of list indicator.
};

//
// Summary:
//    Determines which AES/EBU audio parameter to control at the output.
//
enum EMvAesEbuAudioOutputParameter
{
   KeAesEbuAudioOutputInvalid,   // Invalid value.
   keAesEbuAudioOutputMute,      // Controls the AES/EBU audio muting at the output. Uses a parameter
                                    // of type EMvOnOff. This parameter is supported on Matrox X.linkHD, 
									// X.mio2, and on the first AES/EBU audio pair on DSX LE2/CG.
									// It is not supported on the optional X.RIO module for X.mio2. 
   keAesEbuAudioOutputSPDIF      // Controls the AES/EBU output to generate a SPDIF compatible 
                                    // signal. Uses a parameter of type EMvOnOff. This parameter is not 
									// supported on Matrox DSX LE/CG or DSX LE2/CG.
};

//
// Summary:
//    Specifies the type of the alias surface allocated.
//
enum EMvAliasAccessType
{
   keMvAliasAccessTypeInvalid,   // Invalid value.
   keMvAliasAccessTypeReadWrite, // Specifies that the alias surface can be read and written to, like 
                                    // any normal surface.
   keMvAliasAccessTypeReadOnly,  // Specifies that the alias surface is read-only. The write 
                                    // completion is signaled when the reference surface write event 
                                    // is signaled.  
   keMvAliasAccessTypeLast       // End of list indicator.
};
// This macro is used to get the string of the enum value EMvAliasAccessType
#define MV_ALIAS_ACCESS_TYPE_ENUM_TO_STRING(eAliasAccessType) \
   ((eAliasAccessType == keMvAliasAccessTypeInvalid)  ? ("Invalid") : \
   (eAliasAccessType == keMvAliasAccessTypeReadWrite) ? ("ReadWrite") : \
   (eAliasAccessType == keMvAliasAccessTypeReadOnly)  ? ("ReadOnly") : \
   (eAliasAccessType == keMvAliasAccessTypeLast)      ? ("Last") : \
   ("???"))

//
// Summary:
//    Determines which analog audio parameter to control at the input.
//
enum EMvAnalogAudioInputParameter
{
   keAnalogAudioInputInvalid, // Invalid value.
   keAnalogAudioInputVolume,  // Sets analog audio input gain and attenuation. Uses a parameter of 
                                 // type double. This parameter is not supported on Matrox DSX LE/CG or DSX LE2/CG. 
   keAnalogAudioInputMute,    // Sets analog audio input muting. Uses a parameter of type EMvOnOff.
   keAnalogAudioInputLast     // End of list indicator.
};

//
// Summary:
//    Specifies the analog audio input source.
//
enum EMvAnalogAudioInputSource
{
   keAnalogAudioInputSourceInvalid, // Invalid value.
   keAnalogAudioInputSourceRCA,     // Specifies that the analog audio source is of RCA type.
   keAnalogAudioInputSourceXLR,     // Specifies that the analog audio source is of XLR type.
   keAnalogAudioInputSourceLast     // End of list indicator.
};

//
// Summary:
//    Determines which analog audio output parameter to control.
//
enum EMvAnalogAudioOutputParameter
{
   keAnalogAudioOutputInvalid,         // Invalid value.
   keAnalogAudioOutputVolume,          // Sets analog audio output attenuation. Uses a 
                                          // parameter of type double. This parameter is supported 
										  // on Matrox X.linkSD, X.linkHD, DSX LE, DSX LE2, DSX SD, 
										  // and X.AVCio only.
   keAnalogAudioOutputImpedance,       // Sets the output impedance for balanced analog audio connectors. Uses
                                          // a parameter of type EMvAudioSignal. This parameter is supported 
										  // on Matrox X.linkSD, X.linkHD, DSX LE, DSK LE2, DSX SD, 
										  // and X.AVCio only.
   keAnalogAudioOutputMute,            // Sets analog audio output muting. Uses a
                                          // parameter of type EMvOnOff. This parameter is supported 
										  // on Matrox X.linkSD, X.linkHD, DSX LE, DSK LE2, DSX SD, 
										  // and X.AVCio only.
   keAnalogAudioPreviewOutputVolume,   // Sets the attenuation of the audio preview output. 
                                          // Uses a parameter of type double.
   keAnalogAudioPreviewOutputSource,   // Selects the audio pair that will be used as the source for the audio preview output. 
                                          // Uses a parameter of type EMvAudioPair.
   keAnalogAudioOutputSource,          // Selects the audio pair that will be used as the source
                                          // for the analog audio output. Uses a combination of parameters 
                                          // of type EMvAudioPair and EMvAudioPlaybackChannel.
   keAnalogAudioOutputBalanced,        // Selects the analog audio output type. Uses a
                                          // parameter of type bool.
   keAnalogAudioOutputLast             // End of list indicator.
};

//
// Summary:
//    Determines the analog audio source.
//
enum EMvAnalogAudioSource
{
   keAnalogAudioSourceInvalid,   // Invalid value.
   keAnalogAudioSourceInput,     // Specifies the analog audio source at input.  Uses a parameter 
                                    // of type EMvAnalogAudioInputSource.
   keAnalogAudioSourceOutput,    // Specifies the analog audio source at output.  Uses a parameter
                                    // of type EMvAudioPath.
   keAnalogAudioSourceLast       // End of list indicator.
};

//
// Summary:
//    Determines which HDMI audio output parameter to control.
//
enum EMvHdmiAudioOutputParameter
{
   keHdmiAudioOutputInvalid,        // Invalid value.
   keHdmiAudioOutputSource,         // Selects the audio pair that will be used as the source
                                    // for the HDMI audio output. Uses a combination of parameters 
                                    // of type EMvAudioPair and EMvAudioPlaybackChannel.
   keHdmiAudioOutputChannelType,    // Specifies the channel type for the HDMI audio output.
                                    // Uses a parameter of type EMvChannelType.
   keHdmiAudioOutputInvertCh,       // Invert HDMI audio channels 3 and 4
   keHdmiAudioOutputLast            // End of list indicator.
};

//
// Summary:
//    Determines the path in which an embedded audio stream can pass.
//
enum EMvHdmiAudioIOChannel
{
   keHdmiAudioIOChannelInvalid  = 0x00,  // Invalid value.
   keHdmiAudioIOChannelA        = 0x01,  // Specifies the first stereo HDMI audio channel.
   keHdmiAudioIOChannelB        = 0x02,  // Specifies the second stereo HDMI audio channel.
   keHdmiAudioIOChannelC        = 0x04,  // Specifies the third stereo HDMI audio channel.
   keHdmiAudioIOChannelD        = 0x08,  // Specifies the fourth stereo HDMI audio channel.
   keHdmiAudioIOChannelLast              // End of list indicator.
};

//
// Summary:
//    Enumerates the number of bits per audio sample.
//
enum EMvAudioBitsPerSample
{
   keAudioBitsPerSampleInvalid   = 0,  // Invalid value.
   keAudioBitsPerSample16        = 16, // Indicates that the audio is 16 bits per sample.
   keAudioBitsPerSample17        = 17, // Indicates that the audio is 17 bits per sample.
   keAudioBitsPerSample18        = 18, // Indicates that the audio is 18 bits per sample.
   keAudioBitsPerSample19        = 19, // Indicates that the audio is 19 bits per sample.
   keAudioBitsPerSample20        = 20, // Indicates that the audio is 20 bits per sample.
   keAudioBitsPerSample21        = 21, // Indicates that the audio is 21 bits per sample.
   keAudioBitsPerSample22        = 22, // Indicates that the audio is 22 bits per sample.
   keAudioBitsPerSample23        = 23, // Indicates that the audio is 23 bits per sample.
   keAudioBitsPerSample24        = 24, // Indicates that the audio is 24 bits per sample.
   keAudioBitsPerSample25        = 25, // Indicates that the audio is 25 bits per sample.
   keAudioBitsPerSample26        = 26, // Indicates that the audio is 26 bits per sample.
   keAudioBitsPerSample27        = 27, // Indicates that the audio is 27 bits per sample.
   keAudioBitsPerSample28        = 28, // Indicates that the audio is 28 bits per sample.
   keAudioBitsPerSample29        = 29, // Indicates that the audio is 29 bits per sample.
   keAudioBitsPerSample30        = 30, // Indicates that the audio is 30 bits per sample.
   keAudioBitsPerSample31        = 31, // Indicates that the audio is 31 bits per sample.
   keAudioBitsPerSample32        = 32, // Indicates that the audio is 32 bits per sample.
   keAudioBitsPerSampleLast            // End of list indicator.
};

//
// Summary:
//    Determines the capture path that an audio stream goes through.
//
enum EMvAudioCaptureChannel
{
   keAudioCaptureChannelInvalid      = 0x00000,  // Invalid channel.
   keAudioCaptureChannel0            = 0x00001,  // Specifies the first audio channel for capture from DSX hardware.
   keAudioCaptureChannel1            = 0x00002,  // Specifies the second audio channel for capture from DSX hardware.
   keAudioCaptureChannel2            = 0x00004,  // Specifies the third audio channel for capture from DSX hardware.
   keAudioCaptureChannel3            = 0x00008,  // Specifies the fourth audio channel for capture from DSX hardware.
   keAudioCaptureChannel4            = 0x00010,  // Specifies the fifth audio channel for capture from DSX hardware.
   keAudioCaptureChannel5            = 0x00020,  // Specifies the sixth audio channel for capture from DSX hardware.
   keAudioCaptureChannel6            = 0x00040,  // Specifies the seventh audio channel for capture from DSX hardware.
   keAudioCaptureChannel7            = 0x00080,  // Specifies the eighth audio channel for capture from DSX hardware.
   keAudioCaptureChannelSystemSound0 = 0x00100,  // Specifies the first audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound1 = 0x00200,  // Specifies the second audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound2 = 0x00400,  // Specifies the third audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound3 = 0x00800,  // Specifies the fourth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound4 = 0x01000,  // Specifies the fifth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound5 = 0x02000,  // Specifies the sixth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound6 = 0x04000,  // Specifies the seventh audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound7 = 0x08000,  // Specifies the eighth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound8 = 0x10000,  // Specifies the ninth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelSystemSound9 = 0x20000,  // Specifies the tenth audio channel for capture from the computer's sound card.
   keAudioCaptureChannelLast                    // End of list indicator.
};

//
// Summary:
//    Determines the audio capture part to configure.
//
enum EMvAudioCaptureConfiguration
{
   keAudioCaptureConfigurationInvalid,    // Invalid channel.
   keAudioCaptureConfigurationSyncMaster, // Configures the audio synchronization master for capture.
   keAudioCaptureConfigurationLast        // End of list indicator.
};

//
// Summary:
//    Determines which audio playback part to configure.
//
enum EMvAudioPlaybackConfiguration
{
   keAudioPlaybackConfigurationInvalid,      // Invalid value.
   keAudioPlaybackConfigurationSyncMaster,   // Configures the audio synchronization master for playback.
   keAudioPlaybackConfigurationLast          // End of list indicator.
};

//
// Summary:
//    Enumerates an audio pair. 
//
enum EMvAudioPair
{
   keAudioPairInvalid,  // Invalid value.
   keAudioPair0,        // Indicates audio pair 1. 
   keAudioPair1,        // Indicates audio pair 2.
   keAudioPair2,        // Indicates audio pair 3.
   keAudioPair3,        // Indicates audio pair 4.
   keAudioPair4,        // Indicates audio pair 5.
   keAudioPair5,        // Indicates audio pair 6.
   keAudioPair6,        // Indicates audio pair 7.
   keAudioPair7,        // Indicates audio pair 8.
   keAudioPairLast      // End of list indicator.
};

//
// Summary:
//    Specifies the playback audio channel.
//
enum EMvAudioPlaybackChannel
{
   keAudioPlaybackChannelInvalid       = 0x00000,   // Invalid channel.
   keAudioPlaybackChannel0             = 0x00001,   // Specifies the first audio channel for playback from DSX hardware.
   keAudioPlaybackChannel1             = 0x00002,   // Specifies the second audio channel for playback from DSX hardware.
   keAudioPlaybackChannel2             = 0x00004,   // Specifies the third audio channel for playback from DSX hardware.
   keAudioPlaybackChannel3             = 0x00008,   // Specifies the fourth audio channel for playback from DSX hardware.
   keAudioPlaybackChannel4             = 0x00010,   // Specifies the fifth audio channel for playback from DSX hardware.
   keAudioPlaybackChannel5             = 0x00020,   // Specifies the sixth audio channel for playback from DSX hardware.
   keAudioPlaybackChannel6             = 0x00040,   // Specifies the seventh audio channel for playback from DSX hardware.
   keAudioPlaybackChannel7             = 0x00080,   // Specifies the eighth audio channel for playback from DSX hardware.
   keAudioPlaybackChannelSystemSound0  = 0x00100,   // Specifies the first audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound1  = 0x00200,   // Specifies the second audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound2  = 0x00400,   // Specifies the third audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound3  = 0x00800,   // Specifies the fourth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound4  = 0x01000,   // Specifies the fifth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound5  = 0x02000,   // Specifies the sixth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound6  = 0x04000,   // Specifies the seventh audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound7  = 0x08000,   // Specifies the eighth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound8  = 0x10000,   // Specifies the ninth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelSystemSound9  = 0x20000,   // Specifies the tenth audio channel for playback from the computer's sound card.
   keAudioPlaybackChannelLast                      // End of list indicator.
};

//
// Summary:
//    Determines the path through which an analog audio stream can pass.
//
enum EMvAudioIOChannel
{
   keAudioIOChannelInvalid = 0x00000000,        // Invalid value.
   keAudioIOChannelLeft    = 0x00000001,        // Specifies the left channel of the stereo analog audio stream.
   keAudioIOChannelRight   = 0x00000002,        // Specifies the right channel of the stereo analog audio stream.
   keAudioIOChannel1 = keAudioIOChannelLeft,    // Specifies the first channel of the stereo analog audio stream.
   keAudioIOChannel2 = keAudioIOChannelRight,   // Specifies the second channel of the stereo analog audio stream.
   keAudioIOChannel3       = 0x00000004,        // Specifies the third channel of the stereo analog audio stream.
   keAudioIOChannel4       = 0x00000008,        // Specifies the fourth channel of the stereo analog audio stream.
   keAudioIOChannel5       = 0x00000010,        // Specifies the fifth channel of the stereo analog audio stream.
   keAudioIOChannel6       = 0x00000020,        // Specifies the sixth channel of the stereo analog audio stream.
   keAudioIOChannel7       = 0x00000040,        // Specifies the seventh channel of the stereo analog audio stream.
   keAudioIOChannel8       = 0x00000080,        // Specifies the eighth channel of the stereo analog audio stream.
   keAudioIOChannelPair0 = keAudioIOChannel1 | keAudioIOChannel2,  // Specifies the first stereo pair of the analog audio stream.
   keAudioIOChannelPair1 = keAudioIOChannel3 | keAudioIOChannel4,  // Specifies the second stereo pair of the analog audio stream.
   keAudioIOChannelPair2 = keAudioIOChannel5 | keAudioIOChannel6,  // Specifies the third stereo pair of the analog audio stream.
   keAudioIOChannelPair3 = keAudioIOChannel7 | keAudioIOChannel8,  // Specifies the fourth stereo pair of the analog audio stream.
   keAudioIOChannelLast                         // End of list indicator.
};

//
// Summary:
//    Specifies the audio paths available to the output.
//
enum EMvAudioPath
{
   keAudioPathInvalid   = 0x000, // Invalid value.
   keAudioPathAnalog    = 0x001, // Specifies that the audio comes from the analog audio chip.
   keAudioPathPlayback0 = 0x002, // Specifies that the audio comes from the playback channel 0 of the M.Link.
   keAudioPathPlayback1 = 0x004, // Specifies that the audio comes from the playback channel 1 of the M.Link.
   keAudioPathPlayback2 = 0x008, // Specifies that the audio comes from the playback channel 2 of the M.Link.
   keAudioPathPlayback3 = 0x010, // Specifies that the audio comes from the playback channel 3 of the M.Link.
   keAudioPathPlayback4 = 0x020, // Specifies that the audio comes from the playback channel 4 of the M.Link.
   keAudioPathPlayback5 = 0x040, // Specifies that the audio comes from the playback channel 5 of the M.Link.
   keAudioPathPlayback6 = 0x080, // Specifies that the audio comes from the playback channel 6 of the M.Link.
   keAudioPathPlayback7 = 0x100, // Specifies that the audio comes from the playback channel 7 of the M.Link.
   keAudioPathLast               // End of list indicator.
};

//
// Summary:
//    Specifies the audio sampling rate in samples per second.
//
enum EMvAudioSamplingRate
{
   keAudioSamplingRateInvalid,   // Invalid value.
   keAudioSamplingRate48Khz,     // Specifies the 48,000 samples per seconds sampling rate.
   keAudioSamplingRate96Khz,     // Specifies the 96,000 samples per seconds sampling rate.
   keAudioSamplingRateLast       // End of list indicator.
};

//
// Summary:
//    Indicates the audio signal type.
//
enum EMvAudioSignal
{
   keAudioSignalInvalid,   // Invalid value.
   keAudioSignalXLR600ohm, // Indicates an XLR audio signal at 600 ohm of impedance.
   keAudioSignalXLRHiZ,    // Indicates an XLR audio signal at high impedance.
   keAudioSignalLast       // End of list indicator.
};

//
// Summary:
//    Specifies the type of background processing to perform.
//
enum EMvBackgroundHandling
{
   keMvBackgroundHandlingInvalid = 0x00000000,     // Invalid value.
   keMvBackgroundHandlingWait,                     // Waits for the input and the background to be ready before 
                                                      // rendering the effect. The user application copies 
                                                      // the background data to the output surface before compositing.
   keMvBackgroundHandlingWaitAndCopy,              // Waits for the input and the background to be
                                                      // ready before rendering the effect. While compositing, 
                                                      // the background is copied to the output surface.
   keMvBackgroundHandlingColor,                    // Clears the output surface to the specified color.
   keMvBackgroundHandlingLast,                     // End of list indicator.
   keMvBackgroundHandlingForceDWord = 0x7FFFFFFF   // Forces the enumerated values to 32 bits.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvBackgroundHandling
//
#define MV_BACKGROUND_HANDLING_ENUM_TO_STRING(eMvBgHandling) \
   ((eMvBgHandling == keMvBackgroundHandlingInvalid)    ? ("Invalid") : \
   (eMvBgHandling == keMvBackgroundHandlingWait)        ? ("Wait") : \
   (eMvBgHandling == keMvBackgroundHandlingWaitAndCopy) ? ("Wait and copy") : \
   (eMvBgHandling == keMvBackgroundHandlingColor)       ? ("Color") : \
   ("???"))

//
// Summary:
//    Determines the audio source to capture.
//
enum EMvCaptureAudioSource
{
   keCaptureAudioSourceInvalid            = 0x00000,                                // Invalid value.
   keCaptureAudioSourceAnalog             = 0x00001,                                // Specifies that the capture source is analog audio.
   keCaptureAudioSourceEmbeddedChannelA   = 0x00002,                                // Specifies that the capture source is the embedded channel A.
   keCaptureAudioSourceEmbeddedChannelB   = 0x00004,                                // Specifies that the capture source is the embedded channel B.
   keCaptureAudioSourceEmbeddedChannelC   = 0x00008,                                // Specifies that the capture source is the embedded channel C.
   keCaptureAudioSourceEmbeddedChannelD   = 0x00010,                                // Specifies that the capture source is the embedded channel D.
   keCaptureAudioSourceEmbeddedChannelE   = 0x00020,                                // Specifies that the capture source is the embedded channel E.
   keCaptureAudioSourceEmbeddedChannelF   = 0x00040,                                // Specifies that the capture source is the embedded channel F.
   keCaptureAudioSourceEmbeddedChannelG   = 0x00080,                                // Specifies that the capture source is the embedded channel G.
   keCaptureAudioSourceEmbeddedChannelH   = 0x00100,                                // Specifies that the capture source is the embedded channel H.
   keCaptureAudioSourceAesEbuChannelA     = 0x00200,                                // Specifies that the capture source is the AES/EBU channel A.
   keCaptureAudioSourceAesEbuChannelB     = 0x00400,                                // Specifies that the capture source is the AES/EBU channel B.
   keCaptureAudioSourceAesEbuChannelC     = 0x00800,                                // Specifies that the capture source is the AES/EBU channel C.
   keCaptureAudioSourceAesEbuChannelD     = 0x01000,                                // Specifies that the capture source is the AES/EBU channel D.
   keCaptureAudioSourceAesEbuChannelE     = 0x02000,                                // Specifies that the capture source is the AES/EBU channel E.
   keCaptureAudioSourceAesEbuChannelF     = 0x04000,                                // Specifies that the capture source is the AES/EBU channel F.
   keCaptureAudioSourceAesEbuChannelG     = 0x08000,                                // Specifies that the capture source is the AES/EBU channel G.
   keCaptureAudioSourceAesEbuChannelH     = 0x10000,                                // Specifies that the capture source is the AES/EBU channel H.
   keCaptureAudioSourceEmbeddedStreamA    = keCaptureAudioSourceEmbeddedChannelA,  // Same as keCaptureAudioSourceEmbeddedChannelA.
   keCaptureAudioSourceEmbeddedStreamB    = keCaptureAudioSourceEmbeddedChannelB,  // Same as keCaptureAudioSourceEmbeddedChannelB.
   keCaptureAudioSourceEmbeddedStreamC    = keCaptureAudioSourceEmbeddedChannelC,  // Same as keCaptureAudioSourceEmbeddedChannelC.
   keCaptureAudioSourceEmbeddedStreamD    = keCaptureAudioSourceEmbeddedChannelD,  // Same as keCaptureAudioSourceEmbeddedChannelD.
   keCaptureAudioSourceMicrophone         = 0x20000,                                // Specifies that the capture source is microphone.
   keCaptureAudioSourceHDMI               = 0x40000,                                // Specifies that the capture source is the HDMI.
   keAudioCaptureSourceLast               = 0xfffff                                                        // End of list indicator.
};

//
// Summary:
//    Specifies the capture synchronization master. This determines what channel the capture engine uses
//    to synchronize itself.
//
enum EMvCaptureSyncMaster
{
   keCaptureSyncMasterInvalid          = 0x00000, // Invalid value.
   keCaptureSyncMasterSdiChannelA      = 0x00001, // Specifies that the synchronization master is the
                                                   // SDI channel A. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelB      = 0x00002, // Specifies that the synchronization master is the
                                                   // SDI channel B. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterAesEbuChannelA   = 0x00004, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel A. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelB   = 0x00008, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel B. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelC   = 0x00010, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel C. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelD   = 0x00020, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel D. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelE   = 0x00040, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel E. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelF   = 0x00080, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel F. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelG   = 0x00100, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel G. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterAesEbuChannelH   = 0x00200, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // AES/EBU channel H. However, if the audio device  
                                                   // is not synchronized with the video device, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterGenlock          = 0x00400, // Not implemented. 
                                                   // Specifies that the synchronization master is the
                                                   // genlock. However, if the associated video device 
                                                   // is not synchronized with the genlock source, the  
                                                   // capture will be asynchronous.
   keCaptureSyncMasterSdiChannelC      = 0x00800, // Specifies that the synchronization master is the
                                                   // SDI channel C. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelD      = 0x01000, // Specifies that the synchronization master is the
                                                   // SDI channel D. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelE      = 0x02000, // Specifies that the synchronization master is the
                                                   // SDI channel E. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelF      = 0x04000, // Specifies that the synchronization master is the
                                                   // SDI channel F. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelG      = 0x08000, // Specifies that the synchronization master is the
                                                   // SDI channel G. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterSdiChannelH      = 0x10000, // Specifies that the synchronization master is the
                                                   // SDI channel H. This produces A/V synchronic
                                                   // capture.
   keCaptureSyncMasterLast = 18                 // End of list indicator.
};

//
// Summary:
//    Specifies an AES/EBU channel that provides the audio clock.
//
enum EMvClockMasterSource
{
   keClockMasterSourceInvalid,         // Invalid value.
   keClockMasterSourceAesEbuChannelA,  // Specifies that the audio clock is extracted from AES/EBU channel A.
   keClockMasterSourceAesEbuChannelB,  // Specifies that the audio clock is extracted from AES/EBU channel B.
   keClockMasterSourceAesEbuChannelC,  // Specifies that the audio clock is extracted from AES/EBU channel C.
   keClockMasterSourceAesEbuChannelD,  // Specifies that the audio clock is extracted from AES/EBU channel D.
   keClockMasterSourceLast             // End of list indicator.
};

//
// Summary:
//    Enumerates the available colors.
//
enum EMvColor
{
   keMvColorInvalid                = 0x00000000,   // Invalid value.
   keMvColorBlack                  = 0x00000001,   // Indicates that the color is black with a Y component of 16.
   keMvColorSuperBlack             = 0x00000002,   // Indicates that the color is black with a Y component of 0.
   keMvColorWhite                  = 0x00000003,   // Indicates that the color is white with a Y component of 235.
   keMvColorRed                    = 0x00000004,   // Indicates that the color is red.
   keMvColorGreen                  = 0x00000005,   // Indicates that the color is green.
   keMvColorBlue                   = 0x00000006,   // Indicates that the color is blue. 
   keMvColorLast                   = 0x00000007,   // End of list indicator.
   keMvColorForceDWord             = 0x7FFFFFFF    // Forces the enumerated values to 32 bits.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvColor
//
#define MV_COLOR_ENUM_TO_STRING(eMvColor) \
   ((eMvColor == keGenlockStateInvalid)  ? ("Invalid") : \
   (eMvColor == keMvColorBlack)          ? ("Black") : \
   (eMvColor == keMvColorSuperBlack)     ? ("SuperBlack") : \
   (eMvColor == keMvColorWhite)          ? ("White") : \
   (eMvColor == keMvColorRed)            ? ("Red") : \
   (eMvColor == keMvColorGreen)          ? ("Green") : \
   (eMvColor == keMvColorBlue)           ? ("Blue") : \
   ("???"))

//
// Summary:
//    Used to determine the range of colors allowed for a certain task.
//
enum EMvColorRange
{
   keMvColorRangeInvalid,     // Invalid value.
   keMvColorRangeRgbGraphic,  // Color values range from 0 to 255.
   keMvColorRangeRgbVideo,    // Color values range from 16 to 235.
   keMvColorRangeLast         // End of list indicator.
};

//
// Summary:
//    Used to determine the color components to use for retrieving information, 
//    or the color components that are affected by a function.   
//
enum EMvColorSelect
{
   keMvColorSelectInvalid  = 0x00,  // Invalid value
   keMvColorSelectRed      = 0x01,  // Only the red color component will be considered in the request.
   keMvColorSelectGreen    = 0x02,  // Only the green color component will be considered in the request.
   keMvColorSelectBlue     = 0x04,  // Only the blue color component will be considered in the request.
   keMvColorSelectAll      = 0x07,  // All three color components will be considered in the request.
   keMvColorSelectLast              // End of list indicator.
};

//
// Summary:
//    Describes which copy engine will be used for a copy operation.
//
enum EMvCopyEngineID
{
   keMvCopyEngineID_Invalid         = 0x00000000,  // Invalid value.
   keMvCopyEngineID_CPU             = 0x00000001,  // Software-optimized buffer engine (host CPU).
   keMvCopyEngineID_FXDMA           = 0x00000002,  // DMA hardware device on the X.effects card.
   keMvCopyEngineID_GraphicEngine   = 0x00000003,  // Graphics engine on the X.effects card.
   keMvCopyEngineID_IODMA           = 0x00000004,  // DMA hardware device on the X.io card.
   keMvCopyEngineID_LQScaler        = 0x00000005,  // Onboard scaler on the X.io card.
   keMvCopyEngineID_GraphicEngineDX = 0x00000006,  // Graphics engine on the GPU FX board.
   keMvCopyEngineID_Last            = 0x00000007,  // End of list indicator.
   keMvCopyEngineID_ForceDWord      = 0x7FFFFFFF   // Forces the enumerated values to 32 bits.

};

//
// Summary:
//    Determines which digital audio parameter to control.
//
enum EMvDigitalAudioParameter
{
   keDigitalAudioInvalid,           // Invalid value.
   keDigitalAudioClockMaster,       // Selects the audio master time base. Uses a parameter of
                                    // type EMvClockMasterSource.
   keDigitalAudioSamplingRate,      // Controls the digital audio sampling rate. Uses a parameter
                                    // of type EMvAudioSamplingRate.
   keDigitalAudioCaptureDataType,   // Selects the audio data type for the specified capture channel.
                                    //  Uses a parameter of type SMvAudioCaptureType.
   keDigitalAudioPlaybackDataType,  // Selects the audio data type for the specified playback channel. 
                                    // Uses a parameter of type SMvAudioPlaybackType.
   keDigitalAudioCapturePath,       // Selects the AES/EBU audio pairs to be captured. 
                                    // Uses a parameter of type SMvDigitalAudioCapturePath. This parameter 
                                    // is supported for Matrox X.mio2 and DSX LE3 (not supported on the X.RIO module for X.mio2).
   KeDigitalAudioAlignmentOnSwitchLine,  // Change the audio position from switching line to line 1
   keDigitalAudioLast               // End of list indicator.
};

//
// Summary:
//    Describes the possible status codes that can be returned during the initialization of a DVI output.
//
enum EMvDviStatus
{
   keDviStatusUninitialized         = 0x00,  // The DVI output has not been initialized yet.
   keDviStatusInitializationSuccess = 0x01,  // The DVI output has been successfully powered on. 
                                                // Everything should be up and running.
   keDviStatusUnsupportedFeature    = 0x80,  // This card doesn't have the DVI output feature
                                                // installed.
   keDviStatusNoMonitorConnected    = 0x81,  // There is no monitor connected at the DVI output. 
                                                // DVI will not be powered on.
   keDviStatusMonitorDisconnected   = 0x82,  // The monitor has been disconnected. DVI output will
                                                // be shut down.
   keDviStatusIncompatibleMonitor   = 0x83,  // The monitor connected to the DVI output of the board
                                                // cannot output the signal received.
   keDviStatusEDIDRetrievalError    = 0x84,  // An error occurred while retrieving the EDID content
                                                // from the monitor
   keDviStatusEDIDVersionNotSupport = 0x85,  // The version of the EDID structure contained in the
                                                // monitor in incompatible with this software
   keDviStatusEDIDChecksumError     = 0x86,  // The content of the EDID structure is possibly 
                                                // corrupted.
   keDviStatusEDIDInvalidContent    = 0x87,  // The EDID structure retrieved from the monitor
                                                // contains invalid information.
   keDviStatusEDIDMissingInfo       = 0x88,  // Some information requested by the driver could not be
                                                // found in the EDID structure. DVI output will not
                                                // be powered on.
   keDviStatusDviCircuitryProblem   = 0x89,  // There is a problem with the DVI circuitry
                                                // (possibly the clock doesn't lock). DVI output 
                                                // will be shut down.
   keDviStatusResolutionTooHigh     = 0x8A   // The current resolution of the DVI output is too 
                                                // high for the monitor. DVI output will be shut down.
};

//
// Summary:
//    Describes the channel's embedded audio type.
//
enum EMvEAChannelStatusInfo
{
   keEAChannelStatusInfoInvalid   = 0x00,   // Invalid value.
   keEAChannelStatusInfoLinearPCM,          // The embedded audio is linear PCM samples.
   keEAChannelStatusInfoOtherThanLinearPCM, // The embedded audio is other than linear PCM samples.
   keEAChannelStatusInfoLast                // End of list indicator.
};

//
// Summary:
//    Specifies the embedded audio group.
//
enum EMvEmbeddedAudioGroup
{
   keEmbeddedAudioGroupInvalid   = 0x00,  // Invalid value.
   keEmbeddedAudioGroup1         = 0x01,  // Specifies the first stereo embedded audio group.
   keEmbeddedAudioGroup2         = 0x02,  // Specifies the second stereo embedded audio group.
   keEmbeddedAudioGroup3         = 0x04,  // Specifies the third stereo embedded audio group.
   keEmbeddedAudioGroup4         = 0x08,  // Specifies the fourth stereo embedded audio group.
   keEmbeddedAudioGroupLast               // End of list indicator.
};

//
// Summary:
//    Determines the path in which an embedded audio stream can pass.
//
enum EMvEmbeddedAudioIOChannel
{
   keEmbeddedAudioIOChannelInvalid  = 0x00,  // Invalid value.
   keEmbeddedAudioIOChannelA        = 0x01,  // Specifies the first stereo embedded audio channel.
   keEmbeddedAudioIOChannelB        = 0x02,  // Specifies the second stereo embedded audio channel.
   keEmbeddedAudioIOChannelC        = 0x04,  // Specifies the third stereo embedded audio channel.
   keEmbeddedAudioIOChannelD        = 0x08,  // Specifies the fourth stereo embedded audio channel.
   keEmbeddedAudioIOChannelE        = 0x10,  // Specifies the fifth stereo embedded audio channel.
   keEmbeddedAudioIOChannelF        = 0x20,  // Specifies the sixth stereo embedded audio channel.
   keEmbeddedAudioIOChannelG        = 0x40,  // Specifies the seventh stereo embedded audio channel.
   keEmbeddedAudioIOChannelH        = 0x80,  // Specifies the eighth stereo embedded audio channel.
   keEmbeddedAudioIOChannelLast              // End of list indicator.
};

//
// Summary:
//    Determines which embedded audio output parameters to control.
//
enum EMvEmbeddedAudioOutputParameter
{
   keEmbeddedAudioOutputInvalid,          // Invalid value.
   keEmbeddedAudioOutputPath,             // Routes the SDI audio pairs from the breakout box to an embedded SDI channel. Uses a 
                                             // parameter of type EMvAudioPath.
   keEmbeddedAudioOutputFormat,           // Specifies the number of bits used for SDI audio data. Uses a 
                                             // parameter of type EMvAudioBitsPerSample.
   keEmbeddedAudioOutputInsertionControl, // Sets insertion of audio into the selected SDI video output channel. Uses a 
                                             // parameter of type EMvOnOff.
   keEmbeddedAudioOutputGeneralInsertion, // Sets insertion of audio into all SDI video output channels simultaneously. 
                                             // Uses a parameter of type EMvOnOff.
   keEmbeddedAudioOutputSdDbnControl,     // Controls (set to 1 to activate or 0 to deactivate) the 
                                             // embedded audio Data Block Number (DBN) in Standard 
                                             // Definition (SD) mode. This control has no effect in 
                                             // High Definition (HD) mode because DBN is always 
                                             // activated in HD. Uses a parameter of type EMvOnOff.
											 // Some equipment (usually newer equipment 
											 // with HD/SD support) will not decode audio properly unless 
											 // DBN in audio packets is activated and some equipment 
											 // (usually older equipment) will not work properly, to the 
											 // extent that the video may be corrupted, if DBN in audio data 
											 // packets is activated.  
   keEmbeddedAudioOutputLast              // End of list indicator.
};

//
// Summary:
//    Specifies the embedded audio stereo pair.
//
enum EMvEmbeddedAudioPair
{
   keEmbeddedAudioPairInvalid,   // Invalid value.
   keEmbeddedAudioPair1,         // Specifies the first stereo embedded audio pair.
   keEmbeddedAudioPair2,         // Specifies the second stereo embedded audio pair.
   keEmbeddedAudioPairLast       // End of list indicator.
};

//
// Summary:
//    Describes the status of the fan.
//
enum EMvFanStatus
{
   keFanInvalid,  // Invalid value.
   keFanOk,       // Specifies that the fan is working correctly.
   keFanStopped,  // Specifies that the fan has stopped.
   keFanLast      // End of list indicator.
};

//
// Summary:
//    Describes the memory status of the X.effects card.
//
enum EMvMemStatus
{
   keMemInvalid,     // Invalid value.
   keMemOk,          // Specifies that the memory is working correctly.
   keMemTestFailed,  // Specifies that the memory failed a validation test.
   keMemLast         // End of list indicator.
};

//
// Summary:
//    Specifies the possible general hardware statuses.
//
enum EMvGeneralHardwareStatus
{
   keGeneralHardwareInvalid         = 0x0000,   // Invalid value.
   keGeneralHardwareOk              = 0x0001,   // Specifies that the hardware is working correctly.
   keGeneralHardwarePCIBusError     = 0x0002,   // Specifies that an error was encountered on the PCI bus.
                                                   // This is a critical error that could have corrupted 
                                                   // transfer(s).
   keGeneralHardwareSRIBusError     = 0x0004,   // Specifies that an error was encountered on the SRI bus.
                                                   // This is a critical error that could have corrupted 
                                                   // transfer(s).
   keGeneralHardwareUnsupportedFpga = 0x0008,   // Specifies that the current firmware of the card is not 
                                                   // supported by the installed driver set.
   keGeneralHardwareInvalidModel    = 0x0010,   // Specifies that the current detected hardware is not 
                                                   // valid and could not be supported by the driver set.
   keGeneralHardwareFPGABridgeError = 0x0020,   // Specifies that an error was encountered on the internal bridge
                                                   // This is a critical error that could generate corrupted 
                                                   // streams
   keGeneralHardwareModule1Error    = 0x0040,   // Specifies that an error was encountered on Module1.
                                                   // This is a critical error that could have corrupted 
                                                   // transfer(s).
   keGeneralHardwareModule2Error    = 0x0080,   // Specifies that an error was encountered on Module1.
                                                   // This is a critical error that could have corrupted 
                                                   // transfer(s).
   keGeneralHardwareLast                        // End of list indicator.
};

//
// Summary:
//    Determines all the parameters that can be controlled on the genlock circuit of the card(s).
//
enum EMvGenlockParameter
{
   keGenlockParamInvalid,              // Invalid value.
   keGenlockHorizontalDelay,           // Controls the horizontal delay on the genlock circuit.
                                          // Uses a parameter of type long.
   keGenlockVerticalDelay,             // Controls the vertical delay on the genlock circuit. Uses 
                                          // a parameter of type long.
   keGenlockReferenceTermination,      // Connects or disconnects the analog Reference In termination. Uses a 
                                          // parameter of type EMvOnOff
   keGenlockFlywheelEnable,            // Specifies whether or not to activate the genlock flywheel. See product 
                                          // documentation for more information on the genlock 
                                          // flywheel. Uses a parameter of type EMvOnOff.
   keGenlockFlywheelMaxUnlockTime,     // Specifies the maximum unlock time for the genlock flywheel (number of vsyncs 
                                          // during which the flywheel will keep the last known input frequency). See 
                                          // product documentation for more information on the 
                                          // genlock flywheel. Uses a parameter 
                                          // of type double.
   keGenlockFlywheelMaxRecoveryTime,   // Specifies the maximum recovery time (in vsyncs) for the genlock flywheel. See 
                                          // product documentation for more information on the 
                                          // genlock flywheel. Uses a 
                                          // parameter of type double.
   keGenlockOscillatorCalibrationOffset, // Controls the genlock oscillator calibration offset. When in internal genlock mode,
                                          // enables manual genlock clock frequency control. 
                                          // Uses a parameter of type long.
 
   keGenlockParamLast                  // End of list indicator.
};

//
// Summary:
// 	This macro is used to get the string of the enum value eMvGenLockSource.
//
#define MV_GENLOCK_SOURCE_ENUM_TO_STRING(eMvGenLockSource) \
	((eMvGenLockSource == keGenlockSourceInvalid) ? ("Invalid") : \
	(eMvGenLockSource == keGenlockSourceInternal) ? ("Internal") : \
	(eMvGenLockSource == keGenlockSourceBlackBurst) ? ("Blackburst") : \
	(eMvGenLockSource == keGenlockSourceSDIVideo) ? ("SDI") : \
	(eMvGenLockSource == keGenlockSourceBlackBurstPoorQuality) ? ("Blackburst poor quality") : \
	("???"))
#define MV_MXO_GENLOCK_SOURCE_ENUM_TO_STRING MV_GENLOCK_SOURCE_ENUM_TO_STRING

//
// Summary:
//    Describes the state of the genlock.
// Note:
//    For more information about the genlock states, see the <i>Matrox DSX.sdk User Guide</i>.
//
enum EMvGenlockState
{
   keGenlockStateInvalid,     // Invalid value.
   keGenlockStateLocked,      // Indicates that the genlock circuit is locked. 
   keGenlockStateUnlocked,    // Indicates that the genlock circuit is unlocked. 
   keGenlockStateFreeRunning, // Indicates that the genlock circuit is free running. 
   keGenlockStateRecovering,  // Indicates that the genlock circuit is recovering. 
   keGenlockStateRelocking,   // Indicates that the genlock circuit is relocking. 
   keGenlockStateLast         // End of list indicator.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvGenlockState.
//
#define MV_GENLOCK_STATE_ENUM_TO_STRING(eMvGenLockState) \
	((eMvGenLockState == keGenlockStateInvalid) ? ("Invalid") : \
	(eMvGenLockState == keGenlockStateLocked) ? ("Locked") : \
	(eMvGenLockState == keGenlockStateUnlocked) ? ("Unlocked") : \
	(eMvGenLockState == keGenlockStateFreeRunning) ? ("Free running") : \
	(eMvGenLockState == keGenlockStateRecovering) ? ("Recovering") : \
	(eMvGenLockState == keGenlockStateRelocking) ? ("Relocking") : \
	("???"))

//
// Summary:
//    Enumerates the different hardware series types.
//
enum EMvHardwareSerie
{
   kEMvHardwareSerieInvalid,        // Invalid value.
   kEMvHardwareSerieDSX1000,        // Indicates that DS.X1000 hardware is present. 
   kEMvHardwareSerieDSX1500,        // Indicates that DS.X1500 hardware is present.
   kEMvHardwareSerieDSX2000,        // Indicates that DS.X2000 hardware is present.
   kEMvHardwareSerieDSX3000,        // Indicates that DS.X3000 hardware is present.
   kEMvHardwareSerieDSXmio5000,     // Indicates that DS.XMIO5000 hardware is present.
   kEMvHardwareSerieDSXmio6000,     // Indicates that DS.XMIO6000 hardware is present.
   kEMvHardwareSerieDSXmio7000,     // Indicates that DS.XMIO7000 hardware is present.
   kEMvHardwareSerieDSXmio8000,     // Indicates that DS.XMIO8000 hardware is present.
   kEMvHardwareSerieDSXmio9000,     // Indicates that DS.XMIO9000 hardware is present.
   kEMvHardwareSerieReserved1,      // Reserved for legacy support.
   kEMvHardwareSerieReserved2,      // Reserved for legacy support.
   kEMvHardwareSerieAxioLE,         // Indicates that Axio LE hardware is present.
   kEMvHardwareSerieDSXLE100,       // Indicates that DSX LE100 hardware is present.
   kEMvHardwareSerieDSXLE110,       // Indicates that DSX LE110 hardware is present.
   kEMvHardwareSerieDSXLE200,       // Indicates that DSX LE200 hardware is present.
   kEMvHardwareSerieDSXLE300,       // Indicates that DSX LE300 hardware is present.
   kEMvHardwareSerieDSXLE400,       // Indicates that DSX LE300 hardware is present.
   kEMvHardwareSerieDSXLE500,       // Indicates that DSX LE500 hardware is present.
   kEMvHardwareSerieRTX2,           // Indicates that RT.X2 hardware is present.
   kEMvHardwareSerieDSXopen100,     // Indicates that X.open100 hardware is present.
   kEMvHardwareSerieDSXopen150,     // Indicates that X.open150 hardware is present.
   kEMvHardwareSerieDSXopen200,     // Indicates that X.open200 hardware is present.
   kEMvHardwareSerieDSXopen250,     // Indicates that X.open250 hardware is present.
   kEMvHardwareSerieDSXopen300,     // Indicates that X.open300 hardware is present.
   kEMvHardwareSerieDSXopen350,     // Indicates that X.open350 hardware is present.
   kEMvHardwareSerieDSXopen400,     // Indicates that X.open400 hardware is present.
   kEMvHardwareSerieDSXLE300C,      // Indicates that DSX LE 300/C hardware is present.
   kEMvHardwareSerieDSXLECG,        // Indicates that DSX LE/CG hardware is present.
   kEMvHardwareSerieDSXSD300,       // Indicates that DSX.SD 300 hardware is present.
   kEMvHardwareSerieMXO,            // Indicates that MXO hardware is present.
   kEMvHardwareSerieCNVTDVI,        // Indicates that Convert DVI hardware is present.
   kEMvHardwareSerieCNVTDVIPLUS,    // Indicates that Convert DVI Plus hardware is present.
   kEMvHardwareSerieReserved5,      // Reserved for future use.
   kEMvHardwareSerieDSXSD100,       // Indicates that DSX.SD 100 hardware is present.
   kEMvHardwareSerieDSXmio2_5000,   // Indicates that DS.XMIO2 5000 hardware is present.
   kEMvHardwareSerieDSXmio2_6000,   // Indicates that DS.XMIO2 6000 hardware is present.
   kEMvHardwareSerieDSXmio2_8000,   // Indicates that DS.XMIO2 8000 hardware is present.
   kEMvHardwareSerieReserved6,      // Reserved for future use.
   kEMvHardwareSerieRTX2LE,         // Indicates that RT.X2 LE hardware is present.
   kEMvHardwareSerieReserved7,      // Reserved for future use.
   kEMvHardwareSerieDSXAVCio,       // Indicates that DSX.AVCio hardware is present.
   kEMvHardwareSerieDSXLE2CG,       // Indicates that DSX LE/CG hardware is present.
   kEMvHardwareSerieMXO2,           // Indicates that MXO2 hardware is present.
   kEMvHardwareSerieMXO2Mini,       // Indicates that MXO2Mini hardware is present.
   kEMvHardwareSerieMAX,            // Indicates that MAX hardware is present.
   kEMvHardwareSerieDSXLE2CG_250,   // Indicates that DSX LE2/CG/250 hardware is present.
   kEMvHardwareSerieDSXmio2_8500,   // Indicates that DS.XMIO2 8500 hardware is present.
   kEMvHardwareSerieRIOModule_1000, // Indicates that DS.XMIO2 RIO Module 1000 hardware is present.
   kEMvHardwareSerieRIOModule_5000, // Indicates that DS.XMIO2 RIO Module 5000 hardware is present.
   kEMvHardwareSerieRIOModule_6000, // Indicates that DS.XMIO2 RIO Module 6000 hardware is present.
   kEMvHardwareSerieRIOModule_8000, // Indicates that DS.XMIO2 RIO Module 8000 hardware is present.
   kEMvHardwareSerieRIOModule_8500, // Indicates that DS.XMIO2 RIO Module 8500 hardware is present.
   kEMvHardwareSerieX264,           // Indicates that X264 hardware is present.
   kEMvHardwareSerieX264_1000,      // Indicates that X264/1000 hardware is present.
   kEMvHardwareSerieMXO2RU,         // Indicates that MXO2-RU hardware is present.
   kEMvHardwareSerieMXO2LE,         // Indicates that MXO2-LE hardware is present.
   kEMvHardwareSerieMojito,         // Indicates that MXO2-CARD hardware is present.
   kEMvHardwareSerieX264io,         // Indicates that X264io hardware is present.
   kEMvHardwareSerieX264io_500,     // Indicates that X264io 500 hardware is present.
   kEMvHardwareSerieMXO2LEPro,      // Indicates that MXO2-LE PRO hardware is present.   
   kEMvHardwareSerieMXO2LE_100,     // Indicates that MXO2-LE/100 hardware is present.   
   kEMvHardwareSerieMojito_100,     // Indicates that Mojito/100 (MXO2-CARD/100) hardware is present.
   kEMvHardwareSerieX264iASIo,      // Indicates that X.264io ASI hardware is present.
   kEMvHardwareSerieDSXmio2plus5000,// Indicates that DS.XMIO2 plus 5000 hardware is present.
   kEMvHardwareSerieMojito_200,     // Indicates that Mojito/200 (MXO2-CARD/200) hardware is present.
   kEMvHardwareSerieMXO2LE_200,     // Indicates that MXO2-LE/200 hardware is present.   
   kEMvHardwareSerieDSXmio2plus6000,// Indicates that DS.XMIO2 plus 6000 hardware is present.
   kEMvHardwareSerieDSXmio2plus8000,// Indicates that DS.XMIO2 plus 8000 hardware is present.
   kEMvHardwareSerieDSXmio2plus8500,// Indicates that DS.XMIO2 plus 8500 hardware is present.
   kEMvHardwareSerieRIOModule_8100, // Indicates that DS.XMIO2 RIO Module 8100 hardware is present.
   kEMvHardwareSerieRIOModule_8600, // Indicates that DS.XMIO2 RIO Module 8600 hardware is present.
   kEMvHardwareSerieDSXmio2_8100,   // Indicates that DS.XMIO2 8100 hardware is present.
   kEMvHardwareSerieDSXmio2_8600,   // Indicates that DS.XMIO2 8600 hardware is present.
   kEMvHardwareSerieX264_100,     // Indicates that X264_100 hardware is present.
   kEMvHardwareSerieX264_150,     // Indicates that X264_150 hardware is present.
   kEMvHardwareSerieX264_200,     // Indicates that X264_200 hardware is present.
   kEMvHardwareSerieX264_250,     // Indicates that X264_250 hardware is present.
   kEMvHardwareSerieX264_300,     // Indicates that X264_300 hardware is present.
   kEMvHardwareSerieX264_350,     // Indicates that X264_350 hardware is present.
   kEMvHardwareSerieDSXLE3_100,   // Indicates that DSX LE3/100 hardware is present
   kEMvHardwareSerieMojitoA_100,     // Indicates that Mojito/A/100 (Mojito light/100) hardware is present.
   kEMvHardwareSerieMojitoA_200,     // Indicates that Mojito/A/200 (Mojito light/200) hardware is present.
   kEMvHardwareSerieDSXLE3_500,   // Indicates that DSX LE3/500 hardware is present.
   kEMvHardwareSerieX264_400,     // Indicates that X264_400 hardware is present.
   kEMvHardwareSerieDSXLE3_550,   // Indicates that DSX LE3/550 hardware is present.
   kEMvHardwareSerieDSXLE3_200,   // Indicates that DSX LE3/200 hardware is present.
   kEMvHardwareSerieDSXLE3_VS4,   // Indicates that DSX LE3/VS4 hardware is present.
   kEMvHardwareSerieDSXopen050,     // Indicates that X.openUSB/050 hardware is present.
   kEMvHardwareSerieMojito_4K,     // Indicates that Mojito 4K hardware is present.
   kEMvHardwareSerieDSXLE3_110,   // Indicates that DSX LE3/110 hardware is present
   kEMvHardwareSerieDSXmio3,      // Indicates that DS.XMIO3 hardware is present.
   kEMvHardwareSerieDSXLE3_VS4_PRO, //Indicates that VS4 Pro hardware is present.
   kEMvHardwareSerieDSXLE4,      // Indicates that DSXLE4 hardware is present.
   kEMvHardwareSerieMojito2_100,     // Indicates that Mojito2/100 hardware is present.
   kEMvHardwareSerieMojito2_500,     // Indicates that Mojito2/500 hardware is present.
   kEMvHardwareSerieM264,      // Indicates that M264 hardware is present.
   kEMvHardwareSerieDSXCore,      // Indicates that we are using a DSXCore / sw license / seat.
   kEMvHardwareSerieLast            // End of list indicator.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvHardwareSerie.
//
#define MV_HARDWARE_SERIE_ENUM_TO_STRING(eSerie) \
	((eSerie == kEMvHardwareSerieInvalid) ? ("Invalid") : \
   (eSerie == kEMvHardwareSerieDSX1000) ? ("DSX1000") : \
   (eSerie == kEMvHardwareSerieDSX1500) ? ("DSX1500") : \
   (eSerie == kEMvHardwareSerieDSX2000) ? ("DSX2000") : \
   (eSerie == kEMvHardwareSerieDSX3000) ? ("DSX3000") : \
   (eSerie == kEMvHardwareSerieDSXmio5000) ? ("X.mio 5000") : \
   (eSerie == kEMvHardwareSerieDSXmio6000) ? ("X.mio 6000") : \
   (eSerie == kEMvHardwareSerieDSXmio7000) ? ("X.mio 7000") : \
   (eSerie == kEMvHardwareSerieDSXmio8000) ? ("X.mio 8000") : \
   (eSerie == kEMvHardwareSerieDSXmio9000) ? ("X.mio 9000") : \
   (eSerie == kEMvHardwareSerieReserved1) ? ("Reserved1") : \
   (eSerie == kEMvHardwareSerieReserved2) ? ("Reserved2") : \
   (eSerie == kEMvHardwareSerieAxioLE) ? ("AxioLE") : \
   (eSerie == kEMvHardwareSerieDSXLE100) ? ("DSXLE 100") : \
   (eSerie == kEMvHardwareSerieDSXLE110) ? ("DSXLE 110") : \
   (eSerie == kEMvHardwareSerieDSXLE200) ? ("DSXLE 200") : \
   (eSerie == kEMvHardwareSerieDSXLE300) ? ("DSXLE 300") : \
   (eSerie == kEMvHardwareSerieDSXLE400) ? ("DSXLE 400") : \
   (eSerie == kEMvHardwareSerieDSXLE500) ? ("DSXLE 500") : \
   (eSerie == kEMvHardwareSerieRTX2) ? ("") : \
   (eSerie == kEMvHardwareSerieDSXopen100) ? ("X.open 100") : \
   (eSerie == kEMvHardwareSerieDSXopen150) ? ("X.open 150") : \
   (eSerie == kEMvHardwareSerieDSXopen200) ? ("X.open 200") : \
   (eSerie == kEMvHardwareSerieDSXopen250) ? ("X.open 250") : \
   (eSerie == kEMvHardwareSerieDSXopen300) ? ("X.open 300") : \
   (eSerie == kEMvHardwareSerieDSXopen350) ? ("X.open 350") : \
   (eSerie == kEMvHardwareSerieDSXopen400) ? ("X.open 400") : \
   (eSerie == kEMvHardwareSerieDSXLE300C) ? ("DSXLE 300 /C") : \
   (eSerie == kEMvHardwareSerieDSXLECG) ? ("DSXLE CG") : \
   (eSerie == kEMvHardwareSerieDSXSD300) ? ("DSXSD 300") : \
   (eSerie == kEMvHardwareSerieMXO) ? ("MXO") : \
   (eSerie == kEMvHardwareSerieCNVTDVI) ? ("Convert DVI") : \
   (eSerie == kEMvHardwareSerieCNVTDVIPLUS) ? ("Convert DVI+") : \
   (eSerie == kEMvHardwareSerieReserved5) ? ("Reserved5") : \
   (eSerie == kEMvHardwareSerieDSXSD100) ? ("DSXSD 100") : \
   (eSerie == kEMvHardwareSerieDSXmio2_5000) ? ("X.mio2 5000") : \
   (eSerie == kEMvHardwareSerieDSXmio2_6000) ? ("X.mio2 6000") : \
   (eSerie == kEMvHardwareSerieDSXmio2_8000) ? ("X.mio2 8000") : \
   (eSerie == kEMvHardwareSerieReserved6) ? ("Reserved6") : \
   (eSerie == kEMvHardwareSerieRTX2LE) ? ("RTX2LE") : \
   (eSerie == kEMvHardwareSerieReserved7) ? ("Reserved7") : \
   (eSerie == kEMvHardwareSerieDSXAVCio) ? ("AVCio") : \
   (eSerie == kEMvHardwareSerieDSXLE2CG) ? ("DSXLE2 CG") : \
   (eSerie == kEMvHardwareSerieMXO2) ? ("MXO2") : \
   (eSerie == kEMvHardwareSerieMXO2Mini) ? ("MXO2Mini") : \
   (eSerie == kEMvHardwareSerieMAX) ? ("MAX") : \
   (eSerie == kEMvHardwareSerieDSXLE2CG_250) ? ("DSXLE2 CG 250") : \
   (eSerie == kEMvHardwareSerieDSXmio2_8500) ? ("X.mio2 8500") : \
   (eSerie == kEMvHardwareSerieRIOModule_1000) ? ("RIO 1000") : \
   (eSerie == kEMvHardwareSerieRIOModule_5000) ? ("RIO 5000") : \
   (eSerie == kEMvHardwareSerieRIOModule_6000) ? ("RIO 6000") : \
   (eSerie == kEMvHardwareSerieRIOModule_8000) ? ("RIO 8000") : \
   (eSerie == kEMvHardwareSerieRIOModule_8500) ? ("RIO 8500") : \
   (eSerie == kEMvHardwareSerieX264) ? ("X264") : \
   (eSerie == kEMvHardwareSerieX264_1000) ? ("X264 1000") : \
   (eSerie == kEMvHardwareSerieMXO2RU) ? ("MXO2 RU") : \
   (eSerie == kEMvHardwareSerieMXO2LE) ? ("MXO2 LE") : \
   (eSerie == kEMvHardwareSerieMojito) ? ("Mojito") : \
   (eSerie == kEMvHardwareSerieX264io) ? ("X264io") : \
   (eSerie == kEMvHardwareSerieX264io_500) ? ("X264io 500") : \
   (eSerie == kEMvHardwareSerieMXO2LEPro) ? ("MXO2LE Pro") : \
   (eSerie == kEMvHardwareSerieMXO2LE_100) ? ("MXO2LE 100") : \
   (eSerie == kEMvHardwareSerieMojito_100) ? ("Mojito 100") : \
   (eSerie == kEMvHardwareSerieX264iASIo) ? ("X264io ASI") : \
   (eSerie == kEMvHardwareSerieDSXmio2plus5000) ? ("X.mio2+ 5000") : \
   (eSerie == kEMvHardwareSerieMojito_200) ? ("Mojito 200") : \
   (eSerie == kEMvHardwareSerieMXO2LE_200) ? ("MXO2LE 200") : \
   (eSerie == kEMvHardwareSerieDSXmio2plus6000) ? ("X.mio2+ 6000") : \
   (eSerie == kEMvHardwareSerieDSXmio2plus8000) ? ("X.mio2+ 8000") : \
   (eSerie == kEMvHardwareSerieDSXmio2plus8500) ? ("X.mio2+ 8500") : \
   (eSerie == kEMvHardwareSerieRIOModule_8100) ? ("RIO 8100") : \
   (eSerie == kEMvHardwareSerieRIOModule_8600) ? ("RIO 8600") : \
   (eSerie == kEMvHardwareSerieDSXmio2_8100) ? ("X.mio2 8100") : \
   (eSerie == kEMvHardwareSerieDSXmio2_8600) ? ("X.mio2 8600") : \
   (eSerie == kEMvHardwareSerieX264_100) ? ("X264 100") : \
   (eSerie == kEMvHardwareSerieX264_150) ? ("X264 150") : \
   (eSerie == kEMvHardwareSerieX264_200) ? ("X264 200") : \
   (eSerie == kEMvHardwareSerieX264_250) ? ("X264 250") : \
   (eSerie == kEMvHardwareSerieX264_300) ? ("X264 300") : \
   (eSerie == kEMvHardwareSerieX264_350) ? ("X264 350") : \
   (eSerie == kEMvHardwareSerieDSXLE3_100) ? ("DSXLE3 100") : \
   (eSerie == kEMvHardwareSerieMojitoA_100) ? ("MojitoA 100") : \
   (eSerie == kEMvHardwareSerieMojitoA_200) ? ("MojitoA 200") : \
   (eSerie == kEMvHardwareSerieDSXLE3_500) ? ("DSXLE3 500") : \
   (eSerie == kEMvHardwareSerieX264_400) ? ("X264 400") : \
   (eSerie == kEMvHardwareSerieDSXLE3_550) ? ("DSXLE3 550") : \
   (eSerie == kEMvHardwareSerieDSXLE3_200) ? ("DSXLE3 200") : \
   (eSerie == kEMvHardwareSerieDSXLE3_VS4) ? ("VS4") : \
   (eSerie == kEMvHardwareSerieDSXopen050) ? ("X.open 050") : \
   (eSerie == kEMvHardwareSerieDSXmio3) ? ("X.mio3") : \
   (eSerie == kEMvHardwareSerieDSXLE3_VS4_PRO) ? ("VS4 Pro") : \
   (eSerie == kEMvHardwareSerieDSXLE4) ? ("DSXLE4") : \
   (eSerie == kEMvHardwareSerieM264) ? ("M264") : \
   (eSerie == kEMvHardwareSerieDSXCore) ? ("DSXCore") : \
   ("???"))
//
// Summary:
//    Describes all the possible device or hardware information parameters that can be retrieved. The 
//    information parameters supported may vary from device to device.
//
enum EMvInformationParameter
{
   keInformationParameterInvalid,                     // Invalid value.
   keInformationParameterDeviceName,                  // Fills a character array with the English name of the 
                                                         // device. It should not be used to make device 
                                                         // comparisons in the upper software layer because it 
                                                         // can change without notice. The device ID must be 
                                                         // used instead. In order to receive this information,
                                                         // the SMvInformationParameter structure must be used.
   keInformationParameterDeviceSerialNumber,          // Fills a character array with the device's serial number.
                                                         // In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterDeviceRevision,              // Fills a character array with the device's revision number.
                                                         // In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterDeviceOptions,               // Fills a character array with the names of installed 
                                                         // options for the device, if any. In order to receive 
                                                         // this information, the SMvInformationParameter structure
                                                         // must be used.
   keInformationParameterProgrammableDeviceRevision,  // Fills a character array with the device revision number. 
                                                         // In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterOemIdentification,           // Fills a character array with the OEM identification.
                                                         // In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterProductionDate,              // Fills a character array with the production date of the 
                                                         // device. In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterConfigurationEepromRevision, // Fills a character array with the device's EEPROM 
                                                         // revision number. In order to receive this information,
                                                         // the SMvInformationParameter structure must be used.
   keInformationParameterHardwareFlavor,              // Fills the hardware flavor structure that specifies the
                                                         // model of the device. In order to receive this
                                                         // information, the SMvInformationParameter structure
                                                         // must be used.
   keInformationParameterPartNumber,                  // Fills a character array with the part number of the
                                                         // device. In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterPowerStatus,                 // Fills the power status structure that specifies
                                                         // information about the power of the device. In order 
                                                         // to receive this information, the SMvPowerInformation
                                                         // structure must be used.
   keInformationParameterXlinkStatus,                 // Fills the X.link status structure that specifies 
                                                         // information about an X.link breakout box. In order
                                                         // to receive this information, the SMvXlinkStatus
                                                         // structure must be used.
   keInformationParameterFanStatus,                   // Fills the fan status structure that specifies 
                                                         // information about the device's fan. In order to
                                                         // receive this information, the SMvFanStatus structure
                                                         // must be used.
   keInformationParameterHardwareStatus,              // Fills the hardware status structure that specifies
                                                         // general information about the device. In order to 
                                                         // receive this information, the SMvInformationParameter
                                                         // structure must be used.
   keInformationParameterDefaultResolutions,          // Fills the resolution structure that specifies the
                                                         // resolution of the device when the system is started.
                                                         // In order to receive this information, the 
                                                         // SMvResolutionInfo structure must be used.
   keInformationParameterCableID,                     // Returns the cable type of the attached X.link 
                                                         // breakout box. In order to receive this information,
                                                         // the SMvCableID structure must be used.
   keInformationParameterMemoryStatus,                // Returns the device's memory state. In order to
                                                         // receive this information, the SMvMemStatus 
                                                         // structure must be used.
   keInformationParameterMemorySize,                  // Returns the device's memory size in bytes. In 
                                                         // order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterPciBusInfo,                  // Returns the device's PCI bus location. In order to 
                                                         // receive this information, the SMvInformationParameter
                                                         // structure must be used.
   keInformationParameterModuleADeviceName,           // Fills a character array with the English name of the 
                                                         // device installed at module A position. In order to 
                                                         // receive this information, the SMvInformationParameter 
                                                         // structure must be used.
   keInformationParameterModuleBDeviceName,           // Fills a character array with the English name of the 
                                                         // device installed at module B position. In order to 
                                                         // receive this information, the SMvInformationParameter 
                                                         // structure must be used.
   keInformationParameterModuleADeviceSerialNumber,   // Fills a character array with the module A device's serial 
                                                         // number. In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterModuleBDeviceSerialNumber,   // Fills a character array with the module A device's serial 
                                                         // number. In order to receive this information, the 
                                                         // SMvInformationParameter structure must be used.
   keInformationParameterPCICount,                    // Returns a PCI count.

   keInformationParameterSDIVideoCount,               // Returns a SDI Video Connectors count.

   keInformationParameterAesEbuCount,                 // Returns a AesEbu Connectors count.

   keInformationParameterAnalogVideoCount,            // Returns a Analog Video Connectors count.

   keInformationParameterAnalogAudioCount,            // Returns a Analog Audio Connectors count.
   
   keInformationParameterFirmwareVersion,             // Returns the firmware version.

   keInformationParameterProductUpgradesList,         // Returns the List of Product Upgrades.
   
   KeInformationParameterLast                         // End of list indicator.
};

//
// Summary:
//    Specifies which command to perform on an I/O parameter.
//
enum EMvIOCommand
{
   keIOCommandInvalid,     // Invalid value.
   keIOCommandSetDefault,  // Sets the command as the default.
   keIOCommandGetDefault,  // Gets the default command.
   keIOCommandSetCurrent,  // Sets the current command only. This command is overridden by the default one at boot time.
   keIOCommandGetCurrent,  // Gets the current command.
   keIOCommandGetRange,    // Gets the range of a command.
   keIOCommandLast         // End of list indicator.
};

//
// Summary:
//    Specifies the I/O device identification.
//
enum EMvIODeviceID
{
   keIODeviceIDInvalid     = 0x0000,   // Invalid value.
   keIODeviceIDABob        = 0x6045,   // Specifies that the I/O device is an analog breakout box without an SDI module.
   keIODeviceIDABobSDI     = 0x6040,   // Specifies that the I/O device is an analog breakout box with an SDI module.
   keIODeviceIDABobPlus    = 0x6055,   // Specifies that the I/O device is an analog breakout box without an SDI module.
   keIODeviceIDABobSDIPlus = 0x6050,   // Specifies that the I/O device is an analog breakout box with an SDI module.
   keIODeviceIDHDBob       = 0x6080,   // Specifies that the I/O device is an HD breakout box.
   keIODeviceIDXMio        = 0x0001,   // Specifies that the I/O device is an X.mio card.
   keIODeviceIDXLe         = 0x0002,   // Specifies that the I/O device is a DSX LE card.
   keIODeviceIDRTX2        = 0x0003,   // Specifies that the I/O device is an RT.X2 card.
   keIODeviceIDXopen       = 0x0004,   // Specifies that the I/O device is an X.open card.
   keIODeviceIDXSd         = 0x0005,   // Specifies that the I/O device is an DSX SD card.
   keIODeviceIDMXO         = 0x0006,   // Specifies that the I/O device is an MXO card.
   keIODeviceIDUsbDongle   = 0x0007,   // Specifies that the I/O device is an USB Dongle card.
   keIODeviceIDDSXAVCio    = 0x0008,   // Specifies that the I/O device is a DSX.AVCio card.
   keIODeviceIDMXO2        = 0x0009,   // Specifies that the I/O device is a MXO2 card.
   keIODeviceIDMAX         = 0x0010,   // Specifies that the I/O device is a MAX card.
   keIODeviceIDX264io      = 0x0011,   // Specifies that the I/O device is a X.264io card.
   keIODeviceIDXMio2Plus   = 0x0012,   // Specifies that the I/O device is a X.mio2plus card.
   keIODeviceIDXLe3        = 0x0013,   // Specifies that the I/O device is a DSX.LE3 card.
   keIODeviceIDXMio3       = 0x0014    // Specifies that the I/O device is a X.mio3 card.
};

//
// Summary:
//    Specifies the type of input/output event.
//
enum EMvIOEvent
{
   keIOEventInvalid,          // Invalid value.
   keIOEventGenlock,          // Specifies that the event refers to genlock. This event is notified when 
                                 // the genlock is lost or recovered.
   keIOEventVideo,            // Specifies that the event refers to video. This event is notified when the
                                 // video input is lost or recovered.
   keIOEventAudioTimeBase,    // Specifies that the event refers to audio time base. This event is notified
                                 // when the audio time base is lost or recovered.
   keIOEventEmbeddedAudio,    // Specifies that the event refers to embedded audio. This event is notified 
                                 // when there is a change in extraction channel status.
   keIOEventAesEbuAudio,      // Specifies that the event refers to aes/ebu audio. This event is notified
                                 // when the aes/ebu signal is lost or recovered, and/or when there is a change
                                 // in the channel status of the signal.
   keIOEventDVI,              // Specifies that the event refers to the DVI output of the board. This event is
                                 // notified when there is a change of state with the DVI output.
   keIOEventWatchDog,         // Specifies that the event refers to the "watchdog".
   keIOEventWatchDogA = keIOEventWatchDog, // Specifies that the event refers to channel A "watchdog".
   keIOEventWatchDogB,                     // Specifies that the event refers to channel B "watchdog".
   keIOEventWatchDogC,                     // Specifies that the event refers to channel C "watchdog".
   keIOEventWatchDogD,                     // Specifies that the event refers to channel D "watchdog".
   keIOEventWatchDogE,                     // Specifies that the event refers to channel E "watchdog".
   keIOEventWatchDogF,                     // Specifies that the event refers to channel F "watchdog".
   keIOEventWatchDogG,                     // Specifies that the event refers to channel G "watchdog".
   keIOEventWatchDogH,                     // Specifies that the event refers to channel H "watchdog".
   keIOEventDVIInputChannelE, // Specifies that the event refers to DVI module channel E "pulse".
   keIOEventDVIInputChannelF, // Specifies that the event refers to DVI module channel F "pulse".
   keIOEventLast              // End of list indicator.
};

//
// Summary:
//    Specifies the type of input/output information.
//
enum EMvIOInfo
{
   keIOInfoInvalid,        // Invalid value.
   keIOInfoVideo,          // Indicates that the information refers to video.
   keIOInfoGenlock,        // Indicates that the information refers to genlock.
   keIOInfoAudio,          // Indicates that the information refers to audio.
   keIOInfoEmbeddedAudio,  // Indicates that the information refers to embedded audio.
   keIOInfoAudioCapture,   // Indicates that the information refers to audio capture.
   keIOInfoMisc,           // Indicates that the information refers to miscellaneous information.
   keIOInfoLast            // End of list indicator.
};

//
// Summary:
//    Specifies the type of the input/output status.
//
enum EMvIOStatus
{
   keIOStatusInvalid,                        // Invalid value.
   keIOStatusVideo,                          // Specifies that the status refers to the current video 
                                                // stream (see the SMvVideoStatus definition for details).
   keIOStatusGenlock,                        // Specifies that the status refers to the genlock 
                                                // (see the SMvGenlockStatus definition for details).
   keIOStatusEmbeddedAudio,                  // Specifies that the status refers to the embedded audio
                                                // group and pair (see the SMvEmbeddedAudioStatus definition
                                                // for details).
   keIOStatusEmbbededAudioExtractionFormat,  // Specifies that the status refers to the extraction format
                                                // (bits per sample) of the embedded audio.
   keIOStatusAudioTimeBase,                  // Specifies that the status refers to the audio time base
                                                // (see SMvAudioTimeBase definition for details).
   keIOStatusAesEbuAudio,                    // Specifies that the status refers to the aes/ebu audio signal
                                                // (see the SMvAesEbuAudioStatus definition for details).
   keIOStatusAesEbuChannelStatus,            // Specifies that the status refers to the channel status bytes of
                                                // the aes/ebu audio signal (see SMvDigitalAudioChannelStatus
                                                // definition for details).
   keIOStatusDVI,                            // Specifies that the status refers to the DVI output (see the
                                                // SMvDviStatus definition for details).
   keIOStatusWatchdogBypass,                 // Specifies that the status refers to the watchdog bypass.
                                                // Uses a parameter of type EMvOnOff.
   keIOStatusHdmiAudio,                      // Specifies that the status refers to the Hdmi audio
                                                // (see the SMvHdmiAudioStatus definition for details).
   keIOStatusGenlockTermination,

   keIOStatusLast                            // End of list indicator.
};

//
// Summary:
//    Describes the filtering mode.
//
enum EMvFilterMode
{
   keMvFilterModeInvalid           = 0x00000000,      // Invalid filtering mode
   keMvFilterModeNone              = 0x00000001,      // No filtering is performed. The nearest pixel is taken.
   keMvFilterModeNormal            = 0x00000002,      // Default filtering is used. 
   keMvFilterModeLast              = 0x00000003,      // End of list indicator.
   keMvFilterModeForceDWord        = 0x7FFFFFFF       // Force the enumerated values to be 32 bits.
};

//
// Summary:
//    Specifies which identifier to get for a notification.
//
enum EMvNotificationID
{
   keNotificationIDInvalid,         // Invalid value.
   keNotificationIDXlinkStatus,     // Specifies the identifier of the X.link status notification. 
                                       // This notification is set when there is a change in the 
                                       // X.link status.
   keNotificationIDFanStatus,       // Specifies the identifier of the fan status notification. This 
                                       // notification is set when there is a change in the fan status.
   keNotificationIDPowerStatus,     // Specifies the identifier of the power status notification. 
                                       // This notification is set when there is a change in the 
                                       // power status.
   keNotificationIDHardwareStatus,  // Specifies the identifier of the general hardware status 
                                       // notification. This notification is set when there is a 
                                       // change in the general hardware status.
   keNotificationIDCableID,         // Specifies the identifier of the cable identifier notification. 
                                       // This notification is set when the cable identification 
                                       // process has failed.
   keNotificationIDMemStatus,       // Specifies the identifier of the memory notification. This
                                       // notification is set when a problem is detected with the
                                       // on-board memory of the F/X board.
   keNotificationIDPciBusFrequency, // Specifies the identifier of the PCI bus frequency notification.
                                       // This notification is set when the parameters of the PCI slot
                                       // (bus speed, bus width, etc.) are incompatible with the card.
   keNotificationIDLast             // End of list indicator.
};

//
// Summary:
//    Specifies the state of a parameter.
//
enum EMvOnOff
{
   keOff,   // The parameter is disabled.
   keOn     // The parameter is enabled.
};


//
// Summary:
//    Specifies the pixel ratio of a MGF image.
//
enum EMvPixelRatio
{
   keMvPixelRatioInvalid,				// Invalid value.
   keMvPixelRatioSquare,            // The image contains square pixel.
   keMvPixelRatioStandardNtsc,      // The image contains pixels from the 4:3 NTSC standard.
   keMvPixelRatioStandardPal,       // The image contains pixels from the 4:3 PAL standard.
   keMvPixelRatioWideScreenNtsc,    // The image contains pixels from the 16:9 NTSC standard.
   keMvPixelRatioWideScreendPal,    // The image contains pixels from the 16:9 PAL standard.
   keMvPixelRatioLast               // End of list indicator.
};
// This macro is used to get the string of the enum value EMvPixelRatio.
#define MV_PIXEL_RATIO_ENUM_TO_STRING(ePixelRatio) \
   ((ePixelRatio == keMvPixelRatioInvalid)       ? ("Invalid") : \
   (ePixelRatio == keMvPixelRatioSquare)         ? ("Square") : \
   (ePixelRatio == keMvPixelRatioStandardNtsc)   ? ("StandardNtsc") : \
   (ePixelRatio == keMvPixelRatioStandardPal)    ? ("StandardPal") : \
   (ePixelRatio == keMvPixelRatioWideScreenNtsc) ? ("WideScreenNtsc") : \
   (ePixelRatio == keMvPixelRatioWideScreendPal) ? ("WideScreendPal") : \
   (ePixelRatio == keMvPixelRatioLast)           ? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies the power status of a device.
//
enum EMvPowerStatus
{
   kePowerStatusInvalid,         // Invalid value.
   kePowerStatusOk,              // Specifies that the device is receiving power correctly.
   kePowerStatusMissing,         // Specifies that there is in power on the device, or that the power
                                    // connection is not plugged in. 
   kePowerStatusCircuitProblem,  // Specifies that the device is not receiving power. 
   kePowerStatusLast             // End of list indicator.
};

//
// Summary:
//    Used to specify the resolution information that needs to be returned or controlled for
//    a specified video I/O channel.
//
enum EMvResolutionType
{
   keResolutionTypeInvalid,            // Invalid value.        
   keResolutionTypeInput = 0x01,       // Indicates that only the input resolution will be returned
                                          // or controlled for a specified I/O channel.
   keResolutionTypeOutput = 0x02,      // Indicates that only the output resolution will be returned
                                          // or controlled for a specified I/O channel.
   keResolutionTypeInputOutput = 0x03  // Indicated that both the input and output resolutions will be
                                          // returned or controlled for a specified I/O channel.
};

//
// Summary:
//    Specifies the video output still mode.
//
enum EMvStillMode
{
   keStillModeInvalid,  // Invalid value.
   keStillModeField,    // Specifies that the video output uses only one field for interlaced 
                           // resolutions. This mode is invalid for progressive resolutions.
   keStillModeFrame,    // Specifies that the video output uses both fields in interlaced 
                           // resolutions, and uses a frame in progressive resolutions. 
   keStillModeLast      // End of list indicator.
};

//
// Summary:
// This macro is used to get the string of the enum value eMvStillMode.
//
#define MV_STILL_MODE_ENUM_TO_STRING(eMvStillMode) \
	((eMvStillMode == keStillModeInvalid) ? ("Invalid") : \
	(eMvStillMode == keStillModeField) ? ("Field") : \
	(eMvStillMode == keStillModeFrame) ? ("Frame") : \
	(eMvStillMode == keStillModeLast) ? ("Last") : \
	("???"))
#define MV_MXO_STILL_MODE_ENUM_TO_STRING MV_STILL_MODE_ENUM_TO_STRING

//
// Summary:
//    Determines which input parameter to control.
//
enum EMvVideoInputParameter
{
   keVideoInputParamInvalid,     // Invalid value.
   keVideoInputAgc,              // Enables or disables Automatic Gain Control (analog video only). Uses a parameter of type EMvOnOff.
   keVideoInputSharpening,       // Sets luminance peaking (analog video only). Uses a parameter of type double.
   keVideoInputBroadCastSource,  // Specifies whether or not the video source is broadcast quality (analog video only).
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputLumaContrast,     // Sets luma contrast (analog video only). Uses a parameter of type double.
   keVideoInputLumaBrightness,   // Sets luma brightness (analog video only). Uses a parameter of type double.
   keVideoInputChromaGain,       // Sets chroma (saturation) gain (analog video only). Uses a parameter of type double.
   keVideoInputHue,              // Sets hue (analog video only). Uses a parameter of type double.
   keVideoInputAllowSuperBlack,  // Specifies whether or not to clip an input video signal that is below 7.5 IRE.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputAllowSuperWhite,  // Specifies whether or not to clip an input video signal that is above 100 IRE.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputChromaClipping,   // Specifies whether or not to clip over-saturated chroma levels in the active portion of the input video signal.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputSetup,            // Removes the pedestal of an NTSC video signal.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputKeyUpscaleLuma,   // Specifies whether or not to upscale the luminance range of the input key signal from 16-235 to 0-255.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputKeyInvertLuma,    // Specifies whether or not to invert the luminance part of the key signal and the key value.
                                    // Uses a parameter of type EMvOnOff.
   keVideoInputKeyApplyOffset,   // Applies an offset to the luminance values so that the inverted result falls within the 0-255 range.
                                    // The offset can only be applied if the luminance part of the key signal is inverted (keVideoInputKeyInvertLuma = keOn),
                                    // and the luminance range of the key signal is upscaled (keVideoInputKeyUpscaleLuma = keOn).
                                    // Otherwise, the offset will not be applied and the key signal is not valid. Uses a parameter of type EMvOnOff.
   keVideoInputEnable3GLevelB,  // Enables or disables SMPTE 425M (3G) Level B mapping on the input. When the input is 1080p @ 50 fps, 60 or 59.94 fps, 
                                    // "on" enables Level B mapping, and "off" enables Level A mapping. Uses a parameter of type EMvOnOff. This parameter is 
									// supported for Matrox X.mio2 and DSX LE3 (not supported on the optional X.RIO module for X.mio2).
   keVideoInputDVITimingPreset,  // Specifies the DVI input signal timing presets. This enables the differentiation 
                                    // of different camera with same DVI timings. Uses a parameter
                                    // of type EMvVideoInputDVITiming.
   keVideoInputLast              // End of list indicator.
};

//
// Summary:
//    Specifies an active video line width.
//
enum EMvVideoLineWidth
{
   keVideoLineWidthInvalid,   // Invalid value.
   keVideoLineWidth_720,      // Specifies an active video line width according to the ITU-R BT.470
                                 // (CCIR 624 output) specification (720 pixels NTSC/PAL).
   keVideoLineWidth_710_702,  // Specifies an active video line width according to the ITU-R/SMPTE
                                 // (CCIR 601 output) specification (710 pixels NTSC, 702 pixels PAL).
   keVideoLineWidthLast       // End of list indicator.
};

//
// Summary:
//    Determines which output parameters to control.
//
enum EMvVideoOutputParameter
{
   keVideoOutputInvalid                      = 0x00,              // Invalid value.
   keVideoOutputSchphase                     = 0x01,              // Sets subcarrier phase offset. For analog video only. Uses a parameter
                                                                  // of type double.
   keVideoOutputSdiHorizontalDelay           = 0x02,              // Sets the SDI line buffer delay. For digital video only. Uses a parameter 
                                                                  // of type long.
   keVideoOutputAllowSuperBlack              = 0x03,              // Specifies whether or not to clip an output video signal that is below 7.5 IRE. Uses a parameter of type EMvOnOff. 
                                                                  // On Matrox DSX LE2/CG, this parameter can be called for video 
                                                                  // channels A and B (even though the DSX LE2/CG exposes 
                                                                  // only one playback channel) because both of the card's 
                                                                  // output connectors can be programmed independently.
   keVideoOutputAllowSuperWhite              = 0x04,              // Specifies whether or not to clip an output video signal that is above 100 IRE. Uses a parameter of type EMvOnOff.
                                                                  // On Matrox DSX LE2/CG, this parameter 
                                                                  // can be called for video channels A and B (even though the 
                                                                  // DSX LE2/CG exposes only one playback channel) because both 
                                                                  // of the card's output connectors can be programmed independently.
   keVideoOutputComponentYGain               = 0x05,              // Sets the Y (luminance) gain of the component video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputComponentCbGain              = 0x06,              // Sets the Cb (blue minus luminance) gain of the component video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputComponentCrGain              = 0x07,              // Sets the Cr (red minus luminance) gain of the component video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputSVideoYGain                  = 0x08,              // Sets the Y (luminance) gain of the S-Video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputSVideoCGain                  = 0x09,              // Sets the C (chrominance) gain of the S-Video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputCompositeGain                = 0x0a,              // Sets the gain of the composite video output. Uses a 
                                                                  // parameter of type double.
   keVideoOutputSetup                        = 0x0b,              // Removes the pedestal from an NTSC video signal. 
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputType                         = 0x0c,              // Sets the type of analog output (RGB or YUV). Uses a parameter of type 
                                                                  // EMvOutputType.
   keVideoOutputAspectRatioAutoSwitching     = 0x0d,              // Controls the Copy Generation Management System (CGMS) for NTSC video 
                                                                  // or the Wide Screen Signaling (WSS) for PAL video. Uses a parameter of type EMvOnOff.
   keVideoOutputActiveLineWidth              = 0x0e,              // Changes the width of active lines, in pixels, from 720 (NTSC/PAL) to 710 (NTSC) or 702 (PAL). Uses 
                                                                  // a parameter of type EMvVideoLineWidth.
   keVideoOutputAnalogEdgeSharpeningFilter   = 0x0f,              // Applies an edge sharpening filter to analog output video. The filter reduces ringing artifacts that 
                                                                  // appear due to transitions of high amplitude in 
                                                                  // the analog signal. Uses a parameter of type 
                                                                  // EMvOnOff.
   keVideoOutputDigitalEdgeSharpeningFilter  = 0x10,              // Applies an edge sharpening filter to digital output video. The filter reduces ringing artifacts that 
                                                                  // appear due to transitions of high amplitude in 
                                                                  // the digital signal. Uses a parameter of type 
                                                                  // EMvOnOff. On Matrox DSX LE2/CG, this parameter 
                                                                  // can be called for video channels A and B (even though the 
                                                                  // DSX LE2/CG exposes only one playback channel) because both 
                                                                  // of the card's output connectors can be programmed independently.
   keVideoOutputChromaClipping               = 0x11,              // Specifies whether or not to clip over-saturated chroma levels in the active portion of the output video signal. Uses a 
                                                                  // parameter of type EMvOnOff.
                                                                  // On Matrox DSX LE2/CG, this parameter 
                                                                  // can be called for video channels A and B (even though the 
                                                                  // DSX LE2/CG exposes only one playback channel) because both 
                                                                  // of the card's output connectors can be programmed independently.
   keVideoOutputKeyDownscaleLuma             = 0x12,              // Specifies whether or not to downscale the luminance range of the output key signal from 0-255 to 16-235. Uses a parameter of type 
                                                                  // EMvOnOff. This parameter is supported on Matrox X.mio2, DSX SD, DSX LE/300/C, and DSX LE/CG.
   keVideoOutputKeyInvertLuma                = 0x13,              // Specifies whether or not to invert the luminance part of the output key signal and the key value. Uses a parameter of type EMvOnOff. This parameter is supported 
                                                                  // on Matrox X.mio2, DSX SD, DSX LE/300/C, and DSX LE/CG. 
   keVideoOutputKeyApplyOffset               = 0x14,              // Applies an offset to the luminance values so that the inverted result falls within the 16-235 range.
                                                                  // The offset can only be applied if the luminance part of the key signal is inverted (keVideoOutputKeyInvertLuma = keOn),
                                                                  // and the luminance range of the key signal is downscaled (keVideoOutputKeyDownscaleLuma = keOn). 
                                                                  // Otherwise, the offset will not be applied and the key signal is not valid. Uses a 
                                                                  // parameter of type EMvOnOff. This parameter is supported 
                                                                  // on Matrox X.mio2, DSX SD, DSX LE/300/C, and DSX LE/CG.
   keVideoOutputWatchdogEnable               = 0x15,              // Enables or disables the DSX card's watchdog functionality. Uses a parameter of type EMvOnOff.
   keVideoOutputWatchdogTimeOut              = 0x16,              // Specifies the time limit after which the Watchdog 
                                                                  // system will activate if it is not reset. Uses a 
                                                                  // parameter of type long.
   keVideoOutputWatchdogOutputKeyOpaque      = 0x17,              // Specifies if the output key must be opaque or 
                                                                  // transparent when the watchdog activates. 
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputPreviewOutputSource          = 0x18,              // Selects the video channel that will be used as the 
                                                                  // source for the preview output. Uses a parameter 
                                                                  // of type EMvVideoIOChannel. This parameter is not 
                                                                  // supported on Matrox DSX LE/CG or DSX LE2/CG.
   keVideoOutputAnalogHorizontalDelay        = 0x19,              // Sets the analog buffer delay, relative to the genlock source, to apply at the 
                                                                  // output. Uses a parameter of type long. This parameter is not supported on 
                                                                  // Matrox RT.X2 LE or RT.X2 SD.
   keVideoOutputAnalogOutputSource           = 0x1a,              // Selects the video channel that will be used as the 
                                                                  // source for the analog output. Uses a parameter 
                                                                  // of type EMvVideoIOChannel. This parameter is not 
                                                                  // supported on Matrox DSX LE/CG or DSX LE2/CG.
   keVideoOutputSdiHorizontalFrameDelay      = 0x1b,              // Controls the horizontal delay on the SDI output 
                                                                  // circuit. Combined with 
                                                                  // keVideoOutputSdiVerticalFrameDelay it provides a
                                                                  // range of 0 to 1 frame delay.
   keVideoOutputSdiVerticalFrameDelay        = 0x1c,              // Controls the vertical delay on the SDI output circuit. 
                                                                  // Combined with keVideoOutputSdiHorizontalFrameDelay
                                                                  // it provides a range of 0 to 1 frame delay. Uses a 
                                                                  // parameter of type long.
   keVideoOutputComponent                    = 0x1d,              // Toggles the analog video output mode between Y/C 
                                                                  // (S-Video) and component. Uses a parameter of type 
                                                                  // EMvOnOff. This parameter is not 
                                                                  // supported on Matrox DSX LE/CG or DSX LE2/CG.
   keVideoOutputGammaCorrection              = 0x1e,              // Controls the gamma correction for a RGB output. Uses a
                                                                  // parameter of type SMvGammaCorrectionData.
   keVideoOutputKeyAllowSuperBlack           = 0x1f,              // Clips the luminance below 64 (16 in 8 bit).
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputKeyAllowSuperWhite           = 0x20,              // Clips the luminance above 940 (235 in 8 bit).
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputKeyChromaClipping            = 0x21,              // Clips the chroma to stay between 64 and 960 (16-240 in 
                                                                  // 8 bit). Uses a parameter of type EMvOnOff.
   keVideoOutputAllowForceDviFrameRate       = 0x22,              // Specifies whether or not to force the DVI output frame rate.
                                                                  // Uses a parameter of type EMvOnOff. This parameter is not 
                                                                  // supported on Matrox RT.X2 LE or RT.X2 SD.
   keVideoOutputAllowForcedDviFrameRate      = 0x23,              // Sets the forced frame rate of the DVI output to 60 Hz.
                                                                  // Uses a parameter of type EMvFrameRate. This parameter is not 
                                                                  // supported on Matrox RT.X2 LE or RT.X2 SD.   
   keVideoOutputBlending                     = 0x24,              // Sets the video output blending mode. For Matrox X.mio2 or DSX LE2/CG, it 
                                                                  // sets the video output to blending mode, which enables the zero 
                                                                  // frame-delay feature of X.mio2 or DSX LE2/CG so that there 
                                                                  // is no hardware delay between the input and output channels (not 
                                                                  // supported on the optional X.RIO module for X.mio2). Uses a parameter 
                                                                  // of type EMvOnOff. For X.AVCio, it selects the source of the output, 
                                                                  // loopthrough, or playback for the blender. The blender will operate 
                                                                  // on the selected output. Uses a parameter of type EMvAVCIOBlend.
   keVideoOutputSource                       = 0x25,              // Specifies the video channel that will be used as the source for 
                                                                  // the selected output. Uses a parameter of type 
                                                                  // SMvVideoOutputSource. This parameter is available on DSX LE/300/C, 
                                                                  // DSX LE/CG, and DSX LE2/CG only.
   keVideoOutputColorBurst                   = 0x26,              // Enables or disables the color burst for channel B of DSX SD.
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputReduceCutoffFreq             = 0x27,              // Reduces the cutoff frequency of the analog video encoder for SD video. 
                                                                  // Uses a parameter of type EMvOnOff. Default value is keOff
   keVideoOutputBlendingOpacity              = 0x28,              // Sets the opacity to be applied to the blender's key. The key will be multiplied by this value.
                                                                  // Uses a parameter of type double. A value of 0.0 disables blending,
                                                                  // and a value of 1.0 leaves the key unchanged.
   keVideoOutputPrimarySignal                = 0x29,              // Specifies the output signal type to be enabled.  
                                                                  // All other output signals will be disabled.
                                                                  // Uses a parameter of type EMvVideoSignal.
   keVideoOutputDefaultColor                 = 0x2a,              // Specifies the default output color when playback is stopped.
                                                                  // Uses a parameter of type EMvColor.
   keVideoOutputDefaultOpacity               = 0x2b,              // Specifies the default output alpha opacity when playback is stopped ("on" for opaque, "off" for transparent).
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputCheckDVIMonitorLimits        = 0x2c,              // Specifies whether or not the DVI output will check the monitor's limits and disable the DVI output if the monitor does not support the current output resolution.  
                                                                  // Uses a parameter of type EMvOnOff.
   keVideoOutputDVILumaContrast              = 0x2d,              // Sets the luma contrast of the DVI video output. Uses a parameter of type double.
   keVideoOutputDVILumaBrightness            = 0x2e,              // Sets the luma brightness of the DVI video output. Uses a parameter of type double.
   keVideoOutputDVIHue                       = 0x2f,              // Sets the hue of the DVI video output.
   keVideoOutputDVIChromaGain                = 0x30,              // Sets the chroma gain (saturation) of the DVI video output. Uses a parameter of type double.
   keVideoOutputDVIBlueOnly                  = 0x31,              // Enables blue-only mode for the DVI video output. Uses a parameter of type EMvOnOff.
   keVideoOutputHDMILumaContrast             = 0x2d,              // Controls luma contrast on HDMI output. Uses a parameter of type double.
   keVideoOutputHDMILumaBrightness           = 0x2e,              // Controls luma brightness on HDMI output. Uses a parameter of type double.
   keVideoOutputHDMIHue                      = 0x2f,              // Controls hue on HDMI output. Uses a parameter of type double.
   keVideoOutputHDMIChromaGain               = 0x30,              // Controls chroma gain (saturation) on HDMI output. Uses a parameter of type double.
   keVideoOutputHDMIBlueOnly                 = 0x31,              // Selects blue only mode on HDMI output. Uses a parameter of type EMvOnOff.

   keVideoOutputWatchdogBypassModeHardware   = 0x32,              // Specifies if the bypass mode is hardware (keOn) or mechanical (keOff).
                                                                  // Uses a parameter of type EMvOnOff. This parameter is supported on Matrox X.mio2 (not supported on the optional X.RIO module for X.mio2). 
   keVideoOutputEnable3GLevelB               = 0x33,              // Enables or disables SMPTE 425M Level B mapping on the output. When output resolution is 1080p @ 59.94, 50 or 60 fps, "on" enables Level B 
                                                                  // mapping, and "off" enables Level A mapping. Uses a parameter of type EMvOnOff. This parameter is supported on Matrox X.mio2 and DSX LE3.
   keVideoOutputEnableSMPTE352               = 0x34,              // Enables or disables the transmission of SMPTE 352 packets on SDI outputs for non-3G output resolutions (packets are automatically transmitted for 3G resolutions). 
                                                                  // This parameter is supported on Matrox X.mio2 and X.AVCio only.
   keVideoOutputHDMIType                     = 0x35,              // Type of the HDMI output. Uses a parameter of type 
                                                                  // EMvVideoOutputType.
   keVideoOutputLoopback                     = 0x36,              // Sets the video output loopthrough mode. Selects the source of the output, 
                                                                  // loopthrough or playback. Uses a parameter of type EMvOnOff.
   keVideoOutputHDMIRedGain                  = 0x37,              // Controls RGB Red gain on HDMI output.
   keVideoOutputHDMIGreenGain                = 0x38,              // Controls RGB Green gain on HDMI output.
   keVideoOutputHDMIBlueGain                 = 0x39,              // Controls RGB Blue gain on HDMI output.
   keVideoOutputHDMIGainMatrix               = 0x3A,              // Controls RBG gain matrix on HDMI output
   keVideoOutputEnableAnalogLine21CC         = 0x3B,              // Enables analog output line 21 closed captioning on MXO2 family. Uses a parameter of type EMvOnOff.
   keVideoOutputEnableSDILine21CC            = 0x3C,              // Enables SDI output line 21 closed captioning on MXO2 family. Uses a parameter of type EMvOnOff.
   keVideoOutputEnableSDIVancCC              = 0x3D,              // Enables SDI output VANC closed captioning on MXO2 family. Uses a parameter of type EMvOnOff.

   keVideoOutputBlinkOnboardLED				 = 0x3E,			  // Enable/Disable blinking mode of the onboard LED. Uses a parameter of type EMvOnOff.

   keVideoOutputHDMI3DFlag					 = 0x3F,			  // Enable/Disable HDMI 3D flag
   keVideoOutputDisableOnboardLED			 = 0x40,			  // Enable/Disable onboard LED. Uses a parameter of type EMvOnOff.

   keVideoOutputLast                // End of list indicator.                   
};

//
// Summary:
//    Specifies a video output.
//
enum EMvVideoOutputSelect
{
   keVideoOutputSelectInvalid,   // Invalid value.
   keVideoOutputSelectSDIB,      // Specifies the second SDI output.
   keVideoOutputSelectAnalogA,   // Specifies the first analog output.
   keVideoOutputSelectSDIA,      // Specifies the first SDI output.
   keVideoOutputSelectHDMIA,     // Specifies the first HDMI output.   
   keVideoOutputSelectLast       // End of list indicator.
};

//
// Summary:
//    Specifies a video source.
//
enum EMvVideoOutputSource
{
   keVideoOutputSourceInvalid,   // Invalid value.
   keVideoOutputSourceVideoA,    // Specifies the video from playback A.
   keVideoOutputSourceKeyA,      // Specifies the key (alpha) from playback A.
   keVideoOutputSourceVideoB,    // Specifies the video from playback B.
   keVideoOutputSourceLast       // End of list indicator.
};

//
// Summary:
//    Specifies the analog video output type.
//
enum EMvVideoOutputType
{
   keVideoOutputTypeInvalid,     // Invalid value.
   keVideoOutputTypeRgb,         // Specifies an RGB analog output.
   keVideoOutputTypeRgbGraphic,  // 
   keVideoOutputTypeYuv,         // Specifies a YUV analog output.
   keVideoOutputTypeLast         // End of list indicator.
};

//
// Summary:
//    Enumerates the type of video signal.
//
enum EMvVideoSignal
{
   keVideoSignalInvalid    = 0x00,  // Invalid value.
   keVideoSignalComposite  = 0x01,  // The video signal is analog composite.
   keVideoSignalComponent  = 0x02,  // The video signal is analog component (YPbPr).
   keVideoSignalSVideo     = 0x04,  // The video signal is analog S-Video (Y/C).
   keVideoSignalSDI        = 0x08,  // The video signal is digital SDI (Serial Digital Interface).
   keVideoSignalSDTI       = 0x10,  // The video signal is digital SDTI (Serial Digital Transfer Interface).
   keVideoSignalDVI        = 0x20,  // The video signal is digital DVI (Digital Visual Interface).
   keVideoSignalHDMI       = 0x40,  // The video signal is digital HDMI (High-Definition Multimedia Interface).
   keVideoSignalLast                // End of list indicator.
};

//
// Summary:
//    Specifies the available temperature sensor IDs for the DSX hardware components.
//
enum EMvTemperatureSensorID
{
   keTemperatureSensorIDInvalid,                // Invalid value.
   keTemperatureSensorIDNone,                   // There is no temperature sensor on this device.
   keTemperatureSensorIDXLinkBackPlane,         // Temperature sensor ID for the X.linkSD breakout box.
   keTemperatureSensorIDXLinkSdiModule,         // Temperature sensor ID for the SDI module on the 
                                                   // X.linkSD breakout box.
   keTemperatureSensorIDIoBoardBackPlane,       // Temperature sensor ID for the X.io card.
   keTemperatureSensorIDScalerModuleBackPlane,  // Temperature sensor ID for the X.scaler module.
   keTemperatureSensorIDFxBoardFPGA,            // Temperature sensor ID for the X.effects card.
   keTemperatureSensorIDFxBoardGPU,             // Temperature sensor ID for the GPU on the
                                                   // X.effects card.
   keTemperatureSensorIDXlinkHDBackPlane,       // Temperature sensor ID for the X.linkHD breakout box.
   keTemperatureSensorIDXlinkHDIoModule,        // Temperature sensor ID for the I/O module on the 
                                                   // X.linkHD breakout box.
   keTemperatureSensorIDMIoBoardBackPlane,      // Temperature sensor ID for the X.mio card.
   keTemperatureSensorIDDsxle,                  // Temperature sensor ID for the DSX LE card.
   keTemperatureSensorIDRTX2,                   // Temperature sensor ID for the RT.X2 card.
   keTemperatureSensorIDDsxsd,                  // Temperature sensor ID for the DSX SD card.
   keTemperatureSensorIDMXO,                    // Temperature sensor ID for the MXO card.
   keTemperatureSensorIDMIo2BoardBackPlane,     // Temperature sensor ID for the X.mio2 card.
   keTemperatureSensorIDMIo2Module1,            // Temperature sensor ID for the X.mio2 module 1.
   keTemperatureSensorIDMIo2Module2,            // Temperature sensor ID for the X.mio2 module 2.
   keTemperatureSensorIDAVCio,                  // Temperature sensor ID for the AVCio card.
   keTemperatureSensorIDMXO2,                   // Temperature sensor ID for the MXO2.
   keTemperatureSensorIDMAX,                    // Temperature sensor ID for the MAX card.
   keTemperatureSensorIDX264,                   // Temperature sensor ID for the X.264 card.
   keTemperatureSensorIDX264io,                 // Temperature sensor ID for the X.264io card.
   keTemperatureSensorIDX264ioASI,              // Temperature sensor ID for the ASI version of the X.264io card.
   keTemperatureSensorIDMojito,                 // Temperature sensor ID for the Mojito card.
   keTemperatureSensorIDMio2PlusBackPlane,      // Temperature sensor ID for the temperature sensor of the backplane on the X.mio2 Plus card.
   keTemperatureSensorIDMio2PlusFPGA1,          // Temperature sensor ID for the temperature sensor of the first FPGA chip on the X.mio2 Plus card.
   keTemperatureSensorIDMio2PlusFPGA2,          // Temperature sensor ID for the temperature sensor of the second FPGA chip on the X.mio2 Plus card.
   keTemperatureSensorIDLE3BoardBackPlane,      // Temperature sensor ID for the temperature sensor of the backplane on the DSX LE3 card.
   keTemperatureSensorIDLE3FPGA1,               // Temperature sensor ID for the temperature sensor of the first FPGA chip on the DSX LE3 card.
   keTemperatureSensorIDLE3FPGA2,               // Temperature sensor ID for the temperature sensor of the second FPGA chip on the DSX LE3 card.
   keTemperatureSensorIDVS4BoardBackPlane,      // Temperature sensor ID for the VS4 card.
   keTemperatureSensorIDMio3FamilyFPGA,         // Temperature sensor ID for the temperature sensor of the FPGA chip on the X.mio3 and DSX LE4 card family.
   keTemperatureSensorIDMio3lpFPGA = keTemperatureSensorIDMio3FamilyFPGA, // Temperature sensor ID for the temperature sensor of the FPGA chip on the X.mio3 LP card.
   keTemperatureSensorIDVS4PROBoardBackPlane,   // Temperature sensor ID for the VS4Pro card.
   keTemperatureSensorIDMojito2,                // Temperature sensor ID for the Mojito2 card.
   keTemperatureSensorIDM264,                   // Temperature sensor ID for the M264 line of cards processor chip 
   keTemperatureSensorIDM264SSwitch,            // Temperature sensor ID for the switch on the M264S2 and M264S3
   keTemperatureSensorIDLast                    // End of list indicator.
};

//
// Summary:
//    Describes the status of an X.link device.
//
enum EMvXlinkStatus
{
   keXlinkInvalid       = 0x00,  // Invalid value.
   keXlinkOk            = 0x01,  // Indicates that the X.link is working correctly.
   keXlinkDisconnected  = 0x02,  // Indicates that the X.link has been disconnected.
   keXlinkOverheat      = 0x04,  // Indicates that the X.link has overheated and has been shut down
                                    // to prevent damage.
   keXlinkOvercurrent   = 0x08,  // Indicates that the X.link has got an overcurrent problem and
                                    // has been shut down to prevent damage.
   keXlinkPowerProblem  = 0x10,  // Indicates that the X.link has a power problem and has been shut
                                    // down to prevent damage.
   keXlinkLast          = 0x20   // End of list indicator.
};

//
// Summary:
//    Specifies the X.link cable ID.
//
enum EMvCableID
{
   keCableIDInvalid = -1,  // Invalid value.
   keCableIDType3 = 0,     // Indicates a type 3 cable (not supported).
   keCableIDType2,         // Indicates a type 2 cable (not supported). 
   keCableIDMatrox,        // Indicates a Matrox-compliant cable.
   keCableIDNonMatrox      // Indicates a third-party cable (supported but not recommended).
};

//
// Summary:
//    Determines the source of synchronization clock for the X.scaler.
//
enum EMvSynchronizationSource
{
   keSynchronizationSourceInvalid,              // Invalid value.
   keSynchronizationSourceGenlock,              // Indicates that the clock source originates from the genlock.
   keSynchronizationSourceVideoInputChannelA,   // Indicates that the clock source originates from video input A.
   keSynchronizationSourceVideoInputChannelB,   // Indicates that the clock source originates from video input B.
   keSynchronizationSourceLast                  // End of list indicator.
};

//
// Summary:
//    Determines the video filter frequency response at the output of the X.scaler.
//
enum EMvFilterSelect
{
   keMvFilterSelectInvalid,   // Invalid value.
   keMvFilterSelectNormal,    // Indicates that the filter frequency response is normal. The filter 
                                 // is adjusted according to the ratio of the input and output 
                                 // rectangle sizes (see IMvXScalerHD::Transcode) in order to remove 
                                 // undesired frequencies based on mathematical calculations.
   keMvFilterSelectSmoother,  // Indicates that the filter will cut at a lower-than-normal frequency,
                                 // causing blurring of the image.
   keMvFilterSelectSharper,   // Indicates that the filter will cut at a higher-than-normal frequency.
                                 // The image becomes sharper than normal but may contain artifacts 
                                 // (aliasing).
   keMvFilterSelectSharpest,  // Indicates that the filter will cut at a higher-than-"sharper" 
                                 // frequency, causing the image to become even sharper than normal 
                                 // but to contain more artifacts (aliasing).
   keMvFilterSelectLast       // End of list indicator.
};


//
// Summary:
//    Determines the type of frame in a group of pictures (GOP).
//
enum EMvMpegFrameType
{
   keMvMpegFrameTypeInvalid,   // Invalid value.
   keMvMpegFrameTypeIFrame,    // Identifies the frame as an I-frame.
   keMvMpegFrameTypePFrame,    // Identifies the frame as a P-frame.
   keMvMpegFrameTypeBFrame,    // Identifies the frame as a B-frame.
   keMvMpegFrameTypeIDRFrame,  // Identifies the frame as an IDR-frame.  This is more important than setting I-frame (AVC/H.264).
   keMvMpegFrameTypeIorPFrame, // Identifies the frame as an I-frame or a P-frame when it can't be differentiated (AVC/H.264).
   keMvMpegFrameTypePorBFrame, // Identifies the frame as an P-frame or a B-frame when it can't be differentiated (AVC/H.264).
   keMvMpegFrameTypeUnknownFrame, // Identifies the frame as an unknown frame when it can't be differentiated.  It should be used as last resort (AVC/H.264).
   keMvMpegFrameTypeNonFrameNALUnits, // Identifies other NAL units, such as SPS, PPS, etc.  If there's a frame in the data, don't use this type (AVC/H.264).
   keMvMpegFrameTypeOpenedBFrame, // Identify the frame as a opened B-frame.
   keMvMpegFrameTypeLast      // End of list indicator.
};
// This macro is used to get the string of the enum value EMvMpegFrameType.
#define MV_MPEG_FRAME_TYPE_ENUM_TO_STRING(eMpegFrameType) \
   ((eMpegFrameType == keMvMpegFrameTypeInvalid)         ? ("Invalid") : \
   (eMpegFrameType == keMvMpegFrameTypeIFrame)           ? ("IFrame") : \
   (eMpegFrameType == keMvMpegFrameTypePFrame)           ? ("PFrame") : \
   (eMpegFrameType == keMvMpegFrameTypeBFrame)           ? ("BFrame") : \
   (eMpegFrameType == keMvMpegFrameTypeIDRFrame)         ? ("IDRFrame") : \
   (eMpegFrameType == keMvMpegFrameTypeIorPFrame)        ? ("IorPFrame") : \
   (eMpegFrameType == keMvMpegFrameTypePorBFrame)        ? ("PorBFrame") : \
   (eMpegFrameType == keMvMpegFrameTypeUnknownFrame)        ? ("Unknown Frame") : \
   (eMpegFrameType == keMvMpegFrameTypeNonFrameNALUnits) ? ("NonFrameNALUnits") : \
   (eMpegFrameType == keMvMpegFrameTypeOpenedBFrame)     ? ("Opened BFrame") : \
   (eMpegFrameType == keMvMpegFrameTypeLast)             ? ("Last") : \
   ("???"))


//
// Summary:
//    Determines the type of information.
//
enum EMvInfoType
{
   keMvInfoTypeInvalid,   // Invalid value.
   keMvInfoTypeInfo,      // Identify the info as information.
   keMvInfoTypeWarning,   // Identify the info as warning.
   keMvInfoTypeError,     // Identify the info as error.
   keMvInfoTypeProgress,  // Identify the info as error.
   keMvInfoTypeLast       // End of list indicator.
};
// This macro is used to get the string of the enum value EMvInfoType.
#define MV_INFO_TYPE_ENUM_TO_STRING(eInfoType) \
   ((eInfoType == keMvInfoTypeInvalid)         ? ("Invalid") : \
   (eInfoType == keMvInfoTypeInfo)             ? ("Info") : \
   (eInfoType == keMvInfoTypeWarning)          ? ("Warning") : \
   (eInfoType == keMvInfoTypeError)            ? ("Error") : \
   (eInfoType == keMvInfoTypeProgress)         ? ("Progress") : \
   (eInfoType == keMvInfoTypeLast)             ? ("Last") : \
   ("???"))


//
// Summary:
//    Selects the background layer of the blender on the X.AVCio card.
//
enum EMvAVCIOBlend
{
   keMvAVCIOBlendOverPlayback    = keOff,
   keMvAVCIOBlendOverPassthrough = keOn
};

enum EMvSpeakerMapping
{
   keMvSpeakerMappingInvalid,   // Invalid value.
   keMvSpeakerMappingStereo,    // Identifies the speaker mapping as stereo.
   keMvSpeakerMapping5_1Channels,   // Identifies the speaker mapping as 5.1 channels.
   keMvSpeakerMapping7_1Channels,   // Identifies the speaker mapping as 7.1 channels.
   keMvSpeakerMappingLast       // End of list indicator.
};

//
// Summary:
//    Specifies the camera preset associated with DVI timings. Some cameras with different 
//    resolutions and/or frequencies sometimes have the same DVI timings. This enumeration selects
//    the resolution/frequency that will be associated with the DVI timings.
//
enum EMvVideoInputDVITiming
{
   keVideoInputDVITimingInvalid,     // Invalid value.
   keVideoInputDVITimingManual,      // Allows manual setting of the value. (DO NOT USE.)
   keVideoInputDVITimingPreset1,     // Preset 1.
   keVideoInputDVITimingPreset2,     // Preset 2.
   keVideoInputDVITimingPreset3,     // Preset 3. 
   keVideoInputDVITimingLast
};

//
// Summary:
//    Selects the dongle corresponding to the main X.mio2 card, or the dongle corresponding to the optional X.RIO module for the X.mio2 card. 
//
enum EMvDongleSelect
{
   keDongleSelectInvalid,     // Invalid selection.
   keDongleSelectBaseBoard,   // Selects the X.mio2 card's dongle.
   keDongleSelectRIOModule,   // Selects the X.RIO module's dongle.
   keDongleSelectLast
};

//
// Summary:
//    Describes the SMPTE352 version and payload identifier.
//
enum EMvSMPTE352IdVersionPayload
{
   keMvSMPTE352IdVersionPayloadInvalid       = -1,    // Invalid value. 
   keMvSMPTE352IdVersionPayloadSDSDI         = 0x81,  // Indicates SD SDI.  
   keMvSMPTE352IdVersionPayloadHD720SDI      = 0x84,  // Indicates HD 720 lines SDI. 
   keMvSMPTE352IdVersionPayloadHD1080SDI     = 0x85,  // Indicates HD 1080 lines SDI.  
   keMvSMPTE352IdVersionPayload1080DualLink  = 0x87,  // Indicates 1080 dual-link SDI.    
   keMvSMPTE352IdVersionPayload3G1080LevelA  = 0x89,  // Indicates 3G Level A 1080 lines SDI.    
   keMvSMPTE352IdVersionPayload3G1080LevelB  = 0x8A   // Indicates 3G Level B 1080 lines SDI.   
};

//
// Summary:
//    Selects the de-interlacer processing case.
//
enum EMvDeInterlaceCase 
{
   keMvDeInterlaceCaseInvalid,     // Invalid value.
   keMvDeInterlaceCaseBetween,     // Normal field, between two other fields.
   keMvDeInterlaceCaseFirst,       // First field of a stream.
   keMvDeInterlaceCaseLast         // Last field of a stream.
};

//
// Summary:
//    Selects the vertical anti-aliasing filter configuration for the scaler.
//
enum EMvScalerFilterConfig   
{
   keMvScalerFilterConfigInvalid,         // Invalid value.
   keMvScalerFilterConfigVBefore,         // Normal case: vertical anti-aliasing filter before
                                             // scaling, no sharpness control.
   keMvScalerFilterConfigVAfter,          // Vertical anti-aliasing filter after scaling, 
                                             // no sharpness control.
   keMvScalerFilterConfigVAfterWSharpness,// Vertical anti-aliasing filter after scaling, with
                                             //sharpness control.
   keMvFScalerilterConfigLast             
};

//
// Summary:
//    Selects the scaler configuration.
//
enum EMvScalerConfig   
{
   keMvScalerConfigInvalid,      // Invalid value.
   keMvScalerConfigNormal,       // Normal case.
   keMvScalerConfigProcessPOut,  // Process as progressive output but discard
                                    // one line out of two to generate interlaced video.
   keMvScalerConfigLast          
};

//
// Summary:
//    Describes the status of the genlock input termination (REF IN).
//
enum EMvTerminationStatus
{
   keMvTerminationStatusNotAvailable = 0, // Indicates that the dynamic termination status is not available.
                                             // The termination status is reported only if there is a physical switch on the hardware.
   keMvTerminationStatusOn,               // Indicates that the termination is ON.                
   keMvTerminationStatusOff,              // Indicates that the termination is OFF.                 
   keMvTerminationStatusLast                               
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvTerminationStatus.
//
#define MV_TERMINATION_STATUS_ENUM_TO_STRING(eMvTerminationStatus) \
   ((eMvTerminationStatus == keMvTerminationStatusNotAvailable) ? ("Not Available") : \
   (eMvTerminationStatus == keMvTerminationStatusOn)            ? ("On") : \
   (eMvTerminationStatus == keMvTerminationStatusOff)           ? ("Off") : \
   ("???"))

//
// Summary:
//    Describes the status of the cooling fan.
//
enum EMvCoolingFanStatus
{
   keMvFanStatusNotAvailable,       // Specifies that the fan status is not available on the current hardware model.                        
   keMvFanStatusOk,                 // Specifies that the fan is working correctly.              
   keMvFanStatusTooSlowOrStopped,   // Specifies that the fan is running too slow or has stopped.                            
   keMvFanStatusLast                // End of list indicator.               
};

//
// Summary:
//    Selects the video mixer vertical ancillary data source.
//
enum EMvVideoMixerVancSource
{
   keVideoMixerVancSourceInvalid,      // Invalid value.
   keVideoMixerVancSourceInput,        // Specifies that the input source provides the vertical ancillary data. 
   keVideoMixerVancSourceNode,         // Specifies that the node provides the vertical ancillary data.
   keVideoMixerVancSourceLast          // End of list indicator.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvVideoMixerVancSource.
//
#define MV_VIDEO_MIXER_VANC_SOURCE_ENUM_TO_STRING(eVideoMixerVancSource) \
   ((eVideoMixerVancSource == keVideoMixerVancSourceInvalid)      ? ("Invalid") :\
   (eVideoMixerVancSource  == keVideoMixerVancSourceInput)        ? ("Input")   :\
   (eVideoMixerVancSource  == keVideoMixerVancSourceNode)         ? ("Node")    :\
   (eVideoMixerVancSource  == keVideoMixerVancSourceLast)         ? ("Last")    :\
   ("???"))

//
// Summary:
//    Selects the video mixer audio and horizontal ancillary data source.
//
enum EMvVideoMixerAudioAndHancSource
{
   keVideoMixerAudioAndHancSourceInvalid,       // Invalid value.
   keVideoMixerAudioAndHancSourceInput,         // Specifies that the input provides the audio and horizontal ancillary data.
   keVideoMixerAudioAndHancSourceMixerOrNode,   // Specifies that the node provides the audio and the horizontal ancillary data, 
                                                // or that the audio mixer provides the audio and the node provides the horizontal ancillary data.
   keVideoMixerAudioAndHancSourceLast           // End of list indicator.
};

//
// Summary:
// 	This macro is used to get the string of the enum value EMvVideoMixerAudioAndHancSource.
//
#define MV_VIDEO_MIXER_AUDIO_AND_HANC_SOURCE_ENUM_TO_STRING(eVideoMixerAudioAndHancSource) \
   ((eVideoMixerAudioAndHancSource == keVideoMixerAudioAndHancSourceInvalid)      ? ("Invalid")        :\
   (eVideoMixerAudioAndHancSource  == keVideoMixerAudioAndHancSourceInput)        ? ("Input")          :\
   (eVideoMixerAudioAndHancSource  == keVideoMixerAudioAndHancSourceMixerOrNode)  ? ("Mixer or Node")  :\
   (eVideoMixerAudioAndHancSource  == keVideoMixerAudioAndHancSourceLast)         ? ("Last")           :\
   ("???"))

//*********************************************************************************//
//**                                     UNIONS                                  **//
//*********************************************************************************//
typedef union
{
   uint32_t all;

   union
   {
      uint32_t all;
      struct
      {
         uint32_t version_payload:8;
         uint32_t rate_info:4;
         uint32_t picture_info:4;
         uint32_t structure_info:4;
         uint32_t aspect_info:4;
         uint32_t depth_info:2;
         uint32_t reserved1:1;
         uint32_t range_info:2;
         uint32_t reserved2:1;
         uint32_t link_info:2;
      }fld;

   }USMPTE352Idfield;
} USMPTE352Id;


//*********************************************************************************//
//**                                     STRUCTURES                              **//
//*********************************************************************************//

//
// Summary:
//    Used to return the status of the AES/EBU input signal(s).
//
struct SMvAesEbuAudioStatus
{
   uint32_t   size;                // Structure size in bytes.
   bool     AesEbuInAPresent;    // True if there is an audio signal on AES/EBU input A. For example, this corresponds to 
                                    // pair 1 (<B>AES IN 1/2</B> cable) on connector A on X.mio2.
   bool     AesEbuInBPresent;    // True if there is an audio signal on AES/EBU input B. For example, this corresponds to 
                                    // pair 2 (<B>AES IN 3/4</B> cable) on connector A on X.mio2.
   bool     AesEbuInCPresent;    // True if there is an audio signal on AES/EBU input C. For example, this corresponds to 
                                    // pair 3 (<B>AES IN 5/6</B> cable) on connector A on X.mio2.
   bool     AesEbuInDPresent;    // True if there is an audio signal on AES/EBU input D. For example, this corresponds to 
                                    // pair 4 (<B>AES IN 7/8</B> cable) on connector A on X.mio2.
   bool     AesEbuInEPresent;    // True if there is an audio signal on AES/EBU input E. For example, this corresponds to 
                                    // pair 5 (<B>AES IN 1/2</B> cable) on connector B on X.mio2.
   bool     AesEbuInFPresent;    // True if there is an audio signal on AES/EBU input F. For example, this corresponds to 
                                    // pair 6 (<B>AES IN 3/4</B> cable) on connector B on X.mio2.
   bool     AesEbuInGPresent;    // True if there is an audio signal on AES/EBU input G. For example, this corresponds to 
                                    // pair 7 (<B>AES IN 5/6</B> cable) on connector B on X.mio2.
   bool     AesEbuInHPresent;    // True if there is an audio signal on AES/EBU input H. For example, this corresponds to 
                                    // pair 8 (<B>AES IN 7/8</B> cable) on connector B on X.mio2.
};

//
// Summary:
//    Describes the analog audio output source parameters.
//
struct SMvAudioAnalogOutputSource
{
   uint32_t                   size;             // Structure size in bytes.
   EMvAudioPair               eAudioPair;       // Which audio pair to send to the output.
   EMvAudioPlaybackChannel    ePlaybackChannel; // Which audio channel to take the pair from.
};

//
// Summary:
//    Describes the HDMI audio output source parameters.
//
struct SMvAudioHdmiOutputSource
{
   uint32_t                   size;             // Structure size in bytes.
   EMvAudioPair               eAudioPair;       // Which audio pair to send to the output.
   EMvAudioPlaybackChannel    ePlaybackChannel; // Which audio channel to take the pair from.
};


//
// Summary:
//    Returns the status of the HDMI audio input.
//
struct SMvHdmiAudioStatus
{
   uint32_t   size;                             // Structure size in bytes.
   EMvChannelType       eChannelType;           // Returns the current number of channels for the HDMI audio input
                                                // if there are at least three channels. Otherwise, it will return keChannelTypeInvalid.
   EMvSpeakerMapping    eSpeakerMapping;        // Returns the current HDMI audio input speaker mapping.
};

//
// Summary:
//    Describes information for audio capture.
//
struct SMvAudioCaptureInfo
{
   uint32_t                size;                            // Structure size in bytes.
   EMvCaptureAudioSource   eSupportedAudioCaptureSources;   // A bitwise enumeration that indicates
                                                               // all the supported audio capture 
                                                               // sources.
};

//
// Summary:
//    Determines the data type of the audio captured on a specific channel.
//
struct SMvAudioCaptureType
{
   uint32_t                size;             // Describes an audio capture channel data type.
   EMvAudioDataType        eCaptureType;     // What type of data the audio capture channel is capturing.
   EMvAudioCaptureChannel  eCaptureChannel;  // Which audio capture channel the eCaptureType field is applied to.
};

//
// Summary:
//    Determines the capture path for AES/EBU audio capture.
//
struct SMvDigitalAudioCapturePath
{
   uint32_t                size;             // Specifies the structure size, in bytes.
   EMvAesEbuAudioIOChannel eAesEbuChannel;   // Specifies the AES/EBU cable pair to be captured.
   EMvAudioPair            eAudioPair;       // Specifies the audio capture pair for the incoming audio.
   EMvAudioCaptureChannel  eCaptureChannel;  // Specifies the capture channel. 
};

//
// Summary:
//    Used to describe information about audio input/output.
//
struct SMvAudioIOInfo
{
   uint32_t                   size;                         // Specifies the structure size, in bytes.
   EMvAnalogAudioInputSource  eSupportedAnalogAudioInputs;  // A bitwise enumeration that indicates
                                                               // all the supported analog audio inputs.
   EMvAudioPath               eSupportedAnalogAudioOutputs; // A bitwise enumeration that indicates 
                                                               // all the supported analog audio outputs.
   EMvAudioPath               eSupportedAesEbuAudioOutputs; // A bitwise enumeration that indicates 
                                                               // all the supported AES/EBU audio outputs.
};

//
// Summary:
//    Describes an audio playback channel data type.
//
struct SMvAudioPlaybackType
{
   uint32_t                size;             // Structure size in bytes.
   EMvAudioDataType        ePlaybackType;    // What type of data the audio playback channel is playing.
   EMvAudioPlaybackChannel ePlaybackChannel; // Which audio playback channel the ePlaybackType field is applied to.
};

//
// Summary:
//    Describes the clock status of all the possible audio inputs.
//
struct SMvAudioTimeBaseStatus
{
   uint32_t size;                            // Structure size in bytes.
   bool     bMasterAudioTimeBaseDetected;    // Specifies if the clocks were detected from the master
                                                // audio time base. To set or get the master for audio 
                                                // time base, see EMvDigitalAudioParameter description.
   bool     bAesEbuAudioTimeBaseDetected;    // Specifies if the clocks were detected from the AES/EBU input(s).
   bool     bEmbeddedAudioTimeBaseDetected;  // Specifies if the clocks were detected from the embedded audio input(s).
};

//
// Summary:
//    Returns event names on the audio output engine.
//
struct SMvAudioPlaybackNotifications
{
   uint32_t size;                      // Structure size in bytes.
   char     szStartSilenceEvent[32];   // A sting returning the name of the event that is going to be 
                                          // pulsed when the output starts to play silence.
   char     szStopSilenceEvent[32];    // A sting returning the name of the event that is going to be 
                                          // pulsed when the output stops playing silence.
};

//
// Summary:
//    Specifies the background color that fills the region outside of the output rectangle.
//
struct SMvBackgroundColor
{
   uint32_t  size;       // Structure size in bytes.
   unsigned long  ulYValue;   // Background color luminance value. Range is 16 to 235.
   unsigned long  ulCbValue;  // Background color luminance Cb value. Range is 16 to 240.
   unsigned long  ulCrValue;  // Background color luminance Cr value. Range is 16 to 240.
};

//
// Summary:
//    Returns or programs the first three bytes of the audio channel status (AES or embedded audio).
//
struct SMvDigitalAudioChannelStatus
{
   uint32_t size;                // Structure size in bytes.
   uint8_t  ui8ChStatusByte0;    // Channel status byte 0. See AES3 specification for more info about this byte.
   uint8_t  ui8ChStatusByte1;    // Channel status byte 1. See AES3 specification for more info about this byte.
   uint8_t  ui8ChStatusByte2;    // Channel status byte 2. See AES3 specification for more info about this byte.
};

//
// Summary:
//    Retrieves information about the current state of the DVI output.
//
struct SMvDviStatus
{
   uint32_t       size;          // Structure size in bytes.
   EMvDviStatus   eDviStatus;    // Current status of the DVI output.
};

//
// Summary:
//    Describes information about embedded audio.
//
struct SMvEmbeddedAudioInfo
{
   uint32_t                   size;                            // Structure size in bytes.
   EMvEmbeddedAudioPair       eSupportedEmbeddedAudioPairs;    // A bitwise enumeration that
                                                                  // indicates all the supported 
                                                                  // embedded audio pairs.
   EMvEmbeddedAudioGroup      eSupportedEmbeddedAudioGroups;   // A bitwise enumeration that 
                                                                  // indicates all the supported 
                                                                  // embedded audio groups
};

//
// Summary:
//    Returns the genlock status.
//
struct SMvEmbeddedAudioStatus
{
   uint32_t                size;                // Structure size in bytes.
   bool                    bGroup1Pair1Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup1Pair1CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup1Pair2Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup1Pair2CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup2Pair1Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup2Pair1CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup2Pair2Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup2Pair2CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup3Pair1Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup3Pair1CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup3Pair2Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup3Pair2CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup4Pair1Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup4Pair1CSInfo;  // Specifies the channel status informations for the group and pair.
   bool                    bGroup4Pair2Present; // TRUE if there is an audio signal on the group and pair.
   EMvEAChannelStatusInfo  eGroup4Pair2CSInfo;  // Specifies the channel status informations for the group and pair.
};

//
// Summary:
//    Describes information about genlock.
//
struct SMvGenlockInfo
{
   uint32_t          size;                      // Structure size in bytes.
   EMvGenlockSource  eSupportedGenlockSources;  // A bitwise enumeration that indicates all 
                                                   // supported video genlock sources.
};

//
// Summary:
//    Returns the genlock status.
//
struct SMvGenlockStatus
{
   uint32_t          size;             // Structure size in bytes.
   EMvGenlockSource  eGenlockSource;   // Returns the currently selected genlock source.
   EMvGenlockState   eGenlockState;    // Returns the state of the genlock circuit.
   bool              bAutoDetectGenlockSourceValid;      // Indicates if there is a valid auto-detected genlock resolution.
   SMvResolutionInfo sAutoDetectGenlockSourceResolution; // Returns the auto-detected genlock resolution.
   bool              bAutoDetectBlackBurstValid;     // Indicates if there is a valid auto-detected black burst resolution.
   SMvResolutionInfo sAutoDetectBlackBurstResolution;// Returns the auto-detected black burst resolution.
};

struct SMvHdmiGainMatricesData
{
	uint32_t          size;                  // Structure size in bytes.
	uint16_t		  aui16GainMatrixSD[12]; // Matrix for the gain coefficients in SD colorimetry.
	uint16_t		  aui16GainMatrixHD[12]; // Matrix for the gain coefficients in HD colorimetry.
	bool			  bSetSDMatrix;			 // If true set SD matrix, otherwise set HD matrix
};

struct SMvHdmi3DFlagData
{
   bool						bEnabled;		// Indicate if the HDMI 3D is enabled or disabled
   EMvHDMI3DVideoFormatEnum	eHDMI3DFormat;  // Enum to know at what 3D type we must set the registers
};

//
// Summary:
//    Retrieves or controls the gamma correction tables on a RGB output.
//
struct SMvGammaCorrectionData
{
   uint32_t          size;             // Structure size in bytes.
   EMvColorSelect    eColorSelect;     // Indicates the color components that will be affected by the call.
   uint8_t           aui8Red[256];     // Gamma table for the red color component.
   uint8_t           aui8Green[256];   // Gamma table for the green color component.
   uint8_t           aui8Blue[256];    // Gamma table for the blue color component.
};

//
// Summary:
//    Retrieves or controls the color correction tables on a RGB output.
//
struct SMvColorCorrectionData
{
	uint32_t          size;             // Structure size in bytes.
	bool			  bByPass;			// Indicate if the color correction is bypass or not.
	bool			  bClipping;		// Indicate if we clip super white and super black.
	EMvColorimetry	  eColorimetry;     // Indicate the colorimetry (ITU709 or ITU601).
	EMvColorSelect    eColorSelect;     // Indicates the color components that will be affected by the call.
	uint16_t          aui16Red[1024];   // Color table for the red color component.
	uint16_t          aui16Green[1024];	// Color table for the green color component.
	uint16_t          aui16Blue[1024];  // Color table for the blue color component.
};

//
// Summary:
//    Returns the cable identifier.
//
struct SMvCableID
{
   uint32_t    size;       // Structure size in bytes.
   EMvCableID  eCableID;   // Returns the cable identifier.
};

//
// Summary:
//    Returns the number of all types of devices.
//
struct SMvDeviceCount
{
   uint32_t       size;                                  // Structure size in bytes.
   unsigned int   uiNumberOfVideoCaptureDevices;         // Returns the number of video capture devices.
   unsigned int   uiNumberOfVideoPlaybackDevices;        // Returns the number of video playback devices.
   unsigned int   uiNumberOfAudioCaptureDevices;         // Returns the number of audio capture devices.
   unsigned int   uiNumberOfAudioPlaybackDevices;        // Returns the number of audio playback devices.
   unsigned int   uiNumberOfIODevices;                   // Returns the number of input/output devices.
   unsigned int   uiNumberOfAudioVoiceOverMixerDevices;  // Returns the number of voice-over mixer devices. 
};

//
// Summary:
//    Returns the status of the cooling fan.
//
struct SMvFanStatus
{
   uint32_t       size;    // Structure size in bytes.
   EMvFanStatus   eStatus; // Returns an enumeration value that describes the status of the fan.
};

//
// Summary:
//    Returns the PCI count.
//
struct SMvPCICount
{
   uint32_t       size;          // Structure size in bytes.
   uint32_t       ui32PCICount;  // Returns The PCI count.
};

//
// Summary:
//    Returns the memory status of the X.effects card.
//
struct SMvMemStatus
{
   uint32_t       size;    // Structure size in bytes.
   EMvMemStatus   eStatus; // Returns an enumeration value that describes the status of the memory.
};

//
// Summary:
//    Returns information about the general status of the hardware.
//
struct SMvGeneralHardwareStatus
{
   uint32_t                   size;    // Structure size in bytes.
   EMvGeneralHardwareStatus   eStatus; // Returns an enumeration value that describes the general status of the hardware.
};

//
// Summary:
//    Returns the model of the hardware.
//
struct SMvHardwareFlavorInformation
{
   uint32_t	         size;                   // Structure size in bytes.
   EMvHardwareSerie	eHardwareSerieDetected; // Returns an enumeration value of the detected model.
};

//
// Summary:
//    Describes information about an enumerated hardware profile.
//
struct SMvEnumHardwareProfileInfo
{
   uint32_t                   size;                   // Structure size in bytes.
   SMvHardwareProfileInfo     sHardwareProfileInfo;   // Structure that describes basic information about 
                                                         // the enumerated hardware profile.
   bool                       bIsAvailable;           // Indicates whether or not the hardware profile 
                                                         // is available. A software-only profile and a 
                                                         // helper profile are always available.  Some 
                                                         // hardware profiles will always be available 
                                                         // because they support multiple Open operations.
                                                         // Some hardware profiles with exclusive use of a 
                                                         // resource (such as the X.effects card) do not
                                                         // support multiple Open operations and will be 
                                                         // unavailable when the profile is already in use.
   int                        iXLinkID;               // Indicates the device index to use when controlling
                                                         // the X.link device. A value of -1 indicates 
                                                         // that there is no X.link present.
   int                        iXLinkHDID;             // Indicates the device index to use when controlling 
                                                         // the X.linkHD device. A value of -1 indicates
                                                         // that there is no X.linkHD present.
   EMvHardwareSerie           eHardwareSerie;         // Describes the hardware present.
};


//
// Summary:
//   Returns all information strings.
//
struct SMvInformationParameter
{
   uint32_t size;                      // Structure size in bytes.
   char  	szInformationString[128];  // Receives the string.
};

//
// Summary:
//    Describes a range for an input/output parameter.
//
struct SMvIORange
{
   uint32_t size;                   // Structure size in bytes.
   char     szUnit[32];             // String that indicates the parameter unit.
   double   dMinimum;               // Indicates the minimum possible value of the parameter.
   double   dMaximum;               // Indicates the maximum possible value of the parameter.
   double   dSuggestedGranularity;  // Indicates the suggested granularity to pass through the entire 
                                       // range of the parameter.
   double   dHardwareGranularity;   // Indicates the real hardware granularity of the parameter.
   double   dDefaultFactory;        // Indicates the default value of the parameter.
};

//
// Summary:
//    Returns miscellaneous information about the device.
//
struct SMvMiscInfo
{
   uint32_t        	         size;                                  // Structure size in bytes.
   EMvIODeviceID              eIODeviceID;                           // Returns the I/O device identifier.
   char                       szIODeviceName[32];                    // Returns the I/O device English name.
   char                       szIODeviceOption[32];                  // Returns the I/O device English 
                                                                        // option(s) installed.
   EMvVideoIOChannel          eSupportedVideoInputChannels;          // A bitwise enumeration that indicates 
                                                                        // all supported video channel(s) at the input.
   EMvVideoIOChannel          eSupportedVideoOutputChannels;         // A bitwise enumeration that indicates
                                                                        // all supported video channel(s) at the output.
   EMvAudioCaptureChannel		eSupportedAudioCaptureChannels;        // A bitwise enumeration that indicates
                                                                        // all supported video capture channel(s).
   EMvAudioPlaybackChannel		eSupportedAudioPlaybackChannels;       // A bitwise enumeration that indicates
                                                                        // all supported video playback channel(s).
   EMvEmbeddedAudioIOChannel  eSupportedEAInputChannels;             // A bitwise enumeration of all supported
                                                                        // embedded audio channel(s) at the input.
   EMvEmbeddedAudioIOChannel  eSupportedEAOutputChannels;            // A bitwise enumeration of all supported
                                                                        // embedded audio channel(s) at the output.
   EMvAudioIOChannel				eSupportedAnalogAudioInputChannels;    // A bitwise enumeration of all supported
                                                                        // analog audio channel(s) at the input.
   EMvAudioIOChannel          eSupportedAnalogAudioOutputChannels;   // A bitwise enumeration of all supported
                                                                        // analog audio channel(s) at the output.
   EMvAesEbuAudioIOChannel    eSupportedAesEbuInputChannels;         // A bitwise enumeration of all supported
                                                                        // AES/EBU audio channel(s) at the input.
   EMvAesEbuAudioIOChannel    eSupportedAesEbuOutputChannels;        // A bitwise enumeration of all supported
                                                                        // AES/EBU audio channel(s) at the output.
   EMvHdmiAudioIOChannel      eSupportedHdmiAudioInputChannels;      // A bitwise enumeration of all supported
                                                                        // HDMI audio channel(s) at the input.
   EMvHdmiAudioIOChannel      eSupportedHdmiAudioOutputChannels;     // A bitwise enumeration of all supported
                                                                        // HDMI audio channel(s) at the output.
};

//
// Summary:
//    Describes a two-dimensional point in which axis values are expressed as integers.
// Remarks:
// - The 0,0 coordinate is centered in the image.
// - Only valid for the compositor and buffer-based hardware in-line mixer.
//
struct SMvPoint
{
   int32_t lX;    // Coordinate of the X point. The positive direction points to the right.
   int32_t lY;    // Coordinate of the Y point.The positive direction points to the top.
};

//
// Summary:
//    Returns information about the power status of a device.
//
struct SMvPowerInformation
{
   uint32_t	      size;          // Structure size in bytes.
   EMvPowerStatus	ePowerStatus;  // An enumeration value that describes the status of power.
};

//
// Summary:
//    Controls input and output resolutions to ensure hardware stability when a device must
//    change both resolutions at the same time.
//
struct SMvInputOutputResolutions
{
   uint32_t          size;                // Structure size in bytes.
   SMvResolutionInfo sInputResolution;    // Structure containing the input resolution to control or 
                                             // the one that that is filled with the requested value.
   SMvResolutionInfo sOutputResolution;   // Structure containing the output resolution to control or
                                             // the one that will be filled with the requested value.
};

//
// Summary:
//    Controls default input, output, and genlock resolutions to ensure hardware stability when
//    a device must change all of them at the same time.
//
struct SMvDefaultResolutions
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sGenlockResolution;        // Structure containing the genlock resolution 
                                                            // to control or the structure that is filled 
                                                            // with the requested resolution.
   SMvInputOutputResolutions  sInputOutputResolutions;   // Structure containing the input and output 
                                                            // resolutions to control or the structure 
                                                            // that is filled with the requested resolution.
};

//
// Summary:
//    Returns all the necessary information to add to a notification (event). The information is filled
//    following the passed notification identifier.
//
struct SMvNotification
{
   uint32_t          size;                   // Structure size in bytes.
   EMvNotificationID eNotificationID;        // Passes the notification identifier that the user wants
                                                // information about.
   char              szNotificationName[32]; // Returns the notification name. This name must be passed 
                                                // to the OpenEvent() function to get notified.
};

//
// Summary:
//    Describes a two-dimensional rectangle. Axis values are integer.
//
struct SMvRect
{
   int32_t lLeft;    // Left coordinate of the rectangle.
   int32_t lTop;     // Top coordinate of the rectangle.
   int32_t lRight;   // Right coordinate of the rectangle.
   int32_t lBottom;  // Bottom coordinate of the rectangle.
};

//
// Summary:
//    Describes a two-dimensional rectangle. Axis values are floating point.
//
struct SMvRectF
{
   float fLeft;   // Left coordinate of the rectangle.
   float fTop;    // Top coordinate of the rectangle.
   float fRight;  // Right coordinate of the rectangle.
   float fBottom; // Bottom coordinate of the rectangle.
};


//
// Summary:
//    Describes temperature sensor information for the DSX hardware.
//
struct SMvTemperatureInformation
{
   EMvTemperatureSensorID	eTemperatureID;               // Temperature sensor ID information for a particular DSX hardware.
   double	 	            dTemperature;                 // Current operating temperature for the specified temperature sensor.
   double	 	            dTemperatureErrorThreshold;   // Recommended maximum operating temperature for the specified temperature sensor.
                                                          // A warning is issued when the threshold is exceeded.
   double	 	            dMaxRecordedTemperature;      // Maximum recorded temperature for the specified temperature sensor.														
   EMvCoolingFanStatus     eFanStatus;                   // Current cooling fan status.
};

//
// Summary:
//    Returns information about the video channel controlled by a video device.
//
struct SMvVideoDeviceInfo
{
   uint32_t             size;             // Structure size in bytes.
   EMvVideoIOChannel    eVideoIOChannel;  // Indicates the video I/O channel.
};

//
// Summary:
//    Returns video input/output information.
//
struct SMvVideoIOInfo
{
   uint32_t          size;                         // Structure size in bytes.
   EMvVideoSignal    eSupportedVideoSignalInputs;  // A bitwise enumeration that indicates all supported video signals at the input.
   EMvVideoSignal    eSupportedVideoSignalOutputs; // A bitwise enumeration that indicates all supported video signals at the output.
};

//
// Summary:
//    Selects the video source that will be sent to a video output.
//
struct SMvVideoOutputSource
{
   uint32_t                size;          // Structure size in bytes.
   EMvVideoOutputSelect    eOutputSelect; // Selects the video output.
   EMvVideoOutputSource    eSource;       // Selects the video source that will be sent to the video output.
};

//
// Summary:
//    Returns event names on the video output engine.
//
struct SMvVideoPlaybackNotifications
{
   uint32_t size;                      // Structure size in bytes.
   char     szStartRepeatingEvent[32]; // An array containing a string that returns the name of the event that is going to
                                          // be pulsed when the output starts to repeat.
   char     szStopRepeatingEvent[32];  // An array containing a string that returns the name of the event that is going to
                                          // be pulsed when the output stops repeating.
};

//
// Summary:
//    Returns the video status.
//
struct SMvVideoStatus
{
   uint32_t          size;                         // Structure size in bytes.
   EMvVideoSignal    eSelectedVideoSignal;         // Returns the currently selected input signal.
   bool              bIsVideoPresent;              // Indicates if there is a valid video stream at the input.
   SMvResolutionInfo sInputResolution;             // Returns the current input resolution.
   SMvResolutionInfo sOutputResolution;            // Returns the current output resolution.
   bool              bInputResolutionMismatch;     // Indicates if there is a mismatch between the selected
                                                      // resolution and the video stream resolution at the input 
                                                      // (supported for SDI video only with DSX LE, DSX SD, and 
                                                      // the X.linkSD and X.linkHD breakout boxes). 
   bool              bCopyProtected;               // Indicates if the video stream at the input is protected with 
                                                      // Macrovision (supported for analog video only with DSX LE, 
                                                      // DSX SD, RT.X2, and the X.linkSD breakout box).
   bool              bAutoDetectInputValid;        // Indicates if there is a valid auto-detected resolution 
                                                      // (supported for X.mio2 only).
   SMvResolutionInfo sAutoDetectInputResolution;   // Returns the auto-detected input resolution (supported for X.mio2 only).
   bool              bInputSMPTE352PayloadIdValid; // Indicates that the SMPTE352 payload is valid (supported for X.mio2 only).
   USMPTE352Id       uInputSMPTE352Id;             // Returns the SMPTE352 payload identifier (supported for X.mio2 only).
};

//
// Summary:
//    Describes the status of a video connector.
//
struct SMvVideoConnectorStatus
{
   uint32_t          ui32Size;                     // Structure size in bytes.
   SMvResolutionInfo sDetectedResolution;          // Describes the resolution detected in the input signal.
   bool              bIsVideoPresent;              // If true, video data is present in the input signal.
   bool              bIsInputFlyWheelLocked;       // If true, the input flywheel is locked.
   bool              bIsSMPTE352PayloadIdValid;    // If true, the SMPTE 352 payload ID is valid.
   USMPTE352Id       uSMPTE352PayloadId;           // Returns the SMPTE 352 payload ID.
};

//
// Summary:
//    Returns the status of an X.link device.
//
struct SMvXlinkStatus
{
   uint32_t       size;    // Structure size in bytes.
   EMvXlinkStatus eStatus; // The value that describes the status of the X.link device.
};

//
// Summary:
//    Specifies the X.scaler processing parameters.
//
struct SMvXScalerParameters
{
   uint32_t         size;              // Structure size in bytes.
   unsigned long    ulNoiseReduction;  // Controls the X.scaler motion-adaptive noise reduction hardware.
                                          // This functionality specifically targets regions where noise is
                                          // present and has less effect on images without noise. A higher
                                          // value removes more noise but increases blurring of the image.
                                          // A zero value disables the noise reduction functionality. The
                                          // range of this parameter is 0 to 31. The default value is
                                          // zero (disabled).
   unsigned long    ulDetailEnh;       // Controls the X.scaler detail enhancement hardware. A higher
                                          // value increases image details' crispness. A zero value 
                                          // disables the detail enhancement functionality. The range
                                          // of this parameter is 0 to 31. This control is useful when
                                          // you need to restore sharpness of details that was lost
                                          // because of noise reduction and/or filtering. The default
                                          // value is zero (disabled).
   EMvFilterSelect  eFilterSelect;     // Selects the video filter frequency response (see EMvFilterSelect
                                          // description for more details). This filtering is constant 
                                          // on all images. The filtering is applied after noise reduction
                                          // and detail enhancement. The default value of this parameter
                                          // is keMvFilterSelectNormal. 
};


//
// Summary:
//    Describes an I, B, or P frame inside its group of pictures (GOP).
// Remarks:
// - If you are using the DSX.sdk API, the data is attached to the surface and is not copied by the IMvFlexEngine::CopySurface() method. 
//   It is the responsibility of the user application to propagate the information through its sequencing 
//   pipeline. 
//
// - If you are using the M264 decoder in access unit aligned mode, you will need to initialize the ulDisplayPosition member
//   in order for the decoder to accurately report the number of skipped pictures when there is corruption in the stream.  
//   If the surfaces are obtained from the Matrox MPEG2 TS Demuxer then this value will already be set.  
struct SMvGroupOfPicturesFrame
{
   public:
   uint32_t          size;                // Specifies the structure size, in bytes.
   unsigned long     ulDisplayPosition;   // For AVC, this is an absolute display position from stream start. 
                                             // For MPEG-2, this is Frame's relative position inside the GOP, in chronological order.
   unsigned long     ulCodedOrder;        // For AVC, this is an absolute coded order from stream start. 
                                             // For MPEG-2, Frame's encoded position inside the GOP, may differ from. the chronological order
   unsigned long     ulByteOffset;        // Frame's offset in bytes inside the GOP.
   unsigned long     ulSize;              // Frame's size in bytes inside the GOP.
   EMvMpegFrameType  eType;               // Type of frame (I, B, or P frame).
   bool              bOpenGOP;

//    SMvGroupOfPicturesFrame()
//    : size(sizeof(SMvGroupOfPicturesFrame))
//    , ulDisplayPosition(0)
//    , ulCodedOrder(0)
//    , ulByteOffset(0)
//    , ulSize(0)
//    , eType(keMvMpegFrameTypeInvalid)
//    , bOpenGOP(false)
//    {
//    }

//    SMvGroupOfPicturesFrame
//    (
//       uint32_t          in_size = sizeof(SMvGroupOfPicturesFrame),
//       unsigned long     in_ulDisplayPosition = 0,
//       unsigned long     in_ulCodedOrder = 0, 
//       unsigned long     in_ulByteOffset = 0,
//       unsigned long     in_ulSize = 0,
//       EMvMpegFrameType  in_eType = keMvMpegFrameTypeInvalid,
//       bool              in_bOpenGOP = false
//    )
//       : size(in_size)
//       , ulDisplayPosition(in_ulDisplayPosition)
//       , ulCodedOrder(in_ulCodedOrder)
//       , ulByteOffset(in_ulByteOffset)
//       , ulSize(in_ulSize)
//       , eType(in_eType)
//       , bOpenGOP(in_bOpenGOP)
//    {
//    }

//    SMvGroupOfPicturesFrame
//       (
//       std::initializer_list<uint32_t> list
//       )
//    : size(sizeof(SMvGroupOfPicturesFrame))
//    , ulDisplayPosition(0)
//    , ulCodedOrder(0)
//    , ulByteOffset(0)
//    , ulSize(0)
//    , eType(keMvMpegFrameTypeInvalid)
//    , bOpenGOP(false)
//    {
//       int   counter = 0;
//       for (auto i = list.begin(); i != list.end(); i++)
//       {
//          switch (counter)
//          {
//          case 0:
//             size = (*i);
//             break;
//          case 1:
//             ulDisplayPosition = (unsigned long)(*i);
//             break;
//          case 2:
//             ulCodedOrder = (unsigned long)(*i);
//             break;
//          case 3:
//             ulByteOffset = (unsigned long)(*i);
//             break;
//          case 4:
//             ulSize = (unsigned long)(*i);
//             break;
//          case 5:
//             eType = (EMvMpegFrameType)(*i);
//             break;
//          case 6:
//             bOpenGOP = (*i) ? true : false;
//             break;
//          }
//          counter++;
//       }
//    }

};

//
// Summary
//    Specifies the possible identifiers when connecting the MXO or XDVI device to the computer.
//
struct SMvDVIConnectionsIdentifiers
{
   uint32_t size;                      // Specifies the structure size, in bytes.
   uint32_t ui32GDIDisplayDeviceIndex; // Specifies the adaptor that the MXO is connected to (primary 0, secondary 1, etc.). 
                                          // This is the second parameter passed to a GDI EnumDisplayDevices call, when the 
                                          // first parameter is NULL.                                          
   uint32_t ui32GDIMonitorIndex;       // Identifies the monitor index on the specified adapter. This is the second parameter 
                                          // passed to a GDI EnumDisplayDevices call, when the the first parameter is set to 
                                          // the display device name (DISPLAY_DEVICE.DeviceString).                                         
   uint32_t ui32ControlPanelMonitorID; // Specifies how the monitor identifier appears in the Windows 
                                          // "Control Panel / Display options" dialog box, when the <I>Identify</I> button is clicked.
};



//
// Summary
//    Specifies the color to place in the bar area (can be used for letterbox or pillarbox bars).
//
struct SMvBarColor
{
    uint32_t  size;    // Structure size in bytes.
    unsigned long  ulBitCount; // Can be 8 or 10.
    unsigned long  ulYValue;   // Background color luminance value. Range is 16 to 235 if bit count is 8.
    unsigned long  ulCbValue;  // Background color luminance Cb value. Range is 16 to 240 if bit count is 8. 
    unsigned long  ulCrValue;  // Background color luminance Cr value.  Range is 16 to 240 if bit count is 8.
};


//
// Summary
//    Specifies the configuration of the X.RIO module. 
//
struct SMvRIOConfigurationInfo
{
   unsigned long ulNumberOfInputs;  // Number of inputs.  
   unsigned long ulNumberOfOutputs; // Number of outputs.   
};


//
// Summary:
//    Enumerates each video hardware connector on the card.
//
enum EMvVideoConnectorLabel
{
   keMvVideoConnectorLabelInvalid,  // Invalid value.
   keMvVideoConnectorLabelSdiInA,   // The video connector is SDI input A.
   keMvVideoConnectorLabelSdiInB,   // The video connector is SDI input B.
   keMvVideoConnectorLabelSdiInC,   // The video connector is SDI input C.
   keMvVideoConnectorLabelSdiInD,   // The video connector is SDI input D.
   keMvVideoConnectorLabelSdiInE,   // The video connector is SDI input E.
   keMvVideoConnectorLabelSdiInF,   // The video connector is SDI input F.
   keMvVideoConnectorLabelSdiInG,   // The video connector is SDI input G.
   keMvVideoConnectorLabelSdiInH,   // The video connector is SDI input H.
   keMvVideoConnectorLabelSdiInI,   // The video connector is SDI input I.
   keMvVideoConnectorLabelSdiInJ,   // The video connector is SDI input J.
   keMvVideoConnectorLabelSdiInK,   // The video connector is SDI input K.
   keMvVideoConnectorLabelSdiInL,   // The video connector is SDI input L.
   keMvVideoConnectorLabelLastInput,// End of list indicator for the SDI input labels.

   keMvVideoConnectorLabelSdiOutA=1000, // The video connector is SDI output A.
   keMvVideoConnectorLabelSdiOutB,      // The video connector is SDI output B.
   keMvVideoConnectorLabelSdiOutC,      // The video connector is SDI output C.
   keMvVideoConnectorLabelSdiOutD,      // The video connector is SDI output D.
   keMvVideoConnectorLabelSdiOutE,      // The video connector is SDI output E.
   keMvVideoConnectorLabelSdiOutF,      // The video connector is SDI output F.
   keMvVideoConnectorLabelSdiOutG,      // The video connector is SDI output G.
   keMvVideoConnectorLabelSdiOutH,      // The video connector is SDI output H.
   keMvVideoConnectorLabelSdiOutI,      // The video connector is SDI output I.
   keMvVideoConnectorLabelSdiOutJ,      // The video connector is SDI output J.
   keMvVideoConnectorLabelSdiOutK,      // The video connector is SDI output K.
   keMvVideoConnectorLabelSdiOutL,      // The video connector is SDI output L.
   keMvVideoConnectorLabelLast,          // End of list indicator for the SDI output labels.

   keMvVideoConnectorLabelSdiIpInA = 2000,   // The video connector is input A for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInB,          // The video connector is input B for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInC,          // The video connector is input C for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInD,          // The video connector is input D for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInE,          // The video connector is input E for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInF,          // The video connector is input F for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInG,          // The video connector is input G for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInH,          // The video connector is input H for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInI,          // The video connector is input I for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInJ,          // The video connector is input J for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInK,          // The video connector is input K for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInL,          // The video connector is input L for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInM,          // The video connector is input M for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInN,          // The video connector is input N for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInO,          // The video connector is input O for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInP,          // The video connector is input P for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpInLast,       // End of list indicator for the input labels for an IP stream conforming to SMPTE 2022-6.

   keMvVideoConnectorLabelSdiIpOutA = 3000,  // The video connector is output A for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutB,         // The video connector is output B for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutC,         // The video connector is output C for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutD,         // The video connector is output D for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutE,         // The video connector is output E for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutF,         // The video connector is output F for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutG,         // The video connector is output G for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutH,         // The video connector is output H for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutI,         // The video connector is output I for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutJ,         // The video connector is output J for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutK,         // The video connector is output K for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutL,         // The video connector is output L for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutM,         // The video connector is output M for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutN,         // The video connector is output N for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutO,         // The video connector is output O for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutP,         // The video connector is output P for an IP stream conforming to SMPTE 2022-6.
   keMvVideoConnectorLabelSdiIpOutLast,      // End of list indicator for the output labels for an IP stream conforming to SMPTE 2022-6.

   keMvVideoConnectorLabelAspenVideoInA = 4000,   // The video connector is video input A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInB,          // The video connector is video input B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInC,          // The video connector is video input C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInD,          // The video connector is video input D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInE,          // The video connector is video input E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInF,          // The video connector is video input F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInG,          // The video connector is video input G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInH,          // The video connector is video input H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInI,          // The video connector is video input I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInJ,          // The video connector is video input J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInK,          // The video connector is video input K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInL,          // The video connector is video input L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInM,          // The video connector is video input M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInN,          // The video connector is video input N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInO,          // The video connector is video input O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInP,          // The video connector is video input P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoInLast,       // End of list indicator for the video input labels for an IP stream conforming to the ASPEN protocol.

   keMvVideoConnectorLabelAspenVideoOutA = 4100,  // The video connector is video output A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutB,         // The video connector is video output B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutC,         // The video connector is video output C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutD,         // The video connector is video output D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutE,         // The video connector is video output E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutF,         // The video connector is video output F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutG,         // The video connector is video output G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutH,         // The video connector is video output H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutI,         // The video connector is video output I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutJ,         // The video connector is video output J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutK,         // The video connector is video output K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutL,         // The video connector is video output L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutM,         // The video connector is video output M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutN,         // The video connector is video output N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutO,         // The video connector is video output O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutP,         // The video connector is video output P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVideoOutLast,      // End of list indicator for the video output labels for an IP stream conforming to the ASPEN protocol.

   keMvVideoConnectorLabelAspenAudioInA = 4200,   // The video connector is audio input A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInB,          // The video connector is audio input B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInC,          // The video connector is audio input C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInD,          // The video connector is audio input D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInE,          // The video connector is audio input E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInF,          // The video connector is audio input F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInG,          // The video connector is audio input G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInH,          // The video connector is audio input H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInI,          // The video connector is audio input I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInJ,          // The video connector is audio input J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInK,          // The video connector is audio input K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInL,          // The video connector is audio input L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInM,          // The video connector is audio input M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInN,          // The video connector is audio input N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInO,          // The video connector is audio input O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInP,          // The video connector is audio input P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioInLast,       // End of list indicator for the audio input labels for an IP stream conforming to the ASPEN protocol.

   keMvVideoConnectorLabelAspenAudioOutA = 4300,  // The video connector is audio output A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutB,         // The video connector is audio output B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutC,         // The video connector is audio output C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutD,         // The video connector is audio output D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutE,         // The video connector is audio output E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutF,         // The video connector is audio output F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutG,         // The video connector is audio output G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutH,         // The video connector is audio output H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutI,         // The video connector is audio output I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutJ,         // The video connector is audio output J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutK,         // The video connector is audio output K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutL,         // The video connector is audio output L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutM,         // The video connector is audio output M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutN,         // The video connector is audio output N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutO,         // The video connector is audio output O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutP,         // The video connector is audio output P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenAudioOutLast,      // End of list indicator for the audio output labels for an IP stream conforming to the ASPEN protocol.

   keMvVideoConnectorLabelAspenVancInA = 4400,   // The video connector is ancillary data input A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInB,          // The video connector is ancillary data input B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInC,          // The video connector is ancillary data input C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInD,          // The video connector is ancillary data input D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInE,          // The video connector is ancillary data input E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInF,          // The video connector is ancillary data input F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInG,          // The video connector is ancillary data input G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInH,          // The video connector is ancillary data input H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInI,          // The video connector is ancillary data input I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInJ,          // The video connector is ancillary data input J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInK,          // The video connector is ancillary data input K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInL,          // The video connector is ancillary data input L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInM,          // The video connector is ancillary data input M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInN,          // The video connector is ancillary data input N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInO,          // The video connector is ancillary data input O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInP,          // The video connector is ancillary data input P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancInLast,       // End of list indicator for the ancillary data input labels for an IP stream conforming to the ASPEN protocol.

   keMvVideoConnectorLabelAspenVancOutA = 4500,  // The video connector is ancillary data output A for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutB,         // The video connector is ancillary data output B for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutC,         // The video connector is ancillary data output C for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutD,         // The video connector is ancillary data output D for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutE,         // The video connector is ancillary data output E for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutF,         // The video connector is ancillary data output F for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutG,         // The video connector is ancillary data output G for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutH,         // The video connector is ancillary data output H for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutI,         // The video connector is ancillary data output I for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutJ,         // The video connector is ancillary data output J for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutK,         // The video connector is ancillary data output K for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutL,         // The video connector is ancillary data output L for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutM,         // The video connector is ancillary data output M for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutN,         // The video connector is ancillary data output N for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutO,         // The video connector is ancillary data output O for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutP,         // The video connector is ancillary data output P for an IP stream conforming to the ASPEN protocol.
   keMvVideoConnectorLabelAspenVancOutLast,       // End of list indicator for the ancillary data output labels for an IP stream conforming to the ASPEN protocol.
   
   keMvVideoConnectorLabelIpVideoInA = 5000,   // The video connector is video input A for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInB,          // The video connector is video input B for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInC,          // The video connector is video input C for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInD,          // The video connector is video input D for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInE,          // The video connector is video input E for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInF,          // The video connector is video input F for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInG,          // The video connector is video input G for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInH,          // The video connector is video input H for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInI,          // The video connector is video input I for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInJ,          // The video connector is video input J for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInK,          // The video connector is video input K for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInL,          // The video connector is video input L for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInM,          // The video connector is video input M for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInN,          // The video connector is video input N for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInO,          // The video connector is video input O for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInP,          // The video connector is video input P for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoInLast,       // End of list indicator for the video input labels for an IP stream conforming to the SMPTE 2110-20 draft version.

   keMvVideoConnectorLabelIpVideoOutA = 5100,  // The video connector is video output A for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutB,         // The video connector is video output B for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutC,         // The video connector is video output C for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutD,         // The video connector is video output D for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutE,         // The video connector is video output E for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutF,         // The video connector is video output F for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutG,         // The video connector is video output G for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutH,         // The video connector is video output H for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutI,         // The video connector is video output I for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutJ,         // The video connector is video output J for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutK,         // The video connector is video output K for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutL,         // The video connector is video output L for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutM,         // The video connector is video output M for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutN,         // The video connector is video output N for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutO,         // The video connector is video output O for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutP,         // The video connector is video output P for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvVideoConnectorLabelIpVideoOutLast,      // End of list indicator for the video output labels for an IP stream conforming to the SMPTE 2110-20 draft version.

   keMvVideoConnectorLabelIpAudioInA = 5200,   // The video connector is audio input A for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInB,          // The video connector is audio input B for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInC,          // The video connector is audio input C for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInD,          // The video connector is audio input D for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInE,          // The video connector is audio input E for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInF,          // The video connector is audio input F for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInG,          // The video connector is audio input G for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInH,          // The video connector is audio input H for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInI,          // The video connector is audio input I for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInJ,          // The video connector is audio input J for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInK,          // The video connector is audio input K for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInL,          // The video connector is audio input L for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInM,          // The video connector is audio input M for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInN,          // The video connector is audio input N for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInO,          // The video connector is audio input O for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInP,          // The video connector is audio input P for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioInLast,       // End of list indicator for the audio input labels for an IP stream conforming to the SMPTE 2110-30 draft version.

   keMvVideoConnectorLabelIpAudioOutA = 5300,  // The video connector is audio output A for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutB,         // The video connector is audio output B for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutC,         // The video connector is audio output C for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutD,         // The video connector is audio output D for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutE,         // The video connector is audio output E for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutF,         // The video connector is audio output F for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutG,         // The video connector is audio output G for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutH,         // The video connector is audio output H for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutI,         // The video connector is audio output I for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutJ,         // The video connector is audio output J for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutK,         // The video connector is audio output K for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutL,         // The video connector is audio output L for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutM,         // The video connector is audio output M for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutN,         // The video connector is audio output N for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutO,         // The video connector is audio output O for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutP,         // The video connector is audio output P for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvVideoConnectorLabelIpAudioOutLast,      // End of list indicator for the audio output labels for an IP stream conforming to the SMPTE 2110-30 draft version.

   keMvVideoConnectorLabelIpAncInA = 5400,   // The video connector is ancillary data input A for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInB,          // The video connector is ancillary data input B for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInC,          // The video connector is ancillary data input C for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInD,          // The video connector is ancillary data input D for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInE,          // The video connector is ancillary data input E for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInF,          // The video connector is ancillary data input F for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInG,          // The video connector is ancillary data input G for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInH,          // The video connector is ancillary data input H for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInI,          // The video connector is ancillary data input I for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInJ,          // The video connector is ancillary data input J for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInK,          // The video connector is ancillary data input K for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInL,          // The video connector is ancillary data input L for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInM,          // The video connector is ancillary data input M for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInN,          // The video connector is ancillary data input N for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInO,          // The video connector is ancillary data input O for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInP,          // The video connector is ancillary data input P for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncInLast,       // End of list indicator for the ancillary data input labels for an IP stream conforming to the SMPTE 2110-40 draft version.

   keMvVideoConnectorLabelIpAncOutA = 5500,  // The video connector is ancillary data output A for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutB,         // The video connector is ancillary data output B for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutC,         // The video connector is ancillary data output C for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutD,         // The video connector is ancillary data output D for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutE,         // The video connector is ancillary data output E for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutF,         // The video connector is ancillary data output F for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutG,         // The video connector is ancillary data output G for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutH,         // The video connector is ancillary data output H for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutI,         // The video connector is ancillary data output I for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutJ,         // The video connector is ancillary data output J for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutK,         // The video connector is ancillary data output K for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutL,         // The video connector is ancillary data output L for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutM,         // The video connector is ancillary data output M for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutN,         // The video connector is ancillary data output N for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutO,         // The video connector is ancillary data output O for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutP,         // The video connector is ancillary data output P for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvVideoConnectorLabelIpAncOutLast       // End of list indicator for the ancillary data output labels for an IP stream conforming to the SMPTE 2110-40 draft version.
};

// The macro was changed because the previous one was becoming too big causing the compiler to return :
// fatal error C1026: parser stack overflow, program too complex.
#define MV_VIDEO_CONNECTOR_LABEL_ENUM_TO_STRING(eLabel) ConnectorLabelEnumToString((EMvVideoConnectorLabel)(eLabel))

inline const char * ConnectorLabelEnumToString(EMvVideoConnectorLabel eLabel)
{
   switch (eLabel)
   {
      case keMvVideoConnectorLabelInvalid: return "Invalid";
      case keMvVideoConnectorLabelLast:    return "Last";
      case keMvVideoConnectorLabelSdiInA:  return "SDI IN A";
      case keMvVideoConnectorLabelSdiInB:  return "SDI IN B";
      case keMvVideoConnectorLabelSdiInC:  return "SDI IN C";
      case keMvVideoConnectorLabelSdiInD:  return "SDI IN D";
      case keMvVideoConnectorLabelSdiInE:  return "SDI IN E";
      case keMvVideoConnectorLabelSdiInF:  return "SDI IN F";
      case keMvVideoConnectorLabelSdiInG:  return "SDI IN G";
      case keMvVideoConnectorLabelSdiInH:  return "SDI IN H";
      case keMvVideoConnectorLabelSdiInI:  return "SDI IN I";
      case keMvVideoConnectorLabelSdiInJ:  return "SDI IN J";
      case keMvVideoConnectorLabelSdiInK:  return "SDI IN K";
      case keMvVideoConnectorLabelSdiInL:  return "SDI IN L";
      case keMvVideoConnectorLabelSdiOutA: return "SDI OUT A";
      case keMvVideoConnectorLabelSdiOutB: return "SDI OUT B";
      case keMvVideoConnectorLabelSdiOutC: return "SDI OUT C";
      case keMvVideoConnectorLabelSdiOutD: return "SDI OUT D";
      case keMvVideoConnectorLabelSdiOutE: return "SDI OUT E";
      case keMvVideoConnectorLabelSdiOutF: return "SDI OUT F";
      case keMvVideoConnectorLabelSdiOutG: return "SDI OUT G";
      case keMvVideoConnectorLabelSdiOutH: return "SDI OUT H";
      case keMvVideoConnectorLabelSdiOutI: return "SDI OUT I";
      case keMvVideoConnectorLabelSdiOutJ: return "SDI OUT J";
      case keMvVideoConnectorLabelSdiOutK: return "SDI OUT K";
      case keMvVideoConnectorLabelSdiOutL: return "SDI OUT L";
      case keMvVideoConnectorLabelSdiIpInA:   return "SDI IP IN A";
      case keMvVideoConnectorLabelSdiIpInB:   return "SDI IP IN B";
      case keMvVideoConnectorLabelSdiIpInC:   return "SDI IP IN C";
      case keMvVideoConnectorLabelSdiIpInD:   return "SDI IP IN D";
      case keMvVideoConnectorLabelSdiIpInE:   return "SDI IP IN E";
      case keMvVideoConnectorLabelSdiIpInF:   return "SDI IP IN F";
      case keMvVideoConnectorLabelSdiIpInG:   return "SDI IP IN G";
      case keMvVideoConnectorLabelSdiIpInH:   return "SDI IP IN H";
      case keMvVideoConnectorLabelSdiIpInI:   return "SDI IP IN I";
      case keMvVideoConnectorLabelSdiIpInJ:   return "SDI IP IN J";
      case keMvVideoConnectorLabelSdiIpInK:   return "SDI IP IN K";
      case keMvVideoConnectorLabelSdiIpInL:   return "SDI IP IN L";
      case keMvVideoConnectorLabelSdiIpOutA:  return "SDI IP OUT A";
      case keMvVideoConnectorLabelSdiIpOutB:  return "SDI IP OUT B";
      case keMvVideoConnectorLabelSdiIpOutC:  return "SDI IP OUT C";
      case keMvVideoConnectorLabelSdiIpOutD:  return "SDI IP OUT D";
      case keMvVideoConnectorLabelSdiIpOutE:  return "SDI IP OUT E";
      case keMvVideoConnectorLabelSdiIpOutF:  return "SDI IP OUT F";
      case keMvVideoConnectorLabelSdiIpOutG:  return "SDI IP OUT G";
      case keMvVideoConnectorLabelSdiIpOutH:  return "SDI IP OUT H";
      case keMvVideoConnectorLabelSdiIpOutI:  return "SDI IP OUT I";
      case keMvVideoConnectorLabelSdiIpOutJ:  return "SDI IP OUT J";
      case keMvVideoConnectorLabelSdiIpOutK:  return "SDI IP OUT K";
      case keMvVideoConnectorLabelSdiIpOutL:  return "SDI IP OUT L";
      case keMvVideoConnectorLabelAspenVideoInA:   return "ASPEN video IN A";
      case keMvVideoConnectorLabelAspenVideoInB:   return "ASPEN video IN B";
      case keMvVideoConnectorLabelAspenVideoInC:   return "ASPEN video IN C";
      case keMvVideoConnectorLabelAspenVideoInD:   return "ASPEN video IN D";
      case keMvVideoConnectorLabelAspenVideoInE:   return "ASPEN video IN E";
      case keMvVideoConnectorLabelAspenVideoInF:   return "ASPEN video IN F";
      case keMvVideoConnectorLabelAspenVideoInG:   return "ASPEN video IN G";
      case keMvVideoConnectorLabelAspenVideoInH:   return "ASPEN video IN H";
      case keMvVideoConnectorLabelAspenVideoInI:   return "ASPEN video IN I";
      case keMvVideoConnectorLabelAspenVideoInJ:   return "ASPEN video IN J";
      case keMvVideoConnectorLabelAspenVideoInK:   return "ASPEN video IN K";
      case keMvVideoConnectorLabelAspenVideoInL:   return "ASPEN video IN L";
      case keMvVideoConnectorLabelAspenVideoOutA:  return "ASPEN video OUT A";
      case keMvVideoConnectorLabelAspenVideoOutB:  return "ASPEN video OUT B";
      case keMvVideoConnectorLabelAspenVideoOutC:  return "ASPEN video OUT C";
      case keMvVideoConnectorLabelAspenVideoOutD:  return "ASPEN video OUT D";
      case keMvVideoConnectorLabelAspenVideoOutE:  return "ASPEN video OUT E";
      case keMvVideoConnectorLabelAspenVideoOutF:  return "ASPEN video OUT F";
      case keMvVideoConnectorLabelAspenVideoOutG:  return "ASPEN video OUT G";
      case keMvVideoConnectorLabelAspenVideoOutH:  return "ASPEN video OUT H";
      case keMvVideoConnectorLabelAspenVideoOutI:  return "ASPEN video OUT I";
      case keMvVideoConnectorLabelAspenVideoOutJ:  return "ASPEN video OUT J";
      case keMvVideoConnectorLabelAspenVideoOutK:  return "ASPEN video OUT K";
      case keMvVideoConnectorLabelAspenVideoOutL:  return "ASPEN video OUT L";
      case keMvVideoConnectorLabelAspenAudioInA:   return "ASPEN audio IN A";
      case keMvVideoConnectorLabelAspenAudioInB:   return "ASPEN audio IN B";
      case keMvVideoConnectorLabelAspenAudioInC:   return "ASPEN audio IN C";
      case keMvVideoConnectorLabelAspenAudioInD:   return "ASPEN audio IN D";
      case keMvVideoConnectorLabelAspenAudioInE:   return "ASPEN audio IN E";
      case keMvVideoConnectorLabelAspenAudioInF:   return "ASPEN audio IN F";
      case keMvVideoConnectorLabelAspenAudioInG:   return "ASPEN audio IN G";
      case keMvVideoConnectorLabelAspenAudioInH:   return "ASPEN audio IN H";
      case keMvVideoConnectorLabelAspenAudioInI:   return "ASPEN audio IN I";
      case keMvVideoConnectorLabelAspenAudioInJ:   return "ASPEN audio IN J";
      case keMvVideoConnectorLabelAspenAudioInK:   return "ASPEN audio IN K";
      case keMvVideoConnectorLabelAspenAudioInL:   return "ASPEN audio IN L";
      case keMvVideoConnectorLabelAspenAudioOutA:  return "ASPEN audio OUT A";
      case keMvVideoConnectorLabelAspenAudioOutB:  return "ASPEN audio OUT B";
      case keMvVideoConnectorLabelAspenAudioOutC:  return "ASPEN audio OUT C";
      case keMvVideoConnectorLabelAspenAudioOutD:  return "ASPEN audio OUT D";
      case keMvVideoConnectorLabelAspenAudioOutE:  return "ASPEN audio OUT E";
      case keMvVideoConnectorLabelAspenAudioOutF:  return "ASPEN audio OUT F";
      case keMvVideoConnectorLabelAspenAudioOutG:  return "ASPEN audio OUT G";
      case keMvVideoConnectorLabelAspenAudioOutH:  return "ASPEN audio OUT H";
      case keMvVideoConnectorLabelAspenAudioOutI:  return "ASPEN audio OUT I";
      case keMvVideoConnectorLabelAspenAudioOutJ:  return "ASPEN audio OUT J";
      case keMvVideoConnectorLabelAspenAudioOutK:  return "ASPEN audio OUT K";
      case keMvVideoConnectorLabelAspenAudioOutL:  return "ASPEN audio OUT L";
      case keMvVideoConnectorLabelAspenAudioOutM:  return "ASPEN audio OUT M";
      case keMvVideoConnectorLabelAspenAudioOutN:  return "ASPEN audio OUT N";
      case keMvVideoConnectorLabelAspenAudioOutO:  return "ASPEN audio OUT O";
      case keMvVideoConnectorLabelAspenAudioOutP:  return "ASPEN audio OUT P";
      case keMvVideoConnectorLabelAspenVancInA:    return "ASPEN VANC IN A";
      case keMvVideoConnectorLabelAspenVancInB:    return "ASPEN VANC IN B";
      case keMvVideoConnectorLabelAspenVancInC:    return "ASPEN VANC IN C";
      case keMvVideoConnectorLabelAspenVancInD:    return "ASPEN VANC IN D";
      case keMvVideoConnectorLabelAspenVancInE:    return "ASPEN VANC IN E";
      case keMvVideoConnectorLabelAspenVancInF:    return "ASPEN VANC IN F";
      case keMvVideoConnectorLabelAspenVancInG:    return "ASPEN VANC IN G";
      case keMvVideoConnectorLabelAspenVancInH:    return "ASPEN VANC IN H";
      case keMvVideoConnectorLabelAspenVancInI:    return "ASPEN VANC IN I";
      case keMvVideoConnectorLabelAspenVancInJ:    return "ASPEN VANC IN J";
      case keMvVideoConnectorLabelAspenVancInK:    return "ASPEN VANC IN K";
      case keMvVideoConnectorLabelAspenVancInL:    return "ASPEN VANC IN L";
      case keMvVideoConnectorLabelAspenVancOutA:   return "ASPEN VANC OUT A";
      case keMvVideoConnectorLabelAspenVancOutB:   return "ASPEN VANC OUT B";
      case keMvVideoConnectorLabelAspenVancOutC:   return "ASPEN VANC OUT C";
      case keMvVideoConnectorLabelAspenVancOutD:   return "ASPEN VANC OUT D";
      case keMvVideoConnectorLabelAspenVancOutE:   return "ASPEN VANC OUT E";
      case keMvVideoConnectorLabelAspenVancOutF:   return "ASPEN VANC OUT F";
      case keMvVideoConnectorLabelAspenVancOutG:   return "ASPEN VANC OUT G";
      case keMvVideoConnectorLabelAspenVancOutH:   return "ASPEN VANC OUT H";
      case keMvVideoConnectorLabelAspenVancOutI:   return "ASPEN VANC OUT I";
      case keMvVideoConnectorLabelAspenVancOutJ:   return "ASPEN VANC OUT J";
      case keMvVideoConnectorLabelAspenVancOutK:   return "ASPEN VANC OUT K";
      case keMvVideoConnectorLabelAspenVancOutL:   return "ASPEN VANC OUT L";
      case keMvVideoConnectorLabelIpVideoInA:   return "IP video IN A";
      case keMvVideoConnectorLabelIpVideoInB:   return "IP video IN B";
      case keMvVideoConnectorLabelIpVideoInC:   return "IP video IN C";
      case keMvVideoConnectorLabelIpVideoInD:   return "IP video IN D";
      case keMvVideoConnectorLabelIpVideoInE:   return "IP video IN E";
      case keMvVideoConnectorLabelIpVideoInF:   return "IP video IN F";
      case keMvVideoConnectorLabelIpVideoInG:   return "IP video IN G";
      case keMvVideoConnectorLabelIpVideoInH:   return "IP video IN H";
      case keMvVideoConnectorLabelIpVideoInI:   return "IP video IN I";
      case keMvVideoConnectorLabelIpVideoInJ:   return "IP video IN J";
      case keMvVideoConnectorLabelIpVideoInK:   return "IP video IN K";
      case keMvVideoConnectorLabelIpVideoInL:   return "IP video IN L";
      case keMvVideoConnectorLabelIpVideoOutA:  return "IP video OUT A";
      case keMvVideoConnectorLabelIpVideoOutB:  return "IP video OUT B";
      case keMvVideoConnectorLabelIpVideoOutC:  return "IP video OUT C";
      case keMvVideoConnectorLabelIpVideoOutD:  return "IP video OUT D";
      case keMvVideoConnectorLabelIpVideoOutE:  return "IP video OUT E";
      case keMvVideoConnectorLabelIpVideoOutF:  return "IP video OUT F";
      case keMvVideoConnectorLabelIpVideoOutG:  return "IP video OUT G";
      case keMvVideoConnectorLabelIpVideoOutH:  return "IP video OUT H";
      case keMvVideoConnectorLabelIpVideoOutI:  return "IP video OUT I";
      case keMvVideoConnectorLabelIpVideoOutJ:  return "IP video OUT J";
      case keMvVideoConnectorLabelIpVideoOutK:  return "IP video OUT K";
      case keMvVideoConnectorLabelIpVideoOutL:  return "IP video OUT L";
      case keMvVideoConnectorLabelIpAudioInA:   return "IP audio IN A";
      case keMvVideoConnectorLabelIpAudioInB:   return "IP audio IN B";
      case keMvVideoConnectorLabelIpAudioInC:   return "IP audio IN C";
      case keMvVideoConnectorLabelIpAudioInD:   return "IP audio IN D";
      case keMvVideoConnectorLabelIpAudioInE:   return "IP audio IN E";
      case keMvVideoConnectorLabelIpAudioInF:   return "IP audio IN F";
      case keMvVideoConnectorLabelIpAudioInG:   return "IP audio IN G";
      case keMvVideoConnectorLabelIpAudioInH:   return "IP audio IN H";
      case keMvVideoConnectorLabelIpAudioInI:   return "IP audio IN I";
      case keMvVideoConnectorLabelIpAudioInJ:   return "IP audio IN J";
      case keMvVideoConnectorLabelIpAudioInK:   return "IP audio IN K";
      case keMvVideoConnectorLabelIpAudioInL:   return "IP audio IN L";
      case keMvVideoConnectorLabelIpAudioOutA:  return "IP audio OUT A";
      case keMvVideoConnectorLabelIpAudioOutB:  return "IP audio OUT B";
      case keMvVideoConnectorLabelIpAudioOutC:  return "IP audio OUT C";
      case keMvVideoConnectorLabelIpAudioOutD:  return "IP audio OUT D";
      case keMvVideoConnectorLabelIpAudioOutE:  return "IP audio OUT E";
      case keMvVideoConnectorLabelIpAudioOutF:  return "IP audio OUT F";
      case keMvVideoConnectorLabelIpAudioOutG:  return "IP audio OUT G";
      case keMvVideoConnectorLabelIpAudioOutH:  return "IP audio OUT H";
      case keMvVideoConnectorLabelIpAudioOutI:  return "IP audio OUT I";
      case keMvVideoConnectorLabelIpAudioOutJ:  return "IP audio OUT J";
      case keMvVideoConnectorLabelIpAudioOutK:  return "IP audio OUT K";
      case keMvVideoConnectorLabelIpAudioOutL:  return "IP audio OUT L";
      case keMvVideoConnectorLabelIpAudioOutM:  return "IP audio OUT M";
      case keMvVideoConnectorLabelIpAudioOutN:  return "IP audio OUT N";
      case keMvVideoConnectorLabelIpAudioOutO:  return "IP audio OUT O";
      case keMvVideoConnectorLabelIpAudioOutP:  return "IP audio OUT P";
      case keMvVideoConnectorLabelIpAncInA:     return "IP ANC IN A";
      case keMvVideoConnectorLabelIpAncInB:     return "IP ANC IN B";
      case keMvVideoConnectorLabelIpAncInC:     return "IP ANC IN C";
      case keMvVideoConnectorLabelIpAncInD:     return "IP ANC IN D";
      case keMvVideoConnectorLabelIpAncInE:     return "IP ANC IN E";
      case keMvVideoConnectorLabelIpAncInF:     return "IP ANC IN F";
      case keMvVideoConnectorLabelIpAncInG:     return "IP ANC IN G";
      case keMvVideoConnectorLabelIpAncInH:     return "IP ANC IN H";
      case keMvVideoConnectorLabelIpAncInI:     return "IP ANC IN I";
      case keMvVideoConnectorLabelIpAncInJ:     return "IP ANC IN J";
      case keMvVideoConnectorLabelIpAncInK:     return "IP ANC IN K";
      case keMvVideoConnectorLabelIpAncInL:     return "IP ANC IN L";
      case keMvVideoConnectorLabelIpAncOutA:    return "IP ANC OUT A";
      case keMvVideoConnectorLabelIpAncOutB:    return "IP ANC OUT B";
      case keMvVideoConnectorLabelIpAncOutC:    return "IP ANC OUT C";
      case keMvVideoConnectorLabelIpAncOutD:    return "IP ANC OUT D";
      case keMvVideoConnectorLabelIpAncOutE:    return "IP ANC OUT E";
      case keMvVideoConnectorLabelIpAncOutF:    return "IP ANC OUT F";
      case keMvVideoConnectorLabelIpAncOutG:    return "IP ANC OUT G";
      case keMvVideoConnectorLabelIpAncOutH:    return "IP ANC OUT H";
      case keMvVideoConnectorLabelIpAncOutI:    return "IP ANC OUT I";
      case keMvVideoConnectorLabelIpAncOutJ:    return "IP ANC OUT J";
      case keMvVideoConnectorLabelIpAncOutK:    return "IP ANC OUT K";
      case keMvVideoConnectorLabelIpAncOutL:    return "IP ANC OUT L";
      default: return "???"; 
   }
};

//
// Summary:
//    Describes the type of scaling that is done by the transform stream on the video data.
//
enum EMvVideoTransformType
{
   keMvVideoTransformTypeInvalid = -1, // Invalid value.
   keMvVideoTransformTypeResize  = 0,  // The transform stream scales the video portion of the input node using resize scaling.
   keMvVideoTransformTypeRegion  = 1,  // The transform stream scales the video portion of the input node using region scaling.
   keMvVideoTransformTypeLast          // End of list indicator.
};

#define MV_VIDEO_TRANSFORM_TYPE_ENUM_TO_STRING(eTransformType) \
   ((eTransformType == keMvVideoTransformTypeInvalid) ? ("Invalid") : \
   (eTransformType == keMvVideoTransformTypeLast)     ? ("Last") : \
   (eTransformType == keMvVideoTransformTypeResize)   ? ("Resize") : \
   (eTransformType == keMvVideoTransformTypeRegion)   ? ("Region") : \
   ("???"))

//
// Summary:
//    Describes the type of time base correction that is applied to the input stream.
//
enum EMvInputStreamMode
{
   keMvInputStreamModeInvalid,                  // Invalid value.
   keMvInputStreamModeAudioVideoTBC,            // Time base correction is applied to the input stream by
                                                   // repeating or dropping appropriate video and audio frames.
   keMvInputStreamModeAudioResamplerVideoTBC,   // Time base correction is applied to the input stream by 
                                                   // repeating or dropping appropriate video frames and resampling 
                                                   // the audio. The audio resampling prevents audio dropping/repeating.
   keMvInputStreamModeAsynchronous,             // No time base correction is applied. The input stream gives access to 
                                                   // all the frames obtained from the input connectors. The application
                                                   // must be fast enough to retrieve all frames. Best results are 
                                                   // achieved when the card is genlocked to the input source.
   keMvInputStreamModeLast                      // End of list indicator.
};

#define MV_VIDEO_INPUT_STREAM_ENUM_TO_STRING(eInputStreamMode) \
   ((eInputStreamMode == keMvInputStreamModeInvalid)               ? ("Invalid")                   : \
   (eInputStreamMode  == keMvInputStreamModeAudioVideoTBC)         ? ("Audio Video TBC")           : \
   (eInputStreamMode  == keMvInputStreamModeAudioResamplerVideoTBC)? ("Audio Resampler Video TBC") : \
   (eInputStreamMode  == keMvInputStreamModeAsynchronous)          ? ("Asynchronous")              : \
   (eInputStreamMode  == keMvInputStreamModeLast)                  ? ("Last")                      : \
   ("???"))
   

//
// Summary:
//    Indicates the audio to use for the auxiliary input in the in-line audio mixer (for X.mio2 Plus only).
// Remarks:
// - When using SDI video channel A as the line input to the video mixer, the auxiliary input cannot be keMvAudioMixerSourceInputStreamA.
// - When using SDI video channel B as the line input to the video mixer, the auxiliary input cannot be keMvAudioMixerSourceInputStreamB.
//
enum EMvAudioMixerSourceSelection
{
   keMvAudioMixerSourceInvalid,        // Invalid value.
   keMvAudioMixerSourceNode,           // Indicates that the audio used is from the output stream's node.
   keMvAudioMixerSourceInputStreamA,   // Indicates that the audio used is from audio channel A.
   keMvAudioMixerSourceInputStreamB,   // Indicates that the audio used is from audio channel B.
   keMvAudioMixerSourceInputStreamC,   // Indicates that the audio used is from audio channel C.
   keMvAudioMixerSourceInputStreamD,   // Indicates that the audio used is from audio channel D.
   keMvAudioMixerSourceLast      	   // End of list indicator.
};

#define MV_AUX_SOURCE_SELECTION_ENUM_TO_STRING(eAudioMixerSourceSelection) \
   ((eAudioMixerSourceSelection == keMvAudioMixerSourceInvalid)      ? ("Invalid")        :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceNode)         ? ("Node")           :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceInputStreamA) ? ("Input stream A") :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceInputStreamB) ? ("Input stream B") :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceInputStreamC) ? ("Input stream C") :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceInputStreamD) ? ("Input stream D") :\
   (eAudioMixerSourceSelection  == keMvAudioMixerSourceLast)         ? ("Last")           :\
   ("???"))

//
// Summary:
//    Describes which data field the transform stream processes.
//
enum EMvTransformProcessing
{
   keMvTransformProcessingInvalid      = -1,	// Invalid value.
   keMvTransformProcessingAll          =  0,	// Indicates that the transform stream processes all the fields and frames.
   keMvTransformProcessingFirstField   =  1,	// Indicates that the transform stream processes the first field only.
   keMvTransformProcessingSecondField  =  2,	// Indicates that the transform stream processes the second field only.
   keMvTransformProcessingLast         =  3,	// End of list indicator.
};

//
// Summary:
//    Selects the filter coefficients of transform stream.
//
enum EMvTransformFilterCoefficients
{
   keMvTransformFilterCoeffInvalid   = -1, // Invalid value.
   keMvTransformFilterCoeffStandard  = 0,  // Uses the normal filtering coefficients. This is the default value.
   keMvTransformFilterCoeffAlternate = 1,  // Uses the alternate filtering coefficients.
   keMvTransformFilterCoeffLast            // End of list indicator.
};

#define MV_TRANSFORM_FILTER_COEFFICIENTS_ENUM_TO_STRING(eTransformFilterCoefficients) \
   ((eTransformFilterCoefficients == keMvTransformFilterCoeffInvalid)    ? ("Invalid") : \
   (eTransformFilterCoefficients == keMvTransformFilterCoeffStandard)    ? ("Standard") : \
   (eTransformFilterCoefficients == keMvTransformFilterCoeffAlternate)   ? ("Alternate") : \
   (eTransformFilterCoefficients == keMvTransformFilterCoeffLast)        ? ("Region") : \
   ("???"))

//
// Summary:
//    Indicates whether the GPU Transfer module uses the default mode or GPUDirect.
//
enum EMvGPUTransferMode
{
   keMvGPUTransferModeInvalid,      // Invalid value.
   keMvGPUTransferModeDefault,      // Indicates that the GPU Transfer module uses the default mode.
   keMvGPUTransferModeGPUDirect,    // Indicates that the GPU Transfer module uses GPUDirect.
   keMvGPUTransferModeLast,         // End of list indicator.
};

//
// Summary:
//    Indicates whether the first luma component in a YUAYVA 4:2:2:4 or a YUYV 4:2:2 video surface is located in the red or blue component of the OpenGL or DirectX 11 texture.
//
enum EMvComponentSelection
{
   keMvComponentSelectionInvalid,         // Invalid value.
   keMvComponentSelectionFirstLumaInRed,  // Indicates that the first luma component (Y0) is the red component.
   keMvComponentSelectionFirstLumaInBlue, // Indicates that the first luma component (Y0) is the blue component.
   keMvComponentSelectionLast,            // End of list indicator.
};

//
// Summary:
//    Indicates which rendering mode the GPU Transfer module uses.
//
enum EMvGPUTransferRenderingMode
{
   keMvGPUTransferRenderingModeInvalid,   // Invalid value.
   keMvGPUTransferRenderingModeOGL,       // Indicates that OpenGL is used for 3D rendering.
   keMvGPUTransferRenderingModeD3D11,     // Indicates that DirectX 11 is used for 3D rendering.
   keMvGPUTransferRenderingModeLast,      // End of list indicator.
};

//
// Summary:
//    Indicates the bind flags of the Direct3D texture.
//
enum EMvD3DTextureBindFlags
{
   keMvD3DTextureBindFlagsSR  = 0x8L,  // Corresponds to D3D11_BIND_SHADER_RESOURCE.
   keMvD3DTextureBindFlagsSO  = 0x10L, // Corresponds to D3D11_BIND_STREAM_OUTPUT.
   keMvD3DTextureBindFlagsRT  = 0x20L, // Corresponds to D3D11_BIND_RENDER_TARGET.
};

//
// Summary:
//    Describes the settings the Flex GPU Transfer module will use.
//
struct SMvGPUTranferSettings
{
   uint32_t                    size;                  // Structure size in bytes.
   SMvResolutionInfo           sResolution;           // Structure that specifies the resolution information of the GPU Transfer module.
   EMvComponentSelection       eComponentSelection;   // Indicates whether you want the first luma component in a YUYV or YUAYVA video surface to be located in the red or blue component of the texture.
   EMvGPUTransferRenderingMode eGpuRenderingMode;     // Indicates which rendering mode to use.
   void*                       pD3DDevice;            // If using Direct3D, this is the pointer to the Direct3D device.
};

//
// Summary:
//    Specifies in which quadrant of a UHD image an HD image is placed.
//
enum EMvQuadrant
{
   keMvQuadrantInvalid      = 0,  // Invalid value.
   keMvQuadrantTopLeft      = 1,  // Specifies that the HD image from the SDI connector will be placed in the top left quadrant of the UHD image.
   keMvQuadrantTopRight     = 2,  // Specifies that the HD image from the SDI connector will be placed in the top right quadrant of the UHD image.
   keMvQuadrantBottomLeft   = 4,  // Specifies that the HD image from the SDI connector will be placed in the bottom left quadrant of the UHD image.
   keMvQuadrantBottomRight  = 8,  // Specifies that the HD image from the SDI connector will be placed in the bottom right quadrant of the UHD image.
   keMvQuadrantLast               // End of list indicator.
};

#define MV_QUADRANT_ENUM_TO_STRING(eValue) \
   ((eValue == keMvQuadrantInvalid)     ? ("Invalid")      : \
    (eValue == keMvQuadrantLast)        ? ("Last")         : \
    (eValue == keMvQuadrantTopLeft)     ? ("Top-Left")     : \
    (eValue == keMvQuadrantTopRight)    ? ("Top-Right")    : \
    (eValue == keMvQuadrantBottomLeft)  ? ("Bottom-Left")  : \
    (eValue == keMvQuadrantBottomRight) ? ("Bottom-Right") : \
    ("???"))

//
// Summary:
//    Specifies the type of connector.
//
enum EMvConnectorType
{
   keMvconnectorTypeInvalid = 0,                // Invalid value.
   keMvconnectorTypeSdiVideoInput,              // SDI video input connector.
   keMvconnectorTypeSdiVideoOutput,             // SDI video output connector.
   keMvconnectorTypeEmbeddedAudioInputPair,     // SDI embedded audio input pair connector.
   keMvconnectorTypeEmbeddedAudioOutputPair,    // SDI embedded audio output pair connector.
   keMvconnectorTypeAesEbuAudioInputPair,       // AES/EBU audio input pair connector.
   keMvconnectorTypeAesEbuAudioOutputPair,      // AES/EBU audio output pair connector.
   keMvconnectorTypeSdiIpInput,                 // Input connector for an IP stream conforming to SMPTE 2022-6.
   keMvconnectorTypeSdiIpOutput,                // Output connector for an IP stream conforming to SMPTE 2022-6.
   keMvconnectorTypeSdiIpAudioInputPair,        // Audio input pair connector for an IP stream conforming to SMPTE 2022-6.
   keMvconnectorTypeSdiIpAudioOutputPair,       // Audio output pair connector for an IP stream conforming to SMPTE 2022-6.
   keMvconnectorTypeAspenVideoOutput,           // Video output connector for an IP stream conforming to the ASPEN protocol.
   keMvconnectorTypeAspenAudioOutput,           // Audio output connector for an IP stream conforming to the ASPEN protocol.
   keMvconnectorTypeAspenVancOutput,            // Ancillary data output connector for an IP stream conforming to the ASPEN protocol.
   keMvconnectorTypeIpVideoOutput,              // Video output connector for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvconnectorTypeIpAudioOutput,              // Audio output connector for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvconnectorTypeIpAncOutput,                // Ancillary data output connector for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvconnectorTypeIpVideoInput,               // Video input connector for an IP stream conforming to the SMPTE 2110-20 draft version.
   keMvconnectorTypeIpAudioInput,               // Audio input connector for an IP stream conforming to the SMPTE 2110-30 draft version.
   keMvconnectorTypeIpAncInput,                 // Ancillary data input connector for an IP stream conforming to the SMPTE 2110-40 draft version.
   keMvconnectorTypeLast                        // End of list indicator.
};

#define MV_CONNECTOR_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvconnectorTypeInvalid)                    ? ("Invalid")      : \
    (eValue == keMvconnectorTypeSdiVideoInput)              ? ("Sdi video input") : \
    (eValue == keMvconnectorTypeSdiVideoOutput)             ? ("Sdi video output") : \
    (eValue == keMvconnectorTypeEmbeddedAudioInputPair)     ? ("Embedded audio input pair") : \
    (eValue == keMvconnectorTypeEmbeddedAudioOutputPair)    ? ("Embedded audio output pair") : \
    (eValue == keMvconnectorTypeAesEbuAudioInputPair)       ? ("Aes/Ebu audio input pair") : \
    (eValue == keMvconnectorTypeAesEbuAudioOutputPair)      ? ("Aes/Ebu audio output pair") : \
    (eValue == keMvconnectorTypeSdiIpInput)                 ? ("SDI IP input") : \
    (eValue == keMvconnectorTypeSdiIpOutput)                ? ("SDI IP putput") : \
    (eValue == keMvconnectorTypeSdiIpAudioInputPair)        ? ("SDI IP audio input pair") : \
    (eValue == keMvconnectorTypeSdiIpAudioOutputPair)       ? ("SDI IP audio output pair") : \
    (eValue == keMvconnectorTypeAspenVideoOutput)           ? ("Aspen video output") : \
    (eValue == keMvconnectorTypeAspenAudioOutput)           ? ("Aspen audio output") : \
    (eValue == keMvconnectorTypeAspenVancOutput)            ? ("Aspen VANC output") : \
    (eValue == keMvconnectorTypeIpVideoOutput)              ? ("IP video output") : \
    (eValue == keMvconnectorTypeIpAudioOutput)              ? ("IP audio output") : \
    (eValue == keMvconnectorTypeIpAncOutput)                ? ("IP ANC output") : \
    (eValue == keMvconnectorTypeIpVideoInput)               ? ("IP video input") : \
    (eValue == keMvconnectorTypeIpAudioInput)               ? ("IP audio input") : \
    (eValue == keMvconnectorTypeIpAncInput)                 ? ("IP ANC input") : \
    (eValue == keMvconnectorTypeLast)                       ? ("Last") : \
    ("???"))

//
// Summary:
//    Describes the properties of a seat.
//
struct SMvSeatInfoPublic
{
   uint32_t       uiFirmCode;             // Seat firm code. Reserved for Matrox.
   uint32_t       uiProductCode;          // Seat product code. Reserved for Matrox.
   wchar_t        szSerialNumber[32];     // Seat serial number.
   unsigned char  acLeasedBy[6];          // Mac address of the machine that reserved this seat.
   uint32_t       uiUntil;                // Seat reservation end time.
   wchar_t        szLicenseExpiry[32];    // Seat service date expiration.
   uint32_t       uiNumberOfCores;        // Number of cores supported by this seat.
   bool           bSeatInUse;             // If true, indicates that the seat is currently being used by a process.
};

//
// Summary:
//	   Describes the current value of the DSX Core target seat.
//
struct SMvDSXCoreTargetSeat
{  
   char     szSeatSerialNumber[32];    // Indicates the serial number of the DSX Core target seat.
   unsigned long ulProductCode;        // Indicates the DSX Core product code. Reserved for Matrox.
};

//
// Summary:
//    Describes the SFP+ transceiver MultiSource Agreement (MSA) serial ID data fields.
// Remarks:
//    - This is derived from the SFF Committee, INF-8074i Specification for SFP (Small Form-factor Pluggable) Tranceiver, Table 3.1. Serial ID: Data Fields.
// Description:
//<table>
// Members                          Data address      Field size (bytes)      Description
// ----------------------------     ------------      ------------------      ------------------------------------------------------------------------------------------------
// ui8Identifier                    0                 1                       Type of serial transceiver.
// ui8ExtIdentifier                 1                 1                       Extended identifier of the type of serial transceiver.
// ui8ConnectorType                 2                 1                       Code for the connector type.
// aui8TransceiverCode              3 to 10           8                       Code for the electronic or optical compatibility.
// ui8EncodingCode                  11                1                       Code for the serial encoding algorithm.
// ui8BitRateNominal                12                1                       Nominal bit rate, units of 100 MBits/sec.
// Reserved                         13                1                       Reserved.
// ui8Length9mKm                    14                1                       Link length supported for 9/125 mm fiber, units of km.
// ui8Length9m100m                  15                1                       Link length supported for 9/125 mm fiber, units of 100 m.
// ui8Length50m                     16                1                       Link length supported for 50/125 mm fiber, units of 10 m.
// ui8Length625m                    17                1                       Link length supported for 62.5/125 mm fiber, units of 10 m.
// ui8LengthCopper                  18                1                       Link length supported for copper, units of meters.
// Reserved                         19                1                       Reserved.
// szVendorName                     20 to 35          16                      SFP transceiver vendor name (ASCII). Zero-terminated string.
// Reserved                         36                1                       Reserved.
// aui8VendorOUI                    37 to 39          3                       SFP transceiver vendor IEEE company ID.
// szVendorPartNumber               40 to 55          16                      Part number provided by the SFP transceiver vendor (ASCII). Zero-terminated string.
// szVendorRevision                 56 to 59          4                       Revision level for part number provided by the vendor (ASCII).
// Reserved                         60 to 62          3                       Reserved.
// Not published                    63                1                       Check code for data addresses 0 to 62. Not published.
// aui8Options                      64 to 65          2                       Indicates which optional SFP signals are implemented.
// ui8BitRatMax                     66                1                       Upper bit rate margin percentage.
// ui8BitRatMin                     67                1                       Lower bit rate margin percentage.
// szVendorSerialNumber             68 to 83          16                      Serial number provided by vendor (ASCII). Zero-terminated string.
// aui8ManufacturingDateYear        84 to 85          2                       ASCII code indicating the year of manufacture. (00 = 2000).
// aui8ManufacturingDateMonth       86 to 87          2                       ASCII code indicating the month of manufacture. (01 = Jan through 12 = Dec).
// aui8ManufacturingDateDay         88 to 89          2                       ASCII code indicating the day of manufacture. The values are from 01 to 31.
// aui8ManufacturingDateLot         90 to 91          2                       ASCII code indicating the vendor specific lot code of manufacture. May be blank.
// Reserved                         92 to 94          3                       Reserved.
// Not published                    95                1                       Check code for data addresses 64 to 94. Not published.
//</table>
struct SMvSfpSerialId
{ 
   uint8_t ui8Identifier;                   
   uint8_t ui8ExtIdentifier;                
   uint8_t ui8ConnectorType;                
   uint8_t aui8TransceiverCode[8];          
   uint8_t ui8EncodingCode;                 
   uint8_t ui8BitRateNominal;               
  
   uint8_t ui8Length9mKm;                  
   uint8_t ui8Length9m100m;                
   uint8_t ui8Length50m;                    
   uint8_t ui8Length625m;                   
   uint8_t ui8LengthCopper;  

   char    szVendorName[17];                
   uint8_t aui8VendorOUI[3];                
   char    szVendorPartNumber[17];          
   char    szVendorRevision[5];             
   

   uint8_t aui8Options[2];                  
   uint8_t ui8BitRatMax;                    
   uint8_t ui8BitRatMin;                    
   char    szVendorSerialNumber[17];       
   uint8_t aui8ManufacturingDateYear[2];    
   uint8_t aui8ManufacturingDateMonth[2];   
   uint8_t aui8ManufacturingDateDay[2];     
   uint8_t aui8ManufacturingDateLot[2];  

};

//
// Summary:
//    Identifies the SFP+ diagnostic error and warning flags.
// Remarks:
//    - High flags are set when real time diagnostic measurements are above the SFP+ manufacturer's higher thresholds.
//    - Low flags are set when real time diagnostic measurements are below the SFP+ manufacturer's lower thresholds.
//
typedef union UMvSfpDiagnosticFlags
{
   uint32_t ui32All;
   struct
   {
      uint32_t bTempHigh:1;
      uint32_t bTempLow:1;
      uint32_t bVoltageHigh:1;
      uint32_t bVoltageLow:1;
      uint32_t bTxBiasHigh:1;
      uint32_t bTxBiasLow:1;
      uint32_t bTxPowerHigh:1;
      uint32_t bTxPowerLow:1;
      uint32_t bRxPowerHigh:1;
      uint32_t bRxPowerLow:1;
      uint32_t bLaserTempHigh:1;
      uint32_t bLaserTempLow:1;
      uint32_t bTecCurrentHigh:1;
      uint32_t bTecCurrentLow:1;
   }sFlags;
}TMvSfpDiagnosticFlags;

//
// Summary:
//    Describes the SFP+ diagnostic and status fields.

struct SMvSfpDiagnostic
{
   int32_t  i32Temperature;         // Indicates the temperature. Range: -128 to 128 Celsius.
   uint32_t ui32Vcc;                // Indicates the supply voltage in the transceiver. Range: 0 to 6553 mV.
   uint32_t ui32TxBias;             // Indicates the transmit bias current. Range: 0 to 131000 uA.
   uint32_t ui32TxPower;            // Indicates the transmit output power. Range: 0 to 6553 uW.
   uint32_t ui32RxPower;            // Indicates the receive input power. Range: 0 to 6553 uW.
   uint32_t ui32InputEqualization;  // Indicates the input equalization. Range: 0 to 10dB.
   uint32_t ui32OutputEmphasis;     // Indicates the output emphasis. Range: 0 to 7dB.
   int32_t  i32LaserTempWavelength; // Indicates the laser color temperature or wavelength. Range:  -128 to 128 Celsius. This value is optional.
   int32_t  i32TecCurrent;          // Indicates the thermoelectric cooling current. A positive value indicates cooling. Range: -3276 to 3276 mA. This value is optional.

   bool bIsDisablePinActive;        // If true, the transmit input pin is disabled.
   bool bIsRs0PinActive;            // If true, the RS0 input pin is active.
   bool bIsRs1PinActive;            // If true, the RS1 input pin is active.
   bool bIsTxFaultPinActive;        // If true, the TX_Fault output pin is active.
   bool bIsRxLosPinActive;          // If true, the RX_LOS output pin is active.
   bool bIsPowerLevelOperationHigh; // If true, the operating power level is high (maximum power dissipation). Value of 0: 1.0 Watt max. Value of 1: 1.5 or 2.0 Watt max.
   bool bIsTxCdrUnlocked;           // If true, the transmit Clock and Data Recovery (CDR) is enabled. A value of 1 indicates that the CDR lock is disabled. In bypass mode, set to 0.
   bool bIsRxCdrUnlocked;           // If true, the receive CDR is enabled. A value of 1 indicates that the CDR lock is disabled. In bypass mode, set to 0.

   TMvSfpDiagnosticFlags sWarnings; // Indicates warning flags set by the SFP+ manufacturer when real time diagnostic measurements exceed recommendations.
   TMvSfpDiagnosticFlags sAlarms;   // Indicates alarm flags set by the SFP+ manufacturer when real time diagnostic measurements exceed limits higher than the warnings.
};

//
// Summary:
//    Identifies the type of membership request made when using a multicast address.
//
enum EMvMulticastMembershipType
{
   keMvMulticastMembershipTypeInvalid = 0,   // Invalid value.
   keMvMulticastMembershipTypeNone,          // Indicates that a membership request has not been made.
   keMvMulticastMembershipTypeIGMPv2,        // Indicates that a membership request to Internet Group Management Protocol (IGMP) version 2 has been made.
   keMvMulticastMembershipTypeLast           // End of list indicator.
};

#define MV_MULTICAST_MEMBERSHIP_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvMulticastMembershipTypeInvalid) ? ("Invalid") : \
   (eValue == keMvMulticastMembershipTypeNone)     ? ("None") : \
   (eValue == keMvMulticastMembershipTypeIGMPv2)   ? ("IGMPv2") : \
   ("???"))


//
// Summary:
//    Identifies the standard to which the IP stream conforms.
//
enum EMvFlowStandard
{
   keMvFlowstandardInvalid, // Invalid value.
   keMvFlowstandardST2022,  // Specifies that the IP stream conforms to the SMPTE 2022-6 standard.
   keMvFlowstandardAspen,   // Specifies that the IP stream conforms the ASPEN protocol.
   keMvFlowstandardST2110,  // Specifies that the IP stream conforms the SMPTE ST 2110 draft version.
   keMvFlowstandardLast,    // End of list indicator.
};

#define MV_FLOW_STANDARD_ENUM_TO_STRING(eValue) \
   ((eValue == keMvFlowstandardInvalid) ? ("Invalid") : \
   (eValue == keMvFlowstandardST2022)   ? ("ST2022") : \
   (eValue == keMvFlowstandardAspen)    ? ("Aspen") : \
   (eValue == keMvFlowstandardST2110)   ? ("ST2110") : \
   ("???"))
