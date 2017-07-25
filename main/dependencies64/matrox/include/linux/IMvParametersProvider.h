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
//                    IMVPARAMETERSPROVIDER.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 23, 2003 - 6:17:40 PM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVPARAMETERSPROVIDER_H
#define IMVPARAMETERSPROVIDER_H

//==========================================================================;
// Header files
//==========================================================================;

#include "mvSubjectIF.h"

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMv
//==========================================================================;

/**
 * This generic interface is used to access the Parameters Provider. The role of the Parameters Provider is to generate parameters that the Parametric Effect can understand. It can be a keyframe container, a file that contains pre-calculated parameters, a user interface, an external device, etc. The Parametric Effect uses these parameters to generate the actual Effect Settings and GFX file names.<br>
 * <br><b>Remark:</b>
 * <ul><li>The same Parameter Provider can be attached to multiple Parametric Effects if it finds that they are compatible. To be compatible, two Parametric Effects must at least have the same GUID. As well, depending on the implementation, the Parameters Provider may need to validate some other specific information before accepting to be attached to multiple Parametric Effects. </ul>
 * @interface
 */
interface IMvParametersProvider : public IMvSubject
{
   //==========================================================================;
   // Public operations
   //==========================================================================;
public:

   /**
    * This function is called internally when attaching the Parameters Provider to a Parametric Effect. If the
    * Parameters Provider finds that the given Parametric Effect is not compatible, the function fails. The specific
    * reason of the failure is implementation specific.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>HRESULT error code, if a module reported an error.
    * </ul>
    *
    * @param IMvParametricEffect * in_pIParamFX: Input Parameteric effect interface
    */
   virtual HRESULT __stdcall Initialize(IMvParametricEffect * in_pIParamFX) = 0;

   /**
    * Locks the access to the Parameters Provider to the calling thread so that the thread has exclusive access to it.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the operation completed successfully.
    * <li>MV_E_FAIL, if the lock failed.
    * </ul>
    *
    * @param NONE
    */
   virtual HRESULT __stdcall LockAccess() = 0;

   /**
    * Checks if access to the calling thread is locked.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>MV_E_FAIL, if a parameter is invalid.
    * </ul>
    *
    * @param bool * out_pbIsLocked : Pointer to the boolean value that receives the result.
    */
   virtual HRESULT __stdcall IsAccessLocked(bool * out_pbIsLocked) = 0;

   /**
    * Unlocks access to the Parameters Provider.<br>
    * 
    * <br><b>Remark:</b>
	* <ul><li>None.</ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation completed successfully.
    * <li>MV_E_FAIL, if the access was not locked previously.
    * </ul>
    *
    * @param NONE
    */
   virtual HRESULT __stdcall UnlockAccess() = 0;
};


#endif //IMVPARAMETERSPROVIDER_H
