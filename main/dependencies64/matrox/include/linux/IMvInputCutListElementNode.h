//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvInputCutListElementNode.h $
//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved.
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
//                    IMVINPUTCUTLISTELEMENTNODE.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             SEPTEMBER 28, 2004 - 5:24:18 PM
//   Operating System:       WinXP
//   Author:                 YourName
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVINPUTCUTLISTELEMENTNODE_H
#define IMVINPUTCUTLISTELEMENTNODE_H
//==========================================================================;
// Header files
//==========================================================================;
#include "IMvTreeNode.h"

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvInputNodeCutListElement 
//==========================================================================;

/**
 * This interface allows the user to set a cutlist element on an InputCutListElementTree node.<br>
 * <br><b>Remark:</b>
 * <ul><li>None.</ul>
 * @version 1.0
 * @since October 1, 2004
 * @interface
 * @author Mohamed Jivraj
*/
struct IMvInputCutListElementNode : public IMvTreeNode
{
public:

   /**
    * This operation allows the user to set a cutlist element on an Input Element Tree Node.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Operation can only be called in Stop State.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param  IMvCutListElement *in_pIMvCutListElement : This is the cutlist element to set.
    * @since  October 1, 2004
    * @version 1.0
    * @author Mohamed Jivraj
    */
   virtual HRESULT __stdcall SetCutListElement( IMvCutListElement *in_pIMvCutListElement) = 0;

   /**
    * This operation retrieves the cutlist element set on the input node.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Operation can only be called in Stop State.
    * <li>The function Addrefs the CutListElement.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param  IMvCutListElement **out_ppIMvCutListElement : This is a pointer to the cutlist element pointer currently set on the node.
    * @since  October 1, 2004
    * @version 1.0
    * @author Mohamed Jivraj
    */
   virtual HRESULT __stdcall GetCutListElement( IMvCutListElement **out_ppIMvCutListElement ) = 0;

   /**
    * This operation allows the user to set a MediaSubType on the input element node.
    * The MediaSubType determines if the file will be Video, Graphics, or GFX.
    * <br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Operation can only be called in Stop State.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param  GUID in_guidSubType : The Media SubType to set on the cutlist element node.
    * @since  October 1, 2004
    * @version 1.0
    * @author Mohamed Jivraj
    */
   virtual HRESULT __stdcall SetMediaSubType( GUID in_guidSubType ) = 0;

   /**
   * This operation allows the user to set a MediaSubType on the input element node.
   * The MediaSubType determines if the file will be Video, Graphics, or GFX.
   * <br>
   *
   * <br><b>Remark:</b>
   * <ul><li>Operation can only be called in Stop State.
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR:          Succeeded.
   *     <li>MV_E_INVALIDARG:     A parameter is invalid.
   *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
   *     <li>ERROR CODE:          A module called reported an error.
   * </ul>
   *
   * @param  GUID *out_pguidSubType : The Media SubType currently set on the cutlist element node.
   * @since  October 1, 2004
   * @version 1.0
   * @author Mohamed Jivraj
   */
   virtual HRESULT __stdcall GetMediaSubType( GUID *out_pguidSubType ) = 0;

   /**
    * The operation sets the stream index that should be pulled from the cutlist element.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>Only valid for media files that contain more than one stream, e.g. AVI files, etc.
    * <li>The stream index can only be set in Stop state.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param unsigned long in_ulStreamIndex : The stream index to be set.
    * @since  October 1, 2004
    * @version 1.0
    * @author Mohamed Jivraj
    */
   virtual HRESULT __stdcall SetStreamIndexToPull( unsigned long in_ulStreamIndex ) = 0;

    /**
    * This operation gets the current stream index set on the input node.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>For files that do not have multiple streams, this will always return 1.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR:          Succeeded.
    *     <li>MV_E_INVALIDARG:     A parameter is invalid.
    *     <li>MV_E_UNINITIALIZED:  The current object is not initialized correctly.
    *     <li>ERROR CODE:          A module called reported an error.
    * </ul>
    *
    * @param unsigned long *out_pulStreamIndex : The stream index currently set.
    * @since October 1, 2004
    * @version 1.0
    * @author Mohamed Jivraj
    */
   virtual HRESULT __stdcall GetStreamIndexToPull( unsigned long *out_pulStreamIndex ) = 0;

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

   //==========================================================================;
   // Public operations
   //==========================================================================;
};


#endif //IMVINPUTCUTLISTELEMENTNODE_H
