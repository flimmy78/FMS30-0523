
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

#ifndef IMVCUTLIST2_H
#define IMVCUTLIST2_H

/**
*
* Implements the cutlist given to the Source or Transform filters.
* The filters can access any element using GetSpecifiedElement().
* @interface
*/
interface IMvCutList2 : public IMvCutList
{
   /**
   *  Gets the media type
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
   *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameDuration</var> is an invalid pointer.    
   * </ul>
   * @param <i>uint64_t out_pui64FrameDuration </i>: Pointer to the duration of the cutlist in frames.
   */
   virtual HRESULT __stdcall GetMediaType( SMvMediaType* out_psMediaType ) = 0;
   
   /**
   *  Gets the resolution
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
   *	    <li>MV_E_ELEMENT_NOT_FOUND, if no element is found at the seek position.
   *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_ppIMvElement</var> is an invalid pointer.	
   * </ul>
   * @param <i>uint64_t in_ui64FramePos </i>: Seek position in frames.
   * @param <i>IMvCutListElement out_ppIMvElement </i>: Pointer to the cutlist element's pointer.
   */
   virtual HRESULT __stdcall GetResolutionInfo( SMvResolutionInfo* out_psResolutionInfo ) = 0;
   
};
#endif //IMVCUTLIST2_H