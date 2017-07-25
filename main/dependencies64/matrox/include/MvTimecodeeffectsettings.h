//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2006. All rights reserved. 
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

#pragma once

#include "mvBaseCOM.h"

//DOM-IGNORE-BEGIN
#define FRAMES_PER_FEET_16MM 40
#define FRAMES_PER_FEET_35MM 16
//DOM-IGNORE-END

//
// Summary:
//    Describes the format of the time code. One of the enumerators below must be called whenever the SetFormat method is called.
//
 enum EMvTimecodeFormat
{
   keMvTimecodeFormat_Invalid,      // Invalid time code format.
   keMvTimecodeFormat_Frames,       // Number of frames. 
   keMvTimecodeFormat_Feet_16mm,    // Feet + frames on 16mm film.
   keMvTimecodeFormat_Feet_35mm,    // Feet + frames on 35mm film.
   keMvTimecodeFormat_SMPTE,        // Hours, minutes, seconds, and frames since beginning (SMPTE format).
   keMvTimecodeFormat_Maximum       // The number of possible time code formats + 1
};


//
// Summary:
//    Sets the parameters used by the host software time code effect.
//
interface IMvTimecodeEffectSettings : public IUnknown
{
   //
   // Summary:
   //    Sets the value to be formatted and displayed by the time code effect.
   // Description:
   //    This value is formatted according to the format specified by the SetFormat method.
   //    <table>
   //    Parameter  Valid range           Granularity  Default value  Dependency 
   //    ---------  --------------------  -----------  -------------  ----------
   //    %PAR0%     [LONG_MIN, LONG_MAX]  +1           None           None
   //    </table>
   // Return value:
   //    - mV_NOERROR if completed successfully.
   // Remarks:
   //    - For interlaced video, this value is the same for both top and bottom fields. Field information 
   //      is retrieved from the output surface, and the field symbol (if enabled) is included in the time code.   
   //
   virtual HRESULT __stdcall SetFrameNumber
      (
      long in_lFrameNumber    // Specifies the time code value.
      )=0;

   //
   // Summary:
   //    Sets the text to be displayed as a prefix to the time code.
   // Description:
   //    <table>
   //    Parameter  Valid range         Granularity  Default value  Dependency 
   //    ---------  ------------------  -----------  -------------  ----------
   //    %PAR0%     Up to 3 characters  N/A          “”             None
   //    %PAR1%     [+0, +3]            +1           0              None
   //    </table>
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //    - MV_E_INVALID_PARAMETER if one of the parameters is outside the specified range.
   //
   virtual HRESULT __stdcall SetLeftLabelText
      (
      const wchar_t * in_wszLabelText,       // Specifies the string to be displayed.
      int             in_iLengthInCharacters // Specifies the length of the string to be displayed.
      )=0;

   //
   // Summary:
   //    Sets the opacity of the time code's background window. 
   // Description:
   //    <table>
   //    Parameter  Valid range  Granularity  Default value  Dependency 
   //    ---------  -----------  -----------  -------------  ----------
   //    %PAR0%     [+0, +1]     Not Limited  +1.0           None
   //    </table>
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //    - MV_E_INVALID_PARAMETER if parameter in_fBackgroundOpacity is outside the specified range.
   //
   virtual HRESULT __stdcall SetBackgroundOpacity
      (
      float in_fBackgroundOpacity   // Specifies the opacity of the time code's background window.
      )=0;

   //
   // Summary:
   //    Enables/disables the field symbol that indicates if the video clip is interlaced or progressive. 
   // Description:
   //    <table>
   //    Parameter  Valid range    Default value  Dependency 
   //    ---------  -------------  -------------  ----------
   //    %PAR0%     {true, false}  True           None
   //    </table>
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //
   virtual HRESULT __stdcall SetFieldSymbol
      (
      bool in_bIsFieldSymbolEnabled // Specifies if the field symbol is enabled. 
      )=0;

   //
   // Summary:
   //    Sets the position (in pixels) of the center of the time code, relative to the top left corner of the video clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range             Granularity  Default value  Dependency 
   //    ---------  ----------------------  -----------  -------------  ----------
   //    %PAR0%     [MIN_FLOAT, MAX_FLOAT]  Not limited  (+0.0, +0.0)   None
   //    </table>
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //    - MV_E_INVALID_PTR if in_psPosition is NULL.
   // Remarks:
   //    - The time code will be cropped if positioned outside the video area.
   //
   virtual HRESULT __stdcall SetPosition
      (
      SMvPointF* in_psPosition   // Specifies the coordinates on the video where the time code will appear.
      )=0;

   //
   // Summary:
   //    Sets the time code format to SMPTE, frames, or feet + frames (either 16 mm or 35 mm).  
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //    - MV_E_INVALID_PARAMETER if one of the parameters is outside the specified range.
   // Remarks:
   //    - The frame rate parameter is only applicable if in_eTimecodeFormat is set to keMvTimecodeFormat_SMPTE. 
   //      If the time code format is anything other than SMPTE, the frame rate parameter does not apply and will be ignored. 
   //
   virtual HRESULT __stdcall SetFormat
      (
      EMvTimecodeFormat in_eTimecodeFormat,  // Specifies the time code format.
      EMvFrameRate      in_eFrameRate        // Specifies the video frame rate.
      )=0;

   //
   // Summary:
   //    Sets the size of the time code window.
   // Description:
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  None           None
   //    </table>
   // Return value:
   //    - MV_NOERROR if completed successfully.
   //    - MV_E_INVALID_PARAMETER if one of the parameters is outside the specified range.
   // Remarks:
   //    - A size of 100% will create a time code window that will cover approximately half the screen's height in NTSC resolution, 
   //      and a quarter of the screen's height in 1920 x 1080 resolution.
   //
   virtual HRESULT __stdcall SetTimecodeSize
      (
      float in_fNormalizedSize   // Size of the time code window.
      )=0;

   //
   // Summary:
   //    Updates the time code settings according to the parameters set by other time code methods.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method ensures the integrity of the effect settings, and must be called whenever time code effect settings are modified. 
   // 
   virtual HRESULT __stdcall Update()=0;

   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulMvxTimecodeVersion = 1;
};
