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
//                    IMVVIDEOEFFECTNODE.H
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


#ifndef IMVVIDEOEFFECTNODE_H
#define IMVVIDEOEFFECTNODE_H
#include "IMvTreeNode.h"

/**
 * Used to describe a Flex effect in a tree. All interfaces implemented in video effect nodes are derived from this base interface.
 * @interface
 */
interface IMvVideoEffectNode : public IMvTreeNode
{
public:

   /**
    * Initializes object state when object recycling is used.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Using this function is optional. It is only needed if you are managing a pool of node objects that need to be recycled.
    *        <li>A node cannot be initialized twice. The Flush() method needs to be called beforehand in order to reset object state.
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
    * @param IMvParametricEffect in_pIMvParametricEffect: Pointer to the interface used to get effect settings.
    */
   virtual HRESULT __stdcall Init( IMvParametricEffect * in_pIMvParametricEffect ) = 0;

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
    * Gets the Flex effect unique ID associated with this node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This ID is the same used by the Flex engine.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param GUID out_refguidEffect: Unique ID receiver.
    */
   virtual HRESULT __stdcall GetEffectID( GUID &out_refguidEffect ) = 0;

   /**
    * Gets the parametric effect interface for the Flex effect.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This gives access to effect settings that decipher how to execute the effect.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvParametricEffect out_ppIMvParametricEffect: Address to the interface pointer to the parametric effect.  This interface will have to be released by the caller like all interfaces returned.
    */
   virtual HRESULT __stdcall GetParametricEffect( IMvParametricEffect **out_ppIMvParametricEffect ) = 0;

   /**
    * Deciphers whether or not the effect has to use the alpha channel of an input child.
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
    * @param bool     in_bUseAlpha: Boolean flag to set the alpha usage.
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
    * <ul><li>MV_TRUE, if you use the alpha channel of the input child at a given index.
    *     <li>MV_FALSE, if you don't use the alpha channel of the input child at a given index.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulIndex: Index of the child node.
    */
   virtual HRESULT __stdcall IsUsingAlphaOnChild( unsigned long in_ulIndex ) = 0;

};



#endif //IMVVIDEOEFFECTNODE_H




