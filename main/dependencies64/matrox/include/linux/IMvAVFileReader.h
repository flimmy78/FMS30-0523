//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvAVFileReader.h $
//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make
// changes in specifications and code at any time and without notice.
// No responsibility is assumed by Matrox Electronic Systems Ltd. for
// its use; nor for any infringements of patents or other rights of
// third parties resulting from its use. No license is granted under
// any patents or patent rights of Matrox Electronic Systems Ltd.
//
//==========================================================================;
//                    IMVAVFILEREADER.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             14 MAI 2004 - 09:54:17
//   Operating System:       WinXP
//   Author:                 Fabrice Rousselle
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVAVFILEREADER_H
#define IMVAVFILEREADER_H
//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvAVFileReader
//==========================================================================;

/**
 * This interface is used to read audio or video data from a file (frames or fields for video streams and samples for audio streams).<br>
 * <br><b>Remark:</b>
 * <ul><li>For video, the position is interpreted with the resolution information set (as frames or fields depending on the scan mode).</ul>
 * @version 1.0
 * @author Fabrice Rousselle
 * @since 14 mai 2004
 * @interface
*/
interface IMvAVFileReader : public IUnknown
{
public:
   //==========================================================================;
   // Public operations
   //==========================================================================;

   /**
    * Specifies the resolution the caller is working with. This resolution will be used to process the
    * duration specified in the cutlist independently from the file native resolution.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>The dimensions (width and height) of the resolution have to match those of the file since
    * the reader does not do scaling.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param SMvResolutionInfo in_sResolutionInformation: structure specifying rate, scan mode, surface dimension, etc.
    * @since 14 mai 2004
    * @version 1.0
    * @author Fabrice Rousselle
    */
   virtual HRESULT __stdcall SetResolutionInformation(SMvResolutionInfo in_sResolutionInformation) = 0;

   /**
    * The cutlist element describes what the user intends to read. It defines the trim in and trim out
    * of the file and the duration over which the element should be played.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>The trim in and trim out given in the cutlist element are based on the file native
    * resolution and the duration is based on the working resolution of the user. The cutlist should
    * be either a video or an audio one, not an audio/video one.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param IMvCutlistElement* in_pICutlistElement : Defines what is expected to be read from the file.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall SetCutListElement(IMvCutListElement* in_pICutListElement) = 0;

   /**
    * Reads the position given, based on the cutlist element information and stores the result
    * in an internal buffer that we give back to the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller sets an audio cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInWorkRes: The position to read from the file, refers to the duration of the cutlist.
    * @param IMvSurface** out_ppIVideoBuffer: Internal buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall PullVideoBuffer(uint64_t in_ui64PositionInWorkRes, IMvSurface** out_ppIVideoBuffer) = 0;

   /**
    * Reads the position given based on the cutlist element information and stores the result
    * in a buffer provided by the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller set an audio cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInWorkRes: The position to read from the file, refers to the duration of the cutlist.
    * @param IMvSurface** out_ppIVideoBuffer: External buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall FillVideoBuffer(uint64_t in_ui64PositionInWorkRes, IMvSurface* out_pIVideoBuffer) = 0;

   /**
    * Reads from the position given and for the duration given, based on the cutlist element information.
    * Stores the result in an internal buffer that we give back to the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller set a video cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInSamples: The position of the first sample the caller wants to retrieve.
    * @param uint64_t in_ui64DurationInSamples: How many samples to read - including the first one.
    * @param IMvAudioSamples** out_ppIAudioBuffer: Internal buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall PullAudioBuffer(uint64_t in_ui64PositionInSamples, uint64_t in_ui64DurationInSamples,
      IMvAudioSamples** out_ppIAudioBuffer) = 0;

   /**
    * Reads from the position given and for the duration given, based on the cutlist element information.
    * Stores the result in an external buffer provided by the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller set a video cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInSamples: The position of the first sample the caller wants to retrieve.
    * @param uint64_t in_ui64DurationInSamples: The number of samples to read - including the first one.
    * @param IMvAudioSamples** out_ppIAudioBuffer: External buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall FillAudioBuffer(uint64_t in_ui64PositionInSamples, uint64_t in_ui64DurationInSamples,
      IMvAudioSamples* out_pIAudioBuffer) = 0;

   /**
    * Reads from the position given and for the duration given, based on the cutlist element information.
    * Reads from stereo files and stores the data in two mono buffers that we give back to the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller set a video cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInSamples: The position of the first sample the caller wants to retrieve.
    * @param uint64_t in_ui64DurationInSamples: The number of samples to read - including the first one.
    * @param IMvAudioSamples** out_ppIAudioBuffer: Internal buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall PullAudioBuffersStereoToMono(uint64_t in_ui64PositionInSamples, uint64_t in_ui64DurationInSamples,
      IMvAudioSamples** out_ppIAudioBufferLeft, IMvAudioSamples** out_ppIAudioBufferRight) = 0;

   /**
    * Reads from the position given and for the duration given, based on the cutlist element information.
    * Reads from stereo files and stores the data in two mono buffers provided by the caller.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Will fail if the caller set a video cutlist element.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param uint64_t in_ui64PositionInSamples: The position of the first sample the caller wants to retrieve.
    * @param uint64_t in_ui64DurationInSamples: How many samples to read - including the first one.
    * @param IMvAudioSamples** out_ppIAudioBuffer: External buffer filled with the required data.
    * @since TheDate
    * @version 1.0
    * @author YourName
    */
   virtual HRESULT __stdcall FillAudioBuffersStereoToMono(uint64_t in_ui64PositionInSamples, uint64_t in_ui64DurationInSamples,
      IMvAudioSamples* out_pIAudioBufferLeft, IMvAudioSamples* out_pIAudioBufferRight) = 0;
   
   /**
   * Flush all cached information, e.g. file handle . so that people can delete the file.
   * This function should only be called when system is in stopped state.
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * @since TheDate
   * @version 1.0
   * @author YourName
   */
   virtual HRESULT __stdcall FlushCachedInformation() = 0 ;
};

#endif //IMVAVFILEREADER_H
