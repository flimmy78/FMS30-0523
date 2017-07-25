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
//                    IMVOUTPUTVIDEOPUSHINGNODE.H
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

#ifndef IMVOUTPUTVIDEOPUSHINGNODE_H
#define IMVOUTPUTVIDEOPUSHINGNODE_H

#include "IMvOutputVideoNode.h"

/**
 * This interface is used to send a video stream to the host application.
 * @interface
 */
interface IMvOutputVideoPushingNode : public IMvOutputVideoNode {
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
    * @param EMvPushingMode    in_eMvPushingMode:    Pushing mode of this node.
    * @param IMvVideoPushing   in_pIVideoPushing:    Pushing interface.
    */
   virtual HRESULT __stdcall Init( EMvPushingMode in_eMvPushingMode, IMvVideoPushing *in_pIVideoPushing ) = 0;

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
    * Gets the current operation mode of the pushing node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>The pushing node has three different modes of operation:
    * 		<DIR>
    *			<li>Undefined format mode:   Host application will receive the resulting Flex surface of the child node
    *                                    linked to this pushing node. The obtained result can be of any format.
    *			<li>Defined format mode:     Host application will receive the resulting Flex surface of the child node
    *                                    linked to this pushing node.  The obtained result should be a Flex surface
    *                                    that has a specific format.
    *			<li>Defined format "with destination" mode:
    *                                    Host application will receive a copy of the resulting Flex surface of the
    *                                    child node linked to this pushing node. The copy will be created in a Flex surface
    *                                    provided by the host application. The host application will force the format.
    * 		</DIR>
    *       <li>Communication with the host application is done through the IMvVideoExchange interface, which has to be
    *            implemented on a host application object.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param EMvPushingMode out_refeMvPushingMode: Pushing mode receiver.
    */
   virtual HRESULT __stdcall GetPushingMode( EMvPushingMode &out_refeMvPushingMode ) = 0;

   /**
    * Gets the callback interface implemented by the host application.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>This call will add a reference on the received interface.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param IMvVideoPushing out_ppIMvVideoPushing: Pointer to a pushing interface container.
    */
   virtual HRESULT __stdcall GetCallbackInterface( IMvVideoPushing **out_ppIMvVideoPushing ) = 0;
};



#endif //IMVOUTPUTVIDEOPUSHINGNODE_H




