//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2007. All rights reserved. 
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
// Author:
// $Archive: /VP/FLEXVIDEO/VIDEOEFFECTS/Mvx3DSphere/inc/Mv3DSphereEffectSettings.h $
//===============================================================================

#pragma once

#ifndef _Mvx3DSphereSettings_h_Z4347971A32613711813G26H83410835359G_
#define _Mvx3DSphereSettings_h_Z4347971A32613711813G26H83410835359G_

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceAPI.h"

//
// Summary:
//    Sets the parameters used by the 3D sphere effect. 
//
interface IMv3DSphereEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the crop area to be used when the output mesh is computed. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value         Dependency 
   //    ---------  ---------------------------------------  -----------  --------------------  ----------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>    1.0          0.0, meaning no crop  Left+Right < EditingResolutionWidth<p>
   //                Right [0.0, EditingResolutionWidth]<p>                                      Top+Bottom < EditingResolutionHeight
   //                Top [0.0, EditingResolutionHeight]<p> 
   //                Bottom [0.0, EditingResolutionHeight] 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - All other 3D sphere effect settings are applied to the crop area set by this method.   
   //
   virtual HRESULT __stdcall SetCropArea                 
      ( 
      SMvRectF*     in_psCropArea    // Pointer that specifies the region of the source to use.  
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the output.  
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None    
   // </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetWorldTransformMatrix     
      ( 
      CMvMatrix*    in_poWorldTransformMatrix    // Pointer that specifies the transform matrix to be used. 
      ) = 0;
   
   //
   // Summary:
   //    Enables/disables a cursor in the video clip that indicates the source of the specular light.
   // Description:
   //    <table>
   //    Parameter   Valid range  Default value  Granularity  Dependency 
   //    ----------  -----------  -------------  -----------  ----------
   //    %PAR0%      [0, 1]       0              N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ui8Enabled is not 0 or 1
   //
   virtual HRESULT __stdcall SetLightEnableFlag          
      ( 
      uint8_t       in_ui8Enabled    // Specifies whether or not the specular light source's cursor is enabled.  
      ) = 0;

   //
   // Summary:
   //    Sets the position of the specular light in absolute space according to the default Direct3D (D3D) left-handed Cartesian coordinate system. 
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value       Dependency 
   //    ---------  ------------------------  -----------  ------------------  ----------
   //    %PAR0%     fx [-5000.0, 5000.0]<p>   Not limited  {0.0, 0.0, -300.0}  None
   //                fy [-5000.0, 5000.0]<p>                                                   
   //                fz [-5000.0, 5000.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   //
   virtual HRESULT __stdcall SetLightPosition            
      ( 
      SMvVector3*   in_psPosition    // Specifies the position of the specular light. 
      ) = 0;
   
   //
   // Summary:
   //    Sets the intensity of the diffuse shadow that can be added to the video. A value of zero indicates no diffuse shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value            Dependency 
   //    ---------  --------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0, meaning no shadows  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fIntensity is outside the specified range.
   //
   virtual HRESULT __stdcall SetShadowIntensity          
      ( 
      float         in_fIntensity    // Specifies the diffuse shadow's intensity as a percentage. 
      ) = 0;

   //
   // Summary:
   //    Sets the intensity of the specular light that can be added to the video. A value of zero indicates no specular light. 
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value          Dependency 
   //    ---------  --------------  -----------  ---------------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0, meaning no light  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fIntensity is outside the specified range.
   //
   virtual HRESULT __stdcall SetLightSpecularIntensity   
      ( 
      float         in_fIntensity    // Specifies the specular light's intensity as a percentage.  
      ) = 0;

   //
   // Summary:
   //    Sets the size of the specular light that can be added to the video. 
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  20.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSize is outside the specified range.
   // Remarks:
   //    - Since the specular light for this effect is generated in a vertex shader using the Blinn-Phong 
   //      Shading Model, the parameter in_fSize does not have a linear impact on the light's size, but 
   //      instead is used to control the power term of the formula. This means, for example, that light 
   //      is still visible even if the value of the parameter is set to zero.   
   //
   virtual HRESULT __stdcall SetLightSize                
      ( 
      float         in_fSize    // Specifies the light's size. 
      ) = 0;

   //
   // Summary:
   //    Sets the color of the specular light that can be added to the video. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value                    Dependency 
   //    ---------  -----------  -----------  -------------------------------  ----------
   //    %PAR0%     Any color    Not limited  White, (ARGB value: 0xFFFFFFFF)  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   //    - MV_E_MV_E_INVALID_PARAMETER, if the RGB values entered are outside the specified range.
   //
   virtual HRESULT __stdcall SetLightColor               
      ( 
      SMvColorF*    in_psColor    // Specifies the specular light's color. 
      ) = 0;

   //
   // Summary:
   //    Sets the value of morph progression from two-dimensional flat video surface to three-dimensional sphere.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value          Dependency 
   //    ---------  --------------  -----------  ---------------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0, meaning no morph  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fMorph is outside the specified range.
   //
   virtual HRESULT __stdcall SetSphereMorph              
      ( 
      float         in_fMorph    // Specifies the morph progression as a percentage. 
      ) = 0;

   //
   // Summary:
   //    Sets the value of the sphere's radius, which determines the video surface's size when the morph progression is anything other than zero.
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value    Dependency 
   //    ---------  ---------------  -----------  ---------------  ----------
   //    %PAR0%     [+0.0, +1000.0]  Not limited  100.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fRadius is outside the specified range.
   //
   virtual HRESULT __stdcall SetSphereRadius             
      ( 
      float         in_fRadius    // Specifies the sphere's radius. 
      ) = 0;

   //
   // Summary:
   //    Sets the amount of transparency that can be applied to the video.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value                 Dependency 
   //    ---------  --------------  -----------  ----------------------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0, meaning no transparency  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fTransparency is outside the specified range.
   //
   virtual HRESULT __stdcall SetSphereTransparency       
      ( 
      float         in_fTransparency    // Specifies the amount of transparency as a percentage. 
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness that can be applied to the edges of the video.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value             Dependency 
   //    ---------  --------------  -----------  ------------------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0, meaning no softness  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftness is outside the specified range.
   // Remarks:
   //    - Softness is not supported on the X.effects card. This effect uses the fast blur implemented 
   //      in the effects framework, and will cause the command buffers of the X.effects card to overflow.
   //
   virtual HRESULT __stdcall SetSphereSoftness           
      ( 
      float         in_fSoftness    // Specifies the amount of softness as a percentage. 
      ) = 0;

   //
   // Summary:
   //    Enables/disables the option to show the back face of the output mesh.
   // Description:
   //    <table>
   //    Parameter  Valid range  Default value  Granularity  Dependency 
   //    ---------  -----------  -------------  -----------  ----------
   //    %PAR0%     [0, 1]       0              N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ui8RenderBackface is not 0 or 1
   //
   virtual HRESULT __stdcall SetRenderBackface           
      ( 
      uint8_t       in_ui8RenderBackface    // Specifies whether or not to show the back face.
      ) = 0;

   //
   // Summary:
   //    Enhance or not the sharpness of the effect.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      [-5.0, +5.0]    Not limited    None
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //
   virtual HRESULT __stdcall SetEnhanceSharpness
	   (
	   float in_fEnhanceSharpness  // the factor of sharpness applied to the effect.
	   ) = 0;

   //
   // Summary:
   //    Interface version
   static const unsigned long ms_kulMvx3DSphereVersion = 1;
};
#endif