//==============================================================================
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
//===============================================================================

#pragma once

#include "mvBaseCOM.h"
#include "mvDefinitions.h"
#include "mvFlexDefinitionsPublicSDK.h"



//
// Summary:
//    Enumerates the dissolve effect methods.
//
enum EMvDissolveMethod
{
   keMvDissolveMethodInvalid,          // Invalid value.
   keMvDissolveMethodCrossDissolve,    // Gradually fades-out source A while fading-in source B, blending the first clip into the second clip. 
                                          // The sum of both sources' fade factors are constant and equal to 1.
   keMvDissolveMethodAdditiveDissolve, // The first half of the dissolve progression shows source A and gradually fades-in source B. A dissolve 
                                          // progression of 50% shows source A + source B. The second half of the dissolve progression shows source B and 
                                          // gradually fades-out source A.
   keMvDissolveMethodLast              // End of list indicator.
};


//
// Summary:
//    Sets the parameters used by the dissolve effect. 
//
interface IMvDissolveEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the progression factor. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  1.0            none
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fProgressionFactor is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProgressionFactor
      (
      float in_fProgressionFactor   // Specifies the blending progression factor.
      ) = 0;

   //
   // Summary:
   //    Sets the dissolve method to cross-dissolve or additive-dissolve. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_eDissolveMethod is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDissolveMethod
      (
      EMvDissolveMethod in_eDissolveMethod   // Enumerator that specifies the type of dissolve to set.
      ) = 0;

   //
   // Summary:
   //    Interface version.
   //
   static const unsigned long ms_kulMvcDissolveVersion = 1;
};
