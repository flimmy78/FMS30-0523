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
#include "MvFlexAPIPublicSDK.h"


//
// Summary:
//    Sets the parameters used by the positioner effect.
//
interface IMvPositionerEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the central position of the input contents inside the coordinate system of the
   //    input surface.
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value                Dependency 
   //    ---------  ------------------------  -----------  ---------------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, +MAX_FLOAT]  +1.0         +0.0, meaning the contents'  None
   //                                                       center matches the input
   //                                                       surface's center position
   //                                                       on the x axis
   //    %PAR1%     [-MAX_FLOAT, +MAX_FLOAT]  +1.0         +0.0, meaning the contents'  None
   //                                                       center matches the input
   //                                                       surface's center position
   //                                                       on the y axis
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the source coordinates have been set.
   //    - MV_ERROR, if an input parameter is invalid.
   //
   virtual HRESULT __stdcall SetSourceCoordinates
      (
      float in_fHorizontalCoordinateInPixel, // Specifies the float value representing the center
                                                // position of the input contents on the x axis.
      float in_fVerticalCoordinateInLine     // Specifies the float value representing the center 
                                                // position of the input contents on the y axis.
      ) = 0;

   //
   // Summary:
   //    Specifies the position of the source contents into the destination surface. This 
   //    represents the destination's center coordinates.
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value                Dependency 
   //    ---------  ------------------------  -----------  ---------------------------  ----------
   //    %PAR0%     [-MAX_FLOAT, +MAX_FLOAT]  +1.0         +0.0, meaning the contents'  None
   //                                                       center matches the input
   //                                                       surface's center position
   //                                                       on the x axis
   //    %PAR1%     [-MAX_FLOAT, +MAX_FLOAT]  +1.0         +0.0, meaning the contents'  None
   //                                                       center matches the input
   //                                                       surface's center position
   //                                                       on the y axis
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the destination coordinates have been set.
   //    - MV_ERROR, if an input parameter is invalid.
   //
   virtual HRESULT __stdcall SetDestinationCoordinates
      (
      float in_fHorizontalOffsetInPixel,  // Specifies the float value representing the 
                                             // destination's center position on the x axis.
      float in_fVerticalOffsetInLine      // Specifies the float value representing the 
                                             // destination's center position on the y axis.
      ) = 0;

   //
   // Summary:
   //    Specifies the size of the destination window.
   // Description:
   //    <table>
   //    Parameter  Valid range         Granularity  Default value              Dependency 
   //    ---------  ------------------  -----------  -------------------------  ----------
   //    %PAR0%     [+0.0, +MAX_FLOAT]  +1.0         Width equal to the input   None
   //                                                 surface's size in x
   //    %PAR1%     [+0.0, +MAX_FLOAT]  +1.0         height equal to the input  None
   //                                                 surface's size in y
   //    </table>
   // Return value:
   //    - MV_NOERROR, if the region has been set.
   //    - MV_ERROR, if an input parameter is invalid.
   //
   virtual HRESULT __stdcall SetRegion
      (
      float in_fWidthInPixel,    // Specifies the float value representing the contents' size in x.
      float in_fHeighInLine      // Specifies the float value representing the contents' size in y.
      ) = 0;

   //
   // Summary:
   //    Specifies the input surface parameters.
   // Remarks: 
   //    - This function is a provision for future optimization. It is not used in the current release.
   //
   virtual HRESULT __stdcall SetInputSurfaceDescriptor
      (
      SMvSurfaceDescription * in_poFlexInputDesc   // 
      ) = 0;

   //
   // Summary:
   //    Specifies the output surface parameters.
   // Remarks: 
   //    - This function is a provision for future optimization. It is not used in the current release.
   //
   virtual HRESULT __stdcall SetOutputSurfaceDescriptor
      (
      SMvSurfaceDescription * in_poFlexOutputDesc  // 
      ) = 0;

   //
   // Summary:
   //    Updates the positioner effect settings according to the parameters set by other positioner methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever positioner effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update() = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulVersion = 1;
};
