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
//                    IMVPARAMETRICEFFECT.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 22, 2003 - 10:20:08 AM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVPARAMETRICEFFECT_H
#define IMVPARAMETRICEFFECT_H

//==========================================================================;
// Header files
//==========================================================================;
#include "mvUnknown.h"

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvParametricEffect
//==========================================================================;

/**
 * This generic interface is used to access a Parametric Effect. From this interface, you can query specific interfaces (see below). It also exposes the API to get basic information: the GUID of the Flex object (Compositor, AudioMixer, or Effect) represented by this Parametric Effect, and the GUID of the previous version of this Parametric Effect.<br>
 * <br><b>Remark:</b>
 * <ul><li>You obtain the pointer to a IMvParametricEffect by calling the CreateParametricEffect() function from the DirectShow Flex Helper. This creates the Parametric Effect and automatically associates it with the Flex object it represents. You cannot create a Parametric Effect directly.</ul>
 * <ul><li>The IMvParametricEffect interface supports the following query interfaces: <b>IID_IMvParamFxInitialization</b> and <b>IID_IMvGFXFileNameProvider</b>.</ul>
 * @interface
 */
interface IMvParametricEffect : public IUnknown
{

   //==========================================================================;
   // Public operations
   //==========================================================================;
public:

   /**
    * Returns the type of the Flex Object represented by the Parametric Effect.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>The types currently include Video Compositor, Video Effects (filters and/or transitions), and Audio Mixer.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if an error occured.
    * </ul>
    * @param out_peParamFxFlexObjType: Pointer to a EMvParamFxFlexObjectType enum that will receive the Flex Object type.*/
   virtual HRESULT __stdcall GetRepresentedFlexObjectType(EMvParamFxFlexObjectType * out_peParamFxFlexObjType) = 0;

   /**
    * Returns the GUID of the Flex Object represented by the Parametric Effect.<br>
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
    * <li>HRESULT error code, if a module called reported an error.
    * </ul>
    * @param out_pGUID: Pointer to a CLSID structure that will receive the GUID of the Flex object represented by the Parametric Effect.*/
   virtual HRESULT __stdcall GetRepresentedFlexObjectGUID(CLSID * out_pGUID) = 0;

	   /**
    * Frees the parametric effect so that we can switch flex resources to another process.<br>
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
    * <li>HRESULT error code, if a module called reported an error.
    * </ul>
    * @param */
   virtual HRESULT __stdcall ReleaseParametricEffect() = 0;
	   /**
    * Reloads the parametric effect (called after switching back from another process).<br>
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
    * <li>HRESULT error code, if a module called reported an error.
    * </ul>
    * @param */
   virtual HRESULT __stdcall ReloadParametricEffect() = 0;

};


#endif //IMVPARAMETRICEFFECT_H
