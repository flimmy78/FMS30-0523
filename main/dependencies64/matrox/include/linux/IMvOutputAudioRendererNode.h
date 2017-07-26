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
//                    IMVOUTPUTAUDIORENDERERNODE.H
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


#ifndef IMVOUTPUTAUDIORENDERERNODE_H
#define IMVOUTPUTAUDIORENDERERNODE_H
#include "IMvOutputAudioNode.h"


/**
 * This interface is used to link an output audio stream
 * with a Transform filter output pin connected to a renderer.
 * @interface
 * 
 * 
 */
interface IMvOutputAudioRendererNode : public IMvOutputAudioNode
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
    * @param unsigned long in_ulPinID: Output pin ID on the transform filter.   
    */
   virtual HRESULT __stdcall Init( unsigned long in_ulPinID ) = 0;

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
    * <ul><i><li>This node can only have one child node. If the child node already exists it will be replaced and released.
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
    * @param IMvTreeNode *in_pIMvTreeNodeChild: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildNode( IMvTreeNode *in_pIMvTreeNodeChild ) = 0;

   /**
    * Gets the Transform filter output pin ID linked to this node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>None.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long &out_refulPinID: Output pin ID receiver.
    */
   virtual HRESULT __stdcall GetOutputPinID( unsigned long &out_refulPinID ) = 0;

   /**
    * Sets the synchronization state of the output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>When a stream needs synchronization it means that it has to go through the A/V synch module.
    *        <li>All streams that need synchronization will be synchronized together before being sent to their renderer.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param bool in_bIsSynchronized: Boolean flag to set the synch state.
    */
   virtual HRESULT __stdcall SetSynchronizationState( bool in_bIsSynchronized ) = 0;

   /**
    * Gets the synchronization state of the output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>When a stream needs synchronization it means that it has to go through the A/V synch module.
    *        <li>All streams that need synchronization will be synchronized together before being sent to their renderer.
    *        <li>Take note that the return value is not a boolean.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>S_TRUE, if this output stream is synchronized.
    *     <li>S_FALSE, if this output stream is not synchronized. The A/V synch module does not need to wait for other
    *                      output streams when it receives data from this stream.
    *     <li>HRESULT error code, if failed to get the information.
    * </ul>
    */
   virtual HRESULT __stdcall IsSynchronized() = 0;
};



#endif //IMVOUTPUTAUDIORENDERERNODE_H



