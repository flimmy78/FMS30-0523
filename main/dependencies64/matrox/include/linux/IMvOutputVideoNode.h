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
//                    IMVOUTPUTVIDEONODE.H
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

#ifndef IMVOUTPUTVIDEONODE_H
#define IMVOUTPUTVIDEONODE_H
#include "IMvTreeNode.h"

/**
 * Used to add a child to an output node and set/get an output rate.
 * None of the nodes implement ONLY this interface, you have to use a derived one.
 * @interface
 * 
 * 
 */
interface IMvOutputVideoNode : public IMvTreeNode {
public:

   /**
    * Sets the skipping rate of an output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Rate is expressed with a fraction of elements to keep over a sequence of elements.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvRateDescription &in_refsMvRateDescription: Valid rate structure.
    */
   virtual HRESULT __stdcall SetSkippingRate( SMvRateDescription &in_refsMvRateDescription ) = 0;

   /**
    * Gets the skipping rate of an output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Rate is expressed with a fraction of elements to keep over a sequence of elements.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvRateDescription &io_refsMvRateDescription: Valid rate structure.
    */
   virtual HRESULT __stdcall GetSkippingRate( SMvRateDescription &io_refsMvRateDescription ) = 0;

   /**
    * Links the current (parent) node to a child node.
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
    * @param IMvTreeNode *in_pIMvTreeNodeChild: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildNode( IMvTreeNode *in_pIMvTreeNodeChild ) = 0;

   /**
   * Set the output scaling mode for the node.
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
   virtual HRESULT __stdcall SetOutputScalingMode(EMvScalingMode in_eScalingMode) = 0;

   /**
   * Gets the output scaling mode for the node.
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
   virtual HRESULT __stdcall GetOutputScalingMode(EMvScalingMode& in_refeScalingMode) = 0;
};



#endif //IMVOUTPUTVIDEONODE_H




