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
//                    IMVCOMPOSITORNODE.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 23, 2003 - 4:02:46 PM
//   Operating System:       WinXP
//   Author:                 Serge Grondin
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVCOMPOSITORNODE_H
#define IMVCOMPOSITORNODE_H
//==========================================================================;
// Header files
//==========================================================================;
#include "IMvTreeNode.h"

//==========================================================================;
// Interface IMvCompositorNode
//==========================================================================;

/**
 * This interface is the base interface for all compositing nodes (video and audio mixing).
 */
interface IMvCompositorNode : public IMvTreeNode
{
public:
   //==========================================================================;
   // Public operations
   //==========================================================================;

   /**
    * Initializes object state when object recycling is used.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Using this function is optional, it is only needed if you are managing a pool of node objects that need to be recycled.
    *        <li>A node cannot be initialized twice, "Flush" needs to be called beforehand in order to reset object state.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completely successfully.
    *     <li>MV_E_WRONG_STATE, if node is already initialized.
    *     <li>HRESULT error code, if failed.
    * </ul>    
    * @param bool in_bIsUsingLowestIndexAsTopLayer: Boolean flag, if set to TRUE the lowest index is the top layer (highest is the bottom), if set to FALSE the highest index is the top layer (lowest is the bottom).    
    */
   virtual HRESULT __stdcall Init( bool in_bIsUsingLowestIndexAsTopLayer ) = 0;

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
    * Links a child node (video layer) to a parent compositor with a layer level.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Index is the layer level of the video layer added.
    *        <li>Index is unique and if the layer already exists it will be replaced (old one will be released).
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED:    Index used already exists and the previous node has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP: Trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long         in_ulIndex:              Layer of the video node added.
    * @param IMvTreeNode           in_pIMvTreeNode:         Pointer to a child node interface.
    * @param IMvParametricEffect   in_pIMvParametricEffect: Pointer to the parametric effect used to combine this layer.
    */
   virtual HRESULT __stdcall LinkToChildNode( unsigned long        in_ulIndex,
                                              IMvTreeNode         *in_pIMvTreeNode,
                                              IMvParametricEffect *in_pIMvParametricEffect ) = 0;

   /**
   * Sets the parametric effect interface for a given layer.
   *
   * <br><b>Remark:</b>
   * <ul><i><li> This must be called BEFORE connecting the layer. If it is not called before connecting the 
   *             layer, the connection will fail.
   * </i></ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR: If completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long         in_ulIndex:               Layer of the video node.
   * @param IMvParametricEffect   in_pIMvParametricEffect:  Pointer to the parametric effect interface container.
   */
   virtual HRESULT __stdcall SetParametricEffect( unsigned long in_ulIndex, IMvParametricEffect *in_pIMvParametricEffect ) = 0;

   /**
    * Gets the parametric effect interface for a given layer.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Allows access to the effect settings that decipher how to combine the layer.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long         in_ulIndex:                Layer of the video node.
    * @param IMvParametricEffect   out_ppIMvParametricEffect: Address of the interface pointer on the parametric effect.
    */
   virtual HRESULT __stdcall GetParametricEffect( unsigned long in_ulIndex, IMvParametricEffect **out_ppIMvParametricEffect ) = 0;

   /**
    * Gets indexing and layering order.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Called by the tree decoder to determine the layering order.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_TRUE:  Lowest index is the top layer (highest is the bottom).
    *     <li>MV_FALSE: Highest index is the top layer (lowest is the bottom).
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall IsUsingLowestIndexAsTopLayer() = 0;
};


#endif //IMVCOMPOSITORNODE_H
