//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvParametricEffectInfoList.h $
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

#ifndef IMvParametricEffectInfoList_h_h
#define IMvParametricEffectInfoList_h_h

#include "mvUnknown.h"//For IUnknown and "interface" keyword


#include "IMvParametricEffectInfo.h"
#include "IMvParametricEffectInfoEnumerator.h"

/** Allows the caller to retrieve the properties of registered Parametric effects that are available for the current profile.
* @interface */
interface IMvParametricEffectInfoList : public IUnknown
{
	
public:

   /**
   *  Gets the properties of the latest version of a Parametric Effect with the GUID of an older version.
   *
   * <br><b>Remarks:</b>
   * <ul><li></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the Param Fx properties were found and returned.
   *     <li>MV_E_INVALID_PARAMETER, if in_rsPreviousParamFxGUID is CLSID_NULL.
   *     <li>MV_E_INVALID_POINTER, if out_ppIParamFxInfo is NULL.
   *     <li>MV_E_NOT_FOUND, if no Param Fx with the GUID passed, either as their current or previous GUID, has been registered.
   * </ul>
   * @param <i>REFCLSID in_rsPreviousParamFxGUID </i>: GUID of the previous version of the Parametric Effect. Cannot be CLSID_NULL.
   * @param <i>IMvParametricEffectInfo** out_ppIParamFxInfo </i>: Pointer to the interface that will be filled with the properties of the newest version of the Parameteric effect. Cannot be NULL
   */
	virtual HRESULT __stdcall GetLatestParamFxInfoFromPrevious( REFCLSID in_rsPreviousParamFxGUID, IMvParametricEffectInfo** out_ppIParamFxInfo ) = 0;

   /**
   *  Gets the properties of a Parametric Effect.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the Parametric Effect properties were found and returned.
   *     <li>MV_E_INVALID_PARAMETER, if in_rsParamFxGUID is CLSID_NULL.
   *     <li>MV_E_INVALID_POINTER, if out_ppIParamFxInfo is NULL.
   *     <li>MV_E_NOT_FOUND, if no Parametric Effect with the GUID passed has been registered.
   * </ul>
   * @param <i>REFCLSID in_rsParamFxGUID </i>: GUID of the Parametric Effect whose information is to be retrieved. Cannot be CLSID_NULL.
   * @param <i>IMvParametricEffectInfo** out_ppIParamFxInfo </i>: Pointer to the interface that will be filled with the properties of the newest version of the Parametric Effect. Cannot be NULL.
   */
	virtual HRESULT __stdcall GetParamFxInfo( REFCLSID in_rsParamFxGUID, IMvParametricEffectInfo** out_ppIParamFxInfo ) = 0;
	
   /**
   *  Retrieves a pointer to an enumerator interface.
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the Param Fx enumerator was successfully retrieved.
   *     <li>MV_E_INVALID_POINTER, if the parameter is NULL.
   * </ul>
   * @param <i>IMvParametricEffectInfoEnumerator** out_pIParamFxListEnumerator </i>: Pointer to the interface to be filled by the Parametric Effect List enumerator. The application can now use this interface to enumerate all of the latest Parametric Effect in a specific architecture. Cannot be NULL.
   */
	virtual HRESULT __stdcall GetParamFxInfoEnumerator( IMvParametricEffectInfoEnumerator** out_pIParamFxListEnumerator ) = 0;
	
};

#endif
