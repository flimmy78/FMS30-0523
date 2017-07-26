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
//                    IMVMONOTOSTEREONODE.H
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

#ifndef IMVMONOTOSTEREONODE_H
#define IMVMONOTOSTEREONODE_H

#include "IMvTreeNode.h"

/**
 * This interface is used to combine two audio mono streams into one stereo stream.
 */
interface IMvMonoToStereoNode : public IMvTreeNode
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
    * Links the current node (parent) to the child node that will be used as a left channel in the stereo output.
    *
    * <br><b>Remark:</b>
    * <ul><li>There is only one child for the left channel, if one already exists, it will be replaced.
    *     <li>When enumerating child nodes, the left channel always uses the "keMvAudioChannelLeft" index from EMvAudioChannel enumeration.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if a child node left channel already exists and it has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.    
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvTreeNode in_pIMvTreeNodeLeftChannel: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildLeftChannel( IMvTreeNode * in_pIMvTreeNodeLeftChannel ) = 0;

   /**
    * Links the current node (parent) to the child node that will be used as a right channel in the stereo output.
    *
    * <br><b>Remark:</b>
    * <ul><li>There is only one child for the right channel, if one already exists, it will be replaced.
    *     <li>When enumerating child nodes, the right channel always uses the "keMvAudioChannelRight" index from EMvAudioChannel enumeration.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if a child node right channel already exists and it has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvTreeNode in_pIMvTreeNodeRightChannel: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildRightChannel( IMvTreeNode * in_pIMvTreeNodeRightChannel ) = 0;
  
};

#endif //IMVMONOTOSTEREONODE_H