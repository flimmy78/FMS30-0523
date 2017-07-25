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
//    Sets the parameters used by the volumetric light effect.
//
interface IMvVolumetricLightEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Determines how the original image will be preprocessed.
   //
   enum EMvPreprocessingMode
   {
      keMvPreprocessingModeInvalid = 0,      // Invalid value.
      keMvPreprocessingModeRedOnly,          // Uses only the red component of the source.
      keMvPreprocessingModeGreenOnly,        // Uses only the green component of the source.
      keMvPreprocessingModeBlueOnly,         // Uses only the blue component of the source.
      keMvPreprocessingModeAlphaOnly,        // Uses only the alpha component of the source.
      keMvPreprocessingModeLuma,             // A precise portion of each color channel is added
                                                // together and the result is applied to every 
                                                // color channel. The result should be the precise 
                                                // luminance of the image. 
                                                // Source = 0.299*R + 0.587*G + 0.114*B
      keMvPreprocessingModeOversaturation,   // Every color channel is directly added and the
                                                // result is applied to every color channel. 
                                                // Source = min(1, max(0, R+G+B))
      keMvPreprocessingModeLast,             // End of list indicator.
   };

   //
   // Summary:
   //    Determines how the extrusion layers will blend together.
   //
   enum EMvExtrusionMode
   {
      keMvExtrusionModeInvalid = 0, // Invalid value.
      keMvExtrusionModeAdditive,    // Adds each layer of the extrusion.
      keMvExtrusionModeBlend,       // Blends each layer of the extrusion.
      keMvExtrusionModeLast,        // End of list indicator.
   };

   //
   // Summary:
   //    Determines how the original image will blend with the extrusion.
   //
   enum EMvPostprocessingMode
   {
      keMvPostprocessingModeInvalid = 0,     // Invalid value.
      keMvPostprocessingModeNone,            // result = extrusion
      keMvPostprocessingModeAdd,             // result = extrusion + original
      keMvPostprocessingModeModulate,        // result = extrusion * original
      keMvPostprocessingModeSubtract,        // result = extrusion - original
      keMvPostprocessingModeAddSmooth,       // result = (extrusion + original) - (extrusion * original).
      keMvPostprocessingModeAddSigned2X,     // result = 2 * (extrusion - 0.5) + original
      keMvPostprocessingModeBlend,           // result = extrusion * (1 - original.alpha) + original * original.alpha
      keMvPostprocessingModeBlendSigned2X,   // result = 2 * (extrusion - 0.5f) * (1 - original.alpha) + original * original.alpha
      keMvPostprocessingModeLast,            // End of list indicator.
   };

   static const unsigned int ms_kuiMaxPrecision = 255; // 

   //
   // Summary:
   //    Sets the position of the pseudo light source. This method affects the direction of the 
   //    extrusion.
   // Description:
   //    <table>
   //    Parameter       Valid range               Granularity  Default value  Dependency 
   //    --------------  ------------------------  -----------  -------------  ----------
   //    All parameters  [-MAX_FLOAT, +MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetSourcePosition
      (
      float in_fX,   // The x position of the pseudo light source.
      float in_fY,   // The y position of the pseudo light source.
      float in_fZ    // The z position of the pseudo light source.
      ) = 0;

   //
   // Summary:
   //    Sets the rotation about the z axis of the extrusion.
   // Description:
   //    <table>
   //    Parameter  Valid range                 Granularity  Default value  Dependency 
   //    ---------  --------------------------  -----------  -------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]<p>  Not limited  +0.0           None
   //                High values may yield 
   //                undesirable results.
   //                Recommended range is 
   //                [-1.0, +1.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Will make the extrusion rotate around itself.
   //
   virtual HRESULT __stdcall SetSourceRotation
      (
      float in_fAngleZ  // Specifies the angle of rotation about the z axis, in radians.
      ) = 0;

   //
   // Summary:
   //    Sets the length of the extrusion. A negative value causes the extrusion length to decrease,
   //    and a positive value causes the extrusion length to increase.
   // Description:
   //    <table>
   //    Parameter  Valid range                 Granularity  Default value  Dependency 
   //    ---------  --------------------------  -----------  -------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]<p>  Not limited  +0.1           None
   //                High values may yield
   //                undesirable results. 
   //                Recommended range is 
   //                [-1.0, +1.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetExtrusionLength
      (
      float in_fLength  // Specifies the length of the extrusion.
      ) = 0;

   //
   // Summary:
   //    Sets the number of layers of the extrusion.
   // Description:
   //     High values yield better results, but take more time to process. Low values can also 
   //     yield interesting results.
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +255]   +1           +50            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetExtrusionPrecision
      (
      unsigned int in_uiPrecision   // Specifies the number of layers of the extrusion.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of the extrusion layer that is closest to the original source.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The opacity of the intermediate layers will be interpolated between the start opacity 
   //      and the end opacity.
   //
   virtual HRESULT __stdcall SetExtrusionStartOpacity
      (
      float in_fStartOpacity  // Specifies the opacity of the extrusion layer closest to the
                              // original source.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of the extrusion layer that is farthest from the original source.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The opacity of the intermediate layers will be interpolated between the start opacity 
   //      and the end opacity.
   //
   virtual HRESULT __stdcall SetExtrusionEndOpacity
      (
      float in_fEndOpacity // Specifies the opacity of the extrusion layer farthest from the
                           // original source.
      ) = 0;

   //
   // Summary:
   //    Sets the extrusion mode. This setting affects how the extrusion layers will blend together.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // See also:
   //    EMvExtrusionMode
   //
   virtual HRESULT __stdcall SetExtrusionMode
      (
      EMvExtrusionMode in_eExtrusionMode  // Specifies the extrusion mode.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the preprocessing step. The preprocessing step allows the user to choose
   //    which component of the original source will be extruded.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall EnablePreprocessing
      (
      bool in_bIsPreprocessingEnabled  // Enables/disables the preprocessing step.
      ) = 0;

   //
   // Summary:
   //    Sets the preprocessing mode.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // See also:
   //    EMvPreprocessingMode
   //
   virtual HRESULT __stdcall SetPreprocessingMode
      (
      EMvPreprocessingMode in_ePreprocessingMode   // Specifies the preprocessing mode.
      ) = 0;

   //
   // Summary:
   //    Sets the threshold to be used during preprocessing. This parameter allows the user to select
   //    a subset of the source, based on the preprocessing mode.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetPreprocessingThreshold
      (
      float in_fThreshold  // Specifies the threshold used to select a subset of the original image,
                           // based on the preprocessing mode. A value of 0.0 means that all of the
                           // original image will be selected, and a value of 1.0 means that none
                           // of the original image will be selected.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the use of a mask. A mask allows the user to select a specific part of the
   //    original image to extrude.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall EnableMask
      (
      bool in_bIsMaskEnabled  // Enables/disables the use of a mask.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the mask only.
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetMaskTransform
      (
      SMvMatrix* in_psMatrix  // Pointer that specifies the transform matrix to be used for the mask.
      ) = 0;

   //
   // Summary:
   //    Sets the crop area to be applied to the mask. This allows the user to select a region of the mask.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ------------------------------------------------------------------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= editing resolution width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= editing resolution height
   //                                                rectangle.right = 0<p>
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetMaskCropArea
      (
      SMvRectF* in_psCropArea // Pointer that specifies the crop area to be applied to the mask.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not the mask is to be inverted.
   // Description:
   //     If set to true, (1.0 - mask) will be used as the new mask. 
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall InvertMask
      (
      bool in_bIsMaskInverted     // If true, the mask is inverted.
      ) = 0;

   //
   // Summary:
   //    Sets the alpha outside the mask. This can be useful when the mask is translated/rotated/
   //    scaled/cropped.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - When the mask transform is equal to identity and the crop area of the mask is (0.0, 0.0, 
   //      0.0, 0.0), the mask will cover the whole screen. But, when the mask is transformed or 
   //      cropped, some parts of the screen may not be covered by the mask. These parts will use 
   //      the alpha specified in this method.
   //
   virtual HRESULT __stdcall SetMaskAlphaFill
      (
      float in_fAlphaFill  // Specifies the alpha value that will be used in the area that is not
                           // covered by the mask.
      ) = 0;

   //
   // Summary:
   //    Sets the transparency of the mask.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetMaskTransparency
      (
      float in_fTransparency  // Allows the user to change the appearance of the mask.
                              //- -1.0 = The mask is totally opaque.
                              //- 0.0 = The mask is not modified.
                              //- 1.0 = The mask is totally transparent.
                              //- For all other values, the mask is interpolated between either the
                              //  unmodified version and the totally opaque version, or the 
                              //  unmodified version and the totally transparent version.
      ) = 0;

   //
   // Summary:
   //    Enables the color remapping of the extrusion.
   // Description:
   //    When disabled, the extrusion shares the color of the source. When enabled, the colors of 
   //    the extrusion are multiplied by a gradient. The color remapping often looks better when 
   //    preprocessing is enabled.
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall EnableColorRemapping
      (
      bool in_bIsColorRemappingEnabled // Enables/disables the color remapping operation.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not the effect should use the alpha contained in the gradient. This
   //    can change the appearance of the volume, but only if the gradient contains alpha.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall UseGradientBuiltInAlpha
      (
      bool in_bUseGradientBuiltInAlpha // Uses or ignores the built-in alpha.
      ) = 0;

   //
   // Summary:
   //    Defines the subset of the gradient that will be used to do color remapping.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    %PAR1%     [+0.0, +1.0]  Not limited  +1.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If upper boundary < lower boundary, the gradient will be inverted.
   //
   virtual HRESULT __stdcall SetColorRemappingGradientBoundaries
      (
      float in_fLowerBoundary,   // Specifies the lower boundary of the subset of the gradient.
      float in_fUpperBoundary    // Specifies the upper boundary of the subset of the gradient.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of noise that will be added to the extrusion.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetNoiseAmount
      (
      float in_fNoiseAmount   // Specifies the amount of noise that will be added to the extrusion.
      ) = 0;

   //
   // Summary:
   //    Sets the size of the noise that will be added to the extrusion.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetNoiseSize
      (
      float in_fNoiseSize  // Specifies the size of the noise that will be added to the extrusion.
                           // The higher the value, the larger the noise size will be.
      ) = 0;

   //
   // Summary:
   //    Allows the user to animate the noise.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  +0.0           None
   //    %PAR1%     [-1.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetNoiseProgression
      (
      float in_fNoiseHorizontalProgression,  // Animates the noise horizontally.
      float in_fNoiseVerticalProgression     // Animates the noise vertically.
      ) = 0;

   //
   // Summary:
   //    Sets the post-processing mode, which defines how the original source blends with the
   //    extrusion.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // See also:
   //    EMvPostprocessingMode
   //
   virtual HRESULT __stdcall SetPostprocessingMode
      (
      EMvPostprocessingMode in_ePostprocessingMode // Specifies how the original image blends with
                                                   // the extrusion.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of the original source when blended with the extrusion.
   // Description:
   //     The result depends also on the post-processing mode.
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetPostprocessingOriginalOpacity
      (
      float in_fOpacity // Specifies the opacity of the original layer when blended with the extrusion.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on which the volumetric light effect will be applied.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ------------------------------------------------------------------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= editing resolution width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= editing resolution height
   //                                                rectangle.right = 0<p>
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetCropArea
      (
      SMvRectF* in_psCropArea // Pointer that specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the output.
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   // Remarks:
   //    - Since this effect has an integrated softness, rotating the output may create aliased
   //      edges.
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      SMvMatrix* in_psTransform  // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvVolumetricLightVersion = 1;
};
