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
//                    IMVCUTLISTMANAGER.H
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


#ifndef IMVCUTLISTMANAGER_H
#define IMVCUTLISTMANAGER_H

#include "mvUnknown.h"
#include "IMvCutList.h"

/**
*@interface
* All filters (e.g. Source and Transform) that support cutlists must support <b>IMvFilterCutListManager</b>
* in order to receive this interface.
*/
interface IMvCutListManager : public IUnknown
{
public:   

   /**
    * Retrieves a given cutlist in the Cutlist Manager.
    * <br><b>Remark:</b>
    * <ul><li>The reference count on the returned IMvCutList is incremented by one. The caller should release the interface when it's done with it.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the cutlist was retrieved successfully.
	 *	    <li>MV_E_CUTLIST_ID_NOT_FOUND, if the cutlist with the specified cutlist ID was not found.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_ppIMvCutList</var> is an invalid pointer.
    * </ul>
    * @param <i>unsigned long in_ulCutListID </i>: Cutlist ID.
    * @param <i>IMvCutList out_ppIMvCutList </i>: Pointer to cutlist's pointer.
    */
   virtual HRESULT __stdcall GetCutList
   (
      unsigned long     in_ulCutListID,
      IMvCutList	**out_ppIMvCutList
   ) = 0;

	/**
	 * Gets the media type information of the Cutlist Manager.<br>
    * <b>Remark:</b><ul><li>None</ul>
    * <b>Return Type:</b>
	 * <ul><li>HRESULT</ul>
	 * <b>Return Values:</b>
	 * <ul><li>MV_NOERROR, if the media type was retrieved successfully.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <i>out_ppsMvMediaType </i>is an invalid pointer.
	 *     <li>MV_E_FAIL, if the Cutlist Manager does not have the media type information.
	 * </ul>
    * @param <i>SMvMediaType out_psMvMediaType </i>: Pointer to the SMvMediaType media type structure.
	 */
   virtual HRESULT __stdcall GetMvMediaType
   (
       SMvMediaType *out_psMvMediaType
   ) = 0;

};



#endif //IMVCUTLISTMANAGER_H
