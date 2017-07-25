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
#include "mvFlex3DDeviceApi.h"


enum EMvDifferenceMatteSmoothingType
{
   keMvDifferenceMatteSmoothingTypeInvalid = 0,
   keMvDifferenceMatteSmoothingTypeNone    = 1,
   keMvDifferenceMatteSmoothingTypeLow     = 2,
   keMvDifferenceMatteSmoothingTypeHigh    = 3,
   keMvDifferenceMatteSmoothingTypeLast    = 4
};


//
// Summary:
//    Sets the parameters used by the difference matte effect.
//    
//
interface IMvDifferenceMatteEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the similarity factor value to broaden or reduce the range of color that will be made
   //    transparent.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]      Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_fSimilarityFactor value is outside the specified range.
   // Remarks:
   //    - Higher value increase the color range.
   //
   virtual HRESULT __stdcall SetSimilarity
      (
      float in_fSimilarityFactor // Factor that specifies the similarity in floating-point,
                                 // zero (0) being no similarity.
      ) = 0;

   //
   // Summary:
   //    Specifies the amount of anti-aliasing (softening) applied to the boundary between 
   //    transparent and opaque region with pre-determined values.
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_eSmoothingType value is invalid.
   //
   virtual HRESULT __stdcall SetSmoothingType
      (
      EMvDifferenceMatteSmoothingType in_eSmoothingType  // Enumerator that specifies which 
                                                         // smoothing type we want to use.
      ) = 0;

   //
   // Summary:
   //    To invert the values of the matte.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetReverseMatte
      (
      bool in_bReverse  // When set to true, inverts the values of the matte.
      ) = 0;

   //
   // Summary:
   //    To add a 50% gray, 50% opaque shadow offset 4 pixels down and to right from the opaque
   //    areas of the original clip image.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetDropShadow
      (
      bool in_bDropShadow  // When set to true, enables the addition of a drop shadow.
      ) = 0;

   //
   // Summary:
   //    To display only the clip's alpha channel.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - 
   //
   virtual HRESULT __stdcall SetMaskOnly
      (
      bool in_bMaskOnly // When set to true, displays only the clip's alpha channel.
      ) = 0;

   //
   // Summary:
   //    Specifies the amount of anti-aliasing (softening) applied to the boundary between 
   //    transparent and opaque region.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ------------------------------------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           The effect settings SetSmootingType. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_fSoftness value is outside the specified range.
   // Remarks:
   //    - In order to use this setting, the effect settings SetSmoothingType must be set to 
   //      EMvDifferenceMatteSmoothingTypeNone.
   //
   virtual HRESULT __stdcall SetSoftness
      (
      float in_fSoftness   // Factor that specifies the softness amount in floating-point,
                           // zero (0) being no anti-aliasing.
      ) = 0;

   //
   // Summary:
   //    To set the horizontal offset of the shadow, i.e. to position the shadow to the right 
   //    or to the left.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------------------------------------
   //    %PAR0%     [-15, +15]   +1           0              The settings drop shadow must be enable.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_iShadowOffsetX is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowHorizontalOffset
      (
      int in_iShadowOffsetX   // The shadow horizontal offset, zero (0) being no shadow horizontal offset.
      ) = 0;

   //
   // Summary:
   //    To set the vertical offset of the shadow, i.e. to position down the shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  -----------------------------------------
   //    %PAR0%     [-8, +0]     +1           0              The settings drop shadow must be enable.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_iShadowOffsetY is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowVerticalOffset
      (
      int in_iShadowOffsetY   // The shadow vertical offset, zero (0) being no shadow vertical offset.
      ) = 0;

   virtual HRESULT __stdcall SetShadowColor
      (
      const SMvColor &in_krColor
      ) = 0;

   //
   // Summary:
   //    To set the shadow alpha component.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------------------------------------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           The drop shadow setting must be enable. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_fShadowAlpha is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowAlpha
      (
      float in_fShadowAlpha   // The shadow alpha component value, zero (0) being completely transparent.
      ) = 0;

   //
   // Summary:
   //    To set the shadow alpha component.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------------------------------------
   //    %PAR0%     [+0, +255]   +1           0              The drop shadow setting must be enable. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_uchShadowLuma is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowLuma
      (
      unsigned char in_uchShadowLuma   // The shadow luma component value, zero (0) being completely dark.
      ) = 0;

   //
   // Summary:
   //    To set the shadow U component.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  -----------------------------------------
   //    %PAR0%     [+0, +255]   +1           0              The drop shadow setting must be enable. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_uchShadowU is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowU
      (
      unsigned char in_uchShadowU   // The shadow U component value.
      ) = 0;

   //
   // Summary:
   //    To set the shadow V component.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ---------------------------------------
   //    %PAR0%     [+0, +255]   +1           0              The drop shadow setting must be enable. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if in_uchShadowV is outside the value range.
   //
   virtual HRESULT __stdcall SetShadowV
      (
      unsigned char in_uchShadowV   // The shadow V component value.
      ) = 0;

   //
   // Summary:
   //    Updates settings to reflect what has been specified by other methods. 
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks
   //    - This function ensures the integrity of the effect settings. Modifying the effect 
   //      settings without calling this method will result in a failure when rendering. 
   // 
   virtual HRESULT __stdcall Update() = 0;
  
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvDifferenceMatteVersion = 1;
};
