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
//                    IMVAUDIOEFFECTNODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 23, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVAUDIOEFFECTNODE_H
#define IMVAUDIOEFFECTNODE_H
#include "IMvTreeNode.h"

/**
 * Describes a Flex audio effect in a tree.
 * @interface
 */
interface IMvAudioEffectNode : public IMvTreeNode
{
public:

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
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_WRONG_STATE, if node is already initialized.
   *     <li>HRESULT error code, if failed.
   * </ul>    
   * @param GUID                in_refguidEffectID:      Effect identificator.
   * @param IMvParametricEffect in_pIMvParametricEffect: Pointer to the interface used to get effect settings.
   */
   virtual HRESULT __stdcall Init( GUID &in_refguidEffectID, IMvParametricEffect *in_pIMvParametricEffect ) = 0;   

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
    * Gets the unique ID of the Flex effect associated with this node.
    *
    * <br><b>Remark:</b>
    * <ul><li>This ID is the same used by the Flex engine.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>GUID &ut_refguidEffect:</i> Reference to a unique ID container.
    */
   virtual HRESULT __stdcall GetEffectID( GUID &out_refguidEffect ) = 0;

   /**
    * Gets the parametric effect interface for the Flex effect.
    *
    * <br><b>Remark:</b>
    * <ul><li>This method gives access to effect settings that decipher how to execute the effect.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvParametricEffect out_ppIMvParametricEffect:</i> Address of the interface pointer to the parametric effect interface container.  Will have to be released like all interfaces returned.
    */
   virtual HRESULT __stdcall GetParametricEffect( IMvParametricEffect **out_ppIMvParametricEffect ) = 0;

   /**
    * Links a child node to a parent effect node with an input index.
    *
    * <br><b>Remark:</b>
    * <ul><li>The index is unique and if it already exists it will be replaced (the old one will be released).
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if the index in use already exists and the previous node has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node's category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long in_ulIndex:</i> Index of the node added.
    * @param <i>IMvTreeNode in_pIMvTreeNodeChild:</i> Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChild( unsigned long in_ulIndex, IMvTreeNode *in_pIMvTreeNode ) = 0;
};



#endif //IMVAUDIOEFFECTNODE_H



