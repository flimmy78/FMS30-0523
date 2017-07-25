//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvParametricEffectInfoEnumerator.h $
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

#ifndef IMvParametricEffectInfoEnumerator_h_h
#define IMvParametricEffectInfoEnumerator_h_h

#include "mvUnknown.h"//For IUnknown and "interface" keyword


#include "IMvParametricEffectInfo.h"

/**
* Allows the enumeration of all the latest versions of registered Parametric Effects for a single architecture.
*/
interface IMvParametricEffectInfoEnumerator : public IUnknown
{
	
public:
   /**
   *  Retrieves a specified number of Parametric Effect properties in the enumeration sequence
   *
   * <br><b>Remarks:</b>
   * <ul><li> None.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the properties were successfully retrieved.
   *     <li>MV_E_INVALID_POINTER, if out_ppParamFxInfo is NULL.
   *     <li>MV_E_END_OF_ENUM, if there are no more items to enumerate.
   * </ul>
   * @param <i>const unsigned long in_ulCountRequested </i>: The number of Parametric Effect properties to retrieve. Cannot be 0.
   * @param <i>IMvParametricEffectInfo** out_ppParamFxInfo </i>: Array of size in_ulCountRequested that is filled with pointers to the IMvParametricEffectInfo  interfaces. Cannot be NULL.
   * @param <i>unsigned long* out_pulCountFetched </i>: Pointer to a variable that receives the number of ParamFx properties retrieved. Can be NULL.
   */
	virtual HRESULT __stdcall Next( const unsigned long in_ulCountRequested, IMvParametricEffectInfo** out_ppParamFxInfo, unsigned long* out_pulCountFetched ) = 0;
	
   /**
   *  Resets the enumeration sequence to the beginning.
   *
   * <br><b>Remarks:</b>
   * <ul><li> None
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param None.
   */
	virtual HRESULT __stdcall Reset() = 0;

   /**
   *  Skips over a specified number of Parametric Effect properties.
   *
   * <br><b>Remarks:</b>
   * <ul><li> None.
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   *     <li>MV_NOERROR, if the index was successfully incremented.
   * </ul>
   * @param <i>const unsigned long in_ulNumberToSkip </i>: The number of Parametric Effect properties to skip.
   */
	virtual HRESULT __stdcall Skip( const unsigned long in_ulNumberToSkip ) = 0;
	
};

#endif
