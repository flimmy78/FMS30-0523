//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2004. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// All code and information is provided "as is" without warranty of any kind, 
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

//DOM-IGNORE-BEGIN
enum EMvSoftnessType
{
   keMvSoftnessType_Linear,            
   keMvSoftnessType_MatroxNonLinear1,  
   keMvSoftnessType_Last               // End of list indicator.
};
// DOM-IGNORE-END

//
// Summary:
//    Specifies the parameters used by the wipe effect.
//
interface IMvWipesEffectSettings : public IUnknown
{  
public:

   //
   // Summary:
   //    Specifies the desired progression of the user-defined pattern.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/65536      0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fProgression is outside the specified range.
   //
   virtual HRESULT __stdcall SetProgression
      (
      float in_fProgression   // Specifies the normalized progression. A value of 0.0 shows source A 
                                 // only, and a value of 1.0 shows source B only.
      )=0;

   //
   // Summary:
   //    Specifies the total softness amount to be applied to the image transitions. The softness 
   //       amount value represents the span of the matte values that will fall in the 
   //       softness region for a progression of 50%. The span is represented as a percentage.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/65536      0.0            - The sum of the in_fSoftnessAmount value and the border size, which is set with the SetBorderSize method, must not exceed 100%
   //                                                          - If the sum of the in_fSoftnessAmount
   //                                                            value and the border size exceeds 
   //                                                            100%, the softness value will be 
   //                                                            corrected internally
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessAmount is outside the specified range.
   // Remarks:
   //    - When the softness amount is set to 100%, all matte values (except 0 and 65535) fall in
   //      the softness region for a progression of 50%.
   //    - When a border is required, the softness amount is split between source A/border
   //      and source B/border transitions with the proportion set by the SetSoftnessBalance() method.
   //
   virtual HRESULT __stdcall SetSoftnessAmount
      (
      float in_fAmount  // Specifies the softness amount value.
      )=0;

   //
   // Summary:
   //    Specifies the proportion or "balance" of the total softness amount to be applied to source 
   //    A/border and source B/border transitions if a border is required.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/65536      0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessBalance is outside the specified range.
   // Remarks:
   //    - This parameter has no effect if no border is set.
   //
   virtual HRESULT __stdcall SetSoftnessBalance
      (
      float in_fBalance // Specifies the softness balance value. A value of -1.0 means that 100% of
                           // total softness is applied to the source B/border transition only. A 
                           // value of 0.0 applies 50% of total softness to both source A/border and 
                           // source B/border transitions. A value of 1.0 means that 100% of total 
                           // softness is applied to the source A/border transition only.
      )=0;

   //
   // Summary:
   //    Specifies the softness type.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the in_eMvSoftnessType value is invalid.
   // Remarks:
   //    - Linear softness most likely gives better results with organic patterns, while 
   //      nonlinear softness yields better results with symmetrical or geometrical patterns
   //
   virtual HRESULT __stdcall SetSoftnessType
      (
      EMvSoftnessType in_eType      // Specifies the type of softness to set.
      )=0;

   //
   // Summary:
   //    Enables a border at the transition of source A and source B.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetEnableBorder
      (
      bool in_bEnable      // When set to true, a border is enabled at the transition of source A and source B.
      )=0;

   //
   // Summary:
   //    Specifies the size of the border at the transition of source A and source B. The size specified
   //       represents the span of matte values that will fall in the border region 
   //       for a progression set to 50%. The span is represented as a percentage.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/65536      0.0            Refer to the dependency
   //                                                          of SetSoftnessAmount
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBrightness is outside the specified range.
   // Remarks:
   //    - A border size set to 100% means that all matte values, except 0 and 65535, fall in the
   //      border region when progression is set at 50%. In this particular case, the output would
   //      be almost completely filled with the border color.
   //
   virtual HRESULT __stdcall SetBorderSize
      (
      float in_fSize // The size of the border, as a percentage, with 100% being the maximum 
                     // border size. A value of 1.0 means 100%, and a value of 0.0 means 0%.
      )=0;

   //
   // Summary:
   //    Specifies the color of the border.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1023]  1            64             None
   //    %PAR1%     [+0, +1023]  1            512            None
   //    %PAR2%     [+0, +1023]  1            512            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if one of the parameters is outside the specified range.
   //
   virtual HRESULT __stdcall SetBorderColor
      (
      unsigned int in_ui10bitY,  // Specifies the luminance component value of the desired border color.
      unsigned int in_ui10bitCb, // Specifies the Cb unsigned component value of the desired border color.
      unsigned int in_ui10bitCr  // Specifies the Cr unsigned component value of the desired border color.
      )=0;

   //
   // Summary:
   //    Inverts the transition such that it progresses from source B to source A.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall SetInvertSources
      (
      bool in_bInvert   // When set to true, the transition will progress from source B to source A.
      )=0;

   //
   // Summary:
   //    Updates the wipes effect settings according to the parameters set by other wipes effect methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever wipes effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update()=0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;
};
