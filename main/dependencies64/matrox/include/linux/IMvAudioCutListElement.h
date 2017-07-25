
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

#ifndef IMVAUDIOCUTLISTELEMENT_H
#define IMVAUDIOCUTLISTELEMENT_H
#include "IMvFileCutListElement.h"

/**
* @interface
* Provides information about an audio cutlist element, which is required by the Source filter.
*
*/
interface IMvAudioCutListElement : public IUnknown
{
public:
   /**
    *  Gets the index of the stream in the RIFF file.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully. 
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pulStreamIndex</var> is an invalid pointer.
    * </ul>
    * @param <i>unsigned long out_pulStreamIndex </i>: Pointer to the number of the stream to open.
    */
   virtual HRESULT __stdcall GetStreamIndex
   (
       unsigned long *out_pulStreamIndex
   ) = 0;

   /**
    *  Queries whether or not an element starts with an automatic fade-in.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pbHasFadeIn</var> is an invalid pointer.
	 * </ul>
    * @param <i>bool out_pbHasFadeIn </i>: Pointer to a boolean value. TRUE, if the element starts with an automatic audio fade-in. FALSE, otherwise.
    */
   virtual HRESULT __stdcall HasFadeIn
   (
       bool *out_pbHasFadeIn
   ) = 0;

   /**
    *  Queries whether or not an element ends with an automatic fade-out.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pbHasFadeOut</var> is an invalid pointer.
    * </ul>
    * @param <i>bool out_pbHasFadeOut </i>: Pointer to a boolean value. TRUE, if the element ends with an automatic audio fade-out. FALSE, otherwise.
    */
   virtual HRESULT __stdcall HasFadeOut
   (
       bool *out_pbHasFadeOut
   ) = 0;

};
#endif //IMVAUDIOCUTLISTELEMENT_H