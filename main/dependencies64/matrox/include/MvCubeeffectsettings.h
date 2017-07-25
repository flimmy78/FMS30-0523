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
//    
//
interface IMvCubeEffectSettings : public IUnknown
{

   //
   // Summary:
   //    This enumeration is used to determine which object will be applied to a specific cube face.
   // Remarks:
   //    - The starting value for keSourceSurfaceX must not be 0. Add keSourceSurfaceOffset to have each 
   //      enumeration starting with "keSourceSurface" map to an element of a keSourceSurfaceCount 
   //      lengthed array.
   //
   enum EMvSource
   {
      keSourceStart         = 0, // Start of list indicator.
      keSourceSurfaceStart  = 0, // Identify the surface at index 0 of the input surface array
      keSourceSurface1      = 1, // Identify the surface at index 1 of the input surface array
      keSourceSurface2      = 2, // Identify the surface at index 2 of the input surface array
      keSourceSurface3      = 3, // Identify the surface at index 3 of the input surface array
      keSourceSurface4      = 4, // Identify the surface at index 4 of the input surface array
      keSourceSurface5      = 5, // Identify the surface at index 5 of the input surface array
      keSourceSurface6      = 6, // Identify the surface at index 6 of the input surface array
      keSourceSurfaceLast   = 7,

      keSourceColor         = 7, // Specify that the source will be a color
      keSourceLast          = 8, // End of list indicator.

      keSourceSurfaceCount  = keSourceSurfaceLast - keSourceSurfaceStart - 1, // List count indicator
      keSourceSurfaceOffset = -keSourceSurfaceStart  - 1 // List offset indicator
   };

   //
   // Summary:
   //    This enumeration is used to refer to a specific face of the cube. 
   // Remarks:
   //    - The starting value for keFaceX must not be 0. Add keFaceOffset to have each enumeration map to
   //      an element of a keFaceCount lengthed array.
   //
   enum EMvFace
   {
      keFaceStart  = 0, // Start of list indicator.
      keFaceBack   = 1, // Identify the cube's back face
      keFaceBottom = 2, // Identify the cube's bottom face
      keFaceLeft   = 3, // Identify the cube's left face
      keFaceRight  = 4, // Identify the cube's right face
      keFaceTop    = 5, // Identify the cube's top face
      keFaceFront  = 6, // Identify the cube's front face
      keFaceLast   = 7, // End of list indicator.

      keFaceCount  = keFaceLast - keFaceStart - 1, // List count indicator

      keFaceOffset = -keFaceStart - 1 // List offset indicator
   };


   //
   // Summary:
   //    Binds a cube face with a specific source.
   // Return value:
   //    - MV_NOERROR, completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if either parameter is not defined in the enumeration.
   // Remarks:
   //    - By default, each cube face is bound to a color. 
   //    - If a cube face is bound to an unavailable source, it will not be rendered in the video output.  
   //
   virtual HRESULT __stdcall BindFaceToSource
      (
      EMvFace in_eDestFace,   // Specifies a cube face. 
      EMvSource in_eSource    // Specifies a source to bind to the cube face.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source to apply to the cube face.  
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ---------------------------------------------------------------
   //    %PAR1%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                                rectangle.right = 0<p>   
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   //    - MV_E_INVALID_PARAMETER, if the enumeration is outside the specified range
   // Remarks:
   //    - When a cube face has a color, the crop rectangle will be silently ignored until a video source is mapped to the cube face.   
   //
   virtual HRESULT __stdcall SetFaceCrop
      (
      EMvFace          in_eDestFace,   // Specifies the cube face.
      const SMvRectF * in_kpsCropRect  // Specifies the region of the source to apply to the cube face.
      ) = 0;

   //
   // Summary:
   //    Sets the color to apply to a cube face when the face is not bound to a source. 
   // Description:
   //    <table>
   //    Parameter  Valid range            Granularity  Default value             Dependency 
   //    ---------  ---------------------  -----------  ------------------------  ----------
   //    %PAR1%     [0-255] per component  Not limited  All components at 128     None
   //                                                    (semi-transparent gray)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //    - MV_E_INVALID_PARAMETER, if the enumeration is outside the specified range.
   // Remarks:
   //    - The color is only applied when the specified source is keSourceColor.
   //
   virtual HRESULT __stdcall SetFaceColor
      (
      EMvFace          in_eDestFace,   // Specifies the cube face.
      const SMvColor * in_kpsColor     // Specifies the color to apply to the cube face. 
      ) = 0;

   //
   // Summary:
   //    Sets the depth of the cube.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value  Dependency 
   //    ---------  -----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  +1.0         +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER if the parameter in_fDepth is outside the specified range.
   // Remarks:
   //    - The value passed to this function is multiplied by the average of the width and height.
   //
   virtual HRESULT __stdcall SetCubeDepth
      (
      float in_fDepth   // Specifies the depth value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the outside edges of the cube.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]      Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER if the parameter in_fSoftness is outside the specified range.
   //
   virtual HRESULT __stdcall SetExternalCubeSoftness
      (
      float in_fSoftness   // Specifies the softness value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the cube face edges. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER if the parameter in_fSoftness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetInternalCubeSoftness
      (
      float in_fSoftness   // Specifies the softness value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount and of rotation to apply to the light source.
   // Description:
   //    <table>
   //    Parameter       Valid range             Granularity  Default value  Dependency 
   //    --------------  ----------------------  -----------  -------------  ----------
   //    All parameters  [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER if a parameter is outside its specified range.
   // Remarks:
   //    - The light source is a vector that has no position value since it is directional. 
   //    - The starting point is a light vector that is pointing at the screen, from behind the cube. Therefore the back face 
   //      of the cube is completely lit (highlight), and the front face of the cube is completely dark (shadow).   
   //
   virtual HRESULT __stdcall SetCubeLightRotation
      (
      float in_fRX,  // Rotation around the x-axis.
      float in_fRY,  // Rotation around the y-axis.
      float in_fRZ   // Rotation around the z-axis.
      ) = 0;

   //
   // Summary:
   //    Sets the color and intensity of the shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value                Dependency 
   //    ---------  ------------------------  -----------  ---------------------------  ----------
   //    %PAR0%     [+0, +255] per component  +1           (255, 255, 255, 255), white  None
   //    %PAR1%     [+0.0, +1.0]              Not limited  +1.0                         None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER if a parameter is outside its specified range. 
   //    - MV_E_INVALID_POINTER if the pointer specifying color is NULL. 
   // Remarks:
   //    - The alpha channel is ignored in the parameter in_kpsColor.
   //
   virtual HRESULT __stdcall SetCubeShadowColor
      (
      const SMvColor * in_kpsShadow,   // Pointer that specifies the shadow color.
      float            in_fIntensity   // Specifies the shadow intensity value.
      ) = 0;

   //
   // Summary:
   //    Sets the color and intensity of the highlight.  
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value                Dependency 
   //    ---------  ------------------------  -----------  ---------------------------  ----------
   //    %PAR0%     [+0, +255] per component  +1           (255, 255, 255, 255), white  None
   //    %PAR1%     [+0.0, +1.0]              Not limited  +1.0                         None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER if a parameter is outside its specified range.
   //    - MV_E_INVALID_POINTER if the pointer specifying color is NULL.
   // Remarks:
   //    - The alpha channel is ignored in the parameter in_kpsColor.
   //
   virtual HRESULT __stdcall SetCubeHighlightColor
      (
      const SMvColor * in_kpsHighlight,   // Pointer that specifies the highlight color.
      float            in_fIntensity      // Specifies the highlight intensity value. 
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the video output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the output.
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      SMvMatrix * in_kpsWorldMatrix // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the light indicator, which gives a visual representation of the light's direction.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Granularity  Default value  Dependency 
   //    ----------  -------------  -----------  -------------  ----------
   //    %PAR0%      [+0, +1]       +1           +0              None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetLightIndicatorVisibility
      (
      bool in_bIsVisible // If set to non-zero, the light indicator is enabled.    
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
   //    Interface version.
   //
   static const unsigned long ms_kulMvCubeVersion = 1;
};
