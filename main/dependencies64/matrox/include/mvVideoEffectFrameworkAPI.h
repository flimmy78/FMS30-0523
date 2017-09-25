// $Archive: /VP/FLEXVIDEO/LIBS/mvVideoEffectFramework/inc/mvVideoEffectFrameworkAPI.h $

//==============================================================================
//
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
//
//-------------------------------------------------------------------------------
//	created:	   2003/4/22    11:14
//	filename: 	mvVideoEffectFrameworkAPI.h
//	author:		Luc Poirier
//===============================================================================

#pragma once

#ifndef _MVVIDEOEFFECTFRAMEWORKAPI_H_EB56E65B_8093_43B7_A546_1FD1D44B2957_
#define _MVVIDEOEFFECTFRAMEWORKAPI_H_EB56E65B_8093_43B7_A546_1FD1D44B2957_

#pragma warning(disable:4100)
#include "mvfPoolManagerAPI.h"
#include "mvTypes.h"
#include "MvFlexDefinitions.h"
#include "MvFlexAPI.h"
#include "MvFlexGuids.h"
#include "mvUtilityMacro.h"
#include "mvErrors.h"
#include "MvfAvContentPool.h"
#include <vector>
#pragma warning(default:4100)

//
// E R R O R   C O D E S
// 
#define MV_E_EFFECT_SETTING_DURATION_NOT_SET           MAKE_HRESULT(1, 0xBAD, 0x1)
#define MV_E_EFFECT_SETTING_START_TIME_NOT_SET         MAKE_HRESULT(1, 0xBAD, 0x2)

//
// C L A S S E S
//
class CMvfEffectSettingsBase;
class CMvfVideoEffectAbstract;
class CMvfEffectFactoryBase;
interface IMvOperationScheduler;

//
// C O N S T A N T S
//
const unsigned long kulMvfAddRegistryVersion    = 1;
const unsigned long kulMvfRemoveRegistryVersion = 1;

//------------------------------------------------------------------
// CMvfEffectFactoryBase
//------------------------------------------------------------------
class CMvfEffectFactoryBase
{
public:
   CMvfEffectFactoryBase(){}
   ~CMvfEffectFactoryBase(){}

public:
   static HRESULT WINAPI Register(bool in_bIsLoading, const CLSID *in_psClsID);
};


//
// Summary:
// 
//    This is the base class of all the effect settings.
// 
//    Each specific effect settings class derived from this class
//    must implement the <link CMvfEffectSettingsBase::GetVersion@void, GetVersion()>method.
// Remarks:
//   * This class is used as is for the compositor settings.
//       
//
class CMvfEffectSettingsBase
   : public CMvPoolElement
   , public IMvEffectSettings
{
private:
   CMvfEffectSettingsBase(CMvfEffectSettingsBase &):CMvPoolElement(NULL, NULL){}
   void operator= (CMvfEffectSettingsBase &){}

public:
   CMvfEffectSettingsBase(wchar_t *in_pwszName, IUnknown* in_pIUnk);
   virtual ~CMvfEffectSettingsBase() {};

   STDMETHODIMP NonDelegatingQueryInterface(REFIID in_riid, void **out_ppv);

   //
   // Summary:
   //	   Returns the effect settings version.  This is a virtual method. Each specific 
   //    effect setting must implement it.
   // Remarks:
   //    - The effect settings version will be used by the Parametric Effect to ensure 
   //       that it is returning the right settings.
   virtual uint32_t __stdcall GetVersion(void      // pure virtual
      ) = 0;  

};

//------------------------------------------------------------------
// CMvfVideoEffectAbstract
//------------------------------------------------------------------
class CMvfVideoEffectAbstract
   : public CMvLightUnknown
   , public IMvEffect
   , public IMvEffectSettingsPool
{
private:
   CMvfVideoEffectAbstract(CMvfVideoEffectAbstract &)
      : CMvLightUnknown(NULL,NULL)
      , m_kulNumberOfOperations(0) {}
   void operator= (CMvfVideoEffectAbstract &){}

public:

   CMvfVideoEffectAbstract(
      IMvFlexEngine           *in_pIFlexEngine,
      IMvEffectRenderer       *in_pIGraphicEngineEffect,
      IMvEffectRenderer       *in_paIHostEffect[],
      unsigned long            in_ulNumberOfHostEffects,
      SMvEffectCapabilities   *in_psEffectCapabilities,
      IMvPoolManager          *in_pIPoolManager
      );

   virtual ~CMvfVideoEffectAbstract();


   MVDECLARE_IUNKNOWN

   virtual STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);

   HRESULT __stdcall UpstreamFilter(
      IMvSurface           *io_pIOutputSurface,
      unsigned long         in_ulInputSurfaceCount,
      IMvSurface           *in_apIInputSurfaceArray[], 
      IMvEffectSettings    *in_pIEffectSettings,
      IMvContainer         *in_pIEffectPattern,
      unsigned long         in_ulThreadPoolIndex
      );


   HRESULT __stdcall UpstreamTransition(
      IMvSurface        *io_pIOutputSurface,
      IMvSurface        *in_pISurfaceA,
      IMvSurface        *in_pISurfaceB,
      IMvEffectSettings *in_pIEffectSettings,
      IMvContainer      *in_pIEffectPattern,
      unsigned long      in_ulThreadPoolIndex
      );

   HRESULT __stdcall DownstreamFilter(
      IMvSurface           *io_pIOutputSurface,
      unsigned long         in_ulInputSurfaceCount,
      IMvSurface           *in_apIInputSurfaceArray[], 
      IMvEffectSettings    *in_pIEffectSettings,
      IMvContainer         *in_pIEffectPattern,
      IMvSurface           *in_pIBackgroundSurface,
      EMvColor              in_eColor,
      EMvBackgroundHandling in_eBackgroundHandling,
      IMvEffectSettings    *in_pICompositorSettings,
      unsigned long         in_ulThreadPoolIndex
      );

   HRESULT __stdcall DownstreamTransition(
      IMvSurface             *io_pIOutputSurface,
      IMvSurface             *in_pISurfaceA,
      IMvSurface             *in_pISurfaceB,
      IMvEffectSettings      *in_pIEffectSettings,
      IMvContainer           *in_pIEffectPattern,
      IMvSurface             *in_pIBackgroundSurface,
      EMvColor                in_eColor,
      EMvBackgroundHandling   in_eBackgroundHandling,
      IMvEffectSettings      *in_pICompositorSettings,
      unsigned long           in_ulThreadPoolIndex
      );

   HRESULT __stdcall PreprocessEffectPattern(
      IMvContainer  * in_pInData,
      IMvContainer ** out_ppOutData
      );   

   HRESULT __stdcall GetCapabilities(SMvEffectCapabilities *io_pCapabilities);

   HRESULT __stdcall GetEffectSettings(IMvEffectSettings **io_ppIEffectSettings);

private:
   IMvFlexEngine                    *  m_pIFlexEngine;
   IMvEffectRenderer                *  m_pIGraphicEngineEffect;
   IMvEffectRenderer                *  m_apIHostEffect[kulMvMaxThreadPool];
   SMvEffectCapabilities               m_sEffectCapabilities;
   IMvPoolManager                   *  m_pIPoolManager;

   IMvPoolManager                   *  m_pIPoolManagerUpstreamFilter;
   IMvPoolManager                   *  m_pIPoolManagerUpstreamTransition;
   IMvPoolManager                   *  m_pIPoolManagerDownstreamFilter;
   IMvPoolManager                   *  m_pIPoolManagerDownstreamTransition;
   const unsigned long                 m_kulNumberOfOperations;

   TMvSmartPtr <IMvAvContentPool>      m_pJPoolSurfaceAlias;   

   IMvOperationScheduler*              m_pIOperationScheduler;
};


//------------------------------------------------------------------
// CMvfRegistryManager
//------------------------------------------------------------------
class CMvfRegistryManager
{
private:
   CMvfRegistryManager(CMvfRegistryManager&){}
   void operator=(CMvfRegistryManager&){};

public:
   CMvfRegistryManager();
   ~CMvfRegistryManager();

   HRESULT __stdcall AddGuid(GUID in_oGuid);

   HRESULT __stdcall RemoveGuid(GUID in_oGuid);

};

#endif
