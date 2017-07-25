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
//                    IMvMessageTimingInfo.h
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


#ifndef IMVMESSAGETIMINGINFO_H
#define IMVMESSAGETIMINGINFO_H

/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has several methods which return different timing
* information.
* 
* 
* @interface 
*/
interface IMvMessageTimingInfo : public IUnknown
{
public:

   /**
   *  
   *	Gets the Stream time in editing resolution at which the message or error occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>uint64_t * out_pui64EresStreamTime </i>:The streamtime in editing resolution at which the message or error occurred.
   */
   virtual HRESULT __stdcall GetEresStreamTime( uint64_t * out_pui64EresStreamTime ) = 0;

   /**
   *  
   *	Gets the Stream time in output resolution at which the message or error occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>uint64_t * out_pui64OresStreamTime </i>:The streamtime in output resolution at which the message or error occured.
   */
   virtual HRESULT __stdcall GetOresStreamTime( uint64_t * out_pui64OresStreamTime) = 0;

   /**
   *  
   *	Gets the Stream time in input resolution at which the message or error occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>uint64_t * out_pui64IresStreamTime </i>:The streamtime in input resolution at which the message or error occurred.
   */
   virtual HRESULT __stdcall GetIresStreamTime( uint64_t * out_pui64IresStreamTime) = 0;

   /**
   *  
   *	Gets the Timeline position at which the message or error occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>uint64_t * out_pui64TimelinePos </i>:The timeline position at which the message or error occurred.
   */
   virtual HRESULT __stdcall GetTimeLinePosition( uint64_t * out_pui64TimelinePos) = 0;

   /**
   *  
   *	Gets the system time associated with the message or error that occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> This system time is in nanotime. The same as when calling GetTime on
   *        <li> the Matrox Clock.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   * </ul>
   * @param <i>uint64_t * out_pui64SystemTime </i>:The system time in nanotime for the message or error that occurred.
   */
   virtual HRESULT __stdcall GetSystemTime( uint64_t * out_pui64SystemTime) = 0;

   /**
   *  
   *	Gets the TimeCode associated with the message or error that occurred.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> This method will usually be supported for messages or errors that involve
   *        <li> the usage of DV-1394.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   * </ul>
   * @param <i>TIMECODE_SAMPLE * out_psTimeCode </i>:The time code for the message or error that occured.
   */
   virtual HRESULT __stdcall GetTimeCode( unsigned long * out_pulTimeCode) = 0;


};

#endif //IMVMESSAGETIMINGINFO_H
