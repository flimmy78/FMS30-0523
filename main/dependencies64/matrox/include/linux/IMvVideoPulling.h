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
//                    IMVVIDEOPULLING.H
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

#ifndef IMVVIDEOPULLING_H
#define IMVVIDEOPULLING_H

/**
 * This interface is used to receive a video stream (Flex surfaces) from a host application.
 * Implemented by an application.
 * @interface
 */
interface IMvVideoPulling : public IUnknown
{
public:

   /**
    * This is called by the graph to request an AVContent.
    *
    * <br><b>Remark:</b>
    * <ul><li>.
    *     <li>.
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
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in ERes unit.
    * @param uint64_t            in_ui64Duration:            Duration pulled in ERes unit.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvAVContentReceiver in_pIMvAVContentReceiver:  Interface to call with the AVContent when this one is available.
    */
   virtual HRESULT __stdcall RequestForAVContent( bool                    in_bIsPulledForAnalysis,
                                                  uint64_t               in_ui64TimelinePosition,
                                                  uint64_t               in_ui64Duration,
                                                  double                 in_dShuttlingSpeed,
                                                  unsigned long          in_ulSubCutlistID,
                                                  IMvAVContentReceiver * in_pIMvAVContentReceiver ) = 0;

   /**
    * Pulls an input Flex surface from an external module.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    *     <li>If some processing is needed it can return the surface and signal the write completion later.
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
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in ERes unit.
    * @param uint64_t            in_ui64Duration:            Duration pulled in ERes unit.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvSurface          in_pIMvSurface:             Surface delivered. 
    * @param HANDLE              in_hCompletionEvent:        Event to call when the thread finished using the CPU.
    */
   virtual HRESULT __stdcall WakeUpYourThreadToProcessPull
   ( 
      bool in_bIsPulledForAnalysis,
      uint64_t            in_ui64TimelinePosition,
      uint64_t            in_ui64Duration,
      double              in_dShuttlingSpeed,
      unsigned long       in_ulSubCutlistID,
      IMvSurface         *in_pIMvSurface,
      HANDLE              in_hCompletionEvent
   ) = 0;

   /**
    * Cancels the pulling of a Flex Surface.
    *
    * <br><b>Remark:</b>
    * <ul><li>
    *     <li>
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
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in ERes unit.
    * @param uint64_t            in_ui64Duration:            Duration pulled in ERes unit.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvSurface          in_pIMvSurface:             Surface to cancel.
    * @param HANDLE              in_hCompletionEvent:        Event to set when the cancellation is finished (CPU is not used anymore).
    */
   virtual HRESULT __stdcall CancelPullSurface 
   ( 
      bool in_bIsPulledForAnalysis,
      uint64_t            in_ui64TimelinePosition,
      uint64_t            in_ui64Duration,
      double              in_dShuttlingSpeed,
      unsigned long       in_ulSubCutlistID,
      IMvSurface         *in_pIMvSurface,
      HANDLE              in_hCompletionEvent
   ) = 0;

   /**
    * Gets an input Flex surface description from an external module.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    *     <li>If some processing is needed it can return the surface and signal the write completion later.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in ERes unit.
    * @param uint64_t            in_ui64Duration:            Duration pulled in ERes unit.
    * @param double              in_dShuttlingSpeed:         Shuttling speed.
    * @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param SMvSurfaceDescription io_psSurfaceDesc:         Surface description
    */
   virtual HRESULT __stdcall GetSurfaceDescription(   uint64_t            in_ui64TimelinePosition,
                                                      uint64_t            in_ui64Duration,
                                                      double              in_dShuttlingSpeed,
                                                      unsigned long       in_ulSubCutlistID,
                                                      SMvSurfaceDescription  *io_psSurfaceDesc ) = 0;

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



#endif //IMVVIDEOPULLING_H




