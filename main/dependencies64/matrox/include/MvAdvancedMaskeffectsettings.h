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
// Author:
// $Archive: /VP/FLEXVIDEO/VIDEOEFFECTS/MvxAdvancedMask/inc/MvAdvancedMaskeffectsettings.h $
//===============================================================================

#pragma once

#ifndef _MvAdvancedMaskSettings_h_CB604491H6324861235408D708365705H_
#define _MvAdvancedMaskSettings_h_CB604491H6324861235408D708365705H_

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceAPI.h"

//
// Summary:
//    Sets the parameters used by the advanced mask effect. 
//
interface IMvAdvancedMaskEffectSettings : public IUnknown
{

   //
   // Summary:
   //    Sets the maximum number of control points for each sub-mask. 
   //
   static const unsigned long ms_kulMaximumNumberOfControlPointsPerSubMask = 256;   // Specifies the maximum number of control points.
   
   //
   // Summary:
   //    Sets the maximum number of sub-masks used for a mask.  
   //
   static const unsigned long ms_kulMaximumNumberOfSubMasks = 8;     // Specifies the maximum number of sub-masks.

   //
   // Summary:
   //    Specifies the blend settings used for a sub-mask in SetSubMaskBlendingOperation.
	//
   enum EMvSubMaskBlendingOperation
   {
      keMvSubMaskBlendingOperationInvalid = 0,
      keMvSubMaskBlendingOperationAdd,                      // Adds a sub-mask to the selection. This is used to display what is included in the sub-mask.
      keMvSubMaskBlendingOperationSubtract,                 // Subtracts a sub-mask from the previous sub-mask. This is used to remove part of a selection 
                                                               // (for example, to create a hole inside a mask).
      keMvSubMaskBlendingOperationIntersect,                // Specifies the area of the previous sub-mask that intersects with the current sub-mask. 
      keMvSubMaskBlendingOperationLast,
   };

   //
   //
   // Summary:
   //    Removes control points for all sub-masks. 
   // Description:
   //    Removes all control points on all sub-masks stored in this effect.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Always call this method <B>once</B> before calling any other method from IMvAdvancedMaskEffectSettings, or the effect may not function as intended.  
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Adds a control point to the sub-mask specified by the index.
   // Description:
   //    <table>
   //    Parameter  Valid range                                               Default value  Granularity  Dependency 
   //    ---------  --------------------------------------------------------  -------------  -----------  ----------
   //    %PAR0%     [0, ms_kulMaximumNumberOfSubMasks]                        0              Not Limited  None
   //    Position   [-MAX_FLOAT, MAX_FLOAT]. <p>                              0,0            Not Limited  None
   //                The visible range is [-1.0, 1.0]. <p>
   //                An X value of -1.0 positions the control point on <p>   
   //                the left edge of the screen, and 1.0 positions it <p>
   //                on the right edge. A Y value of -1.0 positions the <p>    
   //                control point at the bottom edge of the screen, <p> 
   //                and 1.0 at the top edge. Values greater than 1.0 or <p>     
   //                less than -1.0 can be used, but doing so would <p> 
   //                position the control point outside the visible area <p>  
   //                of the screen.
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the index specified for the sub-mask is greater than the maximum value, 
   //      or if the control points specified for a sub-mask are equal to the maximum value. 
   // Remarks:
   //    - The order that the control points are added is important, as they will be linked in that order to create the shape of the mask. 
   //    - The maximum number of control points per sub-mask is defined by the constant IMvAdvancedMaskEffectSettings::ms_kulMaximumNumberOfControlPointsPerSubMask.
   //    - The maximum number of sub-masks is defined by the constant IMvAdvancedMaskEffectSettings::ms_kulMaximumNumberOfSubMasks.
   //
   virtual HRESULT __stdcall AddControlPointToSubMask
      (
      const unsigned long in_kulSubMaskIndex,      // Specifies the sub-mask.
      const float in_kfControlPointPositionX,      // Specifies the control point's X position.
      const float in_kfControlPointPositionY       // Specifies the control point's Y position.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the mask.
   // Description:
   //    <table>
   //    Parameter  Valid range                                     Default value  Granularity  Dependency 
   //    ---------  ----------------------------------------------  -------------  -----------  ----------
   //    %PAR0%     [0.0, 1.0]. <p>                                 
   //                0.0 means no softness is applied to the mask.  0              Not Limited  None                          
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the amount of softness specified is outside the valid range.
   // Remarks:
   //    - Softness is applied equally on all sub-masks. 
   //
   virtual HRESULT __stdcall SetSoftness
      (
      const float in_kfSoftness  // Specifies the amount of softness.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of opacity for the specified sub-mask.
   // Description:
   //    <table>
   //    Parameter  Valid range                                      Default value  Granularity  Dependency 
   //    ---------  -----------------------------------------------  -------------  -----------  ----------
   //    %PAR0%     [0, ms_kulMaximumNumberOfSubMasks]               0              Not Limited  None
   //    %PAR1%     [0.0, 1.0]. <p>                                  1.0            Not Limited  None
   //                0.0 sets the sub-mask to fully transparent <p>  
   //                and 1.0 sets it to fully opaque.                
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the specified sub-mask index or the opacity are not valid.
   //
   virtual HRESULT __stdcall SetSubMaskOpacity
      (
      const unsigned long in_kulSubMaskIndex,   // Specifies the sub-mask.
      const float in_kfOpacity                  // Specifies the amount of opacity.
      ) = 0;

   //
   // Summary:
   //    Specifies the blend settings to be used on a sub-mask.
   // Description:
   //    <table>
   //    Parameter  Valid range                                       Default value                    Granularity  Dependency 
   //    ---------  ------------------------------------------------  -------------------------------  -----------  ----------
   //    %PAR0%     [0, ms_kulMaximumNumberOfSubMasks]                0                                Not Limited  None
   //    %PAR1%     - keMvSubMaskBlendingOperationAdd: <p>            keMvSubMaskBlendingOperationAdd  Not Limited  None
   //                Adds the current sub-mask to the <p>             
   //                previous sub-masks. <p>                          
   //                - keMvSubMaskBlendingOperationSubtract: <p>                      
   //                Subtracts the current sub-mask from the <p>      
   //                previous sub-masks. <p>                          
   //                - keMvSubMaskBlendingOperationIntersect: <p>      
   //                Specifies the area of the previous sub-mask <p>     
   //                that intersects with the current sub-mask.        
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the specified sub-mask index or blend setting is not valid. 
   // Remarks:
   //    - Sub-masks will be blended in the same order as they appear in the index (sub-mask with index #0, then 
   //      sub-mask with index #1, etc). This becomes especially important when using the Subtract and Intersect blend settings.   
   //
   virtual HRESULT __stdcall SetSubMaskBlendingOperation
      (
      const unsigned long in_kulSubMaskIndex,            // Specifies the sub-mask.
      const EMvSubMaskBlendingOperation in_keOperation   // Specifies the blending operation.
      ) = 0;

   //
   // Summary:
   //    Enables or disables the option to show the matte by using white for displaying the opaque areas, black for the 
   //    transparent areas, and shades of gray for the semi-transparent areas. This is useful for fine-tuning the mask when 
   //    the clip being used is mostly black.    
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Granularity  Dependency 
   //    ---------  -------------  -------------  -----------  ----------
   //    %PAR0%     [true, false]  false          Not Limited  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall ShowMaskOnly
      (
      const bool in_kbShowMaskOnly  // Specifies whether or not to show the matte. 
      ) = 0;

   //
   // Summary:
   //    Specifies whether or not to invert the opaque and transparent areas of the masks. 
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Granularity  Dependency 
   //    ---------  -------------  -------------  -----------  ----------
   //    %PAR0%     [true, false]  false          Not Limited  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall InvertMask
      (
      const bool in_kbInvertMask // Specifies whether or not the opacity is inverted.
      ) = 0;

   //
   // Interface version
   //
   static const unsigned long ms_kulMvAdvancedMaskVersion = 1;
};
#endif