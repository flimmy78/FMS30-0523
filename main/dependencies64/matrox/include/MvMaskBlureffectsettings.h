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
#include "mvFlex3DDeviceAPI.h"


//
// Summary:
//    Sets the parameters used by the mask blur effect. 
//
interface IMvMaskBlurEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the region of the source on which the mask blur effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value              Dependency 
   //    ---------  -----------------  -----------  -------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0.0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width<p>
   //                                                rectangle.top = 0.0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height
   //                                                rectangle.right = 0.0<p>
   //                                                rectangle.bottom = 0.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF *in_psSourceCrop  // Pointer that specifies the region of the source to use. 
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the video output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation 
   //    (position), scale, and rotation settings to be appliead to the output. 
   //    <table>
   //    Parameter  Valid range               Granularity  Default value        Dependency 
   //    ---------  ------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point      Not limited  The identity matrix  None 
   //                matrix
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Use the softness settings to attenuate aliased edges when applying rotation.
   //
   virtual HRESULT __stdcall SetSourceTransform
      (
      SMvMatrix * in_psSourceTransform   // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the destination (region of interest) on which the mask blur effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value              Dependency 
   //    ---------  -----------------  -----------  -------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0.0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width<p>
   //                                                rectangle.top = 0.0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height
   //                                                rectangle.right = 0.0<p>
   //                                                rectangle.bottom = 0.0
   //    </table>   
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   // Remarks:
   //    - The effect may produce unintended results if the region of interest is not big enough to enclose the region defined by the mask GFX.    
   //    - For the region of interest to be successfully applied, the same blur amount value must be set for the red, green, blue, and alpha channels. 
   //
   virtual HRESULT __stdcall SetSourceRegionOfInterest
      (
      SMvRectF* in_psRegionOfInterest  // Pointer that specifies the region of the destination to use.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the mask on which the blur effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value              Dependency 
   //    ---------  -----------------  -----------  -------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0.0<p>    - rectangle.left + rectangle.right <= Mask Width.<p>  
   //                                                rectangle.top = 0.0<p>     - rectangle.top + rectangle.bottom <= Mask Height.
   //                                                rectangle.right = 0.0<p>  
   //                                                rectangle.bottom = 0.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMaskCrop
      (
      SMvRectF *in_psMaskCrop    // Pointer that specifies the region of the mask to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the mask only.
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskTransform
      (
      SMvMatrix *in_psMaskTransform    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Inverts the region specified as the mask. 
   // Description:
   //     If set to true, (1.0 - mask) will be used as the new mask. 
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMaskInvert
      (
      bool in_bMaskInvert  // If true, the mask is inverted.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not the mask is to be stretched or squeezed to fit the cropped clip.
   // Description:
   //    If set to true, the mask will be stretched/squeezed to fit the cropped clip. If set to 
   //    false, the mask will be cropped by the same amount as the clip.   
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskStretch
      (
      bool in_bMaskStretch    // If true, the mask is stretched/squeezed. If false, it is cropped. 
      ) = 0;

   //
   // Summary:
   //    Sets the transparency of the shape selected as the mask.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fTransparency is outside the specified range. 
   // Remarks:
   //    - A value of 0.0 will not modify the mask. 
   //    - A value of -1.0 will result in a fully opaque mask. 
   //    - A value of 1.0 will result in a fully transparent mask. 
   //    - For all other values, the mask is interpolated between either the unmodified version and 
   //      the fully opaque version, or the unmodified version and the fully transparent version. 
   //
   virtual HRESULT __stdcall SetMaskTransparency
      (
      float in_fTransparency  // Specifies the transparency value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the mask.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMaskSoftness
      (
      float in_fSoftness      // Specifies the softness value. 
      ) = 0;

   //
   // Summary:
   //    Sets the transparency level (alpha) of the area outside the mask, when the mask does 
   //    not cover the entire source clip (for example, if the mask is rotated).   
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value         Dependency 
   //    ---------  ------------  -----------  --------------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0, meaning opaque  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fAlphaOutsideMask is outside the specified range. 
   //
   virtual HRESULT __stdcall SetAlphaOutsideMask
      (
      float in_fAlphaOutsideMask    // Specifies the alpha value to use for the region outside the mask. 
      ) = 0;

   //
   // Summary:
   //    Sets the blur amount to apply to each channel (red, green, blue, alpha) in the source clip.   
   // Description:
   //    <table>
   //    Parameter  Valid range                         Granularity  Default value  Dependency 
   //    ---------  ----------------------------------  -----------  -------------  ----------
   //    For all    [+0.0, +1.0]<p>                     Not limited  +0.0           None
   //                - 0.0 = No blur is performed<p>               
   //                - ]0.0,1.0] = blur increased to 
   //                effect's maximum capacity   
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range.  
   //
   virtual HRESULT __stdcall SetBlurAmount
      (
      float in_fRedOffsetInPercent,    // Specifies the blur amount, as a percentage, to apply to the source clip's red channel. 
      float in_fGreenOffsetInPercent,  // Specifies the blur amount, as a percentage, to apply to the source clip's green channel. 
      float in_fBlueOffsetInPercent,   // Specifies the blur amount, as a percentage, to apply to the source clip's blue channel. 
      float in_fAlphaOffsetInPercent   // Specifies the blur amount, as a percentage, to apply to the source clip's alpha channel. 
      ) = 0;
   
   //
   // Summary:
   //    Sets the color gain that adjusts the amount of color applied to the blurred areas of the clip.   
   // Description:
   //    <table>
   //    Parameter  Valid range                                     Granularity  Default value           Dependency 
   //    ---------  ----------------------------------------------  -----------  ----------------------  ----------
   //    For all    [0.0, 4.0]<p>                                   Not limited  +1.0, meaning color is  None
   //                - 0.0 = Color is not visible<p>                             not modified.
   //                - ]0.0, 1.0[= Color intensity is decreased<p>  
   //                - 1.0 = Color is left as is<p>
   //                - ]1.0, 4.0] = Color intensity is increased   
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_OUT_OF_RANGE, if a parameter is outside its specified range.  
   //
   virtual HRESULT __stdcall SetColorGain
      (
      float in_fRedColorGain,    // Specifies the color gain, as a percentage, to apply to the source clip's red channel. 
      float in_fGreenColorGain,  // Specifies the color gain, as a percentage, to apply to the source clip's green channel. 
      float in_fBlueColorGain    // Specifies the color gain, as a percentage, to apply to the source clip's blue channel. 
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvMaskBlurVersion = 1;
};
