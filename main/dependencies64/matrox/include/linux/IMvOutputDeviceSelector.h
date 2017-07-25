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
//                    IMVOUTPUTDEVICESELECTOR.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVOUTPUTDEVICESELECTOR_H
#define IMVOUTPUTDEVICESELECTOR_H

/** 
  * Some output filters support more than one output. This interface can be used to 
  * change the current output, and get the current set output.
  *
  * @interface 
  */
interface IMvOutputDeviceSelector : public IUnknown 
{
public:   

   /**
   *  Sets the current output.
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
   * <li>MV_E_ALREADY_IN_USE, if the output exists, but is not available.
   * <li>MV_E_NOT_FOUND,      if the output does not exist.
   * </ul>
   * @param <i>SMvOutputInfo& in_refOutputInfo</i>: Output info.
   */

   virtual HRESULT __stdcall SetCurrentOutput(const SMvOutputInfo& in_refOutputInfo) = 0;

   /**
   *  Gets the current output.
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
   * <li>MV_E_FAIL, if operation failed.
   * </ul>
   * @param <i>SMvOutputInfo& out_refOutputInfo</i>: Output info.
   */

   virtual HRESULT __stdcall GetCurrentOutput(SMvOutputInfo& out_refOutputInfo) = 0;

};

#endif //IMVOUTPUTSELECTION_H