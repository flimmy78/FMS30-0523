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
//                    IMVDIRECTSOUNDCAPTURESETTINGS.H
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

#ifndef IMVDIRECTSOUNDCAPTURESETTINGS_H
#define IMVDIRECTSOUNDCAPTURESETTINGS_H

/** Allows the selection of the DirectSound input device used for capture.
* @interface 
*/
interface IMvDirectSoundCaptureSettings : public IUnknown
{
public:


	/**
	*  
	* In Windows Vista, we need to tell the UIF which audio device to use for capture.
	* <br><b>Remarks:</b>
	* <ul><i><li> 
	* </i></ul>
	* 
	* <b>Return type:</b>
	* <ul><li>HRESULT
	* </ul>
	* <b>Return values:</b> 
	* <ul><li>MV_NOERROR, if operation succeeded.
	* </ul>
	* @param <i>GUID in_guidAudioDevice</i>:The GUID of the device to use for capture.  This corresponds to a specific input of the sound card on Windows Vista.
	*/
	virtual HRESULT __stdcall SelectDirectSoundDeviceForCapture(GUID in_guidAudioDevice) = 0;

   /**
   *  
   * In Windows Vista, we need to tell the UIF which audio device to use for capture.
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   * </ul>
   * @param <i>GUID in_guidAudioDevice</i>:The GUID of the device to use for capture.  This corresponds to a specific input of the sound card on Windows Vista.
   */
   virtual HRESULT __stdcall GetDirectSoundDeviceUsedForCapture(GUID *out_pguidAudioDevice) = 0;

};

#endif //IMVDIRECTSOUNDCAPTURESETTINGS_H




