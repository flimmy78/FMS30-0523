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
//                    IMVCAPTURESETTINGSANDCONTROL.H
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


#ifndef IMVCAPTURESETTINGSANDCONTROL_H
#define IMVCAPTURESETTINGSANDCONTROL_H

/** Controls the parameters of capturing. Timecode settings, scan and capture, 
 * Video bit depth, capture duration, and propagation delay are the parameters 
 * that can be set with this interface. This interface also includes methods to start 
 * and stop capture, which are the master controls that decipher if the video/audio 
 * will be written to disk.
 * 
 * @interface 
 */
interface IMvCaptureSettingsAndControl : public IUnknown
{
public:

   /**
    *  
    * Sets the initial timecode to begin capturing.
    * <br><b>Remarks:</b>
    * <ul><i><li> When the filter detects the material (audio and video) tagged with the 
    * timecode set in this method, it will start marking that material to be written to disk. Material 
    * prior to the start timecode will not be written to disk. 
    * This method can be combined with "SetDuration" or "SetEndTimecode".
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    * </ul>
    * @param <i>bool in_bEnable</i>:Boolean flag. If set to TRUE the start timecode passed in the next parameter is to be respected.  If set to FALSE, capture to disk begins when the graph is started. 	
    * @param <i>unsigned long in_ulStartTimeCode</i>:The start timecode where the capture to disk begins. If timecode is not available from input, it will be ignored.
    * @param <i>bool in_bIsFrameCount</i>:Boolean flag. If set to TRUE the start timecode passed is a frame count. If false, the start timecode is binary coded decimal (BCD). 	
    * @param <i>bool in_sTimeCodeRate</i>:The rate of the timecode when in BCD, i.e. in 24, 25, 30, 50, or 60
    */
   virtual HRESULT __stdcall SetStartTimecode( bool in_bEnable, unsigned long in_ulStartTimecode, bool in_bIsFrameCount, short in_sTimeCodeRate ) = 0;



   /**
    *  Sets the duration of capture.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Once video is marked to be written to disk, the Unified Input Filter will mark only 
    * the specified duration to be written to disk. Material past the duration will not be written 
    * to disk. 
    * This method can be combined with "SetStartTimecode". 
    * This method CANNOT BE used at the same time has "SetEndTimecode".
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param <i>bool in_bEnable</i>:Boolean flag. If set to TRUE the duration passed in the next parameter is to be respected.  If set to FALSE, capture to file will end when the graph is stopped. 	
    * @param <i>uint64_t in_ui64Duration</i>:The duration of the capture in frames.
    */
   virtual HRESULT __stdcall SetDuration( bool in_bEnable, unsigned long in_ulDurationInFrame ) = 0;



   /**
    *  
    * Sets the final timecode to stop capturing.
    * <br><b>Remarks:</b>
    * <ul><i><li> When the filter detects the material (audio and video) tagged with the 
    * timecode set in this method, it will stop marking material to be written to disk. Material 
    * past the end timecode will not be written to disk. Note: The data at the end end timecode will not be written to file.
    * This method can be combined with "SetStartTimecode".
    * This method CANNOT BE used at the same time has "SetDuration".
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    * </ul>
    * @param <i>bool in_bEnable</i>:Boolean flag. If set to TRUE the end timecode passed in the next parameter is to be respected.  If set to FALSE, capture to disk ends when the graph is stopped. 	
    * @param <i>unsigned long in_ulStartTimeCode</i>:The end timecode where the capture to disk ends. If timecode is not available from input, it will be ignored.
    * @param <i>bool in_bIsFrameCount</i>:Boolean flag. If set to TRUE the end timecode passed is a frame count. If false, the end timecode is binary coded decimal (BCD). 	
    */
   virtual HRESULT __stdcall SetEndTimecode( bool in_bEnable, unsigned long in_ulEndTimecode, bool in_bIsFrameCount ) = 0;



   /**
    *  Enables the scan and capture mode.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Scan and capture mode creates separate files according 
    * to the scene changes in the material. 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed succefully.
    * </ul>
    * @param <i>bool in_bEnable</i>: Boolean flag. Set to TRUE to enable, or FALSE to disable (FALSE is the default setting).
    */
   virtual HRESULT __stdcall SetScanAndCaptureMode( bool in_bEnable ) = 0;



   /**
    * Sets the the pulldown settings that are on the device you are capturing from.  
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> The type of pulldown sequence,  with the timecode and the frame 
    * of sequence for that timecode, are set with this method.  
    * The user must call this method with the correct settings, so that the Unified Input Filter 
    * can correctly do the reverse pulldown.  
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param  EMvPullDownSequence in_ePullDownSeq:The type of pulldown sequence on the device 
    * that is being captured from. It is either 3-2 pulldown or advanced pulldown.
    * @param  unsigned long in_ulTimeCodeForSequence:The timecode (frame count) for the frame of 
    * sequence that is passed in the next parameter.
    * @param  EMvFrameOfSequence in_eFrameSeqAtTimeCode:The frame of sequence for the timecode 
    * that is specified in the previous parameter.
    */
   virtual HRESULT __stdcall SetPullDownSettings( EMvPullDownSequence in_ePullDownSeq,
                                                  unsigned long       in_ulTimeCodeForSequence, 
                                                  EMvFrameOfSequence  in_eFrameSeqAtTimeCode ) = 0;


   /**
   * Sets the timecode that is presented at specific system time.  The UIF module can then
   * associate buffers captured at specific system times with a timecode.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param  bool in_bEnable:Boolean flag. If set to TRUE parameters passed in this method
   * will be used to calculate the timecode.
   * @param  uint64_t in_ui64SystemTimeOfTimeCode:The systemtime at which the timecode passed
   * in the next parameter is presented.
   * @param  unsigned long in_ulTimeCodeInFramesAtSystemTime:The timecode at presented at the systemtime
   * passed in the previous parameter.
   */
   virtual HRESULT __stdcall SetTimeCodeAtSystemTime( bool in_bEnable,
                                                      uint64_t in_ui64SystemTimeOfTimeCode,           
                                                      unsigned long in_ulTimeCodeInFramesAtSystemTime ) = 0 ;

   /**
    *  Sets the bit depth for capture.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> This method is only valid when the input device chosen is a BOB 
    * (break out box) input device.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    * </ul>
    * @param <i>EMvVideoBitDepth in_eBitDepth</i>:The bit depth of the uncompressed 
    * capture.  It is either 8 bit or 10 bit.
    */
   virtual HRESULT __stdcall SetBitDepthForCapture( EMvVideoBitDepth in_eBitDepth ) = 0;



   /**
    *  Sets the propagation delay for the capture.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> The propagation delay is subtracted from the Runat time given to 
    * the Unified Input Filter, so that the Unified Input Filter will begin to capture video at the Runat 
    * time minus the propagation delay. So if it is important for the user to 
    * capture at a specific system time, the StartCapture method should be called 
    * prior to running the filter graph, and the user should take into account the 
    * propagation delay and the Runat time given to the filter graph.  The 
    * propagation delay cannot be infinitely large, and the maximum amount is to 
    * be determined, but it is number in the 10's of frames.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param <i>uint64_t in_ui64Delay</i>:The propagation delay in nanotime (100ns).
    */
   virtual HRESULT __stdcall SetCapturePropagationDelay( uint64_t in_ui64Delay ) = 0;



   /**
    *  Gets the default capture propagation delay for the capture that is going to be done.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> If the SetCapturePropagationDelay hasn't been called, the default 
    * value is used by the Unified Input Filter.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param uint64_t * out_pui64Delay:The default propagation delay in nanotime (100ns).
    */
   virtual HRESULT __stdcall GetDefaultCapturePropagationDelay( uint64_t * out_pui64Delay ) = 0;

   /**
   *  Sets the mode to varicam mode. 
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> The UIF needs to know it is capturing varicam material 
   * so that it will know that it is normal not to be receiving material
   * with a frame rate that doesn't match that of the editing res.(i.e. 720p 24M).
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param <i>b bool in_bEnableVaricam</i>:Flag to enable/disable varicam mode.
   */
   virtual HRESULT __stdcall SetVaricamMode( bool in_bEnableVaricam ) = 0;


};

interface IMvCaptureSettingsAndControl2 : public IMvCaptureSettingsAndControl
{
public:

	/**
	*  
	* The WriteToFileStatus flag on a buffer will never be set when this
	* function is called.
	* <br><b>Remarks:</b>
	* <ul><i><li> When the user calls this function, it will prevent the
	* WriteToFileStatus flag to be set on any buffer that is processed.
	* By default, the WriteToFileStatus is enabled meaning that if the flag
	* needs to be set on a buffer, it will be set.
	* </i></ul>
	* 
	* <b>Return type:</b>
	* <ul><li>HRESULT
	* </ul>
	* <b>Return values:</b> 
	* <ul><li>MV_NOERROR, if operation succeeded.
	* </ul>
	* @param <i>bool in_bEnable</i>:Boolean flag. If set to TRUE the WriteToFileStatus flag on the buffer will never be set.  If set to FALSE, The WriteToFileStatus flag will be set when needed. 	
	*/
	virtual HRESULT __stdcall DisableWriteToFileStatus(bool in_bDisable) = 0;

   /**
   *  
   * The rate of audio capture correction needed to applied to the captured buffer from the DirectSound capture buffer
   * <br><b>Remarks:</b>
   * <ul><i><li> The user must call this to set the proper rate to which
   * the capture must correct for the clock drift from the matrox clock.
   * By default, no correction is appled or the parameter has the rate of 0.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   * </ul>
   * @param <i>unsigned long in_ulSamples</i>:unsigned long count of samples before one correction. .If set to 0, no correction is applied.
   * @param <i>bool in_bDrop</i>:Boolean flag. If set to true a sample is removed, and if false a sample is generated.
   */
   virtual HRESULT __stdcall SetAudioCaptureCorrectionRate(unsigned long in_ulSamples, bool in_bDrop) = 0;
   virtual HRESULT __stdcall GetAudioCaptureCorrectionRate(unsigned long *out_pulSamples, bool *out_pbDrop) = 0;

   /**
   * Set the input scaling mode for the input filter.
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param EMvScalingMode in_eScalingMode: scaling mode.
   */
   virtual HRESULT __stdcall SetInputScalingMode(EMvScalingMode in_eScalingMode) = 0;

   /**
   * Gets the input scaling mode for the input filter.
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param EMvScalingMode& in_refeScalingMode: Reference to the enum of scaling mode.
   */
   virtual HRESULT __stdcall GetInputScalingMode(EMvScalingMode& in_refeScalingMode) = 0;

};


#endif //IMVCAPTURESETTINGSANDCONTROL_H




