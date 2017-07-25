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
//                    IMVSCROLLINGCUTLISTELEMENT.H
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


#ifndef IMVSCROLLINGCUTLISTELEMENT_H
#define IMVSCROLLINGCUTLISTELEMENT_H

/**
* Used for scrolling the graphics cutlist element.
* @interface
*/
interface IMvScrollingCutListElement : public IUnknown
{
public:

   /**
    * Retrieves the parametric effect for getting scrolling keyframes.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>E_NOINTERFACE, if interface is not supported.
    *	 <li>MV_E_INVALID_POINTER, if the parameter <var>out_ppIMvParametricEffect</var> is an invalid pointer.
    * </ul>
    * @param IMvParametricEffect out_ppIMvParametricEffect:  Pointer to the parametric effect's interface.
    */
   virtual HRESULT __stdcall GetParametricEffect( IMvParametricEffect * * out_ppIMvParametricEffect ) = 0;

   /**
    * Retrieves the output height for scrolling.
    *
    * <br><b>Remark:</b>
    * 
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *	 <li>MV_E_INVALID_POINTER, if the parameter <var>out_pi64Height</var> is an invalid pointer.
    * </ul>
    * @param int64 out_pi64Height:  Pointer to the output height for scrolling.
    */
   virtual HRESULT __stdcall GetOutputHeight( int64_t *out_pi64Height ) = 0 ;
};



#endif //IMVSCROLLINGCUTLISTELEMENT_H




