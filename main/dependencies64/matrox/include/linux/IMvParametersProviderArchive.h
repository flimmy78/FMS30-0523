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
//                    IMVPARAMETERSPROVIDERARCHIVE.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 23, 2003 - 6:17:40 PM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVPARAMETERSPROVIDERARCHIVE_H
#define IMVPARAMETERSPROVIDERARCHIVE_H

//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvParametersProviderArchive
//==========================================================================;

/**
 * This generic interface is used to access a Parameters Provider's Archive. The role of the Parameters Provider Archive is to allow a Parameters Provider to be persistent.<br>
 * <br><b>Remark:</b>
 * <ul><li>None. </ul>
 * @interface
 */
interface IMvParametersProviderArchive : public IUnknown
{
   //==========================================================================;
   // Public operations
   //==========================================================================;
public:

   /**
    * Indicates whether the Archive is in "Storing" or "Restoring" mode.<br>
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
    * <li>HRESULT error code, if a module reported an error.
    * </ul>
    *
    * @param IMvParametricEffect * in_pbIsStoring: Pointer that indicates whether the archive is storing data or not. 
    */
   virtual HRESULT __stdcall IsStoring(bool * in_pbIsStoring) = 0;

};


#endif //IMVPARAMETERSPROVIDERARCHIVE_H
