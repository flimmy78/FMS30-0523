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
//                    IMVTREENODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 14, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVTREENODE_H
#define IMVTREENODE_H

#include "mvUnknown.h"  
#include "IMvEnumTreeNodes.h"

/**
 * This interface is used to walk through a tree description.
 * @interface
 */
interface IMvTreeNode : public IUnknown
{
public:

   /**
    * Gets the number of child nodes linked to this node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>A node can have an infinite number of child nodes.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long out_refulChildNodesCount: Count container.
    */
   virtual HRESULT __stdcall GetChildNodesCount( unsigned long & out_refulChildNodesCount ) = 0;

   /**
    * Gets a child node's enumeration interface.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>There is only one child enumarator per node and every time the node is asked for it, it is reset to  the first child node.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvEnumTreeNodes out_ppIMvEnumTreeNodesChilds: Address of a pointer to a tree node enumerator interface container.
    */
   virtual HRESULT __stdcall GetChildNodesEnumerator( IMvEnumTreeNodes** out_ppIMvEnumTreeNodesChilds ) = 0;

   /**
    * Gets a child node at a specfic index.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This is a fast way to access a child node when you know its child index.
    *        <li>Return node will be AddRef() internally.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>MV_E_OUT_OF_RANGE, if a given index is invalid.
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>
    * @param unsigned long  in_ulIndex:             Index of the child node.
    * @param IMvTreeNode    out_ppIMvTreeNodeChild: Address of a pointer to a tree node interface container.
    */
   virtual HRESULT __stdcall GetChildNodeAtIndex( unsigned long in_ulIndex, IMvTreeNode** out_ppIMvTreeNodeChild ) = 0;

   /**
    * Gets the index of an existing child node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Given node should be child of the current node.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>MV_E_OUT_OF_RANGE, if a given child is invalid (not child of this parent).
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>
    * @param IMvTreeNode   in_pIMvTreeNodeChild: Pointer to a tree node interface.
    * @param unsigned long out_refulIndex:       Reference to a child node index.       
    */
   virtual HRESULT __stdcall GetChildNodeIndex( IMvTreeNode *in_pIMvTreeNodeChild, unsigned long &out_refulIndex ) = 0;

   /**
    * Gets the number of parent nodes linked to this node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>A node can have an infinite number of parent nodes.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long out_refulParentNodesCount: Count container.
    */
   virtual HRESULT __stdcall GetParentNodesCount( unsigned long & out_refulParentNodesCount ) = 0;

   /**
    * Gets a parent node enumeration interface.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>There is only one parent enumerator per node and every time the node is asked for it, it is reset to the first parent node.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvEnumTreeNodes out_ppIMvEnumTreeNodesParents: Address of a pointer to a tree node enumerator interface container.
    */
   virtual HRESULT __stdcall GetParentNodesEnumerator( IMvEnumTreeNodes** out_ppIMvEnumTreeNodesParents ) = 0;

   /**
    * Gets a parent node at a specfic index.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This is a fast way to access a parent node when you know its parent index.
    *        <li>Return node will be AddRef() internally.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>MV_E_OUT_OF_RANGE, if a given index is invalid.
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>
    * @param unsigned long  in_ulIndex:              Index of the parent node.
    * @param IMvTreeNode    out_ppIMvTreeNodeParent: Address of a pointer to a tree node interface container.
    */
   virtual HRESULT __stdcall GetParentNodeAtIndex( unsigned long in_ulIndex, IMvTreeNode** out_ppIMvTreeNodeParent ) = 0;

   /**
    * Gets the index of an existing parent node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Given node should be parent of the current node.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>MV_E_OUT_OF_RANGE, if a given parent is invalid (not parent of this child).
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>
    * @param IMvTreeNode   in_pIMvTreeNodeParent: Pointer to a tree node interface.
    * @param unsigned long out_refulIndex:        Reference to a parent node index.       
    */
   virtual HRESULT __stdcall GetParentNodeIndex( IMvTreeNode *in_pIMvTreeNodeParent, unsigned long &out_refulIndex ) = 0;

   /**
    * Unlinks a child node from the current node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This will release the child node selected.
    *        <li>WARNING! This may delete all the remaining sub-nodes if they are not referenced somewhere else.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>MV_E_INVALID_NODE_INDEX, if a given index is invalid.
    *     <li>HRESULT error code, if failed for any other reason.
    * </ul>
    * @param unsigned long in_ulIndex: Index of the node to delete.
    */
   virtual HRESULT __stdcall UnlinkFromChildNodeAt( unsigned long in_ulIndex ) = 0;

   /**
    * Unlinks all the child nodes.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This will release all the child nodes linked to the current node.
    *        <li>WARNING! This may delete all the remaining sub-nodes if they are not referenced somewhere else.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.       
    *     <li>HRESULT error code, if failed.
    * </ul>       
    */
   virtual HRESULT __stdcall UnlinkAllChilds() = 0;

   /**
    * Gets the node type.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Node types are used to validate nodes' interconnections and are not unique for each specific node (which is the case for subtypes).
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvTreeNodeType out_refeMvTreeNodeType: Type container.
    */
   virtual HRESULT __stdcall GetNodeType( EMvTreeNodeType & out_refeMvTreeNodeType ) = 0;

   /**
    * Gets the node-specific sybtype identificator.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Subtypes are unique for each specific node (which support a specific node interface, derived from the current interface).
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvTreeNodeSubType out_refeMvTreeNodeSubType: Subtype container.
    */
   virtual HRESULT __stdcall GetNodeSubType( EMvTreeNodeSubType & out_refeMvTreeNodeSubType ) = 0;

   /**
    * Connects a node to the child at the specified index.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>The user specifies the index and the usage of the link.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulChildIndex : Connection index.
    * @param EMvChildUsage in_emvChildUsage: Generic child usage flag.
    * @param IMvTreeNode  in_pIMvTreeNodeChild: Child to connect.
    */
   virtual HRESULT __stdcall ConnectToChildNode( unsigned long in_ulChildIndex, EMvChildUsage in_emvChildUsage, IMvTreeNode* in_pIMvTreeNodeChild) = 0;

   /**
    * Disconnects the child at the specified index.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>The user can recover the usage of the child for reconnection purposes.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulChildIndex   : Connection index.
    * @param EMvChildUsage out_peMvChildUsage: Usage of the child that is being disconnected. Can be NULL.
    */
   virtual HRESULT __stdcall DisconnectFromChildNode( unsigned long in_ulChildIndex, EMvChildUsage* out_peMvChildUsage) = 0;

   /**
    * Gets the usage of the child at the given index.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Used to get the usage of the child.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b> 
    * <ul><li>MV_NOERROR, if succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param unsigned long in_ulChildIndex   : Connection index.
    * @param EMvChildUsage out_peMvChildUsage: Usage of the child.
    */
   virtual HRESULT __stdcall GetChildNodeUsage( unsigned long in_ulChildIndex, EMvChildUsage & out_refeMvChildUsage) = 0;


};
#endif //IMVTREENODE_H

