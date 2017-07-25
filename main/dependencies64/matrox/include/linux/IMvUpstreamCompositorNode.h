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
//                    IMVUPSTREAMCOMPOSITORNODE.H
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

#ifndef IMVUPSTREAMCOMPOSITORNODE_H
#define IMVUPSTREAMCOMPOSITORNODE_H
#include "IMvCompositorNode.h"


/**
 * This interface is used to combine video layers and keep a valid alpha in the resulting Flex surface.
 * @interface
 * 
 * 
 */
interface IMvUpstreamCompositorNode : public IMvCompositorNode
{
public:

  /**
   * Sets whether or not the effect has to use the alpha channel of an input child.
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
   * @param unsigned long in_ulIndex:   Index of the child node.
   * @param bool          in_bUseAlpha: Boolean flag to set the alpha usage.
   */
   virtual HRESULT __stdcall SetAlphaUsageOnChild( unsigned long in_ulIndex, bool in_bUseAlpha ) = 0;

   /**
   * Gets the alpha usage status for an input child.
   *
   * <br><b>Remark:</b>
   * <ul><i><li>Please take note that the return value is not a boolean.
   * </i></ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_TRUE, if you want to use the alpha channel of the input child at a given index.
   *     <li>MV_FALSE, if you don't want to use the alpha channel of the input child at a given index.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long in_ulIndex: Index of the child node.
   */
   virtual HRESULT __stdcall IsUsingAlphaOnChild( unsigned long in_ulIndex ) = 0;

};



#endif //IMVUPSTREAMCOMPOSITORNODE_H




