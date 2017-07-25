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


//
// Summary:
//    Sets the parameters used by the chroma key with shadow effect. 
//
interface IMvChromaKeyShadowEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the hue value of the desired key color in degrees. 
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
   virtual HRESULT __stdcall SetHue
      (
      float in_fHue  // Specifies the hue value, in degrees.
      ) = 0;

   //
   // Summary:
   //    Sets the saturation value of the desired key color. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ---------------------------------
   //    %PAR0%     [0, 724]     Integer      0              Must be greater than or equal to 
   //                                                         the saturation threshold set in 
   //                                                         SetSaturationThreshold()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_uiSaturation is outside the specified range. 
   //
   virtual HRESULT __stdcall SetSaturation
      (
      unsigned int in_uiSaturation     // Specifies the saturation value.
      ) = 0;

   //
   // Summary:
   //    Sets the aperture angle that affects the keying region. This method increases or decreases the range of colors to be keyed.   
   // Description:
   //    <table>
   //    Parameter  Valid range    Granularity  Default value  Dependency 
   //    ---------  -------------  -----------  -------------  ----------
   //    %PAR0%     [0.0, +180.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fAperture is outside the specified range. 
   //
   virtual HRESULT __stdcall SetAperture
      (
      float in_fAperture      // Specifies the aperture angle, in degrees.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the keyed region.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftness is outside the specified range. 
   // Remarks:
   //    - A value of 0.0 yields a linear effect key. 
   //    - A value towards -1.0 affects linearity in that the edges globally appear more opaque. 
   //    - A value towards 1.0 affects linearity in that the edges globally appear more transparent. 
   //
   virtual HRESULT __stdcall SetKeyingSoftness
      (
      float in_fSoftness   // Specifies the softness value.
      ) = 0;

   //
   // Summary:
   //    Adjusts chroma spill removal by varying the amount of the residual chroma (spill) around
   //    the edges of your foreground image. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSpillRemoval is outside the specified range. 
   // Remarks:
   //    - A value of 0.0 leaves the residual chroma component along the key color intact. 
   //    - A value of 1.0 completely removes the residual chroma component around the edges of your
   //      foreground image. 
   //
   virtual HRESULT __stdcall SetChromaSpillRemoval
      (
      float in_fSpillRemoval  // Specifies the spill removal factor.
      ) = 0;

   //
   // Summary:
   //    Suppresses your key color from the foreground by adding the opposite key color in the
   //    spectrum. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fChromaSuppression is outside the specified
   //      range. 
   // Remarks:
   //    - A value of 0.0 leaves the residual chroma component in the foreground intact. 
   //    - A value of 1.0 completely suppresses the key color from your foreground and may reveal 
   //      the opposite key color in the spectrum. 
   //
   virtual HRESULT __stdcall SetChromaSuppression
      (
      float in_fChromaSuppression   // Specifies the spill removal factor.
      ) = 0;

   //
   // Summary:
   //    Adjusts the keying region by setting a saturation threshold for the pixel to be considered that is
   //    similar to the key color. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ---------------------------------
   //    %PAR0%     [0, 724]     Integer      0              Must be lower than or equal to 
   //                                                         the saturation threshold set in 
   //                                                         SetSaturation()
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_uiSaturationThreshold is outside the
   //      specified range. 
   // Remarks:
   //    - The closer the saturation threshold value is to the saturation value, the smaller the
   //      keying region becomes. 
   //
   virtual HRESULT __stdcall SetSaturationThreshold
      (
      unsigned int in_uiSaturationThreshold  // Specifies the saturation threshold value.
      ) = 0;

   //
   // Summary:
   //    Sets the luminance reference used for shadow (and highlight) enhancements. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ---------------------------------
   //    %PAR0%     [0, 1023]    Integer      512            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_uiLuminance is outside the specified range. 
   // Remarks
   //    - The luminance of each pixel in the foreground image is compared to the luminance value set by this method
   //      to determine the amount of shadow (or highlight). 
   //
   virtual HRESULT __stdcall SetLuminance
      (
      unsigned int in_uiLuminance   // Specifies the luminance value.
      ) = 0;

   //
   // Summary:
   //     Suppresses shadow (and highlight) enhancements. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fShadowSuppression is outside the specified
   //      range. 
   // Remarks
   //    - A value of 0.0 will not suppress shadow and highlight enhancements at all, and a value of 1.0 will fully suppress shadow and highlight enhancements.   
   //
   virtual HRESULT __stdcall SetShadowSuppression
      (
      float in_fShadowSuppression   // Specifies the shadow suppression value.
      ) = 0;

   //
   // Summary:
   //    Sets the mask rectangle. 
   // Description:
   //    <table>
   //    Parameter  Valid range           Granularity  Default value                 Dependency 
   //    ---------  --------------------  -----------  ----------------------------  ----------
   //    %PAR0%     Signed integer value  Integer      (-1, -1, MAX_LONG, MAX_LONG)  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the rectangle's coordinates are invalid. 
   // Remarks:
   //    - If the invert mask flag is set to false, the pixels inside or on the border of the mask 
   //      rectangle are processed by the chroma keyer. The pixels outside are treated as if their 
   //      effect key is transparent. 
   //    - If the invert mask flag is set to true, the pixels outside the mask rectangle are processed 
   //      by the chroma keyer. The pixels inside or on the border of the mask rectangle are treated as 
   //      if their effect key is transparent.
   //
   virtual HRESULT __stdcall SetMask
      (
      const SMvRect & in_krsMask // Specifies the mask rectangle.
      ) = 0;

   //
   // Summary:
   //    Inverts the specified mask rectangle. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value          Granularity  Dependency 
   //    ----------  -------------  ---------------------  -----------  ----------
   //    %PAR0%      {true, false}  false                  N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetInvertMask
      (
      bool in_bInvertMask  // If true, the mask rectangle is inverted.
      ) = 0;

   //
   // Summary:
   //    Sets the transparency value of the region outside the mask rectangle. 
   // Description:
   //    When set to true, the region outside the mask is transparent. When set to false, the 
   //    region outside the mask is the same as the source. 
   //    <table>
   //    Parameter   Valid range    Default value          Granularity  Dependency 
   //    ----------  -------------  ---------------------  -----------  ----------
   //    %PAR0%      {true, false}  false                  N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetTransparencyOutsideMask
      (
      bool in_bTransparency   // Specifies the transparency value.
      ) = 0;

   //
   // Summary:
   //    Inverts the key selection, the pixels that are used to create the chroma key.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value          Granularity  Dependency 
   //    ----------  -------------  ---------------------  -----------  ----------
   //    %PAR0%      {true, false}  false                  N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Chroma spill removal and chroma suppression are disabled when the invert key flag is true. 
   //
   virtual HRESULT __stdcall SetInvertKey
      (
      bool in_bInvertKey   // If true, the key selection is inverted.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the option to show the matte that was used to create the key effect.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value          Granularity  Dependency 
   //    ----------  -------------  ---------------------  -----------  ----------
   //    %PAR0%      {true, false}  false                  N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - When the show key is enabled, each pixel's luma is replaced with its effect key value, 
   //      its chroma is set to grey, and its alpha, if any, is changed to opaque. 
   //
   virtual HRESULT __stdcall SetShowKeyAsVideo
      (
      bool in_bShowKeyAsVideo // If true, show key as video is enabled. 
      ) = 0;

   //
   // Summary:
   //    Updates the chroma key with shadow effect settings according to the parameters set by other chroma key with shadow methods.     
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_DATA, if the saturation threshold value is greater than the saturation value. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever chroma key with shadow effect settings are modified. 
   //
   virtual HRESULT __stdcall Update() = 0;


   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;
};

