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
//                    IMVOUTPUTVIDEOSINKNODE.H
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

#ifndef IMVOUTPUTVIDEOSINKNODE_H
#define IMVOUTPUTVIDEOSINKNODE_H
#include "IMvOutputVideoNode.h"

/**
 * Links an output video stream
 * and a Transform filter output pin that is connected to a disk writer.
 * @interface
 * 
 * 
 */
interface IMvOutputVideoSinkNode : public IMvOutputVideoNode {
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
    * <ul><li>MV_NOERROR, if completed sucessfully.
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
    * Gets the Transform filter output pin's ID linked to this node.
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
    * @param unsigned long &out_refulPinID: Output pin ID container.
    */
   virtual HRESULT __stdcall GetOutputPinID( unsigned long &out_refulPinID ) = 0;

   /**
    * Sets the recompression state of the output stream that will be written to disk.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This is used to make sure that the video stream that goes to disk has
    *            passsed through at least one compression step, even if the input data is
    *            already compressed in the right format (which means that
    *            this video stream will be decompressed and then compressed again before
    *            being written to disk).
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param bool in_bForceRecompression: Boolean flag to set the recompression state.
    */
   virtual HRESULT __stdcall SetRecompressionState( bool in_bForceRecompression ) = 0;


   /**
    * Gets the recompression state of the output stream that will be written to disk.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This is used to make sure that the video stream that goes to disk has
    *            passed through at least one compression step, even if the input data is
    *            already compressed in the right format (which means that
    *            this video stream will be decompressed and then compressed again before
    *            being written to disk).
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_TRUE, if this output stream is asking for recompression all the time.
    *     <li>MV_FALSE, if this output stream does not care whether the stream is recompressed or not.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall IsForcingRecompression() = 0;
};



#endif //IMVOUTPUTVIDEOSINKNODE_H




