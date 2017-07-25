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
//                    IMvMessageTreeInfo.h
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVMESSAGETREEINFO_H
#define IMVMESSAGETREEINFO_H

/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has several methods which return tree information
* associated with the message or error.
* 
* 
* @interface 
*/
interface IMvMessageTreeInfo : public IUnknown
{
public:

   /**
   *  
   *	Gets a copy of the tree which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> The caller must release the tree which is returned.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>IMvSymbolicRootNode ** out_ppIMvSymbolicRootNode </i>:The root node of the tree which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetTree( IMvSymbolicRootNode ** out_ppIMvSymbolicRootNode ) = 0;

   /**
   *  
   *	Gets the source node ID which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> None
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   * </ul>
   * @param <i>unsigned long * out_pulSourceNodeId </i>:The source node ID which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetSourceNodeID( unsigned long * out_pulSourceNodeId ) = 0;

   /**
   *  
   *	Gets the sink node Id which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> None
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>unsigned long * out_pulSinkNodeId </i>:The sink node ID which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetSinkNodeID( unsigned long * out_pulSinkNodeId ) = 0;

   /**
   *  
   *	Gets the pulling node ID which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> None
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>unsigned long * out_pulPullingNodeId </i>:The sink node ID which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetPullingNodeID( unsigned long * out_pulPullingNodeId ) = 0;

   /**
   *  
   *	Gets the pushing node Id which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> None
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>unsigned long * out_pulPushingNodeId </i>:The sink node ID which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetPushingNodeID( unsigned long * out_pulPushingNodeId ) = 0;


};

#endif //IMVMESSAGETREEINFO_H
