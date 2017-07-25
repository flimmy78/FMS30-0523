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

#include <wtypes.h>

//
// Summary:
//    Helper class to initialize the mid tones, shadows, and highlights grid for the color correction effect.
// See also:
//    IMvColorCorrectionEffectSettings
//
class CMvColorCorrectionHelper
{  
//DOM-IGNORE-BEGIN
private:
   CMvColorCorrectionHelper(CMvColorCorrectionHelper&);
   void operator=(CMvColorCorrectionHelper&){};
//DOM-IGNORE-END

public:
   //
   // Summary:
   //    Default constructor.
   //
   CMvColorCorrectionHelper();

   //
   // Summary:
   //    Default destructor.
   //
   virtual ~CMvColorCorrectionHelper();
   
   //
   // Summary:
   //    This method is used to get the default midtones grid. 
   // Description:
   //    <table>
   //    Parameter  Valid range                       Granularity  Default value                   Dependency 
   //    ---------  --------------------------------  -----------  ------------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]                 Not limited  None                            None
   //    %PAR1%     g_kulMvColorCorrectionGridSize    Integer      g_kulMvColorCorrectionGridSize  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   //    - MV_E_INVALID_PARAMETER, if in_uiGridSize is not equal to IMvColorCorrectionEffectSettings::ms_kulGridsize. 
   //
   HRESULT FillDefaultMidtonesGrid
   (
      float out_afGrid[],           // Destination of the generated grid of size in_uiGridSize.
      unsigned int in_uiGridSize    // Size of the generated grid. Must pass IMvColorCorrectionEffectSettings::ms_kulGridsize.
   );

   //
   // Summary:
   //    This method is used to get the default shadows and highlights grid. 
   // Description:
   //    <table>
   //    Parameter  Valid range                       Granularity  Default value                   Dependency 
   //    ---------  --------------------------------  -----------  ------------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]                 Not limited  None                            None
   //    %PAR1%     g_kulMvColorCorrectionGridSize    Integer      g_kulMvColorCorrectionGridSize  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   //    - MV_E_INVALID_PARAMETER, if in_uiGridSize is not equal to IMvColorCorrectionEffectSettings::ms_kulGridsize
   //
   HRESULT FillDefaultShadHighGrid
   (
      float out_afGrid[],           // Destination of the generated grid of size in_uiGridSize.
      unsigned int in_uiGridSize    // Size of the generated grid. Must pass IMvColorCorrectionEffectSettings::ms_kulGridsize.
   );

   //
   // Summary:
   //    This method is used to get the default luminance grid. 
   // Description:
   //    <table>
   //    Parameter  Valid range                       Granularity  Default value                   Dependency 
   //    ---------  --------------------------------  -----------  ------------------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]                 Not limited  None                            None
   //    %PAR1%     g_kulMvColorCorrectionGridSize    Integer      g_kulMvColorCorrectionGridSize  None
   //    %PAR2%     [+0.0, +1,0]                      Not limited  +0.0                            None
   //    %PAR3%     [+0.0, +1.0]                      Not limited  +0.0                            None
   //    %PAR4%     [+0.0, +1.0]                      Not limited  +0.0                            None
   //    %PAR5%     [+0.0, +1.0]                      Not limited  +0.0                            None
   //    %PAR6%     [+0.0, +2.0[                      Not limited  +1.0                            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the parameter in_afGrid is NULL. 
   //    - MV_E_INVALID_PARAMETER, if in_uiGridSize is not equal to g_kulMvColorCorrectionGridSize. 
   //
   HRESULT FillLuminanceGrid
   (
      float out_afGrid[],           // Destination of the generated grid of size in_uiGridSize.
      unsigned int in_uiGridSize,   // Size of the generated grid. Must pass IMvColorCorrectionEffectSettings::ms_kulGridsize.
      float in_fInputBlackLevel,    // Specifies the normalized input black level.
      float in_fOutputBlackLevel,   // Specifies the normalized output black level.
      float in_fInputWhiteLevel,    // Specifies the normalized input white level.
      float in_fOutputWhiteLevel,   // Specifies the normalized output white level.
      float in_fGammaFactor         // Sets the gamma factor.
   );
};
