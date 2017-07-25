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
//                    IMVPULLINGCALLBACK.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVPULLINGCALLBACK_H
#define IMVPULLINGCALLBACK_H

/**
 * Call back interface for source filters when using pulling elements.
 * Implemented by user application.
 * @interface
 * 
 */
interface IMvPullingCallBack : public IUnknown
{
public:

   /**
    * Used by the source to retrieve the user's buffer acccording to element position
    * in frames.<br>
    * <b>Remark:</b> <ul><li>None.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>NOERROR, if the buffer was returned successfully.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * 
    * @param uint64_t     in_ui64ElementFramePosition: Position of the AVContent requested.
    * @param IMvAVContent out_ppIAVContent:            Address on the pointer of the requested AVContent.
    * 
    */
   virtual HRESULT __stdcall GetAVContent
   (
      uint64_t             in_ui64ElementFramePosition,
      IMvAVContent         **out_ppIAVContent
   ) = 0;

	/**
	 * Gets the element's input duration for DMC.
	 * The output duration is specified in <b>IMvCutListElement</b>.<br>
	 * <b>Remark:</b> <ul><li>None.</ul>
	 * <b>Return Type:</b>
	 * <ul><li>HRESULT</ul>
	 * <b>Return Values:</b>
	 * <ul><li>NOERROR, if the duration was returned successfully.
    *     <li>HRESULT error code, if operation failed.
	 * </ul>
    * 
    * @param uint64_t out_pui64InputDuration: Element input duration.
    * 
    */
   virtual HRESULT __stdcall GetInputDuration
   (
   	uint64_t 	*out_pui64InputDuration
   ) = 0;

   /**
    * Used by the source to retrieve information about the audio and video data.
    * <br>
    * <b>Remark:</b> <ul><li>None.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>NOERROR, if the information structure was returned successfully.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * 
    * @param SMvAudioVideoFileInfo	out_pSMvAVFileInfo: Structure identifying file information.
    * 
    */
   virtual HRESULT __stdcall GetMvAVFileInfo
   (
       SMvAudioVideoFileInfo	*out_pSMvAVFileInfo
   ) = 0;

   /**
    * Used by the source to let the application know the starting and ending frame positions
    * that will be requested for the current read ahead. This allows the application to prepare the buffers
    * in advance.<br>
    * <b>Remark:</b> <ul><li>None.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>NOERROR, if the read task was set successfully.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * 
    * @param uint64_t in_ui64FrameStartPos:  First frame in the read ahead sequence.
    * @param uint64_t in_ui64FrameEndPos:    Last frame in the read ahead sequence.
    * 
    */
   virtual HRESULT __stdcall SetReadTask
   (
       uint64_t 	in_ui64FrameStartPos,
       uint64_t 	in_ui64FrameEndPos
   ) = 0;

   /**
    * Determines if slow motion field/frames should be repeated or blended. The default
    * value in the Source filter is "blended".<br>
    * <b>Remark:</b> <ul><li>None.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>NOERROR, if the flag was obtained successfully.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * 
    * @param bool out_pbIsBlending: Pointer to a boolean telling us if there's blending.
    * 
    */
   virtual HRESULT __stdcall IsSlowMotionBlending
   (
       bool *out_pbIsBlending
   ) = 0;
};

#endif //IMVPULLINGCALLBACK_H
