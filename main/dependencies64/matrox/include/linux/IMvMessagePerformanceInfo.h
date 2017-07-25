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
//                    IMvMessagePerformanceInfo.h
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


#ifndef IMVMESSAGEPERFORMANCEINFO_H
#define IMVMESSAGEPERFORMANCEINFO_H

/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has one method which returns the timeline position and the 
* performance factor associated to that position.
* 
* 
* @interface 
*/
interface IMvMessagePerformanceInfo : public IUnknown
{
public:

   /**
   *  
   *	Gets the performance factor of a played (or scrubbed) timeline position.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> Performance factor is used to give an indication about the "realtime" level of the specified timeline position.
   * <li> Performance factor messages can be disabled by calling DisablePerformanceReporting method on the IMvGraphStateControl interface.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>uint64_t *out_pui64TimelinePosition </i>:The timeline position for which the performance factor has been computed.
   * @param <i>float *out_pfPerformanceFactor </i>:The performance factor associated to the timeline position. A performance factor of 0.0 means that processing engines were totally idle for the processing of the specified timeline position. Performance factors between 0.0 and 1.0 mean that the processing of the specified timeline position can be considered realtime, yet timeline positions with performance factor values around 1.0 can occasionally caused dropped frames. Values higher than 1.0 mean non-realtime, yet their associated timeline position may not necessarily cause dropped frames. In brief, the busier the processing engines are in processing the timeline position, the higher the performance factor.
   */
   virtual HRESULT __stdcall GetPerformanceFactor
      (
      uint64_t *out_pui64TimelinePosition,
      float *out_pfPerformanceFactor
      ) = 0;


   /**
   *  
   *	Gets each specific engine performance factor of a played (or scrubbed) timeline position.
   *
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_INVALID_STRUCTURE_SIZE, if the size of the provided structure is not properly initialized.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   * </ul>
   * @param <i>uint64_t *out_pui64TimelinePosition </i>:The timeline position for which the performance factors have been computed.
   * @param <i>SMvEnginePerformanceFactors *io_psEnginePerformanceFactors </i>: Pointer to a structure containing the performance factor of each engine present in the system for the given timeline position. A performance factor of 0.0 means that processing engine was totally idle for the processing of the specified timeline position. 
   */
   virtual HRESULT __stdcall GetEnginePerformanceFactors
      (
      uint64_t *out_pui64TimelinePosition,
      SMvEnginePerformanceFactors *io_psEnginePerformanceFactors
      ) = 0;

};

#endif //IMVMESSAGEPERFORMANCEINFO_H
