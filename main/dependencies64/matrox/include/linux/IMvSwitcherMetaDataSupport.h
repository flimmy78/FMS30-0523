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
//                    IMVSWITCHERMETADATASUPPORT.H
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


#ifndef IMVSWITCHERMETADATASUPPORT_H
#define IMVSWITCHERMETADATASUPPORT_H

#include "mvUnknown.h"


/**
 * This interface is not implemented yet and could be redesigned!
 * @interface
 */
interface IMvSwitcherMetaDataSupport : public IUnknown
{
public:

  /**
    *  Used to write metadata information to a file.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Should be called after a file has been captured.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FAIL,  if failed.
    * </ul>
    * @param const unsigned long in_ulCookie: Cookie of file to write to.
    */
   virtual HRESULT __stdcall WriteMetaData
   (
      const unsigned long  in_ulCookie
   ) = 0;
};



#endif //IMVSWITCHERMETADATASUPPORT_H




