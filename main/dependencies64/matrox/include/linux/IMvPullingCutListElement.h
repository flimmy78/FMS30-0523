
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


#ifndef IMVPULLINGCUTLISTELEMENT_H
#define IMVPULLINGCUTLISTELEMENT_H

#include "IMvCutListElement.h"
#include "IMvPullingCallBack.h"

/**
 * @interface
 * Allows the Source filter to pull buffers directly from the user application.
 * Instead of the cutlist class implementing callbacks to the user application, the application implements
 * the <b>IMvPullingCallBack</b> interface, which the Source filter will get via this interface.
 * 
 */
interface IMvPullingCutListElement : public IUnknown
{
public:
   /**
    * Gets the pulling callback interface.
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the call succeeded.
    *	   <li>MV_E_INVALID_POINTER, if the parameter <var>out_ppIMvPullingCallback</var> is an invalid pointer.
    *       <li>E_NOINTERFACE, if the interface is not supported.
    * </ul>
    * @param <i>IMvPullingCallBack out_ppIMvPullingCallback </i>: Pointer to the callback interface.
    */
   virtual HRESULT __stdcall GetIMvPullingCallBack
   (
      IMvPullingCallBack	**out_ppIMvPullingCallback
   ) = 0;

   /**
    * Gets the split offset for the pulling element.
    * <br><b>Remark:</b>
    * 
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the call succeeded.
    *	   <li>MV_E_INVALID_POINTER, if the parameter <var>out_pi64SplitOffset</var> is an invalid pointer.
    * </ul>
    * @param <i>int64_t out_pi64SplitOffset </i>: The split position of the element in frames.
    */
   virtual HRESULT __stdcall GetElementSplitOffset
   (
      int64_t 	*out_pi64SplitOffset
   ) = 0;
};

#endif //IMVPULLINGCUTLISTELEMENT_H