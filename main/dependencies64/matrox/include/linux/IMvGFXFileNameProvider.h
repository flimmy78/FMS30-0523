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
//                    IMVGFXFILENAMEPROVIDER.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 23, 2003 - 9:57:39 AM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVGFXFILENAMEPROVIDER_H
#define IMVGFXFILENAMEPROVIDER_H
#include "mvUnknown.h"
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
 * Retrieves the file names of GFX files required by the effect. The file names can then be used to generate the elements that will go in the cutlists of the appropriate GFX sources. The appropriate source nodes can also be added to the effect tree(s).<br>
 * <br><b>Remark:</b>
 * <ul><li>The order in which the file names are retrieved is important. When specifying the index of the GFX source nodes, you must use the same order that was used for the children of the effect node in the effect tree(s).</ul>
 * <ul><li>To generate the GFX file names (such as to generate the Effect Settings), the Parametric Effects use the Parameters Provider to obtain the actual parameters and converts them into the actual complete file names (or into the actual Effect Settings).</ul>
 * @interface
 */
interface IMvGFXFileNameProvider : public IUnknown
{
   //==========================================================================;
   // Public operations
   //==========================================================================;
public:

   /**
    * Returns the number of GFX files required by the effect.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li></ul>
    * 
    * <br><b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module called reported an error.
    * </ul>
    *
    * @param unsigned long * out_pulNbFileNames: Number of files.
    */
   virtual HRESULT __stdcall GetNumberOfGFXFileNames(unsigned long * out_pulNbFileNames) = 0;

   /**
    * Returns the file name (in MBCS format) of the GFX file specified by the index.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>The index used when adding the GFX source node as a child of the effect node does not have to match this index. However, the order of the index must be the same. For example, the GFX 0 and 1 can be added to the effect tree as children 2 and 3 of the effect node respectively, appearing in the same order.</ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module reported an error.
    * </ul>
    *
    * @param unsigned long in_ulIndex: Index of the GFX source node.
    * @param const wchar_t * * out_pstrFileName: Output file name.
   */
   virtual HRESULT __stdcall GetGFXFileNameAlloc(  unsigned long in_ulIndex,
                                                   char * * out_pstrFileName) = 0;
/**
    * Frees the file name allocated using GetGFXFileNameAlloc (in MBCS format) .<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li></ul>
    * 
    * <b>Return Type:</b>
    * <ul><li></ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>
    * </ul>
    *
    * @param const char_t* in_pwszName: pointer to the string.
    * 
    */
   virtual void __stdcall FreeGFXFileName(const char* in_pwszName)=0;


   /**
    * Returns the file name (in Unicode format) of the GFX file specified by the index.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>The index used when adding the GFX source node as a child of the effect node does not have to match this index. However, the order of the index must be the same. For example, the GFX 0 and 1 can be added to the effect tree as children 2 and 3 of the effect node respectively, appearing in the same order.</ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module reported an error.
    * </ul>
    *
    * @param unsigned long in_ulIndex: Index of the GFX source node.
    * @param const wchar_t * * out_pstrFileName: Output file name.
    */
   virtual HRESULT __stdcall GetGFXFileNameAllocW( unsigned long in_ulIndex,
                                                   wchar_t * * out_pstrFileName) = 0;
 /**
    * Frees the file name allocated using GetGFXFileNameAllocW (in Unicode format) .<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li></ul>
    * 
    * <b>Return Type:</b>
    * <ul><li></ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>
    * </ul>
    *
    * @param const wchar_t* in_pwszName: pointer to the string.
    * 
    */
	virtual void __stdcall FreeGFXFileNameW(const wchar_t* in_pwszName)=0;

};


#endif //IMVGFXFILENAMEPROVIDER_H
