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
//                    
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVVIDEOCUTLISTELEMENT_H
#define IMVVIDEOCUTLISTELEMENT_H
#include "IMvFileCutListElement.h"

/**
* Gets the properties of a video cutlist element.
* @interface
* 
*/
interface IMvVideoCutListElement : public IUnknown
{
public:


   /**
    *  Gets the index of the stream in the file. 
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully..
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pulStreamIndex</var> is an invalid pointer.
    * </ul>
    * @param <i>unsigned long out_pulStreamIndex </i>: Pointer to the stream index.
    */
   virtual HRESULT __stdcall GetStreamIndex
   (
       unsigned long *out_pulStreamIndex
   ) = 0;



   /**
    *  Determines whether or not the current cutlist element should use a single frame as the source (with fields repeating normally).
    *
    * <br><b>Remarks:</b>
    * <ul><li> It will use the trim-in point as the single-frame source material.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pbIsSingleFrame</var> is an invalid pointer.
    * </ul>
    * @param <i>bool out_pbIsSingleFrame </i>: TRUE if the cutlist element is to use a single frame as the source. FALSE, otherwise.
    */
   virtual HRESULT __stdcall IsSingleFrame
   (
       bool *out_pbIsSingleFrame
   ) = 0;


   /**
    *  Gets the boolean value indicating whether or not field/frame blending is used to process speed change.
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
    *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pbIsBlending</var> is an invalid pointer.
    * </ul>
    * @param <i>bool out_pbIsBlending </i>: TRUE to apply field/frame-blending processing. FALSE, to apply repeat field/frame processing.
    */
   virtual HRESULT __stdcall IsSlowMotionBlending
   (
       bool *out_pbIsBlending
   ) = 0;

};
#endif //IMVVIDEOCUTLISTELEMENT_H