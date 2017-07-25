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
//                    IMVOUTPUTAUDIOSINKMONONODE.H
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


#ifndef IMVOUTPUTAUDIOSINKMONONODE_H
#define IMVOUTPUTAUDIOSINKMONONODE_H
#include "IMvOutputAudioNode.h"


/**
 * Links an output audio stream (mono)
 * and a Transform filter output pin connected to a disk writer.
 * @interface
 * 
 * 
 */
interface IMvOutputAudioSinkMonoNode : public IMvOutputAudioNode
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
    * <ul><li>MV_NOERROR, if succeeded.
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
    * Links the current node (parent) to a child StereoToMono node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This node can only have one child node. If a child node already exists, it will be replaced and released.
    *        <li>You have to specify the audio channel; this will be used by the StereoToMono node to select the output channel.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successsfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if a child node already exists and it has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvStereoToMonoNode *in_pIMvStereoToMonoNode: Pointer to a child node StereoToMono interface.
    */
   virtual HRESULT __stdcall LinkToChildStereoToMonoNode( EMvAudioChannel in_eMvAudioChannel, IMvStereoToMonoNode *in_pIMvStereoToMonoNode ) = 0;

   /**
    * Links the current node (parent) to a child mono input node.
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
    * @param IMvInputAudioSourceMonoNode *in_pIMvInputAudioSourceMonoNode: Pointer to a child node Mono input interface.
    */
   virtual HRESULT __stdcall LinkToChildMonoInputNode( IMvInputAudioSourceMonoNode *in_pIMvInputAudioSourceMonoNode ) = 0;

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
};



#endif //IMVOUTPUTAUDIOSINKMONONODE_H




