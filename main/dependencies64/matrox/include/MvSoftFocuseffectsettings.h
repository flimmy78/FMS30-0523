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


//
// Summary:
//    Sets the parameters used by the soft focus effect.
//
interface IMvSoftFocusEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the crop area used when computing the soft focus mesh. 
   // Description:
   //    <table>
   //    Parameter  Valid range                               Granularity  Default value          Dependency 
   //    ---------  ----------------------------------------  -----------  ---------------------  ----------
   //    %PAR0%     Left [+0.0, EditingResolutionWidth]<p>    +1.0         (0.0, 0.0, 0.0, 0.0),  - Left+Right < EditingResolution Width<p>
   //                Right [+0.0, EditingResolutionWidth]<p>                 meaning no crop is    - Top+Bottom < EditingResolution Height
   //                Top [+0.0, EditingResolutionHeight]<p>                  performed
   //                Bottom [+0.0, EditingResolutionHeight]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the crop area has been set.
   //    - MV_E_INVALID_POINTER, if the input parameter is NULL.
   // Remarks:
   //    - The center of the crop area is specified in the world transform matrices.
   //
   virtual HRESULT __stdcall SetCropArea
      (
      const SMvRectF * in_pSCropArea   // Pointer to a SMvRectF object that specifies the crop
                                       // area, in pixels, to be used.
      ) = 0;

   //
   // Summary:
   //    Specifies the percentage of the original image that is to be superimposed on top of the
   //    blur result.
   // Description:
   //    <table>
   //    Parameter  Valid range                         Granularity  Default value        Dependency 
   //    ---------  ----------------------------------  -----------  -------------------  ----------
   //    %PAR0%     [+0, +100]<p>                       +1           +0.0, meaning only   None
   //                - +0 = only show the blur result.                the blur result 
   //                - ]+0, +100[ = blend between blur                will be seen
   //                  result and original image.
   //                - +100 = only show original image
   //                  (dud effect).
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the value has been set.
   //
   virtual HRESULT __stdcall SetSourceBlendingFactor
      (
      const unsigned long in_ulBlendFactorInPercent   // Specifies the blending factor value, as
                                                      // a percentage.
      ) = 0;

   //
   // Summary:
   //    Specifies the amount of blur to apply to the original image.
   // Description:
   //    <table>
   //    Parameter  Valid range                     Granularity  Default value            Dependency 
   //    ---------  ------------------------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, +100.0]<p>               +1.0         +0.0, meaning no blur    None
   //                - +0.0 = no blur is performed                is performed (dud 
   //                - ]+0.0, +100.0] = blur up to                effect)
   //                  the effect's maximum 
   //                  capacity
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the value has been set.
   //
   virtual HRESULT __stdcall SetBlurAmount
      (
      const float in_fOffsetInPercent  // Specifies the amount of blur, as a percentage, to apply
                                       // to the original image.
      ) = 0;

   //
   // Summary:
   //    Specifies a correction, as a percentage, to apply to the red channel only. 
   // Description:
   //    Correction is applied to the original non-blurred image only, which is applied on top of 
   //    the blur result.
   //    <table>
   //    Parameter  Valid range                            Granularity  Default value      Dependency 
   //    ---------  -------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [+0, +400]<p>                          +1           +100, meaning the  None
   //                - +0 = red is removed from the image                original level 
   //                - +100 = original level (dud effect)                is kept
   //                - +400 = maximum red correction; 4 
   //                  times the original factor
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the value has been set.
   //
   virtual HRESULT __stdcall SetColorGainRed
      (
      const unsigned long in_ulRedGain // Specifies the amount of correction, as a percentage, to 
                                       // apply to the red channel only.
      ) = 0;

   //
   // Summary:
   //    Specifies a correction, as a percentage, to apply to the green channel only.
   // Description:
   //    Correction is applied to the original non-blurred image only, which is applied on top of 
   //    the blur result.
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value      Dependency 
   //    ---------  ---------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [+0, +400]<p>                            +1           +100, meaning the  None
   //                - +0 = green is removed from the image                original level 
   //                - +100 = original level (dud effect)                  is kept
   //                - +400 = maximum green correction; 4 
   //                  times the original factor
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the value has been set.
   //
   virtual HRESULT __stdcall SetColorGainGreen
      (
      const unsigned long in_ulGreenGain  // Specifies the amount of correction, as a percentage,
                                          // to apply to the green channel only.
      ) = 0;

   //
   // Summary:
   //    Specifies a correction, as a percentage, to apply to the blue channel only.
   // Description:
   //    Correction is applied to the original non-blurred image only, which is applied on top of 
   //    the blur result.
   //    <table>
   //    Parameter  Valid range                             Granularity  Default value      Dependency 
   //    ---------  --------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [+0, +400]<p>                           +1           +100, meaning the  None
   //                - +0 = blue is removed from the image                original level 
   //                - +100 = original level (dud effect)                 is kept
   //                - +400 = maximum blue correction; 4 
   //                  times the original factor
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the value has been set.
   //
   virtual HRESULT __stdcall SetColorGainBlue
      (
      const unsigned long in_ulBlueGain   // Specifies the amount of correction, as a percentage,
                                          // to apply to the blue channel only.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings to be applied to the output.
   // Description:
   //    This effect does not support translation in z, scaling in z, or any rotation. Therefore, the transform matrix should 
   //    only include translation in x or y, and/or scaling in x or y.  
   //    <table>
   //    Parameter  Valid range             Granularity  Default value        Dependency 
   //    ---------  ----------------------  -----------  -------------------  ----------
   //    %PAR0%     Translation (x or y)    Not limited  The identity matrix  None
   //                and/or scale (x or y)
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetTransform
      (
      CMvMatrix * in_poTransformMatrix    // Pointer that specifies the transform matrix to be used.
      ) = 0;
   
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvSoftFocusVersion = 1;
};
