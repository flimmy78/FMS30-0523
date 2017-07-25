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
#include "mvMatrix.h"


//
// Summary:
//    Sets the parameters used by the anamorphic effect. 
//
interface IMvAnamorphicEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the aspect ratio of the original clip, before it is converted to the destination aspect ratio. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     ]0.0, MAX_FLOAT]  Not limited  1.3333         None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetSourceAspectRatio
      (
      float in_fAspectRatio   // Specifies the clip's aspect ratio before it is converted to the destination aspect ratio.  
      ) = 0;

   //
   // Summary:
   //    Sets the destination aspect ratio to which the clip will be converted. 
   // Description:
   //    This method converts the original aspect ratio of the clip to a new aspect ratio determined by the user. 
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     ]0.0, MAX_FLOAT]  Not limited  1.7777         None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetDestinationAspectRatio
      (
      float in_fAspectRatio   // Specifies the destination aspect ratio.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of scaling to apply to the clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range                               Default value  Granularity  Dependency 
   //    ---------  ----------------------------------------  -------------  -----------  ----------
   //    %PAR0%     [0.0, 1.0] positive floating-point value  0.0            Not limited  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetScaleAmount
      (
      float in_fScaleAmount   // Specifies the amount of scaling to apply to the clip. If the value is 0, 
                              // the entire clip will be visible, but black bars will appear above, below, 
                              // or on either side of the clip, depending on its video standard. If the 
                              // value is 1, the clip will fill the entire area defined by ERes (editing resolution).  
      ) = 0;

   //
   // Summary:
   //    Sets the amount of vertical or horizontal translation to apply to the clip.  
   // Description:
   //    The PanScan parameter is used when the sides of the image extend outside of the viewing area. 
   //    <table>
   //    Parameter  Valid range                               Default value   Granularity  Dependency 
   //    ---------  ----------------------------------------  --------------  -----------  ----------
   //    %PAR0%     [0.0, 1.0] positive floating-point value  0.5 (centered)  Not limited  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall SetPanScanAmount
      (
      float in_fPanScanAmount // Specifies the pan and scan amount. When scaled horizontally, 0 displays the 
                              // left side of the source, and 1 displays the right side. When scaled vertically, 
                              // 0 displays the top of the source, 1 displays the bottom.      
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source on which the anamorphic effect will be applied. 
   // Description:
   // <table>
   // Parameter  Valid range                                  Default value          Granularity  Dependency 
   // ---------  -------------------------------------------  ---------------------  -----------  ----------
   // %PAR0%     [0.0, MAX_FLOAT] Rectangle composed of four  rectangle.left = 0,    Not limited  None 
   //             positive floating-point values               rectangle.top = 0,
   //                                                          rectangle.right = 0,
   //                                                          rectangle.bottom = 0
   // </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - rectangle.left + rectangle.right <= ERes Width. 
   //    - rectangle.top + rectangle.bottom <= ERes Height. 
   //
   virtual HRESULT __stdcall SetSourceCrop
      (
      SMvRectF *in_psCrop  // Pointer that specifies the region of the source to use. 
      ) = 0;

   //
   // Summary:
   //    Enables Global View, which displays the whole source clip, and a colored rectangle around the region that will be visible after the effect is applied. 
   // Description:
   //    This feature is helpful when Size is not set to 0. The part of the visible region onscreen
   //    is contained in a colored rectangle. The crop region is also displayed with a colored 
   //    rectangle. 
   // <table>
   // Parameter   Valid range                                       Default value          Granularity  Dependency 
   // ----------  ------------------------------------------------  ---------------------  -----------  ----------
   // %PAR0%      {true, false}                                     false                  N/A          None 
   // %PAR1%      Any valid color, or NULL if in_bEnableGlobalView  NULL                   Not limited  None 
   //              is false
   // %PAR1%      Any valid color, or NULL if in_bEnableGlobalView  NULL                   Not limited  None 
   //              is false
   // </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall EnableGlobalView
      (
      unsigned long in_bEnableGlobalView, // Enables/disables global view.

      SMvColor *in_psViewRectangle,       // Pointer that specifies the color of the rectangle. This value can be set 
                                          // to NULL if in_bEnableGlobalView is false. 

      SMvColor *in_psViewCache            // Pointer that specifies the color value of the cache to be multiplied by 
                                          // the non-visible region. This value can be set to NULL if in_bEnableGlobalView is false.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvAnamorphicVersion = 1;
};
