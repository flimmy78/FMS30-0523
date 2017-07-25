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
#include "mvMatrix.h"


//
// Summary:
//    Sets the parameters used by the material slab effect. 
//
interface IMvMaterialSlabEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the slab, but not the lights. 
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    If you want a DUD effect, the default matrix should be an identity matrix translated
   //    along the z axis. The amount of translation depends on the aspect ratio and the editing
   //    resolution, based on the following equation:<p>
   //    (FRAMEDEPTH/2.0)/((EditRes.Width/EditRes.Height)/(AspectRatio)),<p>
   //    where FRAMEDEPTH = 64 for NTSC or PAL and 128 for HD.<p>
   //    This is needed because the slab is constructed with the origin at its center, so the 
   //    front face is not on the plane z = 0. 
   //
   virtual HRESULT __stdcall SetWorldTransformMatrix    
      (
      CMvMatrix *in_poTransformMatrix  // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the width, height, and depth of the slab. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value                        Dependency 
   //    ---------  -----------------  -----------  -----------------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  Width = Edit resolution width<p>     None
   //                                                Height = Edit resolution height<p>
   //                                                Depth = 64 in NTSC/PAL, 128 in HD
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetSlabDimension           
      (
      float in_fWidth,  // Width of the slab in pixels.
      float in_fHeight, // Height of the slab in pixels.
      float in_fDepth   // Depth of the slab in pixels.
      ) = 0;

   //
   // Summary:
   //    Sets the index of the surface, in the array of input surfaces, to use as the front source. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1]     Not limited  +0             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetFrontSource             
      (
      unsigned long in_ulSource  // Specifies the index of the surface to use as the front source.
      ) = 0;

   //
   // Summary:
   //    Sets the value by which the alpha of the look-and-feel texture is multiplied.
   // Description:
   //    A value of 0 indicates that only the front source will be visible, because the 
   //    look-and-feel texture will be transparent. A value of 1 indicates that the look-and-feel
   //    texture's alpha is unmodified. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetFrontBlendValue         
      (
      float in_fBlendValue    // Alpha multiplier of the look-and-feel texture.
      ) = 0;

   //
   // Summary:
   //    Sets the value by which the alpha of the front source is multiplied.
   // Description:
   //    A value of 0 indicates that only the look-and-feel texture will be visible, because the 
   //    front source is transparent. A value of 1 indicates that the front source alpha is
   //    unmodified. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetFrontAlphaMultiplier    
      (
      float in_fAlphaMultiplier  // Alpha multiplier of the source.
      ) = 0;

   //
   // Summary:
   //    Sets the region (rectangle) of the source that is applied to the front face of the slab. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height. 
   //                                                rectangle.right = 0<p>
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetFrontCrop               
      (
      SMvRectF *in_psCrop  // Crop information.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not the front surface is inverted (upside-down).
   // Description:
   //    If set to non-zero, the surface is inverted. 
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1]          +1           +0             None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - This parameter allows a rotation of the slab around any axis and ensures that the 
   //      visible face is always oriented in the right direction. 
   //
   virtual HRESULT __stdcall SetFrontOrientation        
      (
      unsigned long in_bSourceIsUpsideDown   // Specifies if the front surface is inverted (upside-down).
      ) = 0;

   //
   // Summary:
   //    Sets the index of the surface, in an array of input surfaces, to use as the back source. 
   // Description:
   //    <table>
   //    Parameter  Valid range                          Granularity  Default value  Dependency 
   //    ---------  -----------------------------------  -----------  -------------  ----------
   //    %PAR0%     [0, max number of input surfaces-1]  Not limited  0              None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetBackSource              
      (
      unsigned long in_ulSource  // Index of the surface to use as the back souce.
      ) = 0;

   //
   // Summary:
   //    Sets the value by which the alpha of the look-and-feel texture is multiplied.
   // Description:
   //    A value of 0 indicates that only the back source is visible, because the look-and-feel
   //    texture is transparent. A value of 1 indicates that the alpha of the look-and-feel texture
   //    is unmodified. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetBackBlendValue          
      (
      float in_fBlendValue // Specifies the alpha multiplier of the look-and-feel texture.
      ) = 0;

   //
   // Summary:
   //    Sets the value by which the alpha of the back source is multiplied.
   // Description:
   //    A value of 0 indicates that only the look-and-feel texture is visible, because the back 
   //    source is transparent. A value of 1 indicates that the back source alpha is unmodified. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetBackAlphaMultiplier     
      (
      float in_fAlphaMultiplier  // Specifies the alpha multiplier of the source.
      ) = 0;

   //
   // Summary:
   //    Sets the region (rectangle) of the source that is applied to the back face of the slab. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height. 
   //                                                rectangle.right = 0<p>
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetBackCrop                
      (
      SMvRectF *in_psCrop  // Specifies the crop information.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not the back surface is inverted (upside-down).
   // Description:
   //    If set to non-zero, the surface is inverted. 
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1]          +1           +0             None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - This parameter allows a rotation of the slab around any axis and ensures that the visible
   //      face is always oriented in the right direction. 
   //
   virtual HRESULT __stdcall SetBackOrientation         
      (
      unsigned long in_bSourceIsUpsideDown   // Specifies if the back surface is inverted (upside-down).
      ) = 0;

   //
   // Summary:
   //    Sets the position (x, y, z) of the first point light source. 
   // Description:
   //    <table>
   //    Parameter       Valid range              Granularity  Default value  Dependency 
   //    --------------  -----------------------  -----------  -------------  ----------
   //    All parameters  [-MAX_FLOAT, MAX_FLOAT]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - The light source can be positioned anywhere in the 3-dimensional space. The greater the 
   //      distance between the light and the slab, the less illuminated the slab will be. 
   //
   virtual HRESULT __stdcall SetLight0Position          
      (
      float in_fX,   // Position of the light along the x axis.
      float in_fY,   // Position of the light along the y axis.
      float in_fZ    // Position of the light along the z axis.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the first point light. 
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value     Dependency 
   //    ---------  ------------------------  -----------  ----------------  ----------
   //    %PAR0%     Red = [-1.0, +1.0]<p>     Not limited  Red = +0.0<p>     None
   //                Green = [-1.0, +1.0]<p>                Green = +0.0<p>  
   //                Blue = [-1.0, +1.0]<p>                 Blue = +0.0<p>  
   //                Alpha = +1.0                           Alpha = +1.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Some applications may not want to expose dark light. However, it is supported in DSX as
   //      an important 3D concept. 
   //    - A dark light is a light with one or more negative components. Its main purpose is to
   //      remove light from a spot judged too bright by the user. 
   virtual HRESULT __stdcall SetLight0Color             
      (
      SMvColorF *in_psColorF  // Specifies the color of the light.
      ) = 0;

   //
   // Summary:
   //    Sets the position (x, y, z) of the second point light source. 
   // Description:
   //    <table>
   //    Parameter       Valid range              Granularity  Default value  Dependency 
   //    --------------  -----------------------  -----------  -------------  ----------
   //    All parameters  [-MAX_FLOAT, MAX_FLOAT]  Not limited  0              None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - The light source can be positioned anywhere in the 3-dimensional space. The greater the
   //      distance between the light and the slab, the less illuminated the slab will be. 
   //
   virtual HRESULT __stdcall SetLight1Position          
      (
      float in_fX,   // Position of the light along the x axis.
      float in_fY,   // Position of the light along the y axis.
      float in_fZ    // Position of the light along the z axis.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the second point light. 
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value     Dependency 
   //    ---------  ------------------------  -----------  ----------------  ----------
   //    %PAR0%     Red = [-1.0, +1.0]<p>     Not limited  Red = +0.0<p>     None
   //                Green = [-1.0, +1.0]<p>                Green = +0.0<p>
   //                Blue = [-1.0, +1.0]<p>                 Blue = +0.0<p>
   //                Alpha = 1.0                            Alpha = +1.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Some applications may not want to expose dark light. However, it is supported in DSX as
   //      an important 3D concept. 
   //    - A dark light is a light with one or more negative components. Its main purpose is to 
   //      remove light from a spot judged too bright by the user. 
   //
   virtual HRESULT __stdcall SetLight1Color             
      (
      SMvColorF *in_psColorF  // Specifies the color of the light.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the ambient light. 
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value     Dependency 
   //    ---------  ------------------------  -----------  ----------------  ----------
   //    %PAR0%     Red = [-1.0, +1.0]<p>     Not limited  Red = +0.0<p>     None
   //                Green = [-1.0, +1.0]<p>                Green = +0.0<p>
   //                Blue = [-1.0, +1.0]<p>                 Blue = +0.0<p>
   //                Alpha = 1.0                            Alpha = +1.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Some applications may not want to expose dark light. However, it is supported in DSX as
   //      an important 3D concept. 
   //    - A dark light is a light with one or more negative components. Its main purpose is to 
   //      remove light from a spot judged too bright by the user. 
   //
   virtual HRESULT __stdcall SetAmbientColor            
      (
      SMvColorF *in_psColorF  // Specifies the color of the light.
      ) = 0;

   //
   // Summary:
   //    Enables/disables a special mode where the light positions are displayed using two cursors. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Granularity  Default value  Dependency 
   //    ----------  -------------  -----------  -------------  ----------
   //    %PAR0%      [+0, +1]       +1           +0              None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall EnableLightCursors         
      (
      unsigned long in_bEnableLightCursors   // If set to non-zero, the light cursors are enabled.
      ) = 0;

   //
   // Summary:
   //    Enables or disables the special 2D mode of the slab effect.
   // Description:
   //    This mode is useful to render graphics with alpha. 
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall Enable2DMode               
      (
      bool in_b2DModeEnable   // If set to true, 2D mode is enabled.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the fragment antialiasing feature (FAA). 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetFAAEnable               
      (
      bool in_bFAAEnable   // A value of true enables the light FAA, and a value of false disables it.
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
   //
   static const unsigned long ms_kulVersion = 1;
};
