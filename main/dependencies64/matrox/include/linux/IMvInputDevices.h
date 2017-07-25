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
//                    IMVINPUTDEVICES.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:            Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVINPUTDEVICES_H
#define IMVINPUTDEVICES_H


/** 
 * Enumerates all the "input devices" and sets which actual "input device" are to be used.
 * @interface 
 */
interface IMvInputDevices : public IUnknown
{
public:

   /**
    * Returns the number of input devices available. For example, in a system with an X.linkSD,
    * an X.linkHD, and one DV-1394 camera connected, it would return three.
    *  
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long * out_pulDeviceCount</i>: The number of input devices are set in this variable.
    */
  virtual HRESULT __stdcall GetInputDeviceCount( unsigned long * out_pulDeviceCount ) = 0;

   /**
    * Returns the same count as GetInputDeviceCount plus HW device info so that we can have video 
    * devices with no audio devices. 
    * no audio is supported.
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long * out_pulDeviceCount</i>: The number of input devices are set in this variable.
    * @param <i>SMvDeviceCount * out_psDeviceCount</i>: The structure containing the HW device counts.
    */
  virtual HRESULT __stdcall GetInputDeviceCountEx( unsigned long * out_pulDeviceCount, SMvDeviceCount * out_psDeviceCount ) = 0;

   /**
    * Enumerates all the input devices in the system.  Each input device supports video
    * and audio.  The user should allocate arrays to be passed.
    *  
    *
    * <br><b>Remarks:</b>
    * <ul><li> The size of the arrays that need to be allocated are determined by 
    * calling the IMvInputDevices::GetInputDeviceCount method.  The IMvIODeviceControl 
    * interfaces are returned to list, control, and set the inputs on the input devices.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvInputDeviceType * out_paeInputDeviceType[]: The type of input devices 
    * set in an array.  It is either an X.link breakout box or a DV-1394 device.
    * @param EMvInputDeviceType * out_painputdevicetype[]: An array of strings 
    * describing the input devices.
    * @param IMvIODeviceControl * * out_paIInputDeviceController[]: An array of 
    * the IMvIODeviceControl interfaces to control the input devices.
    * @param unsigned long in_ulArraySize: The size of the arrays passed to this method.
    */
  virtual HRESULT __stdcall EnumerateInputDevices(
              EMvInputDeviceType * out_paeInputDeviceType[],
              char * out_paszInputDeviceDescription[],
              IMvIODeviceControl * * out_paIInputDeviceController[],
              unsigned long in_ulArraySize) = 0;


   /**
    *  Sets the active video and audio input device for capture.  
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Passes the zero-based index values that were given through 
    * the EnumerateInputDevices call. In a system with one X.linkSD and one X.linkHD, 
    * audio can be captured from one breakout box and video from the other.  If a 
    * DV-1394 device is chosen for video, the same DV-1394 device must be 
    * chosen for audio.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned int in_uiVideoDeviceIndex: The zero based index of the input devices returned from EnumerateInputDevices call, that is chosen to capture video from.
    * @param unsigned int in_uiAudioDeviceIndex: The zero based index of the input devices returned from EnumerateInputDevices call, that is chosen to capture audio from.
    */
   virtual HRESULT __stdcall SetVideoAndAudioInputDeviceForCapture(
     unsigned int in_uiVideoDeviceIndex,
     unsigned int in_uiAudioDeviceIndex ) = 0;

   /**
   *  Gets the active video and audio input device for capture.  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> Returns the zero-based index values that were given through 
   * the SetVideoAndAudioInputDeviceForCapture call. If the index wasn't set, 
   * the function will return an error instead of passing back the default value.
   * In a system with one X.linkSD and one X.linkHD, audio can be captured from 
   * one breakout box and video from the other. If a DV-1394 device is chosen for 
   * video, the same DV-1394 device will be chosen for audio.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned int out_ruiVideoDeviceIndex: The zero based index of the input devices set through SetVideoAndAudioInputDeviceForCapture call, that is chosen to capture video from.
   * @param unsigned int out_ruiAudioDeviceIndex: The zero based index of the input devices returned from SetVideoAndAudioInputDeviceForCapture call, that is chosen to capture audio from.
   */
   virtual HRESULT __stdcall GetVideoAndAudioInputDeviceForCapture(
      unsigned int& out_ruiVideoDeviceIndex, 
      unsigned int& out_ruiAudioDeviceIndex ) = 0;

   /**
   *  Sets which streams (video and four audio) are enabled for capture.  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> This method can only be called after the SetVideoAndAudioInputDeviceForCapture is called.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>MV_E_NOT_INITIALIZED, if no input device has been chosen, by calling the SetVideoAndAudioInputDeviceForCapture.
   * </ul>
   * @param bool in_bEnableVideoCapture: Decides to capture video or not.
   * @param bool in_bEnableAudioCaptureOnStream0: Boolean flag. Set to TRUE to capture the first audio stream.
   * @param bool in_bEnableAudioCaptureOnStream1: Boolean flag. Set to TRUE to capture the second audio stream.
   * @param bool in_bEnableAudioCaptureOnStream2: Boolean flag. Set to TRUE to capture the third audio stream.
   * @param bool in_bEnableAudioCaptureOnStream3: Boolean flag. Set to TRUE to capture the fourth audio stream.
   * @param bool in_bEnableAudioCaptureOnStream4: Boolean flag. Set to TRUE to capture the fifth audio (DSound) stream.
   */
   virtual HRESULT __stdcall SetStreamsToCapture(
      bool in_bEnableVideoCapture,
      bool in_bEnableAudioCaptureOnStream0,
      bool in_bEnableAudioCaptureOnStream1,
      bool in_bEnableAudioCaptureOnStream2,
      bool in_bEnableAudioCaptureOnStream3,
      bool in_bEnableAudioCaptureOnStream4
      ) = 0;

   /**
   *  Gets the streams( video and four audio ) that are enabled for capture.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> This method can only be called after the SetVideoAndAudioInputDeviceForCapture is called.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>MV_E_NOT_INITIALIZED, if no input device has been chosen, by calling the SetVideoAndAudioInputDeviceForCapture.
   * </ul>
   * @param bool * out_pbVideoCaptureEnabled: Boolean flag. Set to true if video capture is enabled.
   * @param bool * out_pbAudioCaptureEnabledOnStream0: Boolean flag. Set to TRUE if audio capture for the first audio stream is enabled.
   * @param bool * out_pbAudioCaptureEnabledOnStream1: Boolean flag. Set to TRUE if audio capture for the second audio stream is enabled.
   * @param bool * out_pbAudioCaptureEnabledOnStream2: Boolean flag. Set to TRUE if audio capture for the third audio stream is enabled.
   * @param bool * out_pbAudioCaptureEnabledOnStream3: Boolean flag. Set to TRUE if audio capture for the fourth audio stream is enabled.
   * @param bool * out_pbAudioCaptureEnabledOnStream4: Boolean flag. Set to TRUE if audio capture for the fifth audio stream is enabled.
   */
   virtual HRESULT __stdcall GetStreamsToCapture(
      bool * out_pbVideoCaptureEnabled,
      bool * out_pbAudioCaptureEnabledOnStream0,
      bool * out_pbAudioCaptureEnabledOnStream1,
      bool * out_pbAudioCaptureEnabledOnStream2,
      bool * out_pbAudioCaptureEnabledOnStream3,
      bool * out_pbAudioCaptureEnabledOnStream4
      ) = 0;


   /**
    *  Sets the Input device which will be the genlock master.
    * Passes the zero-based index value.
    * Returns the Flex interface to control Genlock settings.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Passes the zero-based index values that were given through 
    * the EnumerateInputDevices call. In a system with one X.linkSD and one X.linkHD, 
    * audio can be captured from one breakout box and video from the other.  If a 
    * DV-1394 device is chosen for video, the same DV-1394 device must be 
    * chosen for audio.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned int in_uiDeviceIndex</i>: The zero based index of 
    * the input devices returned from EnumerateInputDevices call, that is 
    * chosen to be the Genlock Master.
    * @param <i>IMvGenlockControl ** out_ppIGenlockControl</i>: The Interface 
    * to control the genlock settings of the input device chosen in the previous parameter.
    */
   virtual HRESULT __stdcall SetInputDeviceForMasterGenlock(
                                   unsigned int in_uiDeviceIndex,
                                   IMvGenlockControl ** out_pIGenlockControl) = 0;




   /**
    * To release the current input devices chosen for capture.  
    * After calling this, the Unified Input Filter is in a state in which it doesn't capture.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if failed.
    * </ul>
    */
  virtual HRESULT __stdcall ReleaseCurrentInputDeviceForCapture() = 0;


  /**
  *  Gets the type of 1394 device, either DV or HDV type.
  *
  * <br><b>Remarks:</b>
  * <ul><i><li> If the input device is not 1394 then it will return invalid type.
  * </i></ul>
  * 
  * <b>Return type:</b>
  * <ul><li>HRESULT
  * </ul>
  * <b>Return values:</b> 
  * <ul>
  * <li>MV_NOERROR, if completed successfully.
  * <li>HRESULT error code, if failed.
  * </ul>
  * @param <i>EMv1394InputDeviceType * out_peMv1394InputDeviceType</i>: type of 1394 device returned.
  */
  virtual HRESULT __stdcall Get1394InputDeviceType( EMv1394InputDeviceType * out_peMv1394InputDeviceType) = 0;
     
};



#endif //IMVINPUTDEVICES_H

