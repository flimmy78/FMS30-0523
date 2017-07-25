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
//                    IMVFILTEREFFECTNODE.H
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

#ifndef IMVFILTEREFFECTNODE_H
#define IMVFILTEREFFECTNODE_H
#include "IMvVideoEffectNode.h"


/**
 * Describes a Flex filter effect in a tree.
 * @interface
 */
interface IMvFilterEffectNode : public IMvVideoEffectNode
{
public:

   /**
    * Links a child node (video layer) to a parent effect with an input index.
    *
    * <br><b>Remark:</b>
    * <ul><li>The index is unique and if the index already exists it will be replaced (the old one will be released).
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if the index used already exists and the previous node has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulIndex: Index of the video node added.
    * @param IMvTreeNode in_pIMvTreeNodeChild: Pointer to a child node interface.
    */
   virtual HRESULT __stdcall LinkToChildNode( unsigned long in_ulIndex, IMvTreeNode * in_pIMvTreeNodeChild ) = 0;
  
};

#endif //IMVFILTEREFFECTNODE_H
