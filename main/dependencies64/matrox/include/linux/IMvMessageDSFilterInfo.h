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
//                    I_MV_MESSAGE_DSFILTER_INFO.H
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



#ifndef _I_MV_MESSAGE_DSFILTER_INFO_H
#define _I_MV_MESSAGE_DSFILTER_INFO_H


/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has a method which returns Direct Show filter class ID
* associated with the message or error.
* 
* 
* @interface 
*/
interface IMvMessageDSFilterInfo : public IUnknown 
{
public:

   /**
   *  
   *	Gets a Direct Show filter's class ID, associated with the message or error.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> None.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>CLSID * out_pClsid </i>:Class ID of the filter associated with the message or error.
   */
	virtual HRESULT __stdcall GetClsid( CLSID * pClsid ) = 0;

};

#endif //_I_MV_MESSAGE_DSFILTER_INFO_H
