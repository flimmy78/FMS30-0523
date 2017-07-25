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
//    Sets the parameters used by the mask mosaic effect. 
//
interface IMvMaskMosaicEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the region of the source on which the mask mosaic effect will be applied. 
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
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF *in_psSourceCrop  // Pointer that specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the video output.
   // Description:
   //     The world transform matrix should contain all of the information needed for the translation 
   //     (position), scale, and rotation settings to be applied to the output. 
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Since this effect has an integrated softness, rotating the output may result in aliased edges. 
   //
   virtual HRESULT __stdcall SetSourceTransform
      (
      SMvMatrix* in_psSourceTransform  // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the mask on which the mask mosaic effect will be applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value              Dependency 
   //    ---------  -----------------  -----------  -------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0.0<p>    - rectangle.left + rectangle.right <= Mask Width.<p>
   //                                                rectangle.top = 0.0<p>     - rectangle.top + rectangle.bottom <= Mask Height. 
   //                                                rectangle.right = 0.0<p>
   //                                                rectangle.bottom = 0.0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskCrop
      (
      SMvRectF *in_psMaskCrop    // Pointer that specifies the region of the mask to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the mask only.
   // Description:
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetMaskTransform
      (
      SMvMatrix *in_psMaskTransform    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Inverts the region specified as the mask. 
   // Description:
   //     If set to true, (1.0 - mask) will be used as the new mask. 
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMaskInvert
      (
      bool in_bMaskInvert     // If true, the mask is inverted.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not the mask is to be stretched or squeezed to fit the cropped clip. 
   // Description:
   //    If set to true, the mask will be stretched/squeezed to fit the cropped clip. If set to false, 
   //    the mask will be cropped by the same amount as the clip.   
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
   //    Sets the transparency of the shape selected as the mask.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-1.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fTransparency is outside the specified range. 
   // Remarks:
   //    - A value of 0.0 will not modify the mask. 
   //    - A value of -1.0 will result in a totally opaque mask. 
   //    - A value of 1.0 will result in a totally transparent mask. 
   //    - For all other values, the mask is interpolated between either the unmodified version and
   //      the fully opaque version, or the unmodified version and the fully transparent version. 
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
      float in_fSoftness      // Specifies the softness value. 
      ) = 0;

   //
   // Summary:
   //    Sets the transparency level (alpha) of the area outside the mask, when the mask does not cover 
   //    the entire source clip (for example, if the mask is rotated).  
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value         Dependency 
   //    ---------  ----------------  -----------  --------------------  ----------
   //    %PAR0%     [+0.0, +1.0]      Not limited  +1.0, meaning opaque  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fAlphaOutsideMask is outside the specified range. 
   //
   virtual HRESULT __stdcall SetAlphaOutsideMask
      (
      float in_fAlphaOutsideMask    // Specifies the alpha to use for the region outside the mask. 
      ) = 0;

   //
   // Summary:
   //    Sets the approximate width, in pixels, of the mosaic blocks.
   // Description:
   //    This method is included in the interface for backward-compatibility 
   //    purposes only. For better visual results, the method SetMosaicBlockWidthFloat 
   //    is recommended, as it gives better interpolation between key frames.

#ifndef LINUX_PLATFORM
   #if _MSC_VER >= 1400
      __declspec(deprecated("This method is there for backward compatibility purpose. For better visual results, SetMosaicBlocWidthFloat should be used instead."))
   #else
      #pragma deprecated(SetMosaicBlockWidth)
   #endif
#else
	#pragma deprecated(SetMosaicBlockWidth)
#endif

   virtual HRESULT __stdcall SetMosaicBlockWidth
	   (
	   unsigned long in_ulBlockWidth    // Specifies the approximate block width, in pixels.
	   ) = 0;

   //
   // Summary:
   //    Sets the approximate height, in pixels, of the mosaic blocks.
   // Description:
   //    This method is included in the interface for backward-compatibility 
   //    purposes only. For better visual results, the method SetMosaicBlockHeightFloat 
   //    is recommended, as it gives better interpolation between key frames.

#ifndef LINUX_PLATFORM
   #if _MSC_VER >= 1400
      __declspec(deprecated("This method is there for backward compatibility purpose. For better visual results, SetMosaicBlocHeightFloat should be used instead."))
   #else
      #pragma deprecated(SetMosaicBlockHeight)
   #endif
#else
	#pragma deprecated(SetMosaicBlockHeight)
#endif

   virtual HRESULT __stdcall SetMosaicBlockHeight
	   (
	   unsigned long in_ulBlockWidth    // Specifies the approximate block width, in pixels.
	   ) = 0;

   //
   // Summary:
   //    Enables/disables mosaic color sharpness. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Granularity  Dependency 
   //    ----------  -------------  -------------  -----------  ----------
   //    %PAR0%      {true, false}  false          N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetMosaicColorSharpness
      (
      bool in_bEnableColorSharpness    // Specifies whether or not mosaic color sharpness is enabled.  
      ) = 0;

   //
   // Summary:
   //    Sets the approximate height, in pixels, of the mosaic blocks.
   // Description:
   //    The actual block height may differ slightly from the specified height depending on the aspect ratio and editing resolution used.  
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+1.0, +2048.0]  Not limited  +10.0          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBlockHeight is outside the specified range. 
   // Remarks:
   //    - An in_fBlockHeight value that is greater than the editing resolution height will result in undefined behavior.  
   //
   virtual HRESULT __stdcall SetMosaicBlockHeightFloat
	   (
	   float in_fBlockHeight   // Specifies the approximate block height, in pixels.
	   ) = 0;

   //
   // Summary:
   //    Sets the approximate width, in pixels, of the mosaic blocks.
   // Description:
   //    The actual block width may differ slightly from the specified width depending on the aspect ratio and editing resolution used.  
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+1.0, +2048.0]  Not limited  +10.0          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBlockWidth is outside the specified range. 
   // Remarks:
   //    - An in_fBlockWidth value that is greater than the editing resolution width will result in undefined behavior.  
   //
   virtual HRESULT __stdcall SetMosaicBlockWidthFloat
	   (
	   float in_fBlockWidth    // Specifies the approximate block width, in pixels.
	   ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvMaskMosaicVersion = 1;
};
