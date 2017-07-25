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
//                    IMVGRAPHICSCUTLISTELEMENT.H
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


#ifndef IMVGRAPHICSCUTLISTELEMENT_H
#define IMVGRAPHICSCUTLISTELEMENT_H


/**
 * Used for graphics cutlist elements.
 * @interface
 */
interface IMvGraphicsCutListElement : public IUnknown
{
public:
   /**
    * Retrieves the output position of a graphics element.
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
    *	  <li>MV_E_INVALID_POINTER, if the parameter <var>out_pi64X</var> or <var>out_pi64Y</var> is an invalid pointer.
    * </ul>
    * @param int64_t out_pi64X: Pointer to the X position of the graphics element.
    * @param int64_t out_pi64Y: Pointer to the Y position of the graphics element
    */
   virtual HRESULT __stdcall GetOutputPosition( int64_t * out_pi64X, int64_t * out_pi64Y ) = 0;
};



#endif //IMVGRAPHICSCUTLISTELEMENT_H




