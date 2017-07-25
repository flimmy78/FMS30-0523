/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

#ifndef IMVFILTERCUTLIST_H
#define IMVFILTERCUTLIST_H
#include "IMvCutList.h"
#include "mvUnknown.h"

/**
 * Adds the functionality of setting a 
 * Cutlist Manager on a Source or Transform filter.
 * @interface
 */
interface IMvFilterCutListManager : public IUnknown
{
public:

   /**
    * Retrieves the Cutlist Manager currently held by the Source or Transform filters.<br> <br>
    * <b>Remark:</b> <ul><li>None.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the Cutlist Manager was returned successfully.
    *     <li>MV_E_NOT_INITIALIZED, if there's no Cutlist Manager set on the filter.
    * </ul>
    * @param <i>IMvCutListManager out_ppICutListManager </i>: Pointer to the Cutlist Manager's pointer.
    */

   virtual HRESULT __stdcall GetCutListManager
   (
   	IMvCutListManager		**out_ppICutListManager
   ) = 0;

	/**
	 * Sets a Cutlist Manager on the Source or Transform filters.<br> <br>
	 * <b>Remark:</b> <ul><li>Releases the previously set Cutlist Manager.</ul>
	 * <b>Return Type:</b><ul></ul>
	 * <ul><li>HRESULT</ul>
	 * <b>Return Values:</b>
	 * <ul><li>MV_NOERROR, if the Cutlist Manager was set successfully.
	 *     <li>MV_E_INVALID_POINTER, if the Cutlist Manager pointer is NULL or invalid.
    * </ul>
    * @param <i>IMvCutListManager in_pICutListManager </i>: Pointer to the Cutlist Manager.
	 */
   virtual HRESULT __stdcall SetCutListManager
   (
      IMvCutListManager *in_pICutListManager
   ) = 0;

   /**
    * Releases the current element in the current cutlist
    * being held by the Source or Transform filters.<br> <br>
    * <b>Remark:</b> <ul><li>The filters will not release the cutlist on this call.</ul>
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the element was released successfully.
    *     <li>MV_E_WRONG_STATE, if the filter is not in the STOPPED state. This function call is valid only if the filter is in the STOPPED state.
    * </ul>
    */
   virtual HRESULT __stdcall FreeCurrentElement() = 0;

};
#endif //IMVFILTERCUTLISTMANAGER_H