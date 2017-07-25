//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvGfxFileNameHelper.h $
/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/


#ifndef IMVGFXFILENAMEHELPER_H
#define IMVGFXFILENAMEHELPER_H

#include "mvUnknown.h"//For IUnknown

/** Allows the caller to retrieve information about the location of GFX files and validates whether or not a specified GFX file exists and is of a specific GFX file type.
 * @interface */
interface IMvGfxFileNameHelper : public IUnknown
{
public:

   /**
   * Returns the file extension of the current GFX file type.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>HRESULT
   * </ul>
   *
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
   *     <li>MV_E_INVALID_POINTER, if <i>out_szExtension</i> is NULL.
   *     <li>MV_E_DESTINATION_BUFFER_TOO_SMALL, if <i>out_szExtension</i> is too small to contain the string.
   * </ul>
   * @param <i>char * out_szExtension</i>: Pointer to the string buffer that will be filled with the extension of the GFX file type, including the NULL character. 
   * This parameter cannot be NULL.
   * @param <i>size_t in_sizeSzExtension</i>: Size of the buffer pointed to by <i>out_szExtension</i>. The value cannot be 0.
   */
    virtual HRESULT __stdcall GetGfxExtension(char * out_szExtension, size_t in_sizeSzExtension) = 0;

    /**
    * Returns the file extension of the current GFX file type in a wide character string.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_INVALID_POINTER, if <i>out_wszExtension</i> is NULL.
    *     <li>MV_E_DESTINATION_BUFFER_TOO_SMALL SMALL, if <i>out_wszExtension</i> is too small to contain the string.
    * </ul>
    * @param <i>wchar_t * out_wszExtension</i>: Pointer to the string buffer that will be filled with the extension of the GFX file type, 
	* including the NULL character. This parameter cannot be NULL.
    * @param <i>size_t in_sizeWszExtension</i>: Size of the buffer pointed to by <i>out_wszExtension</i>. The value cannot be 0.
    */
    virtual HRESULT __stdcall GetGfxExtensionW(wchar_t * out_wszExtension, size_t in_sizeWszExtension) = 0;

    /**
    * Gets the directory path where the GFX files of the current type and resolution are stored. 
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The current type and resolution are provided in the <b>Init()</b> function of the <b>IMvGfxFileNameHelperInit</b> interface.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_INVALID_POINTER, if <i>out_szPath</i> is NULL.
    *     <li>MV_E_DESTINATION_BUFFER_TOO_SMALL, if <i>out_szPath</i> is too small to contain the string.
    *     <li>MV_E_NOT_FOUND, if no directory path for the current file type and resolution is found.
    * </ul>
    * @param <i>char_t * out_szPath</i>: Pointer to the string buffer that will be filled with the directory path of the GFX files, including the NULL character. 
	* This parameter cannot be NULL.
    * @param <i>size_t in_sizeSzPath</i>: Size of the buffer pointed to by <i>out_swzPath</i>. The value cannot be 0.
    */
    virtual HRESULT __stdcall GetGfxPathForGfxTypeAndResolution(char * out_szPath, size_t in_sizeSzPath) = 0;

    /**
    * Gets the directory path in a (wide character string) where GFX files of the current type and resolution are stored. 
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The current type and resolution are given in the <b>Init()</b> function of the <b>IMvGfxFileNameHelperInit</b> interface.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_INVALID_POINTER, if <i>out_wszPath</i> is NULL.
    *     <li>MV_E_DESTINATION_BUFFER_TOO_SMALL, if <i>out_wszPath</i> is too small to contain the string.
    *     <li>MV_E_NOT_FOUND if, no directory path for the current file type and resolution is found..
    * </ul>
    * @param <i>wchar_t * out_wszPath</i>: Pointer to the string buffer that will be filled with the directory path of the GFX files, including the NULL character. 
	*	This paramter cannot be NULL.
    * @param <i>size_t in_sizeWszPath</i>: Size of the buffer pointed to by <i>out_swzPath</i>. The value cannot be 0.
    */
    virtual HRESULT __stdcall GetGfxPathForGfxTypeAndResolutionW(wchar_t * out_wszPath, size_t in_sizeWszPath) = 0;

    /**
    * Validates whether or not a specified GFX file exists and whether of not it's of the current type and resolution. 
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The current type and resolution are given in the <b>Init()</b> function of the <b>IMvGfxFileNameHelperInit</b> interface.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_INVALID_POINTER, if a parameter was NULL.
    * </ul>
    * @param <i>const char * in_szGfxFilePath</i>: String containing the complete directory path of the GFX file to validate. 
	* This parameter cannot be NULL.
    * @param <i>bool* out_pbIsOfCurrentTypeAndResolution</i>: Pointer to a boolean value that indicates whether or not the specified GFX file 
	*  exists and whether or not it's of the current type and resolution. TRUE, if the specified GFX file exists and is of the current
	*  type and resoltion. FALSE, otherwise. This parameter cannot be NULL.
    */
    virtual HRESULT __stdcall IsOfCurrentTypeAndResolution(const char * in_szGfxFilePath, bool* out_pbIsOfCurrentTypeAndResolution) = 0;

    /**
    * Validates whether or not a specified GFX file exists and whether or not it's of the current type and resolution. 
	* This interface uses a wide character string. 
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The current type and resolution are given in the <b>Init()</b> function of the <b>IMvGfxFileNameHelperInit</b> interface.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_NOT_INITIALIZED,  if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_INVALID_POINTER, if a parameter was NULL.
    * </ul>
    * @param <i>const wchar_t * in_wszGfxFilePath</i>: String containing the complete directory path of the GFX file to validate. 
	* This parameter cannot be NULL.
    * @param <i>bool* out_pbIsOfCurrentTypeAndResolution</i>: Pointer to a boolean value that indicates whether or not the specified GFX file 
	*  exists and whether or not it's of the current type and resolution. TRUE, if the specified GFX file exists and is of the current
	*  type and resoltion. FALSE, otherwise. This parameter cannot be NULL.
    */
    virtual HRESULT __stdcall IsOfCurrentTypeAndResolutionW(const wchar_t * in_wszGfxFilePath, bool* out_pbIsOfCurrentTypeAndResolution) = 0;

    /**
    * Creates and returns a handle to the GFX file's icon.
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The handle returned can be used in CBitmap's <b>Attach()</b> function.
    *        <li>The handle returned must be closed by an appropriate <b>CloseHandle()</b> function.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if the icon was sucessfully created and returned.
    *     <li>MV_E_INVALID_POINTER, if <i>in_pszFileName</i> or <i>out_phPicon</i> are NULL.
    * </ul>
    * @param <i>const char *in_pszFileName</i>: String containing the complete directory path of the GFX file.
    * @param <i>HBITMAP *out_phPicon</i>: Pointer to the handle that will contain the created icon.
    */
    virtual HRESULT __stdcall CreatePiconBitmap( const char *in_pszFileName, HBITMAP *out_phPicon) = 0;       

    /**
    * Creates and returns a handle to the GFX file's icon. This interface uses a wide character string.
    *
    * <br><b>Remarks:</b>
    * <ul>
    *        <li>The handle returned can be used in CBitmap's <b>Attach()</b> function.
    *        <li>The handle returned must be closed by an appropriate <b>CloseHandle()</b> function.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if the icon was sucessfully created and returned.
    *     <li>MV_E_INVALID_POINTER, if <i>in_pwszFileName</i> or <i>out_phPicon</i> are NULL.
    * </ul>
    * @param <i>const wchar_t *in_pwszFileName</i>: String containing the complete directory path of the GFX file.
    * @param <i>HBITMAP *out_phPicon</i>: Pointer to the handle that will contain the created icon.
    */
    virtual HRESULT __stdcall CreatePiconBitmapW( const wchar_t *in_pwszFileName, HBITMAP *out_phPicon) = 0;       

    
    
    /**
    * Returns the number of linked GFX associated with a GFX. This interface uses a wide character string.
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if the value returned is valid.
    *     <li>MV_E_INVALID_POINTER, if <i>in_pwszMainFileName</i> or <i>out_pulNumberOfLinkedGFX</i> are NULL.
    * </ul>
    * @param <i>const wchar_t *in_pwszMainFileName</i>: String containing the complete directory path of the GFX file.
    * @param <i>unsigned long *out_pulNumberOfLinkedGFX</i>: Pointer to the unsigned long that will contain the number of linked GFX.
    */
    virtual HRESULT __stdcall GetNumberOfLinkedGFX(const wchar_t *in_pwszMainFileName, unsigned long *out_pulNumberOfLinkedGFX) = 0;


    /**
    * Returns the information about a linked GFX associated with a main GFX. This interface uses a wide character string.
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if the value returned is valid.
    *     <li>MV_E_INVALID_POINTER, if <i>in_pwszMainFileName</i> or <i>out_pulNumberOfLinkedGFX</i> are NULL.
    * </ul>
    * @param <i>const wchar_t *in_pwszMainFileName</i>: String containing the complete directory path of the GFX file.
    * @param <i>unsigned long in_ulIndex</i>: Index of the linked GFX in the main GFX.
    * @param <i>SMvLinkedGFXInfo *out_psLinkedGFXInfo</i>: Pointer to the SMvLinkedGFXInfo that will contain the information on the linked GFX.
    */
    virtual HRESULT __stdcall GetLinkedGFXInfo(const wchar_t *in_pwszMainFileName, unsigned long in_ulIndex, SMvLinkedGFXInfo *out_psLinkedGFXInfo) = 0;

    /**
    * Returns the full path of linked a GFX. This interface uses a wide character string.
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>HRESULT
    * </ul>
    *
    * <b>Return values:</b> 
    * <ul>
    *     <li>MV_NOERROR, if the value returned is valid.
    *     <li>MV_E_INVALID_POINTER, if <i>in_psLinkedGFXInfo</i> or <i>out_wszPath</i> are NULL.
    *     <li>MV_E_NOT_INITIALIZED, if the <i>GfxFileHelper</i> object has not been initialized.
    *     <li>MV_E_DESTINATION_BUFFER_TOO_SMALL, if <i>out_wszPath</i> is too small to contain the string.
    *     <li>MV_E_NOT_FOUND if, no full path for the linked GFX file type and resolution is found.
    * </ul>
    * @param <i>SMvLinkedGFXInfo* in_psLinkedGFXInfo</i>: Structure that contains the information about the linked GFX requested.
    * @param <i>wchar_t * out_wszPath</i>: String that will be filled with the full path.
    * @param <i>unsigned long in_ulWszPath</i>: Size of out_wszPath.
    */
    virtual HRESULT __stdcall GetFullPathToLinkedGFX(SMvLinkedGFXInfo* in_psLinkedGFXInfo, wchar_t * out_wszPath, unsigned long in_ulWszPath) = 0;
    
};
#endif //IMVGFXFILENAMEHELPER_H