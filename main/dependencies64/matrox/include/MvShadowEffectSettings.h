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

//
// Summary:
//    Sets the parameters used by the shadow effect.
//
interface IMvShadowEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the shadow only.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the shadow.
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetWorldTransformMatrixShadow
      (
      CMvMatrix * in_poTransformMatrix    // Pointer that specifies the transform matrix to be used for the shadow.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the output.
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetWorldTransformMatrixVideo
      (
      CMvMatrix * in_poTransformMatrix    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Specifies the crop area used when computing the shadow and video output mesh. The center
   //    of the crop area is specified in the world transform matrices.
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value  Dependency 
   //    ---------  ---------------------------------------  -----------  -------------  ----------------------------------------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>    1.0          0.0, meaning   - Left+Right < EditingResolutionWidth<p>
   //                Right [0.0, EditingResolutionWidth]<p>                no crop is     - Top+Bottom < EditingResolutionHeight
   //                Top [0.0, EditingResolutionHeight]<p>                 performed
   //                Bottom [0.0, EditingResolutionHeight]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the crop area has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   //
   virtual HRESULT __stdcall SetCropArea
      (
      SMvRectF * in_poSCropArea  // Specifies the crop area used when computing the shadow and 
                                 // video output mesh. The center of the crop area is specified 
                                 // in the world transform matrices.
      ) = 0;

   //
   // Summary:
   //    Specifies the color of the shadow surface. The shadow is a gradient based on the four
   //    colors passed in the parameter.
   // Description:
   //    <table>
   //    Parameter  Valid range              Granularity  Default value                    Dependency 
   //    ---------  ----------------------   -----------  -------------------------------  ----------
   //    %PAR0%     Any color is valid.<p>   Not limited  Opaque black, for all four       None
   //                Specifying an opacity                 array members (ARGB value: 
   //                value of zero for all                 0xFF000000)
   //                colors yields an 
   //                invisible shadow.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the world transform matrix has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   //
   virtual HRESULT __stdcall SetShadowColorArray
      (
      SMvColor * in_poColor   // Pointer to an array of four SMvColor objects, representing four
                              // ARGB values. Each object colors a corner-point of the 
                              // Gouraud-shadowed mesh, in the following order:<p>
                              // <image Rectangle 1234><p>
                              // The color also specifies the shadow opacity using the alpha 
                              // component value.
      ) = 0;

   //
   // Summary:
   //    Specifies the field of view (FOV) angle of the camera to be used when rendering the shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range                               Granularity  Default value  Dependency 
   //    ---------  ----------------------------------------  -----------  -------------  ----------
   //    %PAR0%     You should limit the angle to a           Not limited  +60.0          None
   //                reasonable value (-100.0 to +100.0) so 
   //                that the resulting scene is viewable.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the shadow's FOV has been set.
   // Remarks:
   //    - Used in conjunction with the camera position setting to manipulate the camera.
   //    - This parameter does not affect the video.
   virtual HRESULT __stdcall SetShadowCameraFOV
      (
      float in_fCameraFOV     // Specifies the float value, in degrees, containing the camera FOV.
      ) = 0;

   //
   // Summary:
   //    Specifies the camera position coordinates used when rendering the shadow.
   // Description:
   //    <table>
   //    Parameter  Valid range                                              Granularity  Default value                      Dependency 
   //    ---------  -------------------------------------------------------  -----------  ---------------------------------  ----------
   //    %PAR0%     - Limited to the input surface size in x and y.          Not limited  (0, 0,-(input_surface_height /2))  None
   //               - In z, you could limit the range from -(Y * 10) to 0.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the shadow's camera position has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   // Remarks:
   //    - Used in conjunction with the camera FOV setting to manipulate the camera.
   //    - This parameter does not affect the video.
   virtual HRESULT __stdcall SetShadowCameraPosition
      (
      SMvVector3 * in_poSCameraPosition   // Pointer to a SMvVector3 object which represents the 
                                          // camera's position in (x,y,z) format. The z coordinate 
                                          // is computed using the following formula:<p>
                                          // (- camera_z_coord) / tanf ( (? * 30.0f) / 180.0f)
      ) = 0;

   //
   // Summary:
   //    Enables or disables the fragment anti-aliasing (FAA) feature.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Only supported on X.effect cards.
   virtual HRESULT __stdcall SetFAAEnable
      (
      bool in_bFAAEnable   // When set to true, the light FAA is enabled.
      ) = 0;

   //
   // Summary:
   //    Specifies the size of the softness between the shadow and the background.
   // Description:
   //    <table>
   //    Parameter  Valid range                                         Granularity  Default value  Dependency 
   //    ---------  --------------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [0.0, half the input surface's size in x and y]<p>  1.0          (0.0, 0.0),    None
   //                For example, if the input surface's size is                      meaning no
   //                720 x 486, then you should limit the range                       softness is
   //                from 0 to 360 in x, and from 0 to 243 in y.                      applied
   //                If you're dealing with a logo of 10 x 10,                         
   //                the limit is 5 in both x and y.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the shadow's camera position has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   // Remarks:
   //    -  This parameter does not affect the video.
   //
   virtual HRESULT __stdcall SetSoftnessSize
      (
      SMvPointF * in_fSoftnessSizeInPixels   // Pointer to a SMvPointF object which represents the
                                             // softness size, in pixels, in (x, y) format.
      )= 0;

   //
   // Summary:
   //    Specifies the softness size between the video and the background.
   // Description:
   //    <table>
   //    Parameter  Valid range                                         Granularity  Default value  Dependency 
   //    ---------  --------------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [0.0, half the input surface's size in x and y]<p>  1.0          (0.0, 0.0),    None
   //                For example, if the input surface's size is                      meaning no
   //                720 x 486, then you should limit the range                       softness is
   //                from 0 to 360 in x, and from 0 to 243 in y.                      applied.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the shadow's camera position has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   // Remarks:
   //    - This parameter does not affect the shadow.
   //
   virtual HRESULT __stdcall SetVideoSoftnessSize
      (
      SMvPointF * in_fSoftnessSizeInPixels   // Pointer to a SMvPointF object which represents the
                                             // softness size, in pixels, in (x, y) format.
      )= 0;

   //
   // Summary:
   //    Specifies the blur amount of the shadow colors. This parameter does not affect the video.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value       Dependency 
   //    ---------  ----------------  -----------  ------------------  ----------
   //    %PAR0%     [0, 100]          1            0, meaning no blur  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the shadow's camera position has been set.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulBlurInPercent is outside specified range.
   //
   virtual HRESULT __stdcall SetBlur
      (
      unsigned long in_ulBlurInPercent    // Specifies the blur amount, as a percentage.
      ) = 0;

   //
   // Summary:
   //    Number of element of the grids needed for SetLuminancegrid(), SetShadHidghGrid and 
   //    SetMidTonesGrid().
   //
   static const unsigned long ms_kulVersion = 1;
};
