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
// Author: Frédérick Martel-Lupien 01/06/2005 15:30
// $Archive: /VP/FLEXVIDEO/VIDEOEFFECTS/MvfAPT/inc/MvAPTeffectsettings.h $
//===============================================================================

#pragma once

#ifndef _MvAPTSettings_h_384438BH4803500933554D17980978893C3H_
#define _MvAPTSettings_h_384438BH4803500933554D17980978893C3H_

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceAPI.h"

//
//Enums that the plug-in need to know about
//

//Transitions name
enum EMvfAPTTransitionNo
{
   keMvfAPTNoInvalid =                   0,
   keMvfAPTNoSplit =                     1,
   keMvfAPTNoBarndoors =                 2,
   keMvfAPTNoInset =                     3,
   keMvfAPTNoRollaway =                  4,
   keMvfAPTNoFoldUp =                    5,
   keMvfAPTNoIrisCross =                 6,
   keMvfAPTNoCenterSplit =               7,
   keMvfAPTNoBandSlide =                 8,
   keMvfAPTNoIrisPoints =                9,
   keMvfAPTNoIrisSquare =               10,
   keMvfAPTNoSpin =                     11,
   keMvfAPTNoSlide =                    12,
   keMvfAPTNoStretch =                  13,
   keMvfAPTNoIrisDiamond =              14,
   keMvfAPTNoCenterMerge =              15,
   keMvfAPTNoZoom =                     16,
   keMvfAPTNoCrossStretch =             17,
   keMvfAPTNoPush =                     18,
   keMvfAPTNoAdditiveDissolve =         19,
   keMvfAPTNoDirect =                   20,
   keMvfAPTNoTake =                     21,
   keMvfAPTNoCrossZoom =                22,
   keMvfAPTNoStretchOver =              23,
   keMvfAPTNoSwingIn =                  24,
   keMvfAPTNoSwingOut =                 25,
   keMvfAPTNoThreeD =                   26,
   keMvfAPTNoTexturize =                27,
   keMvfAPTNoFlipOver =                 28,
   keMvfAPTNoZoomBoxes =                29,
   keMvfAPTNoVenetianBlinds =           30,
   keMvfAPTNoSlidingBands =             31,
   keMvfAPTNoSwap =                     32,
   keMvfAPTNoZigZagBlocks =             33,
   keMvfAPTNoCubeSpin =                 34,
   keMvfAPTNoClockWipe =                35,
   keMvfAPTNoWedgeWipe =                36,
   keMvfAPTNoDoors =                    37,
   keMvfAPTNoIrisStar =                 38,
   keMvfAPTNoCheckerBoard =             39,
   keMvfAPTNoRandomBlocks =             40,
   keMvfAPTNoIrisRound =                41,
   keMvfAPTNoBandWipe =                 42,
   keMvfAPTNoCurtain =                  43,
   keMvfAPTNoCheckerWipe =              44,
   keMvfAPTNoFunnel =                   45,
   keMvfAPTNoMultiSpin =                46,
   keMvfAPTNoIrisShapes =               47,
   keMvfAPTNoPinwheel =                 48,
   keMvfAPTNoRadialWipe =               49,
   keMvfAPTNoRandomInvert =             50,
   keMvfAPTNoSlidingBoxes =             51,
   keMvfAPTNoSpinAway =                 52,
   keMvfAPTNoSpiralBoxes =              53,
   keMvfAPTNoTumbleAway =               54,
   keMvfAPTNoSwirl =                    55,
   keMvfAPTNoSlashSlide =               56,
   keMvfAPTNoRandomWipe =               57,
   keMvfAPTNoZoomTrails =               58,
   keMvfAPTNoStretchIn =                59,
   keMvfAPTNoWipe =                     60,
   keMvfAPTNoLast =                     61,

};

//Directions
enum EMvfAPTDirection
{
   //Match Premiere directions
   keMvfAPTDirectionNone =       0x00,//bitNone,
   keMvfAPTDirectionLeft =       0x08,//bitLeft,
   keMvfAPTDirectionRight =      0x02,//bitRight,
   keMvfAPTDirectionTop =        0x01,//bitTop,
   keMvfAPTDirectionBottom =     0x04,//bitBottom,
   keMvfAPTDirectionUpperRight = 0x10,//bitUpperRight,
   keMvfAPTDirectionLowerRight = 0x20,//bitLowerRight,
   keMvfAPTDirectionLowerLeft =  0x40,//bitLowerLeft,
   keMvfAPTDirectionUpperLeft =  0x80,//bitUpperLeft,
};



interface IMvAPTEffectSettings : public IUnknown
{
   virtual HRESULT __stdcall SetTransitionNo(unsigned long in_ulTransitionNo) = 0;

   virtual HRESULT __stdcall SetProgress(float in_fProgress) = 0;
   virtual HRESULT __stdcall SetSoftness(float in_fSoftness) = 0;
   virtual HRESULT __stdcall SetBorderWidth(float in_fBorderWidth) = 0;
   virtual HRESULT __stdcall SetBorderColor(SMvColorF* in_psBorderColor) = 0;

   virtual HRESULT __stdcall SetCustomParam1(float in_fCustomParam1) = 0;
   virtual HRESULT __stdcall SetCustomParam2(float in_fCustomParam2) = 0;
   virtual HRESULT __stdcall SetCustomParam3(float in_fCustomParam3) = 0;   
   
   virtual HRESULT __stdcall SetFirstCenterX(float in_fFirstCenterX) = 0;
   virtual HRESULT __stdcall SetFirstCenterY(float in_fFirstCenterY) = 0;
   virtual HRESULT __stdcall SetSecondCenterX(float in_fSecondCenterX) = 0;
   virtual HRESULT __stdcall SetSecondCenterY(float in_fSecondCenterY) = 0;
   
   virtual HRESULT __stdcall SetDirection(unsigned long in_ulDirection) = 0;

   virtual HRESULT __stdcall SetReverse(bool in_bReverse) = 0;
   //
   // interface version
   //
   static const unsigned long ms_kulMvAPTVersion = 1;
};
#endif