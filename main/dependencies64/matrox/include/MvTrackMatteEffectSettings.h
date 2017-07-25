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

//
// Summary:
//    Describes the matte channel that will be used as the alpha for the source video.
//
enum EMvMatteCompositeType
{
   keMvMatteCompositeTypeInvalid       = 0,  // Invalid value.
   keMvMatteCompositeTypeAlpha         = 1,  // The new alpha value applied to the source video 
                                                // will come from the alpha channel of the track
                                                // matte.
   keMvMatteCompositeTypeLuma0To255    = 2,  // The new alpha value applied to the source video 
                                                // will come from the luma channel of the track 
                                                // matte. The luma values from the track matte will
                                                // be rescaled according to the range [0, 255].
   keMvMatteCompositeTypeLuma16To235   = 3,  // The new alpha value applied to the source video
                                                // will come from the luma channel of the track
                                                // matte. The luma values from the track matte 
                                                // will be rescaled according to the range 
                                                // [16, 235]. The values below 16 will be totally
                                                // transparent and the values over 235 will be 
                                                // totally opaque.
   keMvMatteCompositeTypeLast          = 4   // End of list indocator.
};


//
// Summary:
//    Sets the parameters used by the track matte effect.
//
interface IMvTrackMatteEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the matte composite type.
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if in_eCompositeType value is invalid.
   //
   virtual HRESULT __stdcall SetCompositeType
      (
      EMvMatteCompositeType in_eCompositeType   // Specifies the matte composite you want to use.
      ) = 0;

   //
   // Summary:
   //    Reverses the matte composite (alpha or luma).
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //
   virtual HRESULT __stdcall SetInverseMatte
      (
      bool in_bReverse     // When set to true, the matte composite is reversed.
      ) = 0;

   //
   // Summary:
   //    Updates the track matte settings according to the parameters set by other track matte methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks
   //    - This method ensures the integrity of the effect settings, and must be called whenever track matte effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update() = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvTrackMatteVersion = 1;
};
