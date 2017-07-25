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
//                    IMVAUDIOPULLING.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 20, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVAUDIOPULLING_H
#define IMVAUDIOPULLING_H

/**
 * Gets Flex audio samples from a user application.
 * @interface
 */
interface IMvAudioPulling : public IUnknown
{
public:

  /**
   * Requests an AVContent to the application.
   *
   * <br><b>Remark:</b>
   * <ul><li>The application will be returned to the requested AVContent through the provided callback function.
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>HRESULT error code, if operation failed.
   * </ul>
   * @param bool                in_bIsPulledForAnalysis:    Pulling is done while transform filter is analyzing the tree.
   * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in samples.
   * @param uint64_t            in_ui64Duration:            Duration pulled in samples.
   * @param double              in_dShuttlingSpeed:         Shuttling speed.
   * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
   * @param IMvAVContentReceiver in_pIMvAVContentReceiver:  Interface to call when the AVContent is available.
   */
virtual HRESULT __stdcall RequestForAVContent(  bool                   in_bIsPulledForAnalysis,
                                                uint64_t               in_ui64TimelinePositionInSamples,
                                                uint64_t               in_ui64DurationInSamples,
                                                double                 in_dShuttlingSpeed,
                                                unsigned long          in_ulSubCutlistID,
                                                IMvAVContentReceiver * in_pIMvAVContentReceiver ) = 0;

  /**
   * Pulls an input Flex audio samples buffer from an external module.
   *
   * <br><b>Remark:</b>
   * <ul><li>Host application should not hold the calling thread.
   *        <li>If some processing is needed, it can return the surface and signal the write completion later.
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>HRESULT error code, if operation failed.
   * </ul>
   * @param bool                in_bIsPulledForAnalysis:          Pulling is done while transform filter is analyzing the tree.
   * @param uint64_t            in_ui64TimelinePositionInSamples: Timeline position pulled in audio samples unit.
   * @param uint64_t            in_ui64DurationInSamples:         Duration pulled in audio samples unit.
   * @param double              in_dShuttlingSpeed:         Shuttling speed.
   * @param unsigned long       in_ulSubCutlistID:                Current sub-cutlist ID.
   * @param IMvAudioSamples     in_pIMvAudioSamples:              Pointer to Flex audio samples interface container received in the RequestForAVContent call.
   * @param HANDLE              in_hCompletionEvent:              Event to signal when the CPU part of the delivering is completed.
   */
  virtual HRESULT __stdcall WakeUpYourThreadToProcessPull( bool in_bIsPulledForAnalysis,
                                          uint64_t            in_ui64TimelinePositionInSamples,
                                          uint64_t            in_ui64DurationInSamples,
                                          double              in_dShuttlingSpeed,
                                          unsigned long       in_ulSubCutlistID,
                                          IMvAudioSamples    *in_pIMvAudioSamples,
                                          HANDLE              in_hCompletionEvent) = 0;

   /**
    * Cancels the pulling of an audio sample.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param bool                in_bIsPulledForAnalysis:    Pulling is done while transform filter is analyzing the tree.
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in samples.
    * @param uint64_t            in_ui64Duration:            Duration pulled in samples.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvAudioSamples     in_pIMvAudioSamples:        Audio samples to cancel.
    * @param HANDLE              in_hCompletionEvent:        Event to signal when the cpu part of the cancellation is completed.
    */
   virtual HRESULT __stdcall CancelPullAudioSamples ( bool in_bIsPulledForAnalysis,
                                          uint64_t            in_ui64TimelinePositionInSamples,
                                          uint64_t            in_ui64DurationInSamples,
                                          double              in_dShuttlingSpeed,
                                          unsigned long       in_ulSubCutlistID,
                                          IMvAudioSamples    *in_pIMvAudioSamples,
                                          HANDLE              in_hCompletionEvent) = 0;

   /**
    * Gets an input Flex audio sample description from an external module.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in samples.
    * @param uint64_t            in_ui64Duration:            Duration pulled in samples.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param SMvAudioSamplesDescription io_psAudioSampleDesc: Audio Sample description
    */
   virtual HRESULT __stdcall GetAudioSamplesDescription( uint64_t            in_ui64TimelinePositionInSamples,
                                                         uint64_t            in_ui64DurationInSamples,
                                                         double              in_dShuttlingSpeed,
                                                         unsigned long       in_ulSubCutlistID,
                                                         SMvAudioSamplesDescription  *io_psAudioSampleDesc ) = 0; 

   /**
   * Indicates the end of pull 
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>HRESULT error code, if operation failed.
   * </ul>
   */
   virtual HRESULT __stdcall EndOfPull () = 0;
};

#endif //IMVAUDIOPULLING_H
