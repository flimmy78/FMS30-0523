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
//                    IMVSTEREOTOMONONODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 26, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVSTEREOTOMONONODE_H
#define IMVSTEREOTOMONONODE_H

#include "IMvTreeNode.h"

/**
 * Splits an audio stereo stream into two mono streams.
 */
interface IMvStereoToMonoNode : public IMvTreeNode
{
public:

   /**
    * Initializes object state when object recycling is used.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Using this function is optional, it is only needed if you are managing a pool of node objects that need to be recycled.
    *        <li>A node cannot be initialized twice, "Flush" needs to be called before to reset object state.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_WRONG_STATE, if node is already initialized.
    *     <li>HRESULT error code, if failed.
    * </ul>    
    */
   virtual HRESULT __stdcall Init() = 0;

   /** 
    * Resets object state when object recycling is used. 
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Using this function is optional, it is only needed if you are managing a pool of node objects that need to be recycled.
    *        <li>This function will fail if the node is still part of a tree.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_WRONG_STATE, if node is still part of a tree and cannot be flushed.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall Flush() = 0;

   /**
    * Links the current node (parent) to a child node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This node can only have one child node. If a child node already exists, it will be replaced and released.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if a child node already exists and it has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvTreeNode in_pIMvTreeNodeChild: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildNode( IMvTreeNode *in_pIMvTreeNodeChild ) = 0;

  /**
   * Gets the parent node for the left channel.
   *
   * <br><b>Remark:</b>
   * <ul><i><li>Returned node is AddRef() and should be released by the caller.
   * </i></ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_INITIALIZED, if no left channel parent has been set.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param IMvTreeNode out_ppIMvTreeNodeParent: Address of a pointer to a node interface container.
   */
   virtual HRESULT __stdcall GetLeftChannelParent( IMvTreeNode **out_ppIMvTreeNodeParent ) = 0;

   /**
    * Gets the parent node for the right channel.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Returned node is AddRef() and should be released by the caller.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED, if no right channel parent has been set.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvTreeNode out_ppIMvTreeNodeParent: Address of a pointer to a node interface container.
    */
   virtual HRESULT __stdcall GetRightChannelParent( IMvTreeNode **out_ppIMvTreeNodeParent ) = 0;
};

#endif //IMVSTEREOTOMONONODE_H
