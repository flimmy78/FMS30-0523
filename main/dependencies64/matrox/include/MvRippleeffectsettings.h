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
//    Sets the parameters used by the ripple effect.
//
interface IMvRippleEffectSettings : public IUnknown
{
   //
   // Summary:
   //    The maximum height that a wave in a given ripple animation can take.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+1.0, +400.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - To have a maximum height of zero, or to have a maximum height greater than that of the
   //      valid range, pass in a transformation matrix that will scale on the z-axis.
   //
   virtual HRESULT __stdcall SetRippleAmplitude
      (
      float in_fAmplitude  // The maximum height of the various waves in the ripple animation.
      ) = 0;

   //
   // Summary:
   //    Maximum number of waves formed by the ripple.
   // Description:
   //    <table>
   //    Parameter  Valid range                          Granularity  Default value  Dependency 
   //    ---------  -----------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+1, +20.0] when using GPU card<p>   Not limited  +4.0	         None
   //                [+1, +8] when using X.effect card
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - The increase in the number of ripples is rounded and does not appear continuous when
   //      increased or decreased; therefore this value should not be keyframed.
   //
   virtual HRESULT __stdcall SetRippleNumberOfPeriods
      (
      float in_fNumPeriods // The number of ring of waves around the source of the ripple that will be formed.
      ) = 0;

   //
   // Summary:
   //    How much the height of the ripple decreases as it leaves the center of the ripple.
   // Description:
   //    The greater the value, the more the height of the ripple will decrease from the center.
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - Set to 0.0 to have all waves in the ripple to have the same height.
   //
   virtual HRESULT __stdcall SetRippleAttenuation
      (
      float in_fAttenutation  // How much the waves get smaller as they leave the middle of the ripple.
      ) = 0;

   //
   // Summary:
   //    How far into the animation sequence of the waves leaving the source of the ripple to go.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - The animation is complete between 0 and 1, that is at 1 the animation is at the same 
   //      place as when it was at 0.
   //
   virtual HRESULT __stdcall SetRippleProgression
      (
      float in_fProgression   // How far into the animation.
      ) = 0;

   //
   // Summary:
   //    Specifies how fast the ripple's waves will leave the center of the ripple.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - At 0, there is no animation.  The ripple is constant, no matter the value of the 
   //      progression.
   //    - If the value of the wave speed is too small (approximately less than 0.01), then the
   //      ripple progression will not wrap around in it's animation cycle; but only complete a 
   //      portion of it on the [0,1] range.
   //    - The wave speed should be set to a constant value during any animation sequence, or else 
   //      unpredictable results may follow.
   //    - To vary the speed of the wave during an animation, use the progression.
   //
   virtual HRESULT __stdcall SetRippleWaveSpeed
      (
      float in_fWaveSpeed  // The speed at which the waves will leave the center of the ripple.
      ) = 0;

   //
   // Summary:
   //    Specifies the center of the ripple.
   // Description:
   //    <table>
   //    Parameter  Valid range                         Granularity  Default value    Dependency 
   //    ---------  ----------------------------------  -----------  ---------------  ----------
   //    %PAR0%     (+0.01, +0.01) to (+99.99, +99.99)  Not limited  (+50.0, +50.0),  None 
   //                                                                 centered
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   // Remarks:
   //    - The values for the center are scaled between 0.001 and 99.99, therefore the center will 
   //      always be at (50,50) independent of the resolution.
   //
   virtual HRESULT __stdcall SetRipplePosition
      (
      const SMvPointF *in_kpsPosition  // The center of the ripple.
      ) = 0;

   //
   // Summary:
   //    Specifies the color of the shadows.
   // Description:
   //    <table>
   //    Parameter  Valid range         Granularity  Default value                Dependency 
   //    ---------  ------------------  -----------  ---------------------------  ----------
   //    %PAR0%     Any color is valid  Not limited  Opaque black, (ARGB value:   None
   //                                                 0xFF000000)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   // Remarks:
   //    - Alpha within the passed structure is ignored.
   //    - The shadow color is modulated with the texture color.  Therefore, white will be invisible
   //      as a shadow color, and other light colors will normally be barely visible.
   //
   virtual HRESULT __stdcall SetRippleShadowColor
      (
      const SMvColor  *in_kpsShadowColor  // The color that the shadows at the bottom of the waves of the ripple.
      ) = 0;

   //
   // Summary:
   //    Specifies the highlight color.
   // Description:
   //    <table>
   //    Parameter  Valid range         Granularity  Default value                Dependency 
   //    ---------  ------------------  -----------  ---------------------------  ----------
   //    %PAR0%     Any color is valid  Not limited  Opaque white, (ARGB value:   None
   //                                                 0xFFFFFFFF)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   // Remarks:
   //    - Alpha component of structure is ignored.
   //    - Highlight colors are added to the texture; therefore black would be invisible as a 
   //      highlight color, and very dark colors barely visible.
   //
   virtual HRESULT __stdcall SetRippleHighlightColor
      (
      const SMvColor  *in_kpsHighlightColor  // The color of the highlights.
      ) = 0;

   //
   // Summary:
   //    Specifies the intensity of the shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetRippleShadowIntensity
      (
      float in_fShadowIntensity  // How much the shadow color will be visible.
      ) = 0;

   //
   // Summary:
   //    Specifies the intensity of the highlights.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetRippleHighlightIntensity
      (
      float in_fHighlightIntensity  // How much the highlight color will be visible.
      ) = 0;


   //
   // Summary:
   //    Sets the region of the source on witch the ripple effect will be applied.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------------------------------------------------------------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                                rectangle.right = 0<p>   
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Very small cropping values (about 3 pixels wide and/or high) will disable the softness.
   //
   virtual HRESULT __stdcall SetRippleCrop
      (
      const SMvRectF * in_kpsCrop   // The region of the source to use.
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
   //    - Lighting is not affected by transformation adjustments. For example, applying rotation will
   //      not modify the location of the shadows and highlights.
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      const SMvMatrix * in_psWorldMatrix  // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Allows for repositioning of the crop rectangle.
   // Description:
   //    <table>
   //    Parameter  Valid range             Granularity  Default value  Dependency 
   //    ---------  ----------------------  -----------  -------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  (+0.0, +0.0)   None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - This is applied to the source image before the ripple effect; at the same time as the crop.
   //    - Use this if the image is to remain stationary, even after cropping, but do not want the
   //      ripple's center to move.
   //
   virtual HRESULT __stdcall SetRippleCropOffset      
      (
      const SMvPointF * in_kpsCropOffset  // Offset of the crop rectangle from its default position.
      ) = 0;

   //
   // Summary:
   //    How much softness to apply to the border of the source image before passing it to the
   //    ripple effect.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetRippleSoftnessAmount  
      (
      float in_fSoftness   // The amount of softness.
      ) = 0;

   //
   // Summary:
   //    How round the corners are, a value of 0 means that the corners are square, and 1 means 
   //    that they are very round.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetRippleSoftnessRadius  
      (
      float in_fSoftRadius // The radius of the softness.
      ) = 0;

   //
   // Summary:
   //    Specify the amount of polygon detail the softness is.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+2, +15]    +1           +2             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - This parameter as no effect when the corner radius softness is 0.
   //    - A value of 2 will make the softness' corners appear polygonal, and as the value is
   //      increased, the rounder it will look.
   //
   virtual HRESULT __stdcall SetRippleSoftnessVertexCount
      (
      int in_nVertexCount  // Number of vertices per corner to use.
      ) = 0;

   //
   // Summary:
   //    A softness that is applied to the final rendered image instead of the source.
   // Description:
   //    This softness takes into account where image data has been rendered, and softens the 
   //    border around that; therefore an image that has a transparent hole in it will also see 
   //    softness where the hole is.  Also, the softness will take into account the edges that 
   //    outline the mesh.
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - This parameter has no effect when using X.Effect card
   //
   virtual HRESULT __stdcall SetRippleAnisotropicSoftness 
      (
      float in_fAnisoSoft  // The amount of anisotropic softness to apply.  0 is none, 1 is maximum.
      ) = 0;
   
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvRippleVersion = 1;
};
