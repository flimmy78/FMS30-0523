//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvFileSystemIONotifyState.h $
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
//                    IMVFILESYSTEMIONOTIFYSTATE.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             AUGUST 4, 2003 - 6:43:15 PM
//   Operating System:       WinXP
//   Author:                 YourName
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVFILESYSTEMIONOTIFYSTATE_H
#define IMVFILESYSTEMIONOTIFYSTATE_H
//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMv
//==========================================================================;

/**
 * Provides information about the current read and write state of the custom file system I/O.<br>
 * <br><b>Remark:</b>
 * <ul><li>None.</ul>
*/
interface IMvFileSystemIONotifyState : public IUnknown
{
public:

   /**
    *Provides the state of a given I/O command specified by the structure or parameters.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param <i>in_eIOState</i>: Current state of the custom file system I/O command.
	* @param <i>*in_psOvlp</i>: Pointer to the file offset location of the I/O.
	* @param <i> in_lBytesReadOrWritten </i>: Size of the processed read or write request in bytes.
    */
   virtual HRESULT __stdcall Notify
   (
      EMvIOState     in_eIOState,            
      SMvOverlapped  *in_psOvlp,             
      long           in_lBytesReadOrWritten  
   ) = 0;

   //==========================================================================;
   // Public operations
   //==========================================================================;
};


#endif //IMVFILESYSTEMIONOTIFYSTATE_H
