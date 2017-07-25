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
#include "mvDefinitions.h"
#include "mvFlex3DDeviceApi.h"


//
// Summary:
//    Sets the parameters used by the multi-camera effect.
//
interface IMvMultiCamEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the current active camera. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+1, +4]          +1           +1             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulCurrentCamera is outside the specified range. 
   //
   virtual HRESULT __stdcall SetCurrentCamera
      (
      unsigned long in_ulCurrentCamera // Specifies the current active camera. The cameras are
                                       // labeled as follows: (clockwise from top left) camera 1, 
                                       // camera 2, camera 3, camera 4.
      ) = 0;

   //
   // Summary:
   //    Used to activate or deactivate the preview display. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  true           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetShowPreviewMonitor
      (
      bool in_bShowPreviewMonitor   // Specifies the status of the preview display. When set to 
                                    // true, the preview display is activated.
      ) = 0;

   //
   // Summary:
   //    Sets the status (on/off) of a camera. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Granularity  Default value  Dependency 
   //    ----------  -------------  -----------  -------------  ----------
   //    %PAR0%      [1, 4]         +1           +1             None 
   //    %PAR1%      {true, false}  N/A          true           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulSelectedCamera is outside the specified range. 
   //
   virtual HRESULT __stdcall SetCameraStatus
      (
      unsigned long in_ulSelectedCamera,  // Specifies the camera to select in order to change its 
                                             // status. The cameras are labeled as follows: 
                                             // (clockwise from top left) camera 1, camera 2, 
                                             // camera 3, camera 4.
      bool          in_bCameraIsOn        // When set to true, the selected camera is on.
      ) = 0;

   //
   // Summary:
   //    Sets the border color of the current active camera. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value                              Dependency 
   //    ---------  -----------  -----------  -----------------------------------------  ----------
   //    %PAR0%     Any color    Not limited  ARGB value: 0x00000000, Transparent black  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulCurrentCamera is outside the specified range. 
   //
   virtual HRESULT __stdcall SetBorderColor
      (
      const SMvColor &in_krColor // Specifies the value of the border color.
      ) = 0;

   //
   // Summary:
   //    Sets the border width of the current active camera. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +16]    +1           +1             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulBorderWidth is outside the specified range. 
   //
   virtual HRESULT __stdcall SetBorderWidth
      (
      unsigned long in_ulBorderWidth   // Specifies the border width in pixels, where zero
                                       // (0) means no border.
      ) = 0;

   //
   // Summary:
   //    Updates the multi-camera effect settings according to the parameters set by other multi-camera methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever multi-camera effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update() = 0;
   
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvMultiCamVersion = 1;
};
