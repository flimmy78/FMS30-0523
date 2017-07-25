//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
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
#include "MvColorCorrectionSettings.h"


//
// Summary:
//    Sets the parameters used by the selective color correction effect.
//
interface IMvSelectiveCCEffectSettings : public IUnknown
{  
public:
   //
   // Summary:
   //    Sets the tint of the colors in the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [-180.0, +180.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fHue is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Hue
      (
      float in_fHue     // Specifies the hue value, in degrees.
      )=0;

   //
   // Summary:
   //    Adjusts the saturation of the image colors. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +4.0]  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSaturation is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Saturation
      (
      float in_fSaturation    // Specifies the saturation value.
      )=0;

   //
   // Summary:
   //    Adjusts the overall brightness of the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBrightness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Brightness
      (
      float in_fBrightness    // Specifies the brightness value.
      )=0;

   //
   // Summary:
   //    Adjusts the difference in luminance between the lightest and darkest areas in the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +4.0[  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fContrast is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Contrast
      (
      float in_fContrast   // Specifies the contrast value. A value of 0.0 means no contrast.
      )=0;

   //
   // Summary:
   //    Sets the luminance grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No luminance grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - Internally raise a flag to consider the grid when Update() is invoked. 
   //    - Grid must remain valid until Update() is invoked. 
   //    - Update() will fail if midtones grid is not set. 
   //    - The luminance grid must contain 1024 normalized floating-point entries. 
   //
   virtual HRESULT __stdcall SetLuminanceGrid
      (
      float in_afGrid[]    // Pointer to the luminance grid.
      )=0;
   
   //
   // Summary:
   //    Sets the midtones grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No mid tones grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - Internally raise a flag to consider the grid when Update() is invoked. 
   //    - Grid must remain valid until Update() is invoked. 
   //    - Update() will fail if midtones grid is not set. 
   //    - The midtones grid must contain 1024 normalized floating-point entries. 
   // 
   virtual HRESULT __stdcall SetMidtonesGrid
      (
      float in_afGrid[]    // Pointer to the midtones grid.
      )=0;

   //
   // Summary:
   //    Sets the shadows and highlights combined-grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                              Dependency 
   //    ---------  ---------------------------  -----------  -----------------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No shadows highlights grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - Internally raise a flag to consider the grid when Update() is invoked. 
   //    - Grid must remain valid until Update() is invoked. 
   //    - Update() will fail if midtones grid is not set. 
   //    - The combined shadows and highlights grid must contain 1024 normalized floating-point 
   //      entries. 
   // 
   virtual HRESULT __stdcall SetShadHighGrid
      (
      float in_afGrid[]    // Pointer to the shadows and highlights combined grid.
      )=0;

   //
   // Summary:
   //    Enables the tonal range sections. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if no error occurs. 
   // 
   virtual HRESULT __stdcall SetColorBalance_EnableTonalRanges
      (
      bool in_bEnable      // When set to true, the tonal range sections are enabled.
      )=0;

   //
   // Summary:
   //    Sets the color balance value of the Y component for the specified tonal range. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_eMvTonalRange value is invalid. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalized is outside the specified range.
   // Remarks:
   //    - A normalized value of 1.0 adds maximum luminance, while a normalized value of -1.0
   //      substracts maximum luminance. 
   //    - The resulting component offset added to the image is weighted by the selected tonal 
   //      range section curve. 
   // 
   virtual HRESULT __stdcall SetColorBalance_Y
      (
      EMvTonalRange  in_eTonalRange,      // The enumerator that specifies which tonal range to set.
      float          in_fNormalizedValue  // Specifies the normalized offset value to add to the
                                             // luminance in the selected tonal range.
      )=0;

   //
   // Summary:
   //    Sets the color balance value of the Cb component for the specified tonal range. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_eMvTonalRange value is invalid. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalized is outside the specified range. 
   // Remarks:
   //    - A normalized value of 1.0 adds maximum chrominance, and a normalized value of -1.0
   //      substracts maximum chrominance. 
   //    - The resulting component offset added to the image is weighted by the selected tonal 
   //      range section curve. 
   // 
   virtual HRESULT __stdcall SetColorBalance_Cb
      (
      EMvTonalRange  in_eTonalRange,      // The enumerator that specifies which tonal range to set.
      float          in_fNormalizedValue  // Specifies the normalized offset value to add to the Cb
                                             // component in the selected tonal range.
      )=0;

   //
   // Summary:
   //    Sets the color balance value of the Cr component for the specified tonal range. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_eMvTonalRange value is invalid. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalized is outside the specified range. 
   // Remarks:
   //    - A normalized value of 1.0 adds maximum chrominance, and a normalized value of -1.0
   //      substracts maximum chrominance. 
   //    - The resulting component offset added to the image is weighted by the selected tonal
   //      range section's curve. 
   //
   virtual HRESULT __stdcall SetColorBalance_Cr
      (
      EMvTonalRange  in_eTonalRange,      // The enumerator that specifies which tonal range to set.
      float          in_fNormalizedValue  // Specifies the normalized offset value to add to the Cr 
                                             // component in the selected tonal range.
      )=0;

   //
   // Summary:
   //    Enables selectivity based on hue parameters.
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetHueKey_Enable
      (
      bool in_bEnable   // When set to true, enables the selectivity based on hue parameters.
      )=0;

   //
   // Summary:
   //    Sets the color on which to key.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [-180.0, +180.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fHueDeg is outside the specified range.
   //
   virtual HRESULT __stdcall SetHueKey_Hue
      (
      float in_fHueDeg  // Specifies the selected hue, in degrees.
      )=0;

   //
   // Summary:
   //    Sets the width of the aperture of the selected hue color on which you want to key.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  --------------------------
   //    %PAR0%     [+1.0, +359.0]  Not limited  1.0            Refer to the dependency of
   //                                                            SetHueKey_Softness()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fHueDeg is outside the specified range.
   //
   virtual HRESULT __stdcall SetHueKey_Aperture
      (
      float in_fApertureDeg   // Specifies the aperture width, in degrees.
      )=0;

   //
   // Summary:
   //    Sets the amount of softness applied to each side of the aperture region.
   // Description:
   //    <table>
   //    Parameter  Valid range    Granularity  Default value  Dependency 
   //    ---------  -------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +45.0]  Not limited  0.0            X + Y/2 <= K<p>
   //                                                           X = in_fSoftnessDeg<p>
   //                                                           Y = Hue Aperture parameter<p>
   //                                                           K = 359.0/2.0 (constant)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessDeg is outside the specified range.
   // Remarks:
   //    - If necessary, this parameter will be adjusted according to the dependency equation.
   //
   virtual HRESULT __stdcall SetHueKey_Softness
      (
      float in_fSoftnessDeg   // Specifies the softness width, in degrees, that is applied to each 
                              // side of the aperture region.
      )=0;

   //
   // Summary:
   //    Enables selectivity (keying) based on color saturation.
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetSaturationKey_Enable
      (
      bool in_bEnable    // When set to true, the selectivity based on saturation parameters is enabled.
      )=0;

   //
   // Summary:
   //    Sets the saturation softness threshold of the low softness saturation region, defined by
   //    saturation low softness threshold and saturation low threshold.
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.4142]  Not limited  0.0            X <= Y<p>
   //                                                             X = in_fNormalizedValue<p>
   //                                                             Y = Saturation LowThreshold parameter
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - Values greater than 1.0 represent the domain of invalid saturation values.
   //    - If necessary, this parameter will be adjusted according to the dependancy equation.
   //
   virtual HRESULT __stdcall SetSaturationKey_LowSoftnessThreshold
      (
      float in_fNormalizedValue  // Specifies the low threshold normalized value, with 0.0 being 
                                 // the lowest saturation value and 1.0 being the highest 
                                 // saturation value.
      )=0;

   //
   // Summary:
   //    Sets the low threshold of fully selected saturation colors. Saturation colors below that
   //    threshold fall into the low softness saturation region.
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.4142]  Not limited  0.0            Refer to the dependency of
   //                                                             SetSaturationKey_LowSoftnessThreshold()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - Values greater than 1.0 represent the domain of invalid saturation values.
   //
   virtual HRESULT __stdcall SetSaturationKey_LowThreshold
      (
      float in_fNormalizedValue  // Specifies the low threshold normalized value, with 0.0 being
                                 // the minimum saturation value and 1.0 being the maximum 
                                 // saturation value.
      )=0;

   //
   // Summary:
   //    Sets the high threshold of fully-selected saturation colors.
   // Description:
   //    Saturation colors beyond that threshold fall into the high softness saturation region, 
   //    defined by saturation high threshold and saturation high softness threshold.
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.4142]  Not limited  0.0            Refer to the dependency of
   //                                                             SetSaturationKey_HighSoftnessThreshold()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - Values greater than 1.0 represent the domain of invalid saturation values.
   //
   virtual HRESULT __stdcall SetSaturationKey_HighThreshold
      (
      float in_fNormalizedValue  // Specifies the high threshold normalized value, with 0.0 being
                                 // the minimum saturation value and 1.0 being the maximum 
                                 // saturation value.
      )=0;

   //
   // Summary:
   //    Sets the saturation softness region beyond the high saturation threshold.
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.4142]  Not limited  0.0            X >= Y<p>
   //                                                             X = in_fNormalizedValue<p>
   //                                                             Y = Saturation High Threshold parameter
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - If necessary, this parameter will be adjusted according to the dependency equation.
   //    - Values greater than 1.0 represent the domain of invalid saturation values.
   //
   virtual HRESULT __stdcall SetSaturationKey_HighSoftnessThreshold
      (
      float in_fNormalizedValue  // Specifies the high softness threshold normalized value, with 
                                 // 0.0 being the minimum saturation value and 1.0 being the 
                                 // maximum saturation value.
      )=0;

   //
   // Summary:
   //    Enables selectivity (keying) based on luminance values.
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetLuminanceKey_Enable
      (
      bool in_bEnable   // When set to true, the selectivity based on luminance values is enabled.
      )=0;

   //
   // Summary:
   //    Sets the luminance softness threshold of the low softness luminance region, defined by
   //    luminance low softness threshold and luminance low threshold.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/1024       0.0            X <= Y<p>
   //                                                          X = in_fNormalizedValue<p>
   //                                                          Y = Luminance LowThreshold parameter
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - If necessary, this parameter will be adjusted according to the dependency equation.
   //
   virtual HRESULT __stdcall SetLuminanceKey_LowSoftnessThreshold
      (
      float in_fNormalizedValue  // Specifies the low threshold normalized value, with 0.0 being
                                 // the lowest luminance value and 1.0 being the maximum luminance 
                                 // value.
      )=0;

   //
   // Summary:
   //    Sets the low threshold of fully-selected luminance values. Luminance values below that
   //    threshold fall into the low softness luminance region.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/1024       0.0            Refer to the dependency of
   //                                                          SetLuminanceKey_LowSoftnessThreshold()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   //
   virtual HRESULT __stdcall SetLuminanceKey_LowThreshold
      (
      float in_fNormalizedValue  // Specifies the low threshold normalized value, with 0.0 being 
                                 // the minimum luminance value and 1.0 being the maximum luminance 
                                 // value.
      )=0;

   //
   // Summary:
   //    Sets the high threshold of fully selected luminance values. Luminance values beyond that
   //    threshold fall into the high softness luminance region, defined by luminance high threshold
   //    and luminance high softness threshold.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/1024       0.0            Refer to the dependency of
   //                                                          SetLuminanceKey_HighSoftnessThreshold()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if parameter in_fNormalizedValue is outside the specified range.
   //
   virtual HRESULT __stdcall SetLuminanceKey_HighThreshold
      (
      float in_fNormalizedValue  // Specifies the high threshold normalized value, with 0.0 being 
                                 // the lowest saturation value and 1.0 being the maximum 
                                 // saturation value.
      )=0;

   //
   // Summary:
   //    Sets the luminance softness region beyond the high luminance threshold.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  1/1024       0.0            X >= Y<p>
   //                                                          X = in_fNormalizedValue<p>
   //                                                          Y = Luminance High Threshold parameter
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNormalizedValue is outside the specified range.
   // Remarks:
   //    - If necessary, this parameter will be adjusted according to the dependency equation.
   //
   virtual HRESULT __stdcall SetLuminanceKey_HighSoftnessThreshold
      (
      float in_fNormalizedValue  // Specifies the high softness threshold normalized value, with
                                 // 0.0 being the minimum saturation value and 1.0 being the 
                                 // maximum saturation value.
      )=0;

   //
   // Summary:
   //    Inverts the effect key.
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   // Remarks:
   //    - Invert key is limited to the effect mask.
   //
   virtual HRESULT __stdcall SetInvertKey
      (
      bool in_bInvert   // When set to true, the resulting selection key is inverted.
      )=0;

   //
   // Summary:
   //    Displays the effect key as video.
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetShowInternalKeyAsVideo
      (
      bool in_bEnable   // When set to true, the key is displayed as video.
      )=0;

   //
   // Summary:
   //    Sets the region where to apply the effect. 
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value                   Dependency 
   //    ---------  ---------------  -----------  ------------------------------  ----------
   //    %PAR0%     [0, MAX_LONG/2]  Integer      (0, 0, MAX_LONG/2, MAX_LONG/2)  None
   //    </table>
   // Return value:
   //    MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Absolute positions will be clipped to the resolution of the surface at render time. 
   //    - Set the effect mask to maximum resolution to color-correct a surface entirely. 
   //
   virtual HRESULT __stdcall SetEffectMask
      (
      SMvRect * psMvRect   // A pointer to the SMvRect structure defining the effect mask with
                           // absolute positions in pixels, ranging from 0 to resolution of the
                           // surface.
      )=0;

   //
   // Summary:
   //    Inverts the specified effect mask, thus inverting the region where to apply the effect. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Absolute positions will be clipped to the resolution of the surface at render time. 
   //
   virtual HRESULT __stdcall SetInvertEffectMask
      (
      bool in_bInvert   // When set to true, the mask set with SetEffectMask is inverted.
      )=0;

   //
   // Summary:
   //    When set, the color correction settings are applied outside the effect mask as if the key is full.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetColorCorrectionOutsideEffectMask
      (
      bool in_bEnable   
      )=0;
   
   //
   // Summary:
   //    Enables the RGB curves.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if no error occurs. 
   // 
   virtual HRESULT __stdcall SetRGB_Enable
      (
      bool in_bRGBEnable       // When set to true, the RGB curves are enabled
      )=0;


   //
   // Summary:
   //    Sets the red curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No red grid set by default        None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - When calling Update(), red, green, and blue grids must be set if RGB curves are enabled.
   //    - Grid must remain valid until Update() is invoked. 
   //    - The grid must contain 1024 values.
      virtual HRESULT __stdcall SetRGBGrid_R
      (
      float in_afGrid[]    // Pointer to the red curve values
      )=0;

   //
   // Summary:
   //    Sets the green curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No green grid set by default      None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - When enabled, all red, green, and blue grids must be set to be considered when calling Update().
   //    - Grid must remain valid until Update() is invoked. 
   //    - The grid must contain 1024 values.
      virtual HRESULT __stdcall SetRGBGrid_G
      (
      float in_afGrid[]    // Pointer to the green curve values
      )=0;

   //
   // Summary:
   //    Sets the blue curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No blue grid set by default        None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   // Remarks:
   //    - When enabled, all red, green, and blue grids must be set to be considered when calling Update().
   //    - Grid must remain valid until Update() is invoked. 
   //    - The grid must contain 1024 values.
      virtual HRESULT __stdcall SetRGBGrid_B
      (
      float in_afGrid[]    // Pointer to the blue curve values
      )=0;


   //
   // Summary:
   //    Updates the selective color correction effect settings according to the parameters set by other selective color correction methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever selective color correction effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update()=0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;

   //
   // Summary:
   //    Number of element of the grids needed for SetLuminancegrid(), SetShadHidghGrid and 
   //    SetMidTonesGrid().
   //
   static const unsigned long ms_kulGridSize = 1024;
};
