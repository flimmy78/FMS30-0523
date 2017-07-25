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
//    Sets the parameters used by the crystallize effect. 
//
interface IMvCrystallizeEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the region of the source clip on which the crystallize effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    rectangle.left + rectangle.right <= Edit Resolution Width<p>
   //                                                rectangle.top = 0<p>     rectangle.top + rectangle.bottom <= Edit Resolution Height. 
   //                                                rectangle.right = 0<p>
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF * in_psSourceCrop    // Pointer that specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings to be applied to the output. 
   // Description:
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4×4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This transform should only contain translation and scaling, not rotation.
   //
   virtual HRESULT __stdcall SetTransform
      (
      SMvMatrix * in_psTransfrom    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of smoothness to apply to the colors in the crystal pattern. The higher the value, the less sharp the colors become.    
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSmoothness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetSmoothness
      (
      float in_fSmoothness    // Specifies the amount of smoothness.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity for the crystallized areas of the clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fCrystalOpacity is outside the specified range. 
   //
   virtual HRESULT __stdcall SetCrystalOpacity
      (
      float in_fCrystalOpacity   // Specifies the crystal opacity.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the crystallize effect for the alpha channel.    
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetCrystallizeAlpha
      (
      bool in_bCrystallizeAlpha  // If true, the alpha channel is crystallized.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the mask on which the crystallize effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value            Dependency 
   //    ---------  --------------  -----------  -----------------------  ----------
   //    %PAR0%     [0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    rectangle.left + rectangle.right <= Edit Resolution Width<p>
   //                                             rectangle.top = 0<p>     rectangle.top + rectangle.bottom <= Edit Resolution Height
   //                                             rectangle.right = 0<p>
   //                                             rectangle.bottom = 0
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskCrop
      (
      SMvRectF * in_psMaskCrop   // Pointer that specifies the region of the mask to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the mask only. 
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
   //    Inverts the region specified as the mask. 
   // Description:
   //     If set to true, (1.0 - mask) will be used as the new mask. 
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskInvert
      (
      bool in_bMaskInvert  // If true, the mask is inverted.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not the mask is to be stretched or squeezed to fit the cropped clip.
   // Description:
   //    If set to true, the mask will be stretched/squeezed to fit the cropped clip. If set to false, the mask will be cropped by the same amount as the clip.   
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskStretch
      (
      bool in_bMaskStretch    // If true, the mask is stretched/squeezed. If false, it is cropped. 
      ) = 0;

   //
   // Summary:
   //    Sets the transparency of the shape selected as the mask.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - A value of 0.0 will not modify the mask. 
   //    - A value of -1.0 will result in a totally opaque mask. 
   //    - A value of 1.0 will result in a totally transparent mask. 
   //    - For all other values, the mask is interpolated between either the unmodified version and 
   //      the totally opaque version, or the unmodified version and the totally transparent version. 
   //
   virtual HRESULT __stdcall SetMaskTransparency
      (
      float in_fTransparency  // Specifies the transparency value.
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
      float in_fSoftness   // Specifies the softness value for the mask.
      ) = 0;

   //
   // Summary:
   //    Sets the transparency level (alpha) of the area outside the mask, when the mask does not cover the entire source clip (for example, if the mask is rotated).  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetAlphaOutsideMask
      (
      float in_fAlphaOutsideMask    // Specifies the alpha to use for the region outside the mask.
      ) = 0;

   //
   // Summary:
   //    Enables/disables the mask.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskEnable
      (
      bool in_bEnableMask     // If true, the mask is enabled.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvCrystallizeVersion = 1;
};
