//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2005. All rights reserved. 
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
//    Sets the parameters used by the lens flare effect.
//
interface IMvLensFlareEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the maximum number of supported glare elements. 
   //
   static const unsigned int g_kuiMaximumNumberOfGlare           = 64;

   //
   // Summary:
   //    Specifies the maximum number of textures available for the glare elements. 
   //
   static const unsigned int g_kuiMaximumNumberOfGlareTextureGFX = 8;

   //
   // Summary:
   //    Specifies the maximum number of gradient GFX elements. 
   //
   static const unsigned int g_kuiMaximumNumberOfGradientGFX     = 8;

   //
   // Summary:
   //    Sets the size (dimensions) of the flare.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value  Dependency 
   //    ---------  -----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - A lens flare is composed of many elements or shapes that give each lens flare 
   //      pattern its appearance. These elements are aligned on an axis, and are defined 
   //      by GFX files. Most of these elements are static except for the flare element. 
   //      Not all lens flare patterns contain a flare element, and some contain more than 
   //      one. The flare settings (size, color, and intensity) of the lens flare effect can 
   //      only be adjusted by the user if the lens flare pattern chosen originally contained 
   //      a flare element. If there is more than one flare element, adjusting the flare settings 
   //      will affect all the flares.  
   //
   virtual HRESULT __stdcall SetFlareSize
      (
      float in_fFlareSize  // Specifies the flare size.
      ) = 0;
   
   //
   // Summary:
   //    Sets the intensity of the flare. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - A lens flare is composed of many elements or shapes that give each lens flare 
   //      pattern its appearance. These elements are aligned on an axis, and are defined 
   //      by GFX files. Most of these elements are static except for the flare element. 
   //      Not all lens flare patterns contain a flare element, and some contain more than 
   //      one. The flare settings (size, color, and intensity) of the lens flare effect can 
   //      only be adjusted by the user if the lens flare pattern chosen originally contained 
   //      a flare element. If there is more than one flare element, adjusting the flare settings 
   //      will affect all the flares. 
   //
   virtual HRESULT __stdcall SetFlareIntensity
      (
      float in_fFlareIntensity   // Specifies the flare intensity. 
      ) = 0;
   
   //
   // Summary:
   //    Sets the color of the flare. 
   // Description:
   //    <table>
   //    Parameter  Valid range         Granularity  Default value    Dependency 
   //    ---------  ------------------  -----------  ---------------  ----------
   //    %PAR0%     Any valid SMvColor  Not limited  (0, 0, 0) black  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   // Remarks:
   //    - A lens flare is composed of many elements or shapes that give each lens flare 
   //      pattern its appearance. These elements are aligned on an axis, and are defined 
   //      by GFX files. Most of these elements are static except for the flare element. 
   //      Not all lens flare patterns contain a flare element, and some contain more than 
   //      one. The flare settings (size, color, and intensity) of the lens flare effect can 
   //      only be adjusted by the user if the lens flare pattern chosen originally contained 
   //      a flare element. If there is more than one flare element, adjusting the flare settings 
   //      will affect all the flares. 
   //
   virtual HRESULT __stdcall SetFlareColor
      (
      SMvColor* in_psFlareColor  // Specifies the flare color.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the lens flare's light source.
   // Description:
   //    Adjusting the light source's position will change the appearance of the lens flare effect. 
   //    For example, moving the light source away from the center will stretch the lens flare.   
   //    <table>
   //    Parameter  Valid range                Granularity  Default value       Dependency 
   //    ---------  -------------------------  -----------  ------------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]<p>  Not limited  (+0.0, +0.0, +0.0)  None 
   //                Larger values may yield 
   //                unintended results  
   //    %PAR1%     [MIN_FLOAT, MAX_FLOAT]<p>  Not limited  (+0.0, +0.0, +0.0)  None 
   //                Larger values may yield 
   //                unintended results  
   //    %PAR2%     [MIN_FLOAT, MAX_FLOAT]<p>  Not limited  (+0.0, +0.0, +0.0)  None 
   //                Larger values may yield 
   //                unintended results  
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetLightSourcePosition
      (
      float in_fX,   // Specifies the x coordinate of the lens flare's light source. 
      float in_fY,   // Specifies the y coordinate of the lens flare's light source. 
      float in_fZ    // Specifies the z coordinate of the lens flare's light source. 
      ) = 0;

   //
   // Summary:
   //    Sets the position of the lens flare's center. 
   // Description:
   //    This method affects the position of the lens flare only, not its appearance.  
   //    <table>
   //    Parameter  Valid range             Granularity  Default value       Dependency 
   //    ---------  ----------------------  -----------  ------------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  (+0.0, +0.0, +0.0)  None 
   //    %PAR1%     [MIN_FLOAT, MAX_FLOAT]  Not limited  (+0.0, +0.0, +0.0)  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetLensFlareCenter
      (
      float in_fX,   // Specifies the x coordinate of the lens flare's center.  
      float in_fY    // Specifies the y coordinate of the lens flare's center.  
      ) = 0;

   //
   // Summary:
   //    Sets the global scaling factor that will affect all the elements of the lens flare 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value  Dependency 
   //    ---------  -----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  (+1.0, +1.0)   None 
   //    %PAR1%     [+0.0, MAX_FLOAT]  Not limited  (+1.0, +1.0)   None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetGlobalScalingFactor
      (
      float in_fScaleX, // Specifies the scaling factor along the x-axis.
      float in_fScaleY  // Specifies the scaling factor along the y-axis.
      ) = 0;
   
   //
   // Summary:
   //    Sets the opacity of the lens flare effect.
   // Description:
   //    This allows the user to adjust the intensity of the lens flare effect, making it fade or disappear entirely.   
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetGlobalOpacity
      (
      float in_fOpacity // Specifies the opacity.
      ) = 0;

   //
   // Summary:
   //    Enables/disables alpha for the lens flare effect. 
   // Description:
   //    If disabled, the lens flare will be transparent where the underlying clip is transparent. 
   //    If enabled, the lens flare will not be affected by the transparent areas of the clip, and will still be visible.  
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall EnableWriteAlpha
      (
      bool in_bIsWriteAlphaEnabled  // Specifies whether or not to enable alpha. 
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on which the flare effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value                Dependency 
   //    ---------  ---------------------------------------  -----------  ---------------------------  ----------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>    Not limited  (+0.0, +0.0, +0.0, +0.0)<p>  - crop.left + crop.right <= editing resolution width<p>
   //                Right [0.0, EditingResolutionWidth]<p>                meaning no                   - crop.top + crop.bottom <= editing resolution height
   //                Top [0.0, EditingResolutionHeight]<p>                 cropping 
   //                Bottom [0.0, EditingResolutionHeight]                                              
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetCropArea
      (
      SMvRectF* in_psCropArea // Pointer that specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the video output. 
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Since this effect does not have border softness, rotation in the matrix may result in border aliasing. 
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      SMvMatrix * in_psTransform    // Pointer that specifies the transform matrix to be used.
      ) = 0; 
   
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvfLensFlareVersion = 1;
};
