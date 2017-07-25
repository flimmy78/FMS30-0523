//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvGfxFileNameHelperInit.h $
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


#ifndef IMVGFXFILENAMEHELPERINIT_H
#define IMVGFXFILENAMEHELPERINIT_H

#include "mvUnknown.h"//For IUnknown

/** Allows the caller to initialize the <i>GfxFileHelper</i> object and thus use the <b>IMvGfxFileNameHelper</b> interface.
 * @interface */
interface IMvGfxFileNameHelperInit : public IUnknown
{
public:    

   /**
   * Initializes the <i>GfxFileHelper</i> object on a specified GFX file type and resolution.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>HRESULT
   * </ul>
   *
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the <i>GfxFileHelper</i> object was initialized sucessfully.
   *     <li>MV_E_FAIL, if the <i>GfxFileHelper</i> was previously initialized.
   * </ul>
   * @param <i>REFCLSID in_rsGfxType</i>: CLSID of a GFX file type (for example, <b>CLSID_GFXTypeMaterial</b>). The parameter cannot be CLSID_NULL.
   * @param <i>const SMvResolutionInfo& in_rsResolutionInfo</i>: Structure containing the editing resolution (ERes) information.
   */
    virtual HRESULT __stdcall Init(REFCLSID in_rsGfxType, const SMvResolutionInfo& in_rsResolutionInfo) = 0;
};
#endif //IMVGFXFILENAMEHELPERINIT_H