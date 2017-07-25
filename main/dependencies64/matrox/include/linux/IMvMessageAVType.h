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
//                    IMvMessageAVType.h
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


#ifndef IMVMESSAGEAVTYPE_H
#define IMVMESSAGEAVTYPE_H

/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has one method which returns the name of the file,
* which is either or read or written to, that caused the message or error to occur. 
* 
* 
* 
* @interface 
*/

interface IMvMessageAVTypeInfo : public IUnknown
{
public:

   /**
   *  
   *	Gets the AVType (audio or video) of the message.
   *
   * <br><b>Remarks:</b>
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   */
   virtual HRESULT __stdcall GetAVType(EMvMessageInfoAVType&  out_eMvAVType) = 0;

};

#endif //IMVMESSAGEAVTYPE_H
