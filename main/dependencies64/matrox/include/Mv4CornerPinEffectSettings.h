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
//    Sets the parameters used by the 4-corner pin effect. 
//
interface IMv4CornerPinEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the region of the source clip on which the 4-corner pin effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value            Dependency 
   //    ---------  --------------  -----------  -----------------------  ----------
   //    %PAR0%     [0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                             rectangle.top = 0<p>     rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                             rectangle.right = 0<p>
   //                                             rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetCrop
      (
      SMvRectF * in_psCropArea   // Specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the top-left corner. 
   // Description:
   //    <table>
   //    Parameter  Valid range              Granularity  Default value             Dependency 
   //    ---------  -----------------------  -----------  ------------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]  Not limited  \x = -EditRes.Width/2<p>  None
   //                                                      y = EditRes.Height/2
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetTopLeftCorner
      (
      SMvPointF * in_psCorner    // Specifies the position (x,y) of the corner.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the top-right corner. 
   // Description:
   //    <table>
   //    Parameter  Valid range              Granularity  Default value            Dependency 
   //    ---------  -----------------------  -----------  -----------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]  Not limited  \x = EditRes.Width/2<p>  None
   //                                                      y = EditRes.Height/2
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetTopRightCorner
      (
      SMvPointF * in_psCorner    // Specifies the position (x,y) of the corner.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the bottom-left corner. 
   // Description:
   //    <table>
   //    Parameter  Valid range              Granularity  Default value             Dependency 
   //    ---------  -----------------------  -----------  ------------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]  Not limited  \x = -EditRes.Width/2<p>  None
   //                                                      y = -EditRes.Height/2
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetBottomLeftCorner
      (
      SMvPointF * in_psCorner    // Specifies the position (x,y) of the corner.
      ) = 0;

   //
   // Summary:
   //    Sets the position of the bottom-right corner. 
   // Description:
   //    <table>
   //    Parameter  Valid range              Granularity  Default value            Dependency 
   //    ---------  -----------------------  -----------  -----------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, MAX_FLOAT]  Not limited  \x = EditRes.Width/2<p>  None
   //                                                      y = -EditRes.Height/2
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetBottomRightCorner
      (
      SMvPointF * in_psCorner    // Specifies the position (x,y) of the corner.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to apply to the edges of the video clip.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value             Dependency 
   //    ---------  ------------  -----------  ------------------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0, meaning no softness  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_INVALID_POINTER, if the parameter in_fSoftness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetSoftness
      (
      float in_fSoftness         // Specifies the amount of softness as a percentage.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of perspective corrected softness that will be added to the video clip.
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
   //    - Unlike the standard softness for this effect, the size of the perspective corrected 
   //      softness will not be affected by transformation/deformation of the video clip. 
   //
   virtual HRESULT __stdcall SetPerspectiveCorrectedSoftness
      (
      float in_fSoftness   // Specifies the amount of perspective corrected softness as a percentage.
      ) = 0;

   //
   // Summary:
   //    Enables/disables show frame mode, which replaces the video clip with a colored rectangular area 
   //    that can be used as a viewing aid to help position the clip.    
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall EnableShowFrame
      (
      bool in_bIsShowFrameEnabled   // If true, show frame mode is enabled.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the rectangular area that replaces the video clip when show frame mode is enabled.  
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     Any color         Not limited  Red            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetShowFrameColor
      (
      SMvColor * in_psColor   // Pointer that specifies the color of the rectangular frame.
      ) = 0;

   //
   // Summary:
   //    Enables/disables cursor mode, where a different colored cursor is displayed on each corner of the video clip.  
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The top-left corner's cursor is red. 
   //    - The top-right corner's cursor is green. 
   //    - The bottom-left corner's cursor is blue. 
   //    - The bottom-right corner's cursor is orange. 
   //
   virtual HRESULT __stdcall EnableCursorMode
      (
      bool in_bIsCursorModeEnabled  // If true, cursor mode is enabled.
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
   static const unsigned long ms_kulMv4CornerPinVersion = 1;
};
