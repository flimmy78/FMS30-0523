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
//                    IMVENUMTREENODES.H
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

#ifndef IMVENUMTREENODES_H
#define IMVENUMTREENODES_H


/**
 * Tree node enumeration interface.
 * @interface
 */
interface IMvEnumTreeNodes : public IUnknown
{
public:
   /**
    * Retrieves the specified number of nodes in the enumeration sequence.
    *
    * <br><b>Remarks:</b>
    * <ul><li>This method gives you access to internal node information structure.
    *     <li>Returned array is filled with pointers to a constant structure description, hence no Release() 
    *         is needed on the pointers returned inside the structure.
    *     <li>If the tree changes (for example, application adds a child
    *         node on the current node), the enumerator is no longer consistent with the tree, and the method returns
    *         MV_E_ENUM_OUT_OF_SYNC. Discard any data obtained from previous calls to the enumerator,
    *         because it might be invalid. Update the enumerator by calling the IMvEnumTreeNode::Reset method.
    *         You can then call the Next method safely.
    *    <li>An information structure extracted with Next() becomes invalid if the tree changes.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_W_ENUM_END_OF_LIST, if there are no more elements to enumerate.
    *     <li>MV_E_ENUM_OUT_OF_SYNC, if the tree has changed and is now inconsistent with the enumerator.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long           in_ulTreeNodeToRetreive:</i> Number of nodes to retrieve.
    * @param <i>const SMvTreeNodeInfo   out_apksMvTreeNodeInfo:</i> Array of size in_ulTreeNodeToRetreive that is filled with
    *                                                               valid tree node information structure pointers (constant).
    * @param <i>unsigned long           out_pulTreeNodeFetched:</i> Pointer to a variable that receives the number of nodes retrieved.
    *                                                      Can be NULL if in_ulTreeNodeToRetreive is 1.
    */ 
   virtual HRESULT __stdcall Next( unsigned long           in_ulTreeNodeToRetreive, 
                                   const SMvTreeNodeInfo **out_apksMvTreeNodeInfo,
                                   unsigned long          *out_pulTreeNodeFetched ) = 0;

   /**
    * Skips over a specified number of nodes.
    *
    * <br><b>Remark:</b>
    * <ul><li>If the tree changes (for example, the application adds a child node on the current node),
    * the enumerator is no longer consistent with the tree, and the method returns
    * MV_E_ENUM_OUT_OF_SYNC. Discard any data obtained from previous calls to the enumerator,
    * because it might be invalid. Update the enumerator by calling the IMvEnumTreeNode::Reset method.
    * You can then call the Skip method safely.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_W_ENUM_END_OF_LIST, if there are no more elements to skip.
    *     <li>MV_E_ENUM_OUT_OF_SYNC, if the tree has changed and is now inconsistent with the enumerator.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long in_ulTreeNodeToSkip:</i> Number of nodes to skip.
    */
   virtual HRESULT __stdcall Skip( unsigned long in_ulTreeNodeToSkip ) = 0;

   /**
    * Resets the enumeration sequence to the beginning.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    *</ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall Reset() = 0;

   /**
    * Makes a copy of the enumerator with the same enumeration state.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvEnumTreeNode out_ppIMvEnumTreeNode:</i> Address of a variable that receives a pointer to the
    *                                                 IMvEnumTreeNode interface of the new enumerator.  The caller should release the interface when done with it.
    */
   virtual HRESULT __stdcall Clone( IMvEnumTreeNodes ** out_ppIMvEnumTreeNode ) = 0;

};

#endif //IMVENUMTREENODES_H
