//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvSetFileSystem.h $
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
//                    IMVSETFILESYSTEM.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             AUGUST 4, 2003 - 6:19:15 PM
//   Operating System:       WinXP
//   Author:                 YourName
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVSETFILESYSTEM_H
#define IMVSETFILESYSTEM_H
//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvSetFileSystem
//==========================================================================;

/**
 * Provides the ability to use a file system other than FAT 32 or NTFS.<br>
*/
interface IMvSetFileSystem : public IUnknown
{
public:

   /**
    * Specifies the GUID that implements the file I/O, which allows the selection of the custom file system I/O interface.<br>
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
    *     <li>ERROR CODE, if a function reported an error.
    * </ul>
    *
    * @param <i>in_clsidFileSystem</I>: ID of the custom file system.
    */
   virtual HRESULT __stdcall SelectFileIO
   (
      REFCLSID in_clsidFileSystem
   ) = 0;

   /**
    * Sets the interface used for the custom file system I/O.<br>
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
    *     <li>ERROR CODE, if a function reported an error.
    * </ul>
    *
    *@param <i>*in_pICustomFileIO</I>: Pointer to the <i>IMvCustomFileSystemIO</i> interface.
    */
   virtual HRESULT __stdcall SetCustomFileIO
   (
      IMvCustomFileSystemIO   *in_pICustomFileIO
   ) = 0;

   /**
    * Gets the interface used by the custom file system I/O.<br>
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
    *     <li>ERROR CODE, if a function reported an error.
    * </ul>
    *
    * @param <i>**out_ppICustomFileIO</I>: Pointer to the <i>IMvCustomFileSystemIO</i> interface's pointer.
    */
   virtual HRESULT __stdcall GetCustomFileIO
   (
      IMvCustomFileSystemIO   **out_ppICustomFileIO
   ) = 0;

   //==========================================================================;
   // Public operations
   //==========================================================================;
};


#endif //IMVSETFILESYSTEM_H
