//==============================================================================
//
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
//
//===============================================================================

#pragma once


//
// Summary:
//    Sets the parameters used by the mask effect. 
//
interface IMvMaskEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the video output. 
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the output.
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      SMvMatrix * in_psWorldTransform  // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the mask only.
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskTransform
      (
      SMvMatrix * in_psMaskTransform   // Pointer that specifies the transform matrix to be used for the mask.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the mask that will be used in the video output.  
   // Description:
   //    <table>
   //    Parameter  Valid range                             Granularity  Default value               Dependency 
   //    ---------  --------------------------------------  -----------  --------------------------  ---------------------------------------------------------------
   //    %PAR0%     [0.0, MAX_FLOAT] Rectangle composed of  Not limited  rectangle.left = 0.0<p>     - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                four positive floating-point values.                 rectangle.top = 0.0<p>      - rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                                                     rectangle.right = 0.0<p>
   //                                                                     rectangle.bottom = 0.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskCrop
      (
      SMvRectF * in_psMaskCrop   // Pointer that specifies the region of the mask to use.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on which the mask effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range                             Granularity  Default value              Dependency 
   //    ---------  --------------------------------------  -----------  -------------------------  ----------
   //    %PAR0%     [0.0, MAX_FLOAT] Rectangle composed of  Not limited  rectangle.left = 0.0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                four positive floating-point values.                 rectangle.top = 0.0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height. 
   //                                                                     rectangle.right = 0.0<p>
   //                                                                     rectangle.bottom = 0.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF * in_psSourceCrop    // Pointer that specifies the region of the source to use.
      ) = 0;
   
   //
   // Summary:
   //    Inverts the region specified as the mask. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [0, 1]            1            0              None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskInvert
      (
      unsigned long in_bMaskInvert  // If set to a non-zero value, the mask is inverted.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not the mask is to be stretched or squeezed to fit the cropped clip. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskStretch
      (
      bool in_bMaskStretch    // If true, the mask is stretched/squeezed. If false, it is cropped. 
      ) = 0;

   //
   // Summary:
   //    Sets the color of the area outside the mask, when the mask does not cover the entire source clip (for example, if the mask is rotated).   
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value  Dependency 
   //    ---------  -------------------------  -----------  -------------  ----------
   //    %PAR0%     SMvColor 4 unsigned char,  Not limited  0xFFFFFFFF     None 
   //                or 1 unsigned long 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetColorOutsideMask
      (
      SMvColor in_sColorOutsideMask    // Specifies the color to use for the region outside the mask. 
      ) = 0;   

   //
   // Summary:
   //    Sets the value that will be multiplied by the mask's alpha value before the mask is applied to the source clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    -  If set to 0, the mask is completely opaque. If set to 1, the mask is unchanged. 
   //
   virtual HRESULT __stdcall SetMaskAlphaMultiplier
      (
      float in_fMaskAlphaMultiplier    // Specifies the multiplier for the mask's alpha value.
      ) = 0;

   //
   // Summary:
   //    Sets the value used to interpolate the input mask with a fully transparent mask. 
   // Description:
   //    If the value is 0, the mask is transparent. If set to 1, the mask is unchanged.  
   //
   //    Mask_used = (interpolant * mask_input) + ((1-interpolant) * no_mask) 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskInterpolant
      (
      float in_fMaskInterpolant     // Specifies the interpolant to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the mask. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMaskSoftness
      (
      float in_fSoftness      // Specifies the softness value.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;
};
