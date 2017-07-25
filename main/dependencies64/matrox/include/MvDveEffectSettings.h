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
#include "mvFlex3DDeviceStructs.h"
#include "mvMatrix.h"


//
// Summary:
//    Lists the border types that can be set by IMvDveEffectSettings::SetBorderType.
//
namespace NBorderTypes
{
   static const unsigned long ulNone     = 0x0;    // No border. Select this if you don't intend to
                                                      // use a border. 
   static const unsigned long ulFlat     = 0x1;    // Single-color border. 
   static const unsigned long ulGradient = 0x2;    // Dual-color, Gouraud-shaded border. 
   static const unsigned long ulTexture  = 0x4;    // Presently unsupported. 
   static const unsigned long ulAlphaEdge= 0x10;   // This can be used with flat or gradient border types, 
                                                      // and should be used for irregular shapes, such as 
                                                      // a graphic with alpha, which will apply color to 
                                                      // the shape based on the clip's alpha channel. 
};


//
// Summary:
//    Sets the parameters used by the 3D DVE effect. 
//
interface IMvDveEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the video output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation 
   //    settings to be applied to the output.     
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   // Remarks:
   //    - Undesirable matrices will produce undesirable transformations, such as a shadow 
   //      surface being placed outside the visible area.
   //    - Values that contain fractional parts will be truncated by the effect. 
   virtual HRESULT __stdcall SetWorldTransformMatrix
      (
      CMvMatrix * in_poTransformMatrix    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value  Dependency 
   //    ---------  ---------------------------------------  -----------  -------------  -----------------------------
   //    %PAR0%     [0.0, half the input surface's size]<p>  1.0          0.0, meaning   The effect softness rectangle
   //                (For example, if the input surface                    no softness    must not intersect the 
   //                size is 720 x 486, then you should                    is applied     border rectangle (except if 
   //                limit the range from 0 to 360 in x,                                  equal).
   //                and from 0 to 243 in y. If you're 
   //                dealing with a logo of 10 x 10, then 
   //                you should limit the size to 5 in x 
   //                and y)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks
   //    - Values that contain fractional parts will be truncated by the effect. 
   //    - This is the global effect softness. 
   //
   virtual HRESULT __stdcall SetEffectSoftness
      (
      SMvPointF *in_poSEffectSoftness  // Pointer to the SMvPointF object that specifies the softness 
                                          // value in pixels. Softness values are expressed in (x, y) 
                                          // format, and apply to both sides of the clip. For example, 
                                          // a value of 5 for x will soften 5 pixels on the left and 5 
                                          // pixels on the right side of the clip.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of perspective corrected softness to apply to the clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value             Dependency 
   //    ---------  ------------  -----------  ------------------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0, meaning no softness  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_INVALID_POINTER, if the parameter in_fSoftness is outside the specified range.
   // Remarks:
   //    - Unlike the standard softness for this effect, the size of the perspective corrected softness will 
   //      not be affected by transformation/deformation of the video surface. 
   //
   virtual HRESULT __stdcall SetEffectPerspectiveCorrectedSoftness
      (
      float in_fSoftness   // Specifies the amount of perspective corrected softness as a percentage.
      ) = 0;

   //
   // Summary:
   //    Sets the softness of the border's interior, which softens the boundary between the inner edge of border and the video clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range          Granularity  Default value  Dependency 
   //    ---------  -------------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, border size]  1.0          0.0, meaning   - The selected border type value must be different from 0<p>
   //                                                  no softness    - The border inner softness size should be smaller or equal to the border size
   //                                                  is applied.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetBorderInnerSoftness
      (
      SMvPointF *in_poSBorderInnerSoftness   // Pointer to the SMvPointF object that specifies the softness value in pixels. Softness values 
                                                // are expressed in (x, y) format, and apply to both sides of the clip. For example, a value 
                                                // of 5 for x will soften 5 pixels on the left and 5 pixels on the right side of the clip.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on which the DVE effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range                             Granularity  Default value         Dependency 
   //    ---------  --------------------------------------  -----------  --------------------  ----------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>   1.0          0.0, meaning no crop  Left+Right < EditingResolutionWidth<p>
   //                Right [0., EditingResolutionWidth]<p>                                      Top+Bottom < EditingResolutionHeight
   //                Top [0.0, EditingResolutionHeight]<p>
   //                Bottom [0.0, EditingResolutionHeight]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - All other 3D DVE effect settings are applied to the crop area set by this method. 
   //
   virtual HRESULT __stdcall SetCropArea
      (
      SMvRectF  *in_poSCropArea  // Pointer to the SMvRectF object that specifies the crop area to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the border type. 
   // Description:
   //    <table>
   //    Parameter  Valid range                    Granularity  Default value         Dependency 
   //    ---------  -----------------------------  -----------  --------------------  ----------
   //    %PAR0%     0, one of the border types in  None         0, meaning no border  None 
   //                the NBorderTypes namespace.                 
   //    </table>
   // See also:
   //    NBorderTypes
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetBorderType
      (
      unsigned long in_ulBorderType // Specifies the border type to be used based on the NBorderTypes namespace. 
      ) = 0;

   //
   // Summary:
   //    Sets the border size.  
   // Description:
   //    <table>
   //    Parameter  Valid range                               Granularity  Default value           Dependency 
   //    ---------  ---------------------------------------   -----------  ----------------------  ---------------------
   //    %PAR0%     [0.0, half the input surface's size]<p>   1.0          0.0, meaning no border  - The value selected for the border type must not be 0. <p>
   //                For example, if the input surface size                                        - The border's rectangle must not intersect the effect softness rectangle.
   //                is 720 x 486, then you should limit 
   //                the range from 0 to 360 for x, and from  
   //                0 to 243 for y. If you're dealing with
   //                a logo of 10 x 10, then you should 
   //                limit the size to 5 for x and y.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetBorderSizeInPixels
      (
      SMvPointF *in_poSBorderSizeInPixels // Pointer to the SMvPointF object that specifies the border size value in pixels. The value is expressed in an (x, y) format.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the border's interior, including the color's transparency value through the alpha channel.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value                           Dependency 
   //    ---------  -----------  -----------  --------------------------------------  -------------------------------------------------------------
   //    %PAR0%     Any color    Not limited  Opaque black, (ARGB value: 0xFF000000)  - The selected border type value must be different from 0.<p>
   //                                                                                  - The border size must be greater than 0.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall SetBorderColorInside
      (
      SMvColor  *in_poSColor  // Pointer to the SMvColor object that specifies the desired color. 
      ) = 0;

   //
   // Summary:
   //    Sets the color of the border's exterior, including the color's transparency value through the alpha channel. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value                           Dependency 
   //    ---------  -----------  -----------  --------------------------------------  -------------------------------------------------------------
   //    %PAR0%     Any color    Not limited  Opaque black, (ARGB value: 0xFF000000)  - The selected border type value must be different from 0.<p>
   //                                                                                  - The border size must be greater than 0.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetBorderColorOutside
      (
      SMvColor  *in_poSColor  // Pointer to the SMvColor object that specifies the desired color. 
      ) = 0;

   //
   // Summary:
   //    Sets the size of the border's round corners. 
   // Description:
   //    <table>
   //    Parameter  Valid range                               Granularity  Default value  Dependency 
   //    ---------  ---------------------------------------   -----------  -------------  ------------------------------------------------------------
   //    %PAR0%     [0.0, half the input surface's size]<p>   1.0          0.0, meaning   - If x is greater than 0, then y must be greater than 0.<p>
   //                For example, if the input surface size                square          - If y is greater than 0, then x must be greater than 0.
   //                is 720 x 486, then you should limit                   corners.
   //                the range from 0 to 360 for x, and 
   //                from 0 to 243 for y. If you're dealing   
   //                with a logo of 10 x 10, then you 
   //                should limit the size to 5 for x and y.   
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetRoundCornerSizeInPixels
      (
      SMvPointF *in_posRoundCornerSize // Pointer to the SMvPointF object that specifies the border size value in pixels. The value is expressed in an (x, y) format..
      ) = 0;

   //
   // Summary:
   //    Specifies the reference points used for the round corners of a border.
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value              Dependency 
   //    ---------  ---------------------------------------  -----------  -------------------------  ----------------------------------------------------------
   //    %PAR0%     [minus half the input surface's size,    1.0          0.0, meaning no offset<p>  - The round corner size in pixels must be greater than 0.0
   //                plus half the input surface's size]<p>                (the control points will
   //                It is possible for the mesh to look                   be the corner's square 
   //                'broken' if undesirable control points                coordinates).
   //                are used. The control points used in 
   //                conjunction with the 
   //                SetRoundCornerSizeInPixels method 
   //                allows for significant modification
   //                of the mesh. 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Each corner is symmetrical. 
   //
   virtual HRESULT __stdcall SetRoundCornerBezierControlPoints
      (
      SMvPointF *in_poSBezierControlPoints   // Pointer to an array of two SMvPointF 
                                             // objects that specify an offset value, in pixels, relative 
                                             // to the points' natural corner coordinates, expressed in an (x, y)
                                             // format. For example, if the size of the input surface is 720 x 486, 
                                             // the coordinates range from -360 to 360 for x and 243 to 
                                             // -243 for y. Therefore, the top-left corner coordinate is: <p>
                                             // (-360 - in_poSBezierControlPoints.fX, 243 +
                                             // in_poSBezierControlPoints.fY ).
      ) = 0;

   //
   // Summary:
   //    Enables/disables full screen anti-aliasing of the effect. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method is specific to the X.effects card only. 
   //
   virtual HRESULT __stdcall SetFAAEnable
      (
      bool in_bFAAEnable   // If true, full screen anti-aliasing is enabled.
      ) = 0;

   //
   // Summary:
   //    Enables/disables frame processing when rendering from frame to field. This option specifies whether or not the effect is processed directly into a field, or into a frame from
   //    which the correct field is then extracted. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetFrameProcessing
      (
      bool in_bFrameProcessEnable   // If true, the effect will be processed in a frame, from which the correct field will be extracted.
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
