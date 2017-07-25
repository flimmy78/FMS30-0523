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
//                    IMVTREENODEPARENTLINK.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 14, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVTREENODEPARENTLINK_H
#define IMVTREENODEPARENTLINK_H


/**
 * This internal tree management interface is used to set a parent node on a child node.
 * @interface
 */
interface IMvTreeNodeParentLink : public IUnknown
{
public:

   /**
    * Links the current (child) node to a parent node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This interface should not be used by any tree builder. It is used for internal management.
    *</i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed. 
    * </ul>
    * @param unsigned long  in_ulIndexInParent:        Node index at parent node level.
    * @param IMvTreeNode    in_pIMvTreeNodeParent:     Pointer to a parent node interface.
    * @param EMvChildUsage  in_emvReceivedUsage:       Received usage from parent.
    * @param unsigned long  out_refParentIndexInChild: Node index given for parent in child.
    */
   virtual HRESULT __stdcall LinkToParentNode(unsigned long  in_ulIndexInParent, 
                                              IMvTreeNode   *in_pIMvTreeNodeParent, 
                                              EMvChildUsage  in_emvReceivedUsage,
                                              unsigned long &out_refParentIndexInChild) = 0;

   /**
    * Advises the current (child) node that a parent node is breaking the link.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This interface should not be used by any tree builder. It is used for internal management.
    *</i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_RANGE, if the given parent node inside internal list of parents is not found.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long  in_ulIndexAsParent:    Node index as parent for given nod in next paramameter.
    * @param IMvTreeNode    in_pIMvTreeNodeParent: Pointer to a parent node interface.    
    */
   virtual HRESULT __stdcall UnlinkFromParentNode( unsigned long  in_ulIndexAsParent,
                                                   IMvTreeNode   *in_pIMvTreeNodeParent ) = 0;
};

#endif //IMVTREENODEPARENTLINK_H
