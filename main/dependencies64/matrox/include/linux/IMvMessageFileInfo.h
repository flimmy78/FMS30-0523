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
//                    IMvMessageFileInfo.h
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


#ifndef IMVMESSAGEFILEINFO_H
#define IMVMESSAGEFILEINFO_H

/** 
* This interface may be supported on the object attached to IMvMessage objects which are
* on the message stack.  This interface has one method which returns the name of the file,
* which is either or read or written to, that caused the message or error to occur. 
* 
* 
* 
* @interface 
*/
interface IMvMessageFileInfo : public IUnknown
{
public:

   /**
   *  
   *	Gets the filename which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> A filename is usually returned for messages or errors that involve either
   *        reading or writing that file. 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error.   
   * </ul>
   * @param <i>const char ** out_ppszFullFileNameandPath </i>:The filename which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetFileName( const char ** out_ppszFullFileNameandPath ) = 0;

   /**
   *  
   *	Gets the filename (in wide character) which caused the message or error to occur.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> A filename is usually returned for messages or errors that involve either
   *        reading or writing that file. 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if operation succeeded.
   *     <li>MV_E_NOT_SUPPORTED, if not supported for this type of message or error   
   * </ul>
   * @param <i>const wchar_t ** out_ppwszFullFileNameandPath </i>:The filename which caused the message or error to occur.
   */
   virtual HRESULT __stdcall GetFileNameW( const wchar_t ** out_ppwszFullFileNameandPath ) = 0;

};

#endif //IMVMESSAGEFILEINFO_H
