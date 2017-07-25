//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvParametricEffectInfo.h $
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

#ifndef IMvParametricEffectInfo_h_h
#define IMvParametricEffectInfo_h_h

#include "mvUnknown.h"//For IUnknown and "interface" keyword

/** Retrieves information on a specific registered Parametric Effect available for the current profile.
* @interface */
interface IMvParametricEffectInfo : public IUnknown
{
	
public:

   /**
   *  Gets the Parametric Effect's architecture GUID.
   *
   * <br><b>Remarks:</b>
   * <ul><li>None
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the GUID was retrieved successfully.
   *     <li>MV_E_INVALID_POINTER, if out_pGUID is NULL.
   * </ul>
   * @param <i>GUID* out_pGUID </i>: Pointer to receive the GUID.
   */
	virtual HRESULT __stdcall GetArchitectureGUID( GUID* out_pGUID ) const = 0;

   /**
   *  Gets the Parametric Effect's GUID.
   *
   * <br><b>Remarks:</b>
   * <ul><li>None.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the GUID was retrieved successfully.
   *     <li>MV_E_INVALID_POINTER, if out_pGUID is NULL.
   * </ul>
   * @param <i>GUID* out_pGUID </i>: Pointer to receive the GUID.
   */
	virtual HRESULT __stdcall GetParamFxGUID( GUID* out_pGUID ) const = 0;

   /**
   *  Gets the GUID of the previous version of the Parametric Effect.
   *
   * <br><b>Remarks:</b>
   * <ul><li>If the returned GUID is GUID_NULL, it means the Parametric Effect is the latest one.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the GUID was retrieved successfully.
   *     <li>MV_E_INVALID_POINTER, if out_pGUID is NULL.
   * </ul>
   * @param <i>GUID* out_pGUID </i>: Pointer to receive the GUID.
   */
	virtual HRESULT __stdcall GetParamFxPreviousVersionGUID( GUID* out_pGUID ) const = 0;

   /**
   *  Gets the name of the Parametric Effect.
   *
   * <br><b>Remarks:</b>
   * <ul><li>None.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if operation completed successfully.
   *     <li>MV_E_INVALID_POINTER, if out_pkwszEffectName is NULL.
   * </ul>
   * @param <i>const wchar_t** out_pkwszEffectName </i>: Pointer to the string of the effect name. Cannot be NULL.
   */
   virtual HRESULT __stdcall GetParamFxName( const wchar_t** out_pkwszParamFxName ) const = 0;

   /**
    * Gets the type of the Flex Object represented by the Parametric Effect.<br>
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
   virtual HRESULT __stdcall GetRepresentedFlexObjectType(EMvParamFxFlexObjectType * out_peParamFxFlexObjType) const = 0;

   /**
    * Gets the GUID of the Flex Object represented by the Parametric Effect.<br>
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
   virtual HRESULT __stdcall GetRepresentedFlexObjectGUID(CLSID * out_pGUID) const = 0;

   /**
   *  Gets the number of sources required for the Video Filter Effect represented by the Parametric Effect.
   *
   * <br><b>Remarks:</b>
   * <ul><li>Supported only if the Parametric Effect represents an Video Filter Effect.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if operation completed successfully.
   *     <li>MV_E_INVALID_POINTER, if out_pulNumberOfSources is NULL.
   *     <li>MV_E_NOT_SUPPORTED, if the ParamFx doesn't represent a Video Filter effect.
   * </ul>
   * @param <i> unsigned long* out_pulNumberOfSources </i>: Pointer to the number of sources required by the Parametric Effect. Cannot be NULL.
   */
   virtual HRESULT __stdcall GetNumberOfVideoFilterSources( unsigned long* out_pulNumberOfSources ) const = 0;
};

#endif
