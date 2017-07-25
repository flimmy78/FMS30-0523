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
//                    IMVINPUTVIDEOSOURCENODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 20, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVINPUTVIDEOSOURCENODE_H
#define IMVINPUTVIDEOSOURCENODE_H
#include "IMvTreeNode.h"

/**
 * This interface is used to notify the Transform filter that the
 * input video stream comes from a Source filter connected on an input pin.
 * @interface 
 */
interface IMvInputVideoSourceNode : public IMvTreeNode 
{
public:

   /**
    * Initialization function, called to initialize object state when object recycling is used.
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
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>    
    * @param unsigned long in_ulPinID: Input pin ID on the transform filter.
    */
   virtual HRESULT __stdcall Init( unsigned long in_ulPinID ) = 0;

   /** 
    * Flush function, called to reset object state when object recycling is used. 
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
    * Gets the Transform filter input pin ID linked to this node.
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
    * @param unsigned long out_refulInputPinID: Input pin ID receiver.
    */
   virtual HRESULT __stdcall GetInputPinID( unsigned long &out_refulInputPinID ) = 0;
  
   /**
   * Set the input scaling mode for the node.
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param EMvScalingMode in_eScalingMode: scaling mode.
   */
   virtual HRESULT __stdcall SetInputScalingMode(EMvScalingMode in_eScalingMode) = 0;

   /**
   * Gets the input scaling mode for the node.
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param EMvScalingMode& in_refeScalingMode: Reference to the enum of scaling mode.
   */
   virtual HRESULT __stdcall GetInputScalingMode(EMvScalingMode& in_refeScalingMode) = 0;

};



#endif //IMVINPUTVIDEOSOURCENODE_H




