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
//                    IMVSYMBOLICROOTNODE.H
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

#ifndef IMVSYMBOLICROOTNODE_H
#define IMVSYMBOLICROOTNODE_H
#include "IMvTreeNode.h"

/**
 * This interface is implemented by the first node of the tree and gives access to the whole tree.
 * @interface
 * 
 * 
 */
interface IMvSymbolicRootNode : public IMvTreeNode
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
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_WRONG_STATE, if node is already initialized.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvTreeProcessingType   in_eMvTreeProcessingType:   Type of tree (audio or video).
    * @param EMvTreeProcessingFormat in_eMvTreeProcessingFormat: Format used for processing inside the entire tree.
    */
   virtual HRESULT __stdcall Init( EMvTreeProcessingType in_eMvTreeProcessingType, EMvTreeProcessingFormat in_eMvTreeProcessingFormat ) = 0;

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
    * <ul><i><li>Indexes are unique; using an existing index will replace the child node and all its subchild nodes.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_W_PREVIOUS_NODE_REPLACED, if the index used already exists and the previous node has been replaced and released.
    *     <li>MV_E_INVALID_NODE_RELATIONSHIP, if trying to link to a child node that is not compatible with this node category.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long   in_ulIndex:           Index of the child node
    * @param IMvTreeNode*    in_pIMvTreeNodeChild: Pointer to a child node interface.    
    */
   virtual HRESULT __stdcall LinkToChildNode( unsigned long in_ulIndex, IMvTreeNode * in_pIMvTreeNodeChild) = 0;

   /**
    * Sets the degradation rate for the entire tree.
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
    * @param SMvRateDescription & in_refsMvRateDescription: Reference to a valid rate structure (size should be initialized).
    */
   virtual HRESULT __stdcall SetDegradationRate( SMvRateDescription & in_refsMvRateDescription ) = 0;

   /**
    * Gets the degradation rate of the entire tree.
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
    * @param SMvRateDescription & io_refsMvRateDescription: Reference to a valid rate structure (size should be initialized).
    */
   virtual HRESULT __stdcall GetDegradationRate( SMvRateDescription & io_refsMvRateDescription ) = 0;

   /**
    * Gets the main processing type of a tree (audio or video).
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
    * @param EMvTreeProcessingType & out_refeMvTreeProcessingType: Processing type container.
    */
   virtual HRESULT __stdcall GetTreeProcessingType( EMvTreeProcessingType & out_refeMvTreeProcessingType ) = 0;
  
   /**
    * Gets the main processing format of a tree (video 8 bits, video 10 bits, audio 16 bits, audio 24 bits, etc).
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
    * @param EMvTreeProcessingFormat & out_refeMvTreeProcessingFormat: Processing format container.
    */
   virtual HRESULT __stdcall GetTreeProcessingFormat( EMvTreeProcessingFormat & out_refeMvTreeProcessingFormat ) = 0;
   /**
    * Sets the serialization property for the tree.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Set serialize property of the processing. 
    * <ul><i><li>If serialization is true, the position will have to finish before the next position is programmed.
    * <ul><i><li>If serialization is false, next positions can be programmed before the current one is finished.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param bool in_bSerialize: true to serialize and false to not serialize.
    */
   virtual HRESULT __stdcall SetSerializePosition( bool in_bSerialize ) = 0;

   /**
    * Gets the serialization property for the tree.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Get serialize property of the processing. 
    * <ul><i><li>If serialization is true, the position will have to finish before the next position is programmed.
    * <ul><i><li>If serialization is false, next positions can be programmed before the current one is finished.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param bool & io_refbSerializePosition: true is serialized, and false is not serialize.
    */
   virtual HRESULT __stdcall GetSerializePosition( bool & out_refbSerializePosition ) = 0;

};



#endif //IMVSYMBOLICROOTNODE_H




