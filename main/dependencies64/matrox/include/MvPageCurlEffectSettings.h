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
//    Describes the fold type for the page curl effect.
//
enum EMvPageCurlFoldType
{
   keMvPageCurlFoldTypeInvalid      = 0x00000000,  // The zero value is invalid.
   keMvPageCurlFoldTypePeel1Section = 0x00000001,  // A page peel with only one section.
   keMvPageCurlFoldTypeRool1Section = 0x00000002,  // A page roll with only one section.
   keMvPageCurlFoldTypeLast         = 0x00000003,  // End of list indicator.
   keMvPageCurlFoldTypeForceDWord   = 0x7FFFFFFF,  // Force the enumerated values to be 32 bits.

};


//
// Summary:
//    Sets the parameters used by the selective page curl effect.
//
interface IMvPageCurlEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the page curl fold type.
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the specified value is invalid.
   //
   virtual HRESULT __stdcall SetFoldType
      (
      EMvPageCurlFoldType in_eFoldType // Specifies the type of fold.
      ) = 0;        

   //
   // Summary:
   //    Sets the page curl radius.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fCurlRadius is outside the specified range.
   //
   virtual HRESULT __stdcall SetCurlRadius
      (
      float in_fCurlRadius // Specifies the radius of the fold.
      ) = 0;     

   //
   // Summary:
   //    Sets the angular displacement (progression) of the page curl effect.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fCurlAngularDisplacement is outside
   //      specified range.
   //
   virtual HRESULT __stdcall SetCurlAngularDisplacement
      (
      float in_fCurlAngularDisplacement   // Specifies the progression of the page curl.
      ) = 0;         

   //
   // Summary:
   //    Sets the page curl fold angle.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [-360.0, +360.0]  Not limited  +45.0          None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fFoldAngle is outside the specified range.
   //
   virtual HRESULT __stdcall SetFoldAngle
      (
      float in_fFoldAngle  // Specifies the page curl fold angle, in degrees.
      ) = 0;   

   //
   // Summary:
   //    Sets the page curl front-face softness.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fFrontFaceSoftnessLevel is outside the
   //      specified range.
   //
   virtual HRESULT __stdcall SetFrontFaceSoftnessLevel
      (
      float in_fFrontFaceSoftnessLevel // Specifies the amount of front-face softness. The maximum
                                       // front-face softness level (+1.0) will soften 30 pixels 
                                       // around the front face of the page curl.
      ) = 0;

   //
   // Summary:
   //    Sets the softness level of the fold.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fCurlSoftnessLevel is outside the
   //      specified range.
   //
   virtual HRESULT __stdcall SetCurlSoftnessLevel
      (
      float in_fCurlSoftnessLevel   // Specifies the amount of softness on the fold. The maximum
                                    // curl softness level (+1.0) will soften 10 pixels along the 
                                    // edge of the fold.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the highlight band on the back face of the curl.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.5           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fHighlightPosition is outside the
   //      specified range.
   //
   virtual HRESULT __stdcall SetHighlightPosition
      (
      float in_fHighlightPosition   // Specifies the position of the highlight on the back face of
                                    // the curl. The minimum value (+0.0) positions the highlight 
                                    // near the edge of the fold. As the highlight position 
                                    // increases, the highlight band moves away from the edge.
      ) = 0;

   //
   // Summary:
   //    Sets the intensity of the highlight band.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.8           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fHighlightIntensity is outside the
   //      specified range.
   //
   virtual HRESULT __stdcall SetHighlightIntensity
      (
      float in_fHighlightIntensity  // Specifies the intensity of the highlight band. The maximum
                                    // value (+1.0) gives the highest intensity of the highlight 
                                    // band. As the highlight intensity decreases, the highlight 
                                    // band vanishes.
      ) = 0;

   //
   // Summary:
   //    Sets the intensity of the shadow projected by the curl.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.8           None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_fShadowIntensity is outside the specified
   //      range.
   //
   virtual HRESULT __stdcall SetShadowIntensity
      (
      float in_fShadowIntensity  // Specifies the intensity of the shadow. The maximum value (+1.0)
                                 // gives the highest shadow intensity. As the shadow intensity
                                 // decreases, the curl shadow vanishes.
      ) = 0;

   //
   // Summary:
   //    Sets the crop rectangle.
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value  Dependency 
   //    ---------  ---------------------------------------  -----------  -------------  ----------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>    +1.0         0.0            - Left+Right < EditingResolutionWidth<p>
   //                Right [0.0, EditingResolutionWidth]<p>                               - Top+Bottom < EditingResolutionHeight
   //                Top [0.0, EditingResolutionHeight]<p>
   //                Bottom [0.0, EditingResolutionHeight]
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if no error occurs.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_psCropRect is outside the specified range.
   //
   virtual HRESULT __stdcall SetCropRectangle
      (
      SMvRectF * in_psCropRect   // Pointer to the structure SmvRectF that contains the desired 
                                 // crop rectangle to apply to the effect. The left value represents 
                                 // the amount of pixels to crop on the left of the input image. 
                                 // The right value represents the amount of pixels to crop on the 
                                 // right of the input image. The bottom value represents the 
                                 // amount of pixels to crop at the bottom of the input image. The 
                                 // top value represents the amount of pixels to crop at the top of 
                                 // the input image. All the four values should be set to zero if 
                                 // no cropping is desired.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the output.
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None
   //    </table>
   // Return value:
   //    - MVF_NOERROR, if completed successfully.
   //    - MVF_E_INVALID_PARAMETER, if the parameter in_poTransformMatrix is outside the specified
   //      range.
   // Remarks:
   //    - Negative scaling is not supported. Negative scaling on the z-axis will make parts of the surface disappear 
   //      by reversing the orientation of the triangles, and causing them to be culled by DirectX. Negative scaling 
   //      on other axes can have similar undesirable effects depending on the orientation of the page curl. 
   //
   virtual HRESULT __stdcall SetTransformMatrix
      (
      CMvMatrix * in_poTransformMatrix    // Pointer that specifies the transform matrix to be used.
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
   //    Number of element of the grids needed for SetLuminancegrid(), SetShadHidghGrid and 
   //    SetMidTonesGrid().
   //
   static const unsigned long ms_kulVersion = 1;
};
