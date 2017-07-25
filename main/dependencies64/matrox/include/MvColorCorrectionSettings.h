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


//
// Summary:
//    Describes which tonal range will be affected by the color correction effect.  
//
enum EMvTonalRange
{
    keMvTonalRange_Flat      = 0,   // No tonal range.
    keMvTonalRange_Shadows   = 1,   // Shadows.
    keMvTonalRange_Midtones  = 2,   // Midtones.
    keMvTonalRange_Highlights= 3,   // Highlights.
    keMvTonalRange_MAX       = 4    // The number of possible tonal range types +1.
};


//
// Summary:
//    Sets the parameters used by the color correction effect. 
//
interface IMvColorCorrectionEffectSettings : public IUnknown
{  
public:
   //
   // Summary:
   //    Sets the mask on which the effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value                     Dependency 
   //    ---------  -------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [-MAX_LONG/2, MAX_LONG/2]  Integer      (-1, -1, MAX_LONG/2, MAX_LONG/2)  None
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - In the video output, the absolute positions that define the mask will be clipped to the resolution of the surface. 
   //    - To color correct the entire video surface, the mask must be set to maximum resolution.  
   //
   virtual HRESULT __stdcall SetEffectMask
      (
      SMvRect * psMvRect   // Pointer to the SMvRect structure that defines the mask using absolute 
                           // positions in pixels, ranging from 0 to the full resolution of the video surface.
      )=0;

   //
   // Summary:
   //    Inverts the region specified as the mask. When this method is called, color correction will be applied to the inverted region.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - In the video output, the absolute positions that define the mask will be clipped to the resolution of the surface.
   //
   virtual HRESULT __stdcall SetInvertEffectMask
      (
      bool in_bInvert   // If true, the mask set by SetEffectMask is inverted.
      )=0;

   //
   // Summary:
   //    Sets the tint of the colors in the clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [-180.0, +180.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fHue is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Hue
      (
      float in_fHue     // Specifies the hue value, in degrees.
      )=0;

   //
   // Summary:
   //    Sets the saturation of the colors in the clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +4.0]  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSaturation is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Saturation
      (
      float in_fSaturation    // Specifies the saturation value.
      )=0;

   //
   // Summary:
   //    Sets the overall brightness of the clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBrightness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetProcAmps_Brightness
      (
      float in_fBrightness    // Specifies the brightness value.
      )=0;

   //
   // Summary:
   //    Sets the difference in luminance between the lightest and darkest areas of the clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +4.0]  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
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
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Color balance must be enabled for the luminance grid to be considered when Update() is called. 
   //    - When color balance is enabled, calling Update() will fail if the luminance grid is not set.  
   //    - The luminance grid must remain valid until Update() is called.  
   //    - The luminance grid must contain 1024 normalized floating-point values. 
   //    - Use the CMvColorCorrectionHelper class to properly fill the array for the in_afGrid parameter.
   // See also:
   //    CMvColorCorrectionHelper
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
   //    Parameter  Valid range                  Granularity  Default value                    Dependency 
   //    ---------  ---------------------------  -----------  -------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No midtones grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Color balance must be enabled for the midtones grid to be considered when Update() is called. 
   //    - When color balance is enabled, calling Update() will fail if the midtones grid is not set. 
   //    - The midtones grid must remain valid until Update() is called.  
   //    - The midtones grid must contain 1024 normalized floating-point values. 
   //    - Use the CMvColorCorrectionHelper class to properly fill the array for the in_afGrid parameter.
   // See also:
   //    CMvColorCorrectionHelper
   // 
   virtual HRESULT __stdcall SetMidtonesGrid
      (
      float in_afGrid[]    // Pointer to the midtones grid.
      )=0;

   //
   // Summary:
   //    Sets the shadows/highlights grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                              Dependency 
   //    ---------  ---------------------------  -----------  -----------------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No shadows/highlights grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Color balance must be enabled for the shadows/highlights grid to be considered when Update() is called. 
   //    - When color balance is enabled, calling Update() will fail if the shadows/highlights grid has not been set. 
   //    - The shadows/highlights grid must remain valid until Update() is called.  
   //    - The shadows/highlights grid must contain 1024 normalized floating-point values. 
   //    - Use the CMvColorCorrectionHelper class to properly fill the array for the in_afGrid parameter.
   // See also:
   //    CMvColorCorrectionHelper
   // 
   virtual HRESULT __stdcall SetShadHighGrid
      (
      float in_afGrid[]    // Pointer to the grid that specifies both the shadows and highlights.   
      )=0;

   //
   // Summary:
   //    Enables the color balance tonal range sections (shadows, midtones, and highlights).  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall SetColorBalance_EnableTonalRanges
      (
      bool in_bEnable      // If true, the tonal range sections are enabled.
      )=0;

   //
   // Summary:
   //    Sets the Y component color balance value for the specified tonal range.   
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid or outside its specified range.
   // Remarks:
   //    - A normalized value of 1.0 adds maximum luminance, while a normalized value of -1.0
   //      subtracts maximum luminance. 
   //    - The normalized offset value added to the Y component is weighted by the specified tonal range curve.  
   // 
   virtual HRESULT __stdcall SetColorBalance_Y
      (
      EMvTonalRange  in_eTonalRange,      // Specifies the tonal range. 
      float          in_fNormalizedValue  // Specifies the normalized offset value to be added to the Y component in the specified tonal range.
      )=0;

   //
   // Summary:
   //    Sets the Cb (B-Y) component color balance value for the specified tonal range.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid or outside its specified range. 
   // Remarks:
   //    - A normalized value of 1.0 adds maximum chrominance, and a normalized value of -1.0
   //      subtracts maximum chrominance. 
   //    - The normalized offset value added to the B-Y component is weighted by the specified tonal range curve.   
   // 
   virtual HRESULT __stdcall SetColorBalance_Cb
      (
      EMvTonalRange  in_eTonalRange,      // Specifies the tonal range. 
      float          in_fNormalizedValue  // Specifies the normalized offset value to be added to the B-Y component in the specified tonal range.
      )=0;

   //
   // Summary:
   //    Sets the Cr (R-Y) component color balance value for the specified tonal range.   
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  1/512        0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid or outside its specified range. 
   // Remarks:
   //    - A normalized value of 1.0 adds maximum chrominance, and a normalized value of -1.0
   //      subtracts maximum chrominance. 
   //    - The normalized offset value added to the R-Y component is weighted by the specified tonal range curve.   
   //
   virtual HRESULT __stdcall SetColorBalance_Cr
      (
      EMvTonalRange  in_eTonalRange,      // Specifies the tonal range. 
      float          in_fNormalizedValue  // Specifies the normalized offset value to be added to the R-Y component in the specified tonal range.
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
   //    MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall SetRGB_Enable
      (
      bool in_bRGBEnable       // If true, the RGB curves are enabled.
      )=0;


   //
   // Summary:
   //    Sets the red curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                     Dependency 
   //    ---------  ---------------------------  -----------  --------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No red curve grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - When RGB curves are enabled, the red, green, and blue grids must be set to be considered when Update() is called.
   //    - The red curve grid must remain valid until Update() is called.
   //    - The grid must contain 1024 normalized floating-point values.
      virtual HRESULT __stdcall SetRGBGrid_R
      (
      float in_afGrid[]    // Pointer to the red curve values.
      )=0;

   //
   // Summary:
   //    Sets the green curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                       Dependency 
   //    ---------  ---------------------------  -----------  ----------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No green curve grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - When RGB curves are enabled, the red, green, and blue grids must be set to be considered when Update() is called.
   //    - The green curve grid must remain valid until Update() is called. 
   //    - The grid must contain 1024 normalized floating-point values.
      virtual HRESULT __stdcall SetRGBGrid_G
      (
      float in_afGrid[]    // Pointer to the green curve values.
      )=0;

   //
   // Summary:
   //    Sets the blue curve grid pointer. 
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value                      Dependency 
   //    ---------  ---------------------------  -----------  ---------------------------------  ----------
   //    %PAR0%     [+0.0, +1.0] for each value  Not limited  No blue curve grid set by default  None 
   //                in the grid
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - When RGB curves are enabled, the red, green, and blue grids must be set to be considered when Update() is called.
   //    - The blue curve grid must remain valid until Update() is called. 
   //    - The grid must contain 1024 normalized floating-point values.
      virtual HRESULT __stdcall SetRGBGrid_B
      (
      float in_afGrid[]    // Pointer to the blue curve values.
      )=0;


   //
   // Summary:
   //    Updates the color correction effect settings according to the parameters set by other color correction methods.   
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever color correction effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update()=0;

   //
   // Summary:
   //    Interface version.
   //
   static const unsigned long ms_kulVersion = 1;

   //
   // Summary:
   //    Specifies the number of elements for the grids in the methods SetLuminanceGrid(), SetShadHighGrid(), and SetMidtonesGrid().  
   //
   static const unsigned long ms_kulGridSize = 1024;

};
