//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//                    IMVFILEVALIDATION.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 11, 2004
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVFILEVALIDATION_H
#define IMVFILEVALIDATION_H


/**
 * Allows access to query codec capabilities.
 *
 * @interface 
 */
interface IMvFileValidation : public IUnknown
{
public:
   /**
    * Gets the file description for the file name given
    *
    * <br><b>Remarks:</b>
    * <ul><li>
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR: No error in reading the file information. The info file is known to Matrox file readers and can be decoded. This file can be played.
    *     <li>MV_E_CODEC_INFO_NOT_AVAILABLE: Codec info is not available. No checking of the file format can be done.
    *     <li>MV_E_VIDEO_DECODER_NOT_AVAILABLE: The file info is known to Matrox file reader but the required video decoder is not available. This error code is returned for video only file. This file can not be played.
    *     <li>MV_E_AUDIO_DECODER_NOT_AVAILABLE: The file info is known to Matrox file reader (eg: 44.1Khz audio or mp3 type audio) but the required audio decoder is not available. This error code is returned for audio only file. This file cannot be played.
    *     <li>MV_W_AVI_AUDIO_NOT_SUPPORTED: The interleaved AV file info is known to Matrox file reader but the audio format is not supported. This warning code is only returned for interleaved AV files.  Only the video portion of the file can be played.
    *     <li>MV_W_AVI_VIDEO_NOT_SUPPORTED: The interleaved AV file info is known to Matrox file reader but the video format is not supported. This warning code is only returned for interleaved AV files.  Only the audio portion of the file can be played.
    *     <li>MV_E_AVI_NOT_SUPPORTED: The interleaved AV file info is known to Matrox file reader but the video and audio formats are not supported. This warning code is only returned for interleaved AV files.  This file cannot be played.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED: The file info is unknown to Matrox file reader (eg: a .txt file); the file information could not be retried on this file. The file info structure is invalid and should not be used.  This file cannot be played.
    * </ul>
    * @param <i>wchar_t * in_pwszFileName </i>: Pointer to the path and file name of the file to open.
    * @param <i>SMvFileInfo * io_psmvFileInfo </i>: Pointer to the <b>SMvFileInfo</b> structure.
    */
   virtual HRESULT __stdcall GetFileDescription(wchar_t * in_pwszFileName, SMvFileInfo * io_psmvFileInfo) = 0;
   
   /**
    * Checks if the file information structure is compatible with currently resolution.
    *
    * <br><b>Remarks:</b>
    * <ul><li>
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR: No error detected. This file can be streamed with the current resolution settings.
    *     <li>MV_E_ERES_NOT_SET: The requested check cannot be completed because there is no valid resolution setting currently set. 
    *     <li>MV_E_INCOMPATIBLE_WIDTH: The width of the file and the editing resolution is incompatible. The file can not be streamed.
    *     <li>MV_E_INCOMPATIBLE_HEIGHT: The height of the file and the editing resolution is incompatible. The file can not be streamed.
    *     <li>MV_E_INCOMPATIBLE_COMPONENT_BIT_COUNT: The component bit count of the file and the editing resolution is incompatible. The file can not be streamed.
    *     <li>MV_W_MISMATCH_PIXEL_ASPECT_RATIO: The pixel aspect ratio is not the same as the current pixel aspect ratio determined from the editing resolution. In the case of MGF, the dimensions can be stretched to fit the editing resolution. The file can still be streamed.
    *     <li>MV_W_MISMATCH_FILE_ASPECT_RATIO: The file aspect ratio is not the same as the current editing aspect ratio. The file can still be streamed.
    *     <li>MV_E_INCOMPATIBLE_FRAME_RATE: The frame rate of the file and the editing resolution is incompatible. The file can not be streamed.
    *     <li>MV_E_INCOMPATIBLE_SCAN_MODE: The scan mode of the file and the editing resolution are different.
    * </ul>
    * @param <i>wchar_t * in_pwszFileName </i>: Pointer to the path and file name of the file to open.
    * @param <i>SMvFileInfo * io_psmvFileInfo </i>: Pointer to the <b>SMvFileInfo</b> structure.
    */
   virtual HRESULT __stdcall CheckFileCompatibleWithEres(SMvFileInfo * in_psmvFileInfo) = 0;

};



#endif //IMVCODECPROFILEINFO_H
