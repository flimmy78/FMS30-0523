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


#ifndef IMVTREECUTLISTELEMENT_H
#define IMVTREECUTLISTELEMENT_H
#include "IMvCutListElement.h"
#include "IMvTreeNode.h"

/**
 * Adds the functionality of obtaining a tree root node on an object that already supports <b>IMvCutListElement</b>.
 * 
 * This is used by the Transform filter so that it can support a tree cutlist.
 * @interface
 */
interface IMvTreeCutListElement : public IUnknown
{
public:   

   /**
   * Used by the Transform filters to extract the trees from the cutlist elements.
   * <br><b>Remarks:</b>
   * <ul><li> 
   * </ul>
   * 
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   * <b>Return Values:</b> 
   * <ul><li>MV_NOERROR, if there is a tree set on the cutlist element.
   *     <li>MV_E_INVALID_POINTER, if the passed tree pointer is NULL or invalid.
   *     <li>E_NOINTERFACE, if there is no tree set on the cutlist element.
   * </ul>
   * @param <i>IMvTreeNode out_ppIMvTreeNode </i>: Pointer to the tree that is contained in the element and returned to the caller.
   */
   virtual HRESULT __stdcall GetTreeRootNode( IMvTreeNode * * out_ppIMvTreeNode ) = 0;
};
#endif //IMVTREECUTLISTELEMENT_H

