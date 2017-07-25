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
//    Sets the parameters used by the old movie effect.
//
interface IMvOldMovieEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Represents the different methods that can be used by the 
   //    IMvOldMovieEffectSettings::SetPreprocessingMode method.
   //
   enum EMvPreprocessingMode
   {
      keMvPreprocessingModeInvalid = 0,      // Invalid value.
      keMvPreprocessingModeRedOnly,          // The value of the red channel of a pixel is directly
                                                // applied to all other color channels.
      keMvPreprocessingModeGreenOnly,        // The value of the green channel of a pixel is 
                                                // directly applied to all other color channels.
      keMvPreprocessingModeBlueOnly,         // The value of the blue channel of a pixel is 
                                                // directly applied to all other color channels.
      keMvPreprocessingModeAlphaOnly,        // The value of the alpha channel of a pixel is
                                                // directly applied to all color channels.
      keMvPreprocessingModeLuma,             // A precise portion of each color channel is added 
                                                // together and the result is applied to every color
                                                // channel. The result should be the precise 
                                                // luminance of the image.
      keMvPreprocessingModeOversaturation,   // Every color channel is directly added and the 
                                                // result is applied to every color channel.
      keMvPreprocessingModeLast,             // End of list indocator.
   };

   //
   // Summary:
   //    Specifies the transform settings (translation, scale, rotation) to be applied to the output.
   // Description:
   //    The world transform matrix should contain all of the information needed for the translation (position), scale, and rotation settings to be 
   //    applied to the output.
   //    <table>
   //    Parameter  Valid range                Granularity  Default value        Dependency 
   //    ---------  -------------------------  -----------  -------------------  ----------
   //    %PAR0%     4x4 floating-point matrix  Not limited  The identity matrix  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetWorldTransform
      (
      SMvMatrix * in_psWorldMatrix   // Pointer that specifies the transform matrix to be used.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source that the old movie effect will be applied to. 
   // Description:
   //    <table>
   //    Parameter  Valid range        Granularity  Default value            Dependency 
   //    ---------  -----------------  -----------  -----------------------  ----------
   //    %PAR0%     [+0.0, MAX_FLOAT]  Not limited  rectangle.left = 0<p>    - rectangle.left + rectangle.right <= Edit Resolution Width.<p>
   //                                                rectangle.top = 0<p>     - rectangle.top + rectangle.bottom <= Edit Resolution Height.
   //                                                rectangle.right = 0<p>   
   //                                                rectangle.bottom = 0
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   //
   virtual HRESULT __stdcall SetCrop
      (
      SMvRectF *in_psCropArea // Specifies the region of the source to use.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of softness to be applied to the borders of the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftness is outside the specified range. 
   //
   virtual HRESULT __stdcall SetSoftness
      (
      float in_fSoftness   // Specifies the relative amount of softness that will be applied.
      ) = 0;

   //
   // Summary:
   //    Sets the radius of the image's round corners. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fCornerRadius is outside the specified range. 
   //
   virtual HRESULT __stdcall SetCornerRadius
      (
      float in_fRadius  // Specifies the relative radius of the round corners.
      ) = 0;

   //
   // Summary:
   //    Sets the number of points used to generate each round corner. 
   // Description:
   //    <table>
   //    Parameter  Valid range       Granularity  Default value  Dependency 
   //    ---------  ----------------  -----------  -------------  ----------
   //    %PAR0%     [+3, +25]         +1           +15            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iNbPointsPerCorner is outside the specified range. 
   //
   virtual HRESULT __stdcall SetNbPointsPerCorner
      (
      int in_iNbPointsPerCorner  // Specifies the number of points per corner that will be used to
                                 // render round corners.
      ) = 0;

   //
   // Summary:
   //    Enables/disables preprocessing (black and white). 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetPreprocess
      (
      bool in_bPreprocess  // Specifies the preprocessing state (on/off).
      ) = 0;

   //
   // Summary:
   //    Sets the preprocessing mode. 
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_ePreprocessingMode is outside the specified range. 
   //
   virtual HRESULT __stdcall SetPreprocessingMode
      (
      EMvPreprocessingMode in_ePreprocessingMode   // Specifies the method that will be used to 
                                                   // compute preprocessing.
      ) = 0;

   //
   // Summary:
   //    Enables/disables manual control of jitter. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Giving "true" as the parameter for this effect bypasses SetJitterProbability. 
   //    - The user has to change only the input parameter of SetJitterOffset to control jitter
   //      movement. 
   //
   virtual HRESULT __stdcall SetJitterIsManualMode
      (
      bool in_bJitterIsManualMode   // Specifies the state (on/off) of jitter manual control.
      ) = 0;

   //
   // Summary:
   //    Sets the maximum jitter offset. 

   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fJitterOffset is outside the specified range. 
   //
   virtual HRESULT __stdcall SetJitterOffset
      (
      float in_fJitterOffset  // Specifies the relative offset of jitter movement.
      ) = 0;

   //
   // Summary:
   //    Sets the probability of jitter occurance. 
   // Description:
   //    <table>
   //    Parameter  Valid range     Granularity  Default value  Dependency 
   //    ---------  --------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +100.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fJitterProbability is outside the specified range. 
   //
   virtual HRESULT __stdcall SetJitterProbability
      (
      float in_fJitterProbability   // Specifies the probability of jitter occurance.
      ) = 0;

   //
   // Summary:
   //    Sets the distance between the main frame and the bottom frame when jitter occurs. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fDistanceBetweenFrames is outside the
   //      specified range. 
   //
   virtual HRESULT __stdcall SetDistanceBetweenFrames
      (
      float in_fDistanceBetweenFrames  // Specifies the relative distance between the current
                                       // frame and the bottom frame when jitter occurs.
      ) = 0;

   //
   // Summary:
   //    Sets frequency of the sine portion of flicker (logarithmic scale). 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [-2.0, +2.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fFlickerFrequency is outside the specified range. 
   //
   virtual HRESULT __stdcall SetFlickerFrequency
      (
      float in_fFlickerFrequency // Specifies the frequency of the sine portion of flicker
                                 // (10 to the power of in_fFlickerFrequency Hz).
      ) = 0;

   //
   // Summary:
   //    Sets the lowest intensity of flicker. 

   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fFlickerLowerBound is outside the specified range. 
   //
   virtual HRESULT __stdcall SetFlickerLowerBound
      (
      float in_fFlickerLowerBound   // Specifies the lowest flicker intensity.
      ) = 0;

   //
   // Summary:
   //    Sets the highest intensity of flicker. 
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fFlickerHigherBound is outside the specified range. 
   //
   virtual HRESULT __stdcall SetFlickerHigherBound
      (
      float in_fFlickerHigherBound  // Specifies the highest flicker intensity.
      ) = 0;

   //
   // Summary:
   //    Sets the proportion of flicker randomness. 
   // Description:
   //    <table>
   //    Parameter  Valid range                                      Granularity  Default value  Dependency 
   //    ---------  -----------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]<p>                                  Not limited  +0.0           None
   //                - +0.0 = Flicker follows a pure sine wave 
   //                  of frequency given by SetFlickerFrequency<p>
   //                - ]+0.0, +1.0[ = Flicker is a mix of sine 
   //                  wave and total randomness between the 
   //                  lowest and highest intensity<p>
   //                - +1.0 = Flicker is randomly generated 
   //                  between the lowest and highest intensity
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fFlickerInterpolationFactor is outside the 
   //      specified range. 
   //
   virtual HRESULT __stdcall SetFlickerInterpolationFactor
      (
      float in_fFlickerInterpolationFactor   // Specifies the proportion of flicker randomness.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of red gain to be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range                                     Granularity  Default value  Dependency 
   //    ---------  ----------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+0, +400]<p>                                   +1           +100, meaning  None 
   //                - +0 = Color is not visible<p>                               color is not 
   //                - ]+0, +100[ = Color intensity is lessened<p>                modified.
   //                - +100 = Color is left as is<p>
   //                - ]+100, +400] = Color is intensified<p>
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iRedCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetRedCGain
      (
      int in_iRedCGain  // Specifies the gain applied to the original image red channel.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of green gain to be applied. 

   // Description:
   //    <table>
   //    Parameter  Valid range                                     Granularity  Default value  Dependency 
   //    ---------  ----------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+0, +400]<p>                                   +1           +100, meaning  None 
   //                - +0 = Color is not visible<p>                               color is not 
   //                - ]+0, +100[ = Color intensity is lessened<p>                modified.
   //                - +100 = Color is left as is<p>
   //                - ]+100, +400] = Color is intensified<p>
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iGreenCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetGreenCGain
      (
      int in_iGreenCGain   // Specifies the gain applied to the original image green channel.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of blue gain to be applied. 
   // Description:
   //    <table>
   //    Parameter  Valid range                                     Granularity  Default value  Dependency 
   //    ---------  ----------------------------------------------  -----------  -------------  ----------
   //    %PAR0%     [+0, +400]<p>                                   +1           +100, meaning  None 
   //                - +0 = Color is not visible<p>                               color is not 
   //                - ]+0, +100[ = Color intensity is lessened<p>                modified.
   //                - +100 = Color is left as is<p>
   //                - ]+100, +400] = Color is intensified<p>
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iBlueCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetBlueCGain
      (
      int in_iBlueCGain // Specifies the gain applied to the original image blue channel.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of red to be added to the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value      Dependency 
   //    ---------  ---------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [-255, +255]<p>                          +1           +0, meaning color  None 
   //                - -255 = Color is not visible<p>                      is not modified 
   //                - ]-255, +0[ = Color is substracted<p>
   //                - +0 = Color is left as is<p>
   //                - ]+0, +255] = Color is added
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iRedCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetRedCAdd
      (
      int in_iRedCAdd   // Specifies the amount of red to be added to the original image.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of green to be added to the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value      Dependency 
   //    ---------  ---------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [-255, +255]<p>                          +1           +0, meaning color  None 
   //                - -255 = Color is not visible<p>                      is not modified 
   //                - ]-255, +0[ = Color is substracted<p>
   //                - +0 = Color is left as is<p>
   //                - ]+0, +255] = Color is added
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iGreenCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetGreenCAdd
      (
      int in_iGreenCAdd // Specifies the amount of green to be added to the original image.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of blue to be added to the image. 
   // Description:
   //    <table>
   //    Parameter  Valid range                              Granularity  Default value      Dependency 
   //    ---------  ---------------------------------------  -----------  -----------------  ----------
   //    %PAR0%     [-255, +255]<p>                          +1           +0, meaning color  None 
   //                - -255 = Color is not visible<p>                      is not modified 
   //                - ]-255, +0[ = Color is substracted<p>
   //                - +0 = Color is left as is<p>
   //                - ]+0, +255] = Color is added
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iBlueCGain is outside the specified range. 
   //
   virtual HRESULT __stdcall SetBlueCAdd
      (
      int in_iBlueCAdd  // Specifies the amount of blue to be added to the original image.
      ) = 0;

   //
   // Summary:
   //    Sets the current position in time (frame number).
   // Description:
   //    The value must be a double number in which the integer part represents the current frame.
   //    The decimal portion can represent anything, such as the field number, but it will not be 
   //    taken into account by the effect. 
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, DBL_MAX]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - The integer portion represents the current frame, and the decimal portion is ignored. 
   //
   virtual HRESULT __stdcall SetProgression
      (
      double in_dProgression  // Specifies the current position in time.
      ) = 0;

   //
   // Summary:
   //    Sets the random generator seed. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1023]  +1           +100           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - INVALID_PARAMETER, if the parameter in_iSeed is outside the specified range. 
   //
   virtual HRESULT __stdcall SetSeed
      (
      int in_iSeed   // Specifies the seed that will be used by the random generator.
      ) = 0;

   //
   // Summary:
   //    Sets the maximum amount of streak particles that will be visible at the same time. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +10]    +1           +0             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iStreakAmount is outside the specified range. 
   //
   virtual HRESULT __stdcall SetStreakAmount
      (
      int in_iStreakAmount // Specifies the maximum number of streak particles visible at any given time.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of the streak particles.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fStreakOpacity is outside the specified range. 
   //
   virtual HRESULT __stdcall SetStreakOpacity
      (
      float in_fStreakOpacity // Specifies the opacity of the streak particles.
      ) = 0;

   //
   // Summary:
   //    Sets the color of the streak particles. 
   // Description:
   //    <table>
   //    Parameter  Valid range                                    Granularity  Default value                   Dependency 
   //    ---------  ---------------------------------------------  -----------  ------------------------------  ----------
   //    %PAR0%     From 0x00000000 (black) to 0xFFFFFFFF (white)  Not limited  Black (ARGB value: 0x00000000)  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Alpha is not taken into account in this method. 
   //    - The order of the different channels is as follows:
   //<CODE>     0x00     00     00     00
          //     (alpha) (red) (green) (blue)</CODE>
   //
   virtual HRESULT __stdcall SetStreakColor
      (
      unsigned long in_ulColor   // Specifies the color of the streak particles.
      ) = 0;

   //
   // Summary:
   //    Sets the maximum amount of dust particles visible at the same time. 

   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +50]    +1           +0             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iDustAmount is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDustAmount
      (
      int in_iDustAmount   // Specifies the maximum amount of dust particles visible at any given time.
      ) = 0;           

   //
   // Summary:
   //    Sets the maximum number of consecutive frames that dust particles will stay still. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +50]    +1           +1             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iDustLifetime is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDustLifetime
      (
      int in_iDustLifetime // Specifies the maximum number of frames that dust particles will stay still.
      ) = 0;         

   //
   // Summary:
   //    Sets the opacity of dust particles. 

   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fDustOpacity is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDustOpacity
      (
      float in_fDustOpacity   // Specifies the opacity of the dust particles.
      ) = 0;

   //
   // Summary:
   //    Sets the color of dust particles. 
   // Description:
   //    <table>
   //    Parameter  Valid range                                    Granularity  Default value                   Dependency 
   //    ---------  ---------------------------------------------  -----------  ------------------------------  ----------
   //    %PAR0%     From 0x00000000 (black) to 0xFFFFFFFF (white)  Not limited  Black (ARGB value: 0x00000000)  None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   // Remarks:
   //    - Alpha is not taken into account in this method. 
   //    - The order of the different channels is as follows:
   //<CODE>     0x00     00     00     00
         //     (alpha) (red) (green) (blue)</CODE>
   //
   virtual HRESULT __stdcall SetDustColor
      (
      unsigned long in_ulColor   // Specifies the color of the dust particles.
      ) = 0;            

   //
   // Summary:
   //    Enables/disables the presence of a fixed particle on the image. 
   // Description:
   //    <table>
   //    Parameter   Valid range    Default value  Dependency 
   //    ----------  -------------  -------------  ----------
   //    %PAR0%      {true, false}  false          None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //
   virtual HRESULT __stdcall SetDustBoolFixedParticle
      (
      bool in_bIsFixedParticle   // Specifies the fixed particle state.
      ) = 0;

   //
   // Summary:
   //    Sets the fixed particle number (there are 68 particles per GFX file). 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +67]    +1           +0             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iFixedParticleNumber is outside the specified range. 
   // Remarks
   //    - Particles 0 to 31 are 16×6 pixels in SD GFX files and 32×32 in HD GFX files. 
   //    - Particles 32 to 55 are 32×32 pixels in SD GFX files and 64×64 in HD GFX files. 
   //    - Particles 56 to 63 are 64×64 pixels in SD GFX files and 128×128 in HD GFX files. 
   //    - Particles 64 to 67 are 128×128 pixels in SD GFX files and 256×256 in HD GFX files. 
   //
   virtual HRESULT __stdcall SetDustFixedParticleNumber
      (
      int in_iFixedParticleNumber   // Specifies the fixed particle number.
      ) = 0;

   //
   // Summary:
   //    Sets the fixed particle horizontal position. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +67]    +1           +0             None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iFixedParticleNumber is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDustFixedParticleXPos
      (
      float in_fFixedParticleXPos   // Specifies the fixed particle number.
      ) = 0;

   //
   // Summary:
   //    Sets the fixed particle vertical position.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fFixedParticleYPos is outside the
   //      specified range.
   //
   virtual HRESULT __stdcall SetDustFixedParticleYPos
      (
      float in_fFixedParticleYPos   // Specifies the relative vertical position of the fixed dust particle.
      ) = 0;

   //
   // Summary:
   //    Sets the opacity of noise pattern.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  +0.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fNoiseOpacity is outside the specified
   //      range.
   //
   virtual HRESULT __stdcall SetNoiseOpacity
      (
      float in_fNoiseOpacity  // Specifies the opacity of the noise particles.
      ) = 0;

   //
   // Summary:
   //    Sets the exact number of consecutive frames that noise pattern will stay still.
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +40]    +1           +1             None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_iNoiseLifetime is outside the specified
   //      range.
   //
   virtual HRESULT __stdcall SetNoiseLifetime
      (
      int in_iNoiseLifetime   // Specifies the number of frames that noise pattern will stay still.
      ) = 0;

   //
   // Summary:
   //    Sets the color of noise pattern.
   // Description:
   //    <table>
   //    Parameter  Valid range                                    Granularity  Default value                  Dependency 
   //    ---------  ---------------------------------------------  -----------  -----------------------------  ----------
   //    %PAR0%     From 0x00000000 (black) to 0xFFFFFFFF (white)  Not limited  Black (ARGB value:0x00000000)  None
   //    </table>
   // Return value:
   //    - MV_NOERROR, if no error occurs.
   // Remarks:
   //    - Alpha is not taken into account in this method.
   //    - The order of the different channels is as follows:
   //<CODE>     0x00     00     00     00
         //     (alpha) (red) (green) (blue)</CODE>
   virtual HRESULT __stdcall SetNoiseColor
      (
      unsigned long in_ulNoiseColor // Specifies the color of noise pattern.
      ) = 0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvOldMovieVersion = 1;
};
