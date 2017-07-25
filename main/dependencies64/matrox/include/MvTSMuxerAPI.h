#include "MvFlexAPIPublicSDK.h"

#ifndef MVTSMUXERAPI_H
#define MVTSMUXERAPI_H
//
// F O R W A R D   D E C L A R A T I O N
//
interface IMvTSMuxerSettings;
interface IMvTSMuxer;
interface IMvTSMuxerProgramSettings;
interface IMvTSMuxerProgram;
interface IMvTSVideoElementaryStreamSettings;
interface IMvTSElementaryStream;
interface IMvTSMuxerOutputCallBack;

//
// Summary:
//    Determines the type of elementary stream to create using IMvTSMuxerProgram::CreateElementaryStream().
// Remarks:
//    - This enumerator is provided by the user application. 
//
enum EMvTSMuxerMediaType
{
   keMvTSMuxerMediaTypeInvalid,  // Invalid value.
   keMvTSMuxerMediaTypeVideo,    // Indicates that a video elementary stream will be created.
   keMvTSMuxerMediaTypeAudio,    // Indicates that an audio elementary stream will be created.
   keMvTSMuxerMediaTypeVanc,     // Indicates that a VANC elementary stream will be created.
   keMvTSMuxerMediaTypeLast      // End of list indicator.
};

//
// Summary:
//    Determines the type of video elementary stream to create.
// Remarks:
//    - This enumerator is provided by the user application and is retrieved by the muxer. 
// 
enum EMvTSMuxerVideoType
{
   keMvTSMuxerVideoTypeInvalid,     // Invalid value.
   keMvTSMuxerVideoTypeH264,        // Indicates that an H.264 video elementary stream will be created.
   keMvTSMuxerVideoTypeMPEG2IBP,    // Indicates that an MPEG-2 IBP video elementary stream will be created.
   keMvTSMuxerVideoTypeLast          // End of list indicator.
};

//
// Summary:
//    Determines the type of audio elementary stream to create.
// Remarks:
//    - This enumerator is provided by the user application and is retrieved by the muxer. 
//
enum EMvTSMuxerAudioType
{
   keMvTSMuxerAudioTypeInvalid,     // Invalid value.
   keMvTSMuxerAudioTypePCM,         // Indicates that a pulse-code modulation (PCM) audio elementary stream will be created.
   keMvTSMuxerAudioTypeLPCM,        // Indicates that a linear pulse-code modulation (LPCM) audio elementary stream will be created.
   keMvTSMuxerAudioTypeAAC,         // Indicates that an Advanced Audio Coding (AAC) audio elementary stream will be created.
   keMvTSMuxerAudioTypeLast          // End of list indicator.
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to create a program stream. 
// Remarks:
//    - This interface is returned when the Matrox MPEG-2 Transport Stream Muxer is created using IMvFlexEngine::CreateMPEG2TSMuxer().
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSMuxer : public IUnknown
{
   //
   // Summary:
   //    Creates a program stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This program is used to create an elementary stream and is described in the stream's Program Map Table (PMT). 
   //    - The settings of the IMvTSMuxerProgramSettings interface must be implemented by the user application before it can be 
   //      passed as a pointer. 
   //
   virtual HRESULT __stdcall CreateProgram
      (
      IMvTSMuxerProgramSettings* in_pIProgramSettings,   // Pointer to the transport stream (TS) muxer program settings interface.
      IMvTSMuxerProgram **out_ppIProgram                 // Pointer that receives the TS muxer program interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to provide variable bit rate (VBR) or constant bit rate (CBR) settings. 
// Remarks:
//    - These settings are used only when the Matrox MPEG-2 Transport Stream Muxer is created.
//    - This interface must be implemented by the user application before it can be passed as a pointer when the muxer is created.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSMuxerSettings : public IUnknown
{
   //
   // Summary:
   //    Determines whether the bit rate is variable (VBR) or constant (CBR).
   // Remarks:
   //    - In the case of CBR, the target bit rate value is used for padding. 
   //
   virtual bool __stdcall IsVBR() = 0;
   
   //
   // Summary:
   //    Gets the target bit rate of the output in bits per second (bps).
   // Remarks:
   //    - This value should encompass the bit rate of the video, audio, and VANC streams.
   //    - If the target bit rate is too low, the muxer will underflow. If this occurs, the presentation time stamp (PTS) and the
   //      Program Clock Reference (PCR) values may not synchronize the streams properly.
   //    - If you would like the muxer to determine the target bit rate, return 0.
   virtual uint64_t __stdcall GetAverageBitRate() = 0;  
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the packet ID (PID) and the program number of the program stream. 
// Remarks:
//    - The settings of this interface must be implemented by the user application before it can be passed as a pointer when a program stream is created.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSMuxerProgramSettings : public IUnknown
{
   //
   // Summary:
   //    Returns the PID of the Program Map Table (PMT) for this program stream.
   //
   virtual uint64_t __stdcall GetProgramPID() = 0;
   
   //
   // Summary:
   //    Returns the program number of the program stream.
   // Remarks:
   //    - If you would like the muxer to determine the program number, return 0. 
   //
   virtual uint64_t __stdcall GetProgramNumber() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Generic interface used to determine the type of elementary stream to create. 
// Remarks:
//    - This interface is implemented by the user application.
//    - Once the type of elementary stream to create is determined, the muxer will cast the provided pointer
//      into the specific interface for the type of elementary stream setting.
//    - There is no casting for VANC elementary streams because there are no additional settings for VANC.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSElementaryStreamSettings : public IUnknown
{
   //
   // Summary:
   //    Returns the packet ID (PID) of the elementary stream.
   // Remarks:
   //    - If you would like the muxer to determine the PID value to use, return 0.
   //
   virtual uint64_t __stdcall GetPID() = 0;
   
   //
   // Summary:
   //    Returns the type of elementary stream to create.
   // 
   virtual EMvTSMuxerMediaType __stdcall GetMediaType() = 0;
   
   //
   // Summary:
   //    Returns the resolution of elementary stream to create.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // 
   virtual HRESULT __stdcall GetResolutionInfo
      (
      SMvResolutionInfo *out_psResolutionInfo   // Pointer to the structure containing the resolution information of the elementary stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Specific interface used to provide information about the audio elementary stream. 
// Remarks:
//    - This interface is implemented by the user application.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSAudioElementaryStreamSettings : public IMvTSElementaryStreamSettings
{
   //
   // Summary:
   //    Returns the type of audio elementary stream to create.
   //
   virtual EMvTSMuxerAudioType __stdcall GetAudioType() = 0;
   
   //
   // Summary:
   //    Returns the number of channels in the audio elementary stream.
   // Return value:
   //    - An error message is returned, if the buffer description does not match.
   //
   virtual uint64_t __stdcall GetChannelCount() = 0;
   
   //
   // Summary:
   //    Returns the number of bits per audio sample.
   // Return value:
   //    - An error message is returned, if the buffer description does not match.
   // Remarks:
   //    - The possible values are 16, 24, or 32.
   //    - This method is used in conjunction with GetValidBitsPerSample().
   //
   virtual uint64_t __stdcall GetBitsPerSample() = 0;
   
   //
   // Summary:
   //    Returns the valid number of bits per audio sample.
   // Remarks:
   //    - The possible values are 16 or 24.
   //    - This value should always be less than or equal to the value returned by GetBitsPerSample().
   // Description:
   //    - This method is used in conjunction with GetBitsPerSample() to determine the audio sample format as shown in following table.
   //<table>
   // Audio sample format        Audio sample         Buffer                            
   // ---------------------      ---------------      ----------   
   // 16-bit                     16-bit               16-bit
   // 24-bit                     24-bit               24-bit
   // 32-bit                     24-bit               32-bit
   // </table>
   //
   virtual uint64_t __stdcall GetValidBitsPerSample() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Specific interface used to provide information about the video elementary stream. 
// Remarks:
//    - This interface is implemented by the user application.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSVideoElementaryStreamSettings : public IMvTSElementaryStreamSettings
{
   //
   // Summary:
   //    Returns the type of video elementary stream to create.
   //
   virtual EMvTSMuxerVideoType __stdcall GetVideoType() = 0;
  
   //
   // Summary:
   //    Returns the maximum video elementary stream delay (in ms).
   // Remarks:
   //    - The maximum allowable delay is the difference between the presentation time stamp (PTS) and 
   //      the Program Clock Reference (PCR). That is, Max delay = PTS - PCR
   //    - For AVC, the maximum allowable delay is the video elementary stream's Coded Picture Buffer (CPB)
   //      divided by the maximum bit rate (or, if no Hypothetical Reference Decoder (HRD) is found, the 
   //      maximum value for the profile). That is, Max delay = CPB / Max bit rate
   //    - If this value is too low, a temporal bit rate peak can surge a frame past the reduced lead time, and 
   //      the resulting video elementary stream may contain PCRs with a higher PTS value than the video frames following it.
   //    - If you would like the muxer to determine the value to use, return 0.
   virtual uint32_t           __stdcall GetMaxStreamDelay() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to create elementary streams for the program. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSMuxerProgram  : public IUnknown
{
   //
   // Summary:
   //    Creates an elementary stream for the program for each video, audio, and VANC elementary stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - A pointer to the IMvTSElementaryStreamSettings interface is required for each elementary stream.
   virtual HRESULT __stdcall CreateElementaryStream
      (
      IMvTSElementaryStreamSettings *in_pIESSettings,    // Pointer to the transport stream (TS) elementary stream settings interface.
      IMvTSElementaryStream **out_ppIES                  // Pointer that receives the TS elementary stream interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to provide data to the muxer. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSElementaryStream : public IUnknown
{
   //
   // Summary:
   //    Adds video, audio, or VANC elementary data to the muxer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The in_pIAVContent parameter represents either video, audio, or VANC data.
   //    - A valid time stamp is required for proper A/V synchronization.
   //    - For AVC and MPEG-2 IBP, the display order can be retrieved by calling
   //      IMvSurface::GetGroupOfPicturesFrameInfos(SMvGroupOfPicturesFrame, 1).
   virtual HRESULT __stdcall PutData
      (
      IMvAVContent *in_pIAVContent     // Pointer to the IMvAVContent interface.
      ) = 0;
   
   //
   // Summary:
   //    Starts the muxer's closing process.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The user application must call this method when there is no more data to provide for a specific stream.
   //    - The muxer will close when Close() has been called on all the elementary streams.
   virtual HRESULT __stdcall Close() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain buffers from the user application and notify when a buffer is written. 
// Remarks:
//    - This interface must be implemented by the user application before it can be passed as a pointer 
//      when the muxer is created.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSMuxerOutputCallBack : public IUnknown
{
   //
   // Summary:
   //    Gets buffers from the user application.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The muxer calls this method as data is added to the muxer by the user application.
   //    - This method is asynchronous.
   virtual HRESULT __stdcall GetBuffer
      (
      void** out_ppBuffer,          // Pointer that receives the buffer from the user application.
      uint64_t in_ui64BufferSize    // Indicates the buffer size (in bytes) of the transport stream (TS) packet.
      ) = 0;
   
   //
   // Summary:
   //    Notifies when a buffer is written.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The muxer calls this method when a buffer is written.
   //    - This method is asynchronous.
   //    - To indicate that the last buffer has been written, the muxer will call this method with the 
   //      MV_M_MPEG2MUXERCLOSED message.
   //    - To indicate that no more data will be sent and that the muxer will close at the end of the call, 
   //      the muxer will call this method with the MV_M_MPEG2TS_MUXER_END_OF_STREAM message.
   virtual void __stdcall NotifyStatus
      (
      void *in_pBuffer,                // Pointer to the buffer.
      uint64_t in_ui64BytesWritten,    // Indicates the size of the buffer that is written (in bytes).
      HRESULT in_hResult               // Indicates the state of the muxer.
      ) = 0;
};

#endif
