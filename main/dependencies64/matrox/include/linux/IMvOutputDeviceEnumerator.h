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
//                    IMVOUTPUTDEVICEENUMERATOR.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVOUTPUTDEVICEENUMERATOR_H
#define IMVOUTPUTDEVICEENUMERATOR_H

/** 
* Some output filters support more than one output. This interface can be used to 
* enumerate the devices that are available to the user on this filter.
*
* @interface 
*/
interface IMvOutputDeviceEnumerator : public IUnknown {
public:

   /**
   *   Gets the next output device available.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> Gets the next output connected to the system.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   * <li>MV_E_FAIL,  if operation fails.
   * </ul>
   * @param <i>unsigned long  in_ulNbEnumOutputsRequested</i>: Size of the output array. Specifies the number of output descriptions user requests.
   * @param <i>SMvOutputInfo* out_pasMvOutputInfo[]</i>: Output array of SMvOutputInfo type. Contains the description of the available outputs.
   * @param <i>unsigned long* out_pulEnumOutputsFetched</i>: Actual number of output descriptions that are returned.
   */

   virtual HRESULT __stdcall  Next (unsigned long  in_ulNbEnumOutputsRequested, 
                                    SMvOutputInfo* out_pasMvOutputInfo[],               
                                    unsigned long* out_pulEnumOutputsFetched) = 0;

   /**
   *  Resets the enumerator.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   * <li>MV_E_FAIL, if operation failed.
   * </ul>
   */

   virtual HRESULT __stdcall Reset() = 0;

   /**
   *  Moves the enumerator forward by count.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   * <li>MV_E_FAIL, if operation failed.
   * </ul>
   * @param <i>unsigned long in_ulCount</i>: Number of outputs too skip.
   */
   virtual HRESULT __stdcall Skip (unsigned long in_ulCount) = 0;
};

#endif //IMVOUTPUTENUMERATOR_H