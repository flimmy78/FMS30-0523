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
//    Sets the parameters used by the luma key effect. 
//
interface IMvLumaKeyEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the maximum value of the effect key. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fMaxKey is outside the specified range. 
   // Remarks:
   //    - A value of 1.0 represents the full keying range (100%) and a value of 0.0 represents a
   //      single keying value fully transparent. 
   //
   virtual HRESULT __stdcall SetMaxKey
      (
      float in_fMaxKey     // Specifies the maximum key value.
      ) = 0;

   //
   // Summary:
   //    Sets the higher threshold value of the desired luma range.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  --------------------------------------
   //    %PAR0%     [+0, +1023]  1            1023           Must be greater than low threshold set
   //                                                         in SetLowerThreshold(). 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_uiHighThreshold is outside the specified range. 
   // Remarks:
   //    - Luma greater than the threshold has keying values below the maximum key. 
   //
   virtual HRESULT __stdcall SetHigherThreshold
      (
      unsigned int in_uiHighThreshold     // This threshold represents the highest luma associated
                                          // with the maximum keying value.
      ) = 0;

   //
   // Summary:
   //    Sets the keying slope from higher threshold value. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fHighSlope is outside the specified range. 
   // Remarks:
   //    - The key value is equal to the maximum at the higher threshold point and decreases with 
   //      each luma value increment. A value of 0.5 represents a negative 45 degree 
   //
   virtual HRESULT __stdcall SetHigherSlope
      (
      float in_fHighSlope     // This parameter represents the decreasing rate of the key value for
                              // luma greater than the higher threshold.
      ) = 0;

   //
   // Summary:
   //    Sets the lower threshold value of the desired luma range. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ------------------------------------
   //    %PAR0%     [+0, +1023]  1            0              Must be less than high threshold set
   //                                                         in SetHigherThreshold().
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_uiLowThreshold is outside the specified range. 
   // Remarks:
   //    - Luma lower than the threshold has keying values below the maximum key. 
   //
   virtual HRESULT __stdcall SetLowerThreshold
      (
      unsigned int in_uiLowThreshold   // This threshold represents the lowest luma associated
                                       // with the maximum keying value.
      ) = 0;

   //
   // Summary:
   //    Sets keying slope from lower threshold value. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fLowSlope is outside the specified range. 
   // Remarks:
   //    - The key value is equal to the maximum at the lower threshold point and decreases with
   //      each luma value decrement. A value of 0.5 represents a positive 45 degree slope. 
   //
   virtual HRESULT __stdcall SetLowerSlope
      (
      float in_fLowSlope      // This parameter represents the decreasing rate of the key value for
                              // luma less than the lower threshold.
      ) = 0;

   //
   // Summary:
   //    Sets the mask rectangle. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value                 Dependency 
   //    ---------  -----------  -----------  ----------------------------  ----------
   //    %PAR0%     Not limited  1            (-1, -1, MAX_LONG, MAX_LONG)  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   //    - MV_E_INVALID_PARAMETER, if the rectangular coordinates are invalid. 
   // Remarks:
   //    - If a pixel falls within, or on the boundary of, the rectangular garbage mask region,
   //      and the invert garbage mask flag is false, it is processed by the luma keyer. All other
   //      pixels are treated as if their effect key was 0.0. 
   //    - If the invert garbage mask flag is true, all pixels outside the rectangular region are
   //      processed by the luma keyer. The pixels inside, or on the boundary of, the rectangular
   //      garbage mask region are treated as if their effect key was 0.0. 
   //
   virtual HRESULT __stdcall SetMask
      (
      const SMvRect & in_krsMask    // Specifies the mask rectangle.
      ) = 0;

   //
   // Summary:
   //    Inverts the mask region. 
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - If a pixel falls within, or on the boundary of, the rectangular garbage mask region, 
   //      and the invert garbage mask flag is false, it is processed by the luma keyer. All other
   //      pixels are treated as if their effect key was 0.0. 
   //    - If the invert garbage mask flag is true, all pixels outside the rectangular region are
   //      processed by the luma keyer. The pixels inside, or on the boundary of, the rectangular
   //      garbage mask region are treated as if their effect key was 0.0. 
   //
   virtual HRESULT __stdcall SetInvertMask
      (
      bool in_bInvertMask     // If set to true, the garbage mask flag is inverted.
      ) = 0;

   //
   // Summary:
   //    Inverts the effect key of pixels processed by the chroma keyer. 
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Effect_key = (1.0 - effect_key), when the invert key flag is true. 
   //
   virtual HRESULT __stdcall SetInvertKey
      (
      bool in_bInvertKey      // If set to true, the key flag is inverted.
      ) = 0;

   //
   // Summary:
   //    Sets the transparency mode.
   // Description:
   //    When set to true, the region outside the mask is transparent. When set to false, the 
   //    region outside the mask is a copy of the first input surface. 
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if operation is successful. 
   // Remarks:
   //    - Affects both normal and special output modes. 
   //
   virtual HRESULT __stdcall SetTransparencyOutsideMask
      (
      bool in_bTransparency      // Specifies the transparency mode.  When set to true, the outside
                                 // transparency is set to opaque.  When set to false, the outside
                                 // transparency is tranparent.
      ) = 0;

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
   // Remarks:
   //    - When the show key as video flag is true, each pixel's luma is replaced with its effect
   //      key value, its chroma is set to grey, and its alpha, if any, is changed to opaque. 
   //
   virtual HRESULT __stdcall SetShowKeyAsVideo
      (
      bool in_bShowKeyAsVideo    // If set to true, the effect key is shown as video.
      ) = 0;

   //
   // Summary:
   //    Updates the luma key effect settings according to the parameters set by other luma key methods.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_DATA, if the higher threshold value is lower than the lower threshold value. 
   // Remarks:
   //    - This method ensures the integrity of the effect settings, and must be called whenever luma key effect settings are modified. 
   //
   virtual HRESULT __stdcall Update() = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;
};
