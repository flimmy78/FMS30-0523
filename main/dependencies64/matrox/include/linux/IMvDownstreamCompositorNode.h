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
//                    IMVDOWNSTREAMCOMPOSITORNODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 21, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVDOWNSTREAMCOMPOSITORNODE_H
#define IMVDOWNSTREAMCOMPOSITORNODE_H
#include "IMvUpstreamCompositorNode.h"

/**
 * This interface is used to create the final combination of video layers.
 * This operation does not have to produce a valid alpha in the resulting Flex surface.
 * @interface
 */
interface IMvDownstreamCompositorNode : public IMvUpstreamCompositorNode
{
public:



   /**
    * Links the current (parent) node to a background child node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>The node added will be used as a background for the downstream composition.
    *        <li>The background will get a specific index in order to avoid conflict with other video layers.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulIndex:     Index of the background node.
    * @param IMvTreeNode* in_pIMvTreeNode: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildBackground( unsigned long in_ulIndex, IMvTreeNode * in_pIMvTreeNode ) = 0;

   /**
    * Gets the specific index of the background node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Be sure you don't override the background node when adding a new layer.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long &out_refulBackgroundIndex: Index receiver.
    */
   virtual HRESULT __stdcall GetBackgroundNodeIndex( unsigned long &out_refulBackgroundIndex ) = 0;

};



#endif //IMVDOWNSTREAMCOMPOSITORNODE_H




