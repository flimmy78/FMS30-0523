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
//                    IMVMULTISINKCAPTURE.H
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


#ifndef IMVMULTISINKCAPTURE_H
#define IMVMULTISINKCAPTURE_H
#include "mvUnknown.h"

/**
* Notifies the Sink Switcher filter of the capture state.
* @interface
* 
*/
interface IMvMultiSinkCapture : public IUnknown
{
public:   

   /**
    * Notifies the Sink Switcher filter that "writable" buffers need to be sent to the internal
    * Sink filter so that they can be written to disk (captured). Buffers are
	 * captured according to the specified interval parameter. For example, 
    * if the interval is 1, every "writable" buffer will be captured, and
    * if the interval is 5, every fifth "writable" buffer is captured. 
    * <br><b>Remark:</b>
    * <ul><li>This is not a time-based function, meaning that it is not frame accurate. The function
    * is similar to an operating mode that allows the user a more responsive capture. </ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the call was sucessfull.
    *     <li>MV_E_FAIL, if failed.
    * </ul>
    * @param unsigned long in_ulCaptureInterval: Frame interval to capture.
    */
   virtual HRESULT __stdcall SetCaptureInterval
   (
      unsigned long  in_ulCaptureInterval
   ) = 0;

   /**
    * Notifies the Sink Switcher that the next "writable" buffer received should be written to disk.
    * The call returns after the Sink Switcher receives the buffer.
    * <br><b>Remark:</b>
    * <ul><li>Should not be called while in StartCapture() mode. It is used for StopMotion functionality.
    * </ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return Values:</b>
    * <ul>
    * <li>MV_NOERROR, if the call was sucessfull.
	 * <li>MV_E_WRONG_STATE, if the capture interval is not 0.
    * </ul>
    * @param None.
    */
   virtual HRESULT __stdcall CaptureSingleFrameNow() = 0;

};



#endif //IMVMULTISINKCAPTURE_H
