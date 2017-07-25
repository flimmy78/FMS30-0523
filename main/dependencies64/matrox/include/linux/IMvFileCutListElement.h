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

#ifndef IMVFILECUTLISTELEMENT_H
#define IMVFILECUTLISTELEMENT_H

#include "IMvCutListElement.h"
#include "IMvCustomFileSystemIO.h"

/**
* Gets the properties of a file cutlist element.
* @interface
* 
*/
interface IMvdSpannedFiles;

interface IMvFileCutListElement : public IUnknown
{
public:
    
   /**
    *  Gets the trim length of the file.
    *
    * <br><b>Remarks:</b>
    * <ul><li> Trim length is the total duration of all split elements
    * or the duration if the element is not split.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameLength</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameLength </i>: Pointer to the trim length in frames.
    */
   virtual HRESULT __stdcall GetTrimLength
   (
   	uint64_t		*out_pui64FrameLength
   ) = 0;

   /**
    *  Gets the file name of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> The caller allocates space and the caller frees the space.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter out_ppwszFileName is an invalid pointer.
    *	    <li>MV_E_OUT_OF_MEMORY, if there is not sufficient memory available.
    * </ul>
    * @param <i>wchar_t out_ppwszFileName </i>: Pointer to the file names' pointer.
    */
   virtual HRESULT __stdcall GetFileName
   (
      wchar_t **out_ppwszFileName
   ) = 0;

   /**
    * Gets the Trim-in position of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameTrimIn</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameTrimIn </i>: Pointer to the Trim-in position of the element in frames.
    */
   virtual HRESULT __stdcall GetTrimInPosition
   (
   	uint64_t 	*out_pui64FrameTrimIn
   ) = 0;

   /**
    *  Gets the Trim-out position of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameTrimOut</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameTrimOut </i>: Pointer to the Trim-out position of the element in frames.
    */
   virtual HRESULT __stdcall GetTrimOutPosition
   (
   	uint64_t		*out_pui64FrameTrimOut
   ) = 0;

   /**
    *  Gets the origin position of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameOrigin</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameOrigin </i>: Pointer to the origin position of the element in frames.
    */
   virtual HRESULT __stdcall GetOriginPosition
   (
   	uint64_t		*out_pui64FrameOrigin
   ) = 0;

   /**
    *  Gets the split offset of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	* </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameOffset</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameOffset </i>: Pointer to the split offset of the element in frames. The value is 0 if there is no offset.
    */
   virtual HRESULT __stdcall GetElementSplitOffset
   (
   	uint64_t 	*out_pui64FrameOffset
   ) = 0;

	/**
	 * Specifies the custom file I/O to use for the element.
	 *
     * <br><b>Remarks:</b>
	 * <ul><li>
	 * </ul>
	 *
	 * <b>Return Type:</b>
	 * <ul><li>HRESULT
	 * </ul>
	 * <b>Return Values:</b>
	 * <ul><li>MV_NOERROR, if completed successfully.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_ppIMvFileSystemIO</var> is an invalid pointer.
     * </ul>
     * @param <i>IMvCustomFileSystemIO out_ppIMvFileSystemIO </i>: Pointer to the IMvCustomFileSystemIO file system interface or NULL if none.
    */
   virtual HRESULT __stdcall GetCustomFileIO
   (
   	IMvCustomFileSystemIO   **out_ppIMvFileSystemIO
   ) = 0;


   /**
    * Notifies the Source filter that the current file is in Time Delay mode (for example, 
    * (for example, the file is still being used for capture).
    *
    * <br><b>Remarks:</b>
	* <ul><li>
	* </ul>
	*
    * <b>Return Type:</b>
    * <ul><li>HRESULT
	*</ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pbTDIR<var> is an invalid pointer.
	* </ul>
    * @param <i>bool out_pbTDIR </i>: TRUE, if the current file is in Time Delay mode. FALSE, if otherwise.
    */
   virtual HRESULT __stdcall IsRemoteTD
   (
      bool  *out_pbTDIR
   ) = 0;

   /**
    *  Gets the Index file name of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> The caller allocates space and the caller frees the space.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter out_ppwszFileName is an invalid pointer.
    *	    <li>MV_E_OUT_OF_MEMORY, if there is not sufficient memory available.
    * </ul>
    * @param <i>wchar_t out_ppwszFileName </i>: Pointer to the file names' pointer.
    */
   virtual HRESULT __stdcall GetIndexFileName
   (
      wchar_t **out_ppwszIndexFileName
   ) = 0;


   /**
    *  Gets the spanned file interface  of the element.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> The caller allocates space and the caller frees the space.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter out_ppwszFileName is an invalid pointer.
    *	    <li>MV_E_OUT_OF_MEMORY, if there is not sufficient memory available.
    * </ul>
    * @param <i>wchar_t out_ppwszFileName </i>: Pointer to the file names' pointer.
    */
   virtual HRESULT __stdcall GetSpannedFiles
   (
      IMvdSpannedFiles ** out_pISpannedFiles
   ) = 0;


};
#endif //IMVFILECUTLISTELEMENT_H