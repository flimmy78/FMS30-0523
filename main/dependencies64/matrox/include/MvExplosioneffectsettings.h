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
// $Archive: /VP/FLEXVIDEO/VIDEOEFFECTS/mvfExplosion/Inc/MvExplosioneffectsettings.h $
//===============================================================================

#pragma once

#ifndef _MvfExplosionSettings_h_GZ094429A0505533163590H22251930191G_
#define _MvfExplosionSettings_h_GZ094429A0505533163590H22251930191G_

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceAPI.h"

//
// Summary:
//    Sets the parameters used by the explosion effect. 
//
interface IMvExplosionEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to apply to the video output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to video output.  
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value        Dependency 
   //    ---------  ---------------------------  -----------  -------------------  ----------
   //    %PAR0%     4 x 4 floating-point matrix  Not limited  The identity matrix  None    
   // </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetSourceTransform(SMvMatrix* in_psSourceTransform) = 0;

   //
   // Summary:
   //    Sets the amount of cropping to apply to the edges of the clip, which determines the region on which the explosion effect will be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value         Dependency 
   //    ---------  ---------------------------------------  -----------  --------------------  --------------------------------------
   //    %PAR0%     Left [0.0, EditingResolutionWidth]<p>    1.0          0.0, meaning no crop  Left+Right < EditingResolutionWidth<p>
   //                Right [0.0, EditingResolutionWidth]<p>                                      Top+Bottom < EditingResolutionHeight
   //                Top [0.0, EditingResolutionHeight]<p> 
   //                Bottom [0.0, EditingResolutionHeight] 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - All other explosion effect settings are applied to the region of the source set by this method.   
   //
   virtual HRESULT __stdcall SetSourceCrop(SMvRectF* in_psSourceCrop) = 0;

   //
   // Summary:
   //    Sets the progression of the explosion. A value of 0.0 specifies the beginning of the explosion, 0.5 is the 
   //    mid-point of the explosion, and 1.0 is the end of the explosion.   
   // Description:
   //    The explosion progression can be set at any frame. For example, you can set the progression to 0.5 at the 
   //    first frame to make your explosion start only at its mid-point.  
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fProgression is outside the specified range.
   //
   virtual HRESULT __stdcall SetProgression(float in_fProgression) = 0;
   
   //
   // Summary:
   //    Sets the spread of the explosion, which determines the point at which the particles start to explode. 
   // Description:
   //    The spread affects the explosion's sequence. The higher the spread value, the closer to the beginning of the clip 
   //    the particles start to explode. At a value of 0.0, the explosion will follow the sequence defined in the GFX. At 
   //    a value of 1.0, the particles will start to explode at the first frame of the clip.
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSpread is outside the specified range.
   //
   virtual HRESULT __stdcall SetSpread(float in_fSpread) = 0;
   
   //
   // Summary:
   //    Sets the speed at which the particles explode. This value also affects the speed of the particles' individual rotation and movement after 
   //    the explosion is applied.  
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fParticleSpeed is outside the specified range.
   //
   virtual HRESULT __stdcall SetParticleSpeed(float in_fParticleSpeed) = 0;
   
   //
   // Summary:
   //    (EXCLUDE FROM DOCUMENTATION) Sets the border softness of the video clip.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fBorderSoftness is outside the specified range.
   //
   virtual HRESULT __stdcall SetBorderSoftness(float in_fBorderSoftness) = 0;
   
   //
   // Summary:
   //    Sets the random seed of the explosion, which determines the random behavior of the explosion pattern. 
   // Description:
   //    Each value in the specified range (0 to 100) represents a different random pattern. Setting a 
   //    random seed will allow you to reproduce the same explosion pattern. Changing the seed will 
   //    change the random behavior of the explosion.
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  0.0            None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ulRandomSeed is outside the specified range.
   //
   virtual HRESULT __stdcall SetRandomSeed(unsigned long in_ulRandomSeed) = 0;

   //
   // Summary:
   //    Specifies whether or not the vanishing particle feature is enabled. If enabled, the particles 
   //    will vanish after they explode. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Default value  Granularity  Dependency 
   //    ---------  -----------  -------------  -----------  ----------
   //    %PAR0%     [0, 1]       0              N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_bVanishing is not 0 or 1.
   //
   virtual HRESULT __stdcall SetVanishingParticles(bool in_bVanishing) = 0;
   
   //
   // Summary:
   //    Specifies whether or not to apply softness to the borders of the particles.
   // Description:
   //    <table>
   //    Parameter   Valid range  Default value  Granularity  Dependency 
   //    ----------  -----------  -------------  -----------  ----------
   //    %PAR0%      [0, 1]       0              N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_bParticleSoftness is not 0 or 1.
   //
   // Remarks:
   //    - The degree of particle softness is defined in the TGA file from which the explosion's GFX is 
   //      created. The degree of softness cannot be parameterized in this method.      
   //
   virtual HRESULT __stdcall SetParticleSoftness(bool in_bParticleSoftness) = 0;
   
   //
   // Summary:
   //    Specifies whether or not to reverse the explosion sequence defined in the GFX.
   // Description:
   //    <table>
   //    Parameter   Valid range  Default value  Granularity  Dependency 
   //    ----------  -----------  -------------  -----------  ----------
   //    %PAR0%      [0, 1]       0              N/A          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_bReverseSeq is not 0 or 1.
   //
   virtual HRESULT __stdcall SetReverseSequence(bool in_bReverseSeq) = 0;

   //
   // Summary:
   //    Sets the speed vector of the explosion, which determines the overall direction and affects the velocity of the explosion pattern.
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value    Dependency 
   //    ---------  ------------------------  -----------  ---------------  ----------
   //    %PAR0%     fx [-5000.0, 5000.0]<p>   Not limited  {0.0, 0.0, 0.0}  None
   //                fy [-5000.0, 5000.0]<p>                                                   
   //                fz [-5000.0, 5000.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetSpeedVector(SMvVector3* in_psSpeed) = 0;

   //
   // Summary:
   //    Sets the gravity vector of the explosion, which affects the overall direction and velocity of the explosion over time.
   //    Particles accelerate in the direction of the specified gravity vector. 
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value       Dependency 
   //    ---------  ------------------------  -----------  ------------------  ----------
   //    %PAR0%     fx [-5000.0, 5000.0]<p>   Not limited  {0.0, 0.0, -300.0}  None
   //                fy [-5000.0, 5000.0]<p>                                                   
   //                fz [-5000.0, 5000.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetGravityVector(SMvVector3* in_psGravity) = 0;

   //
   // Summary:
   //    Sets the dispersion vector of the explosion, which determines the scattering range of the explosion pattern. 
   //    This method adds randomness to the particles' rotation and movement after the explosion occurs.
   // Description:
   //    <table>
   //    Parameter  Valid range               Granularity  Default value       Dependency 
   //    ---------  ------------------------  -----------  ------------------  ----------
   //    %PAR0%     fx [-5000.0, 5000.0]<p>   Not limited  {0.0, 0.0, -300.0}  None
   //                fy [-5000.0, 5000.0]<p>                                                   
   //                fz [-5000.0, 5000.0]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if the pointer is NULL.
   //
   virtual HRESULT __stdcall SetDispersionVector(SMvVector3* in_psDispersion) = 0;

   static const unsigned long ms_kulMvfExplosionVersion = 1;
};
#endif