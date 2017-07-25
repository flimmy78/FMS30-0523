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
//                    IMVOUTPUTAUDIOPUSHINGNODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 23, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVOUTPUTAUDIOPUSHINGNODE_H
#define IMVOUTPUTAUDIOPUSHINGNODE_H
#include "IMvOutputAudioNode.h"


/**
 * This interface is used to send an audio stream to the host application.
 * @interface
 * 
 * 
 * 
 */
interface IMvOutputAudioPushingNode : public IMvOutputAudioNode
{
public:

   /**
    * Gets the current operation mode of the pushing node.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>The pushing node has three different modes of operation:
    * 		 <DIR>
    *			<li>Undefined format mode: Host application will receive the resulting Flex audio samples of the child node 
    *                                  linked to this pushing node.
    *			<li>Defined format mode:   Host application will receive a copy of the resulting Flex audio samples of the
    *                                  child node linked to this pushing node. The copy should be a Flex audio samples'
    *                                  buffer that has a specific format.
    *			<li>Defined format with destination mode:
    *                                  Host application will receive a copy of the resulting Flex audio samples of the
    *                                  child node linked to this pushing node. The copy will be created in a Flex audio samples'
    *                                  buffer provided by the host application. The host application will force the format.
    * 		 </DIR>
    *        <li>Communication with the host application is carried out through the IMvAudioExchange interface, which has to be
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
    * @param EMvPushingMode &out_refeMvPushingMode: Pushing node receiver.
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
    * @param IMvAudioPushing* out_ppIMvAudioPushing: Pointer to a pushing interface container.
    */
   virtual HRESULT __stdcall GetCallbackInterface( IMvAudioPushing * * out_ppIMvAudioPushing ) = 0;
};



#endif //IMVOUTPUTAUDIOPUSHINGNODE_H




