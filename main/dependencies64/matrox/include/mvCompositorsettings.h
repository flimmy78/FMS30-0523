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

//
// Summary:
//    Sets the values for the compositor effect (hardware or software). 
//
interface IMvCompositorSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the opacity of the layer.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fLayerOpacity is not within the specified range. 
   //
   virtual HRESULT __stdcall SetLayerOpacity
      (
      float in_fLayerOpacity  // Indicates the transparency factor that is applied to the layer. <p> The range is from 0 to 1, where 0 indicates
                              // completely transparent and 1 indicates completely opaque. The default value is 1. <p>
                              // <b> Note: </b> The granularity is not limited.
      ) = 0;
   //
   // Summary:
   //    Indicates the IMvCompositorSettings interface version.
   //
   static const unsigned long ms_kulVersion = 1;
};

//
// Summary:
//    Sets the chroma filter of the onboard compositor. 
//
interface IMvHardwareCompositorSettings : public IMvCompositorSettings
{
   //
   // Summary:
   //    Indicates whether or not the chroma filter of the onboard compositor is enabled. Applies to ARGB layers only. 
   // Return value:
   //    MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the layer is other than ARGB, the chroma filter is not applied.
   //    - Can be used to reduce color distortions around the edges of objects in an image as a result of chroma subsampling from ARGB to YUV color space.
   //
   virtual HRESULT __stdcall SetLayerChromaFilterARGB
      (
      bool in_bFilterEnabled  // If true, enables the chroma filter of the onboard compositor. <p> The default value is false.
      ) = 0;
};


//
// Summary:
//    Gets the settings used by the compositor. 
//
interface IMvCompositorSettingsInternal : public IUnknown
{
   //
   // Summary:
   //    Gets the opacity of the layer.
   // Return value:
   //    MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetLayerOpacity
      (
      float *out_pfLayerOpacity  // Pointer to the opacity value of the layer indicating the transparency factor that is applied to the layer.
      ) = 0;
   //
   // Summary:
   //    Gets the chroma filter settings of the layer.
   // Return value:
   //    MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetLayerChromaFilterARGB
      (
      bool *out_pbFilterEnabled  // Pointer to the boolean value indicating whether or not the chroma filter is enabled.
      ) = 0;
};

