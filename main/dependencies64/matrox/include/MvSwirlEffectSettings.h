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

//DOM-IGNORE-BEGIN
#define BULGE
//DOM-IGNORE-END

//
// Summary:
//    Sets the parameters used by the swirl effect.
//
interface IMvSwirlEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the center of the swirl's distortion donut.
   // Description:
   //    <table>
   //    Parameter  Valid range                           Granularity  Default value                  Dependency 
   //    ---------  ------------------------------------  -----------  -----------------------------  ----------
   //    %PAR0%     (-200.0, -200.0) to (+200.0, +200.0)  Not limited  (+0.0, +0.0), center of image  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - The center of the image, independent of the source, is always (0,0).
   //    - The corners, independent of the resolution, are always at (-50.0, -50.0), (-50.0, +50.0),
   //      (+50.0, -50.0) and (+50.0, +50.0).
   //
   virtual HRESULT __stdcall SetSwirlCenter
      (
      const SMvPointF *in_kpsCenter // The location of the center of the swirl.
      ) = 0;

   //
   // Summary:
   //    Sets the outer radius of the donut-shaped region.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  +100.0         None
   //    %PAR1%     [+0.0, +100.0]  Not limited  +100.0         None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - The shape of the donut is elliptical; which is why there are two parameters.
   //    - On an wide-screen clip, specifying “50” for both parameters will result in an elliptical
   //      shape since the width of the source video is longer than the height.
   //
   virtual HRESULT __stdcall SetSwirlOuterRadius
      (
      float in_fOuterRadiusW, // The outer radius of the donut-shaped region.  This is a percentage
                                 // of the width of the input source.
      float in_fOuterRadiusH  // The outer radius of the donut-shaped region.  This is a percentage
                                 // of the height of the input source.
      ) = 0;

   //
   // Summary:
   //    Sets the inner radius of the donut-shaped region.
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   // Remarks:
   //    - The specified radius is a percentage of outer radius.  0% is no inner radius, and 100%
   //      means that the inner radius is right on top of the outer radius.
   //
   virtual HRESULT __stdcall SetSwirlInnerRadius
      (
      float in_fInnerRadius   // The inner radius of the donut-shaped region.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of circular distortion within the donut shaped region.
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [-720.0, +720.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetSwirlAngle
      (
      float in_fAngle   // The angle at which things are distorted.
      ) = 0;

   // Summary:
   //    Make the distortion effect appear to begin from the inner or outer part of the donut.
   // Description:
   //    The top-most image is the original. The second is the one with the effect applied, and
   //    invert off. Notice that the inner circle is clearly visible, while the outer radius blends
   //    in with the rest of the triangle. The last picture is the one with this flag set to true.
   //    Notice how the inner part of the triangle is continuous with the distortion with little or
   //    no apparent edge, whereas there is a clear edge for the circle on the outer part of the
   //    donut-shaped distortion region.<p>
   //    <image NoSwirl><p>
   //    <image OuterToInerSwirl><p>
   //    <image InnerToOuterSwirl><p>
   //    <table>
   //    Parameter   Valid range     Default value   Dependency
   //    ----------  --------------  --------------  -----------
   //    %PAR0%      {true, false}   false           None
   //    </table>
   // Returns:
   //       - MV_NOERROR, if no error occurs.
   // Remarks:
   //       - This parameter has no effect when bulge mode is turned on.
   //                                                                                                      
   virtual HRESULT __stdcall SetSwirlInvert
      (
      bool in_bInvert   // Indicate if the swirl is inverted or not.
      ) = 0;

   //
   // Summary:
   //    Sets how much smoothing to apply to the region of the image that is distorted by the effect.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value       Dependency 
   //    ---------  ------------  -----------  ------------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0, no smoothing  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if out of range.
   //
   virtual HRESULT __stdcall SetSwirlSmooth
      (
      float in_fAmount  // The amount of smoothing to apply.
      ) = 0;

   //
   // Summary:
   //    Changes the type of distortion used in the swirl to that of the bulge.
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetSwirlBuldgeMode
      (
      bool in_bBuldge   // Set to True to enable bulge mode.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source the effect will be applied to. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------------------------------------------------------------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                                rectangle.right = 0<p>   
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if pointer is NULL
   // Remarks:
   //    - The crop is applied after the swirl, before the 3D transformations.
   //
   virtual HRESULT __stdcall SetSwirlCrop
      (
      const SMvRectF *in_kpsCrop // The portion of the region to be cropped.
      ) = 0;

   //
   // Summary:
   //    Enables/Disables the stretch of the cropped area to the original size of the image
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetSwirlCropStretch
      (
      bool in_bStretchRect  // Set to True to stretch the cropped area to the original size
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
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL
   // Remarks:
   //    - If you are in bulge mode with a negative swirl angle, rotation on x or y, and scaling on z may produce unintended results.
   //
   virtual HRESULT __stdcall SetWorldTransformMatrix
      (
      SMvMatrix *in_psTransformMatrix  // Pointer that specifies the transform matrix to be used. 
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvSwirlVersion = 1;
};
