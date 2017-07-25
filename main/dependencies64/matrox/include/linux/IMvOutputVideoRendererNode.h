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
//                    IMVOUTPUTVIDEORENDERERNODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 15, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVOUTPUTVIDEORENDERERNODE_H
#define IMVOUTPUTVIDEORENDERERNODE_H
#include "IMvOutputVideoNode.h"

/**
 * Used to link an output video stream
 * to a Transform filter output pin that is connected to a renderer.
 * @interface
 * 
 * 
 */
interface IMvOutputVideoRendererNode : public IMvOutputVideoNode {
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
    * @param unsigned long in_ulPinID: Output pin ID on the transform filter.    
    * @param IMvVideoClosedCaptioningPulling * in_pIMvVideoClosedCaptioningPulling: Pulling interface from application.    
    */
   virtual HRESULT __stdcall Init( unsigned long in_ulPinID, IMvVideoClosedCaptioningPulling * in_pIMvVideoClosedCaptioningPulling ) = 0;

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
    * Gets the callback interface implemented by the host application.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This call will add a reference on the received interface.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvVideoClosedCaptioningPulling **out_ppIMvVideoClosedCaptioningPulling: Pointer to a pulling interface container.
    */
   virtual HRESULT __stdcall GetVideoClosedCaptioningCallbackInterface(IMvVideoClosedCaptioningPulling **out_ppIMvVideoClosedCaptioningPulling ) = 0;

   /**
    * Sets the synchronization state of the output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>When a stream needs synchronization, it means that is has to go through the A/V synch module.
    *        <li>All streams that need synchronization will be synchronized before being sent to their renderer.
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
    * <ul><i><li>When a stream needs synchronization it means that is has to go through the A/V synch module.
    *        <li>All streams that need synchronization will be synchronized before being sent to their renderer.
    *        <li>Please take note that the return value is not a boolean.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_TRUE, if this output stream is synchronized.
    *     <li>MV_FALSE, if this output stream is not synchronized. A/V synch module does not need to wait on other
    *                      output streams when it receives data from this stream.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall IsSynchronized() = 0;

   /**
    * Sets the pulldown sequence type for the node.
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvPullDownSequence in_ePullDownSequence: mode of pulldown sequence, either keSequence_3_2
    *          or keSequence_Advanced.
    */
   virtual HRESULT __stdcall SetPullDownSequence(EMvPullDownSequence in_ePullDownSequence) = 0;

   /**
    * Gets the pulldown sequence type for the node.
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvPullDownSequence& in_refePullDownSequence: Reference to the enum of pulldown sequence.
    */
   virtual HRESULT __stdcall GetPullDownSequence(EMvPullDownSequence& in_refePullDownSequence) = 0;
};



#endif //IMVOUTPUTVIDEORENDERERNODE_H




