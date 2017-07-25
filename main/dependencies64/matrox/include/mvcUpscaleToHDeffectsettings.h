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
// $Archive: /VP/FLEXVIDEO/VIDEOEFFECTS/mvcUpscaleToHD/inc/mvcUpscaleToHDeffectsettings.h $
//===============================================================================

#pragma once

#ifndef _mvcUpscaleToHDSettings_h_937837C3H714B071288002D21362677967H_
#define _mvcUpscaleToHDSettings_h_937837C3H714B071288002D21362677967H_

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceStructs.h"

interface ImvcUpscaleToHDEffectSettings : public IUnknown
{
   virtual HRESULT __stdcall SetSrcAspectRatio(EMvAspectRatio in_eAspectRatio  ) = 0;        
   virtual HRESULT __stdcall SetDstAspectRatio(EMvAspectRatio in_eAspectRatio  ) = 0;        
   virtual HRESULT __stdcall SetPillarColor(SMvColor in_sColor) = 0;            
//
// interface version
//
   static const unsigned long ms_kulmvcUpscaleToHDVersion = 1;
};
#endif

