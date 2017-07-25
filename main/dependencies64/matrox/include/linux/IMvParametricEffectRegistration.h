//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvParametricEffectRegistration.h $
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

#ifndef IMvParametricEffectRegistration_h_h
#define IMvParametricEffectRegistration_h_h

#include "mvUnknown.h"//For IUnknown and "interface" keyword
#include "mvdDef.h" //For SMvParamFxRegistrationInfo

/** Allows the Registration and Unregistration of Parametric Effects on the system.
* @interface */
interface IMvParametricEffectRegistration : public IUnknown
{
	
public:

   /**
   *  Registers a new Parametric Effect.
   *
   * <br><b>Remarks:</b>
   * <ul>
   *        <li>CLSID_NULL can be passed as the previous GUID to inform the enumerator that it is the oldest one.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the Parametric Effect was registered successfully
   *     <li>MV_E_INVALID_PARAMETER, if a parameter contains erronous data.
   *     <li>MV_E_FAIL, if a Parametric Effect with the same previous GUID has already been registered or if the enumerator was unsuccessful in writing it to the Settings Manager.
   * </ul>
   * @param <i>REFCLSID in_sParamFxArchitectureGUID </i>: GUID of the Parametric Effect's architecture. The different registered Parametric Effects will be grouped according to this parameter. When enumerating, an application specifies which architecture it is enumerating. Cannot be CLSID_NULL.
   * @param <i>REFCLSID in_ParamFxGUID </i>: GUID of the Parametric Effect to register. Cannot be CLSID_NULL.
   * @param <i>const SMvParamFxRegistrationInfo& in_sParamFxInfo </i>: Structure containing all the information that needs to be enumerated by the enumerator and returned to the application. The variable <i>previousFxGUID</i> is especially important and determines whether or not the Parametric Effect is the newest version. Cannot be CLSID_NULL
   */
	virtual HRESULT __stdcall Register( REFCLSID in_sParamFxArchitectureGUID, REFCLSID in_ParamFxGUID, const SMvParamFxRegistrationInfo& in_sParamFxInfo ) = 0;

   /**
   *  Unregisters a Parametric Effect from the list of registered ones.
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
   *     <li>MV_NOERROR, if the Parametric Effect was unregistered successfully.
   *     <li>MV_E_INVALID_PARAMETER, if one of the parameters is CLSID_NULL.
   *     <li>MV_E_NOT_FOUND, if no Parametric Effect with the GUID passed has been registered.
   *     <li>MV_E_FAIL, if the enumerator was unsuccessful in removing it from the Settings Manager or if the architecture does not exist.
   * </ul>
   * @param <i>REFCLSID in_sParamFxArchitectureGUID </i>: GUID of the Parametric Effect's architecture. The different registered Parametric Effects will be grouped according to this parameter. When enumerating, an application specifies which architecture it is enumerating. Cannot be CLSID_NULL.
   * @param <i>REFCLSID in_ParamFxGUID </i>: GUID of the Parametric Effect to unregister. Cannot be CLSID_NULL.
   */
	virtual HRESULT __stdcall Unregister( REFCLSID in_sParamFxArchitectureGUID, REFCLSID in_ParamFxGUID ) = 0;
	
};

#endif
