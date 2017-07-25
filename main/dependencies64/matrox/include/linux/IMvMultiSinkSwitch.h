
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
//                    
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVMULTISINKSWITCH_H
#define IMVMULTISINKSWITCH_H
#include "mvUnknown.h"
#include "mvTypes.h"

/**
* Control and informational interface for the Sink Switcher filter.
* @interface
* 
*/
interface IMvMultiSinkSwitch : public IUnknown
{
public:

   /**
    *  Cues the next file that's to be used in the capture.
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
    *     <li>MV_E_FAIL, if  failed.
    * </ul>
    * @param <i>const unsigned long in_ulCookie</i>: The cookie of the next file.
    */
   virtual HRESULT __stdcall Cue
   (
       const unsigned long in_ulCookie
   ) = 0;

   /**
    *  Verifies whether or not a file is ready to be captured to.
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
    *     <li>MV_TIME_OUT, if the operation timed out.
    *     <li>MV_E_FAIL, if failed.
    * </ul>
    * @param <i>const uint64_t in_ui64MilliSecTimeOut</i>: Delay after which to time out is issued.
    * @param <i>const unsigned long in_ulCookie</i>: Cookie of file.
    */
   virtual HRESULT __stdcall IsCued
   (
       const uint64_t 	in_ui64MilliSecTimeOut,
       const unsigned long in_ulCookie
   ) = 0;

   /**
    *  Gets the boolean value that verfies whether or not a file can be cued.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li>The user can cue only one file at a time. 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FAIL, if failed.
    * </ul>
    * @param <i>bool  *out_pbCanCue</i>: TRUE if the file can be cued. FALSE, otherwise.
    */
   virtual HRESULT __stdcall CanCue
   (
      bool  *out_pbCanCue
   ) = 0;

   /**
    *  Resets the file that is currently cued.
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
    *     <li>MV_E_FAIL, if failed.
    * </ul>
    * @param <i>const unsigned long in_ulCookie</i>: Cookie of the file to reset.
    */
   virtual HRESULT __stdcall Reset
   (
       const unsigned long in_ulCookie
   ) = 0;

   /**
    *  Specifies the time to switch capturing to the next file.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> If the switch time has passed, the switch occurs as soon as possible.
    * In this case, the filter is forced to resume streaming.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FAIL, if failed.
    * </ul>
    * @param <i>const unsigned long in_ulCookie</i>: Cookie of the file to switch to.
    * @param <i>const uint64_t in_ui64SwitchAtInFrames</i>: Frame position in stream time.
    */
   virtual HRESULT __stdcall SwitchAt
   (
       const unsigned long in_ulCookie,
       const uint64_t 	in_ui64SwitchAtInFrames
   ) = 0;

   /**
    *  Gets the current stream information.
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
	*	 <li>MV_E_FAIL, if  failed.
    * </ul>
    * @param <i>unsigned long *out_pulCookie</i>: Pointer to the cookie of current file.
	* @param <i>unsigned long *out_pulCutListID</i>: Pointer to the cutlist ID.
    * @param <i>uint64_t *out_pui64StreamTimeInFrames</i>: Pointer to the stream time in frames.
    * @param <i>uint64_t *out_pui64MediaTimeInFrames</i>: Pointer to the media time in frames.
    * @param <i>uint64_t *out_pui64TimelineTimeInEres</i>: Pointer to the Timeline position in frames.
	* @param <i>uint64_t *out_pui64TimelineTimeInOres</i>: Pointer to the Timeline postion in the output resolution.
    */
   virtual HRESULT __stdcall GetCurrentStreamInfo
   (
       unsigned long *out_pulCookie,
       unsigned long *out_pulCutListID,
       uint64_t 		*out_pui64StreamTimeInFrames,
       uint64_t 		*out_pui64MediaTimeInFrames,
       uint64_t 		*out_pui64TimelineTimeInEres,
       uint64_t 		*out_pui64TimelineTimeInOres
   ) = 0;

   /**
    *  Gets the next possible stream time a SwitchAt() can occur.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> This call blocks the filter from streaming until a SwitchAt() is received,
    * or for a maximum of 10 seconds.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
	*	 <li>MV_E_FAIL, if  failed.
    * </ul>
    * @param <i>uint64_t *out_pui64StreamTimeInFrames </i>: Pointer to the next stream time in frames.
    */
   virtual HRESULT __stdcall GetNextStreamTime
   (
       uint64_t 	*out_pui64StreamTimeInFrames 
   ) = 0;
};
#endif //IMVMULTISINKSWITCH_H