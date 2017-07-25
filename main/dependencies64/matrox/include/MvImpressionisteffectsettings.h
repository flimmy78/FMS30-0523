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
//    Sets the parameters used by the impressionist effect.
//
interface IMvImpressionistEffectSettings : public IUnknown
{
public:

   //
   // Summary:
   //    Specifies the brush render order to use in IMvImpressionistEffectSettings::SetRenderOrder.
   //
   enum EMvBrushRenderOrder
   {
      keMvBrushRenderOrderInvalid = 0, // Invalid value.
      keMvBrushRenderOrderRandom,      // Brushes will be rendered in random order. 
      keMvBrushRenderOrderLast,        // End of list indicator.
   };

   //
   // Summary:
   //    Specifies the brush UV method to use in IMvImpressionistEffectSettings::SetUVMethod.
   //
   enum EMvBrushUVMethod
   {
      keMvBrushUVMethodInvalid = 0, // Invalid value.
      keMvBrushUVMethodPreDelta, // The UV value of the mesh is computed <B>before</B> the positioning is computed. 
      keMvBrushUVMethodPostDelta, // The UV value of the mesh is computed <B>after</B> the positioning is computed. 
      keMvBrushUVMethodLast,        // End of list indicator.
   };

   //
   // Summary:
   //    Specifies the brush Z ordering method to use in IMvImpressionistEffectSettings::SetBrushZOrdering.
   //
   enum EMvBrushZOrdering
   {
      keMvBrushZOrderingInvalid = 0,   // Invalid value.
      keMvBrushZOrderingNone,          // No Z Ordering
      keMvBrushZOrderingLast,          // End of list indicator.
   };

   //DOM-IGNORE-BEGIN
   static const unsigned long m_kulMinCount = 1;
   static const unsigned long m_kulMaxCount = 250;
   //DOM-IGNORE-END

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
   virtual HRESULT __stdcall SetSourceTransform
      (
      SMvMatrix * in_psSourceTransform    // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on witch the impressionist effect will be applied.
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
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Although this effect supports rotation, it is not recommended since there is no edge softness included with the effect.   
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF * in_psSourceCrop    // Pointer that specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Sets the level of smoothness to apply to the colors in the brush strokes. The higher the value, the less sharp the colors become. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetSmoothness
      (
      float in_fSmoothness // Specifies the level of smoothness. 
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not the effect will modify the alpha channel. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetPreserveAlpha
      (
      bool in_bPreserveAlpha  // If true, the alpha channel is preserved and will not be modified by the effect.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not to blend the effect with the original clip. This helps to reduce semi-transparent areas around smaller brush strokes.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetBlendOverOriginal
      (
      bool in_bBlendOverOriginal // If true, the effect is blended,and the original clip will be copied to the output before the effect is applied.
      ) = 0;

   //
   // Summary:
   //    Sets the number of brush strokes along the x-axis.
   // Description:
   //    <table>
   //    Parameter  Valid range                           Granularity  Default value  Dependency 
   //    ---------  ------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+1, +250] when using GPU card<p>     +1           +10            None
   //                [+1, +25] when using X.effects card  
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulXCount is outside the specified range. 
   //
   virtual HRESULT __stdcall SetStrokeCountX
      (
      unsigned long in_ulXCount  // Specifies the number of brush strokes. 
      ) = 0;

   //
   // Summary:
   //    Sets the number of brush strokes along the y-axis.
   // Description:
   //    <table>
   //    Parameter  Valid range                           Granularity  Default value  Dependency 
   //    ---------  ------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+1, +250] when using GPU card<p>     +1           +10            None
   //                [+1, +25] when using X.effects card  
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulYCount is outside the specified range. 
   //
   virtual HRESULT __stdcall SetStrokeCountY
      (
      unsigned long in_ulYCount  // Specifies the number of brush strokes. 
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of the brush strokes (mean opacity & opacity variation). 
   // Description:  
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR1%     [+0.0, +1.0]  Not limited  +1.0           None 
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range.
   //    
   virtual HRESULT __stdcall SetBrushOpacity
      (
      float in_fMean,      // Specifies the mean opacity of the brush strokes.  
      float in_fVariation  // Specifies the level of opacity variation to apply to the brush strokes. 
                              // A random proportion of this value will be used to modify in_fMean.   
      ) = 0;

   //
   // Summary:
   //    Sets the rotation of the brush strokes (mean rotation & rotation variation).
   // Description:
   //    <table>
   //    Parameter  Valid range             Granularity  Default value  Dependency 
   //    ---------  ----------------------  -----------  -------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    %PAR1%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range. 
   //
   virtual HRESULT __stdcall SetRotation
      (
      float in_fMean,      // Specifies the mean rotation angle of the brush strokes. 
      float in_fVariation  // Specifies the level of rotation variation to apply to the brush strokes. 
                              // A random proportion of this value will be used to modify in_fMean.   
      ) = 0;

   //
   // Summary:
   //    Sets the size of the brush strokes (mean size & size variation) along the x-axis.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value  Dependency 
   //    ---------  -----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  +1.0           None
   //    %PAR1%     [+0.0, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range.
   //
   virtual HRESULT __stdcall SetBrushSizeX
      (
      float in_fMean,      // Specifies the mean size of the brush strokes along the x-axis. 
      float in_fVariation  // Specifies the level of size variation to apply to the brush strokes 
                              // along the x-axis. A random proportion of this value will be used 
                              // to modify in_fMean.   
      ) = 0;

   //
   // Summary:
   //    Sets the size of the brush strokes (mean size & size variation) along the y-axis.
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value  Dependency 
   //    ---------  -----------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  +1.0           None
   //    %PAR1%     [+0.0, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range.
   //
   virtual HRESULT __stdcall SetBrushSizeY
      (
      float in_fMean,      // Specifies the mean size of the brush strokes along the y-axis. 
      float in_fVariation  // Specifies the level of size variation to apply to the brush strokes 
                              // along the y-axis. A random proportion of this value will be used 
                              // to modify in_fMean.
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not to preserve the aspect ratio of the brush when changing the brush size. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall PreserveBrushSizeAspectRatio
      (
      bool in_bPreserveBrushSizeAspectRatio  // If true, the aspect ratio will not be affected when changing the brush size.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the brush strokes (mean position & position variation) along the x-axis. 
   // Description:
   //    <table>
   //    Parameter  Valid range             Granularity  Default value  Dependency 
   //    ---------  ----------------------  -----------  -------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    %PAR1%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetBrushPositionX
      (
      float in_fMean,      // Specifies the mean position of the brush strokes along the x-axis. 
      float in_fVariation  // Specifies the level of position variation to apply to the brush strokes 
                              // along the x-axis. A random proportion of this value will be used to 
                              // modify in_fMean.   
      ) = 0;

   //
   // Summary:
   //    Sets the position of the brush strokes (mean position & position variation) along the y-axis.
   // Description:
   //    <table>
   //    Parameter  Valid range             Granularity  Default value  Dependency 
   //    ---------  ----------------------  -----------  -------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    %PAR1%     [MIN_FLOAT, MAX_FLOAT]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetBrushPositionY
      (
      float in_fMean,      // Specifies the mean position of the brush strokes along the y-axis. 
      float in_fVariation  // Specifies the level of position variation to apply to the brush strokes 
                              // along the y-axis. A random proportion of this value will be used to 
                              // modify in_fMean.   
      ) = 0;

   //
   // Summary:
   //    Specifies the method to use to compute the UV values for each brush stroke.  
   // Description:
   //    <table>
   //    Parameter  Valid range                    Granularity  Default value               Dependency 
   //    ---------  ----------------------------   -----------  --------------------------  ----------
   //    %PAR0%     one of the UV method members   None         keMvBrushUVMethodPostDelta  None 
   //                of EMvBrushUVMethod 
   //    </table>
   // See also:
   //    EMvBrushUVMethod
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is outside the specified range. 
   //
   virtual HRESULT __stdcall SetUVMethod
      (
      EMvBrushUVMethod in_eUVMethod // Specifies the method to use.
      ) = 0;

   //
   // Summary:
   //    Sets the rendering order for the brush strokes.
   // Description:
   //    <table>
   //    Parameter  Valid range                            Granularity  Default value               Dependency 
   //    ---------  -------------------------------------  -----------  --------------------------  ----------
   //    %PAR0%     one of the brush render order members  None         keMvBrushRenderOrderRandom  None 
   //                of EMvBrushRenderOrder 
   //    </table>
   // See also:
   //    EMvBrushRenderOrder
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the parameter is outside the specified range.
   //
   virtual HRESULT __stdcall SetRenderOrder
      (
      EMvBrushRenderOrder in_eRenderOrder // Specifies the method to use.
      ) = 0;

   //
   // Summary:
   //    Specifies the brush Z ordering method to use in  
   // Return value:
   //    - MV_E_NOT_SUPPORTED, The settings if not implemented. 
   // Remarks:
   //    - Not implemented in this release.
   //
   virtual HRESULT __stdcall SetBrushZOrdering
      (
      EMvBrushZOrdering in_eZOrdering  // Specifies the method to use for the order of the brushes' Z buffer rendering.
      ) = 0;

   //
   // Summary:
   //    Sets the seed that will be used by the random number generator to 
   //    randomize the placement of the brush strokes in the clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [0, +100]    +1           +1             None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is outside the specified range.
   //
   virtual HRESULT __stdcall SetRandomSeed
      (
      unsigned long in_ulRandomSeed // Specifies the seed for the random number generator.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvImpressionistVersion = 1;
};
