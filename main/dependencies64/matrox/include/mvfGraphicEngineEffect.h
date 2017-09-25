// $Archive: /VP/FLEXVIDEO/LIBS/mvfGraphicEngineEffectBase/inc/mvfGraphicEngineEffect.h $

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
//	created:	   2003/2/21    17:19
//	filename: 	mvfgraphicengineeffect.h
//	author:		Luc Poirier
//===============================================================================


#pragma once

#include "mvBaseCOM.h"
#include "mvFlex3DDeviceApi.h"
#include "mvErrors.h"
#include "mvFlexDefinitions.h"
#include "mvFlexAPI.h"
#include "mvFlexGuids.h"
#include "mvUtilityMacro.h"
#include "mvEffectHelpers.h"

#pragma comment(lib, "mvEffectHelpers.lib")

//
// Summary:
//    This base class implements some of the functionality behind IMvEffectRenderer,
//    so you have to implement only the important methods. In
//    fact, a full effect can be implemented simply by overriding
//    the method <link CMvfGraphicEngineEffect::UpstreamFilter@IMvSurface *@unsigned long@IMvSurface *@IMvEffectSettings *@IMvContainer *, UpstreamFilter()>.
//
class CMvfGraphicEngineEffect :
   public CMvLightUnknown,
   public IMvEffectRenderer
{
private:
   CMvfGraphicEngineEffect(CMvfGraphicEngineEffect&):CMvLightUnknown(NULL, NULL){}
   void operator=(CMvfGraphicEngineEffect&){}


public:
   
   CMvfGraphicEngineEffect(
      IMvFlexEngine  *in_pIFlexEngine,
      wchar_t               *in_pwszName,
      SMvEffectCapabilities *in_pCapabilities,
      IUnknown              *in_pIUnk,
      HRESULT               *out_phr);
   
   virtual ~CMvfGraphicEngineEffect(void);

   //
   // COM interface
   //
   MVDECLARE_IUNKNOWN;

   //
   // Summary:
   //    Performs an upstream filter operation in.
   // 
   virtual HRESULT __stdcall UpstreamFilter(
      IMvSurface           *io_pIOutputSurface,			   // The output surface in which to render.
      unsigned long         in_ulInputSurfaceCount,		// The number of input surfaces passed in the array in order for the effect to render.
      IMvSurface           *in_apIInputSurfaceArray[],	// The array pointer in which to retrieve the input surface.
      IMvEffectSettings    *in_pIEffectSettings,		   // Pointer to the effect settings necessary to render the effect.
      IMvContainer         *in_pIEffectPattern			   // Pointer to IMvContainer that holds additional data needed by the effect. Can be NULL if not needed.
      ) = 0;

   //
   // Summary:
   //    Performs an upstream transition operation.
   //
   virtual HRESULT __stdcall UpstreamTransition(
      IMvSurface        *io_pIOutputSurface,			   // The output surface in which to render.
      IMvSurface        *in_pISurfaceA,					// A pointer to the input surface A.
      IMvSurface        *in_pISurfaceB,					// A pointer to the input surface B.
      IMvEffectSettings *in_pIEffectSettings,			// Pointer to the effect settings necessary to render the effect.
      IMvContainer      *in_pIEffectPattern				// Pointer to IMvContainer that holds additional data needed by the effect.  Can be NULL if not needed.
      );

   //
   // Summary:
   //    Performs a downstream filter operation.
   // 
   virtual HRESULT __stdcall DownstreamFilter(
      IMvSurface           *io_pIOutputSurface,			   // The output surface in which to render.
      unsigned long         in_ulInputSurfaceCount,		// The number of input surfaces passed in the array in order for the effect to render.
      IMvSurface           *in_apIInputSurfaceArray[],	// The array pointer in which to retrieve the input surface.
      IMvEffectSettings    *in_pIEffectSettings,		   // Pointer to the effect settings necessary to render the effect.
      IMvContainer         *in_pIEffectPattern,			   // Pointer to an IMvContainer that holds additional data needed by the effect.  Can be NULL if not needed.
      IMvSurface           *in_pIBackgroundSurface,		// The background surface in which to render.
      EMvColor              in_eColor,					      // Color associated with the background.
      EMvBackgroundHandling in_eBackgroundHandling,		// Flags indicating how the effect must handle the background.
      IMvEffectSettings    *in_pICompositorSettings		// Pointer to the compositor settings.
      );
	
   //
   // Summary:
   //    Performs a downstream transition operation.
   // 
   virtual HRESULT __stdcall DownstreamTransition(
      IMvSurface             *io_pIOutputSurface,		// The output surface in which to render.
      IMvSurface             *in_pISurfaceA,			   // A pointer to the input surface A.
      IMvSurface             *in_pISurfaceB,			   // A pointer to the input surface B.
      IMvEffectSettings      *in_pIEffectSettings,		// Pointer to the effect settings necessary to render the effect.
      IMvContainer           *in_pIEffectPattern,		// Pointer to IMvContainer that holds additional data needed by the effect.  Can be NULL if not needed.
      IMvSurface             *in_pIBackgroundSurface,	// The background surface in which to render.
      EMvColor                in_eColor,				   // Color associated with the background.
      EMvBackgroundHandling   in_eBackgroundHandling,	// Flags indicating how the effect must handle the background.
      IMvEffectSettings      *in_pICompositorSettings	// Pointer to the compositor settings.


      );


   //
   // Summary:
   //	   Generates the effect GFX (effect pattern) data that is ready to be written into a file.
   //
   virtual HRESULT __stdcall PreprocessEffectPattern(
      IMvContainer  *in_pInData,		   // Container that holds the data that will be used to generate a GFX.
      IMvContainer **out_ppOutData		// Container that holds the data that will be written in the GFX.
      );
   
   //
   // Helpers
   //
protected:
  
   bool  __stdcall IsDXProfile();

   //
   // Summary:
   //    Performs an upstream transition operation, using the
   //    UpstreamFilter() method. You can then implement
   //    UpstreamTransition() by implementing only UpstreamFilter().
   // 
   HRESULT __stdcall UpstreamTransitionWithRecipe(
      IMvSurface        *io_pIOutputSurface,		   // The output surface in which to render.
      IMvSurface        *in_pISurfaceA,				// A pointer to the input surface A.
      IMvSurface        *in_pISurfaceB,				// A pointer to the input surface B.
      IMvEffectSettings *in_pIEffectSettings,		// A pointer to the effect settings necessary to render the effect.
      IMvContainer      *in_pIEffectPattern,		   // A pointer to IMvContainer that holds additional data needed by the effect.  Can be NULL if not needed.
      IMvSurface        *in_pITemporarySurface1,	// A pointer to a temporary surface used for the recipe.
      IMvSurface        *in_pITemporarySurface2		// A pointer to a temporary surface used for the recipe, cannot be the same as in_pITemporarySurface1.
	  );	

   virtual float __stdcall GetUTexelCenter() { return 0.5f; };
   virtual float __stdcall GetVTexelCenter() { return 0.5f; };

   TMvSmartPtr<IMvFlex3DDevice>  m_pJFlex3DDevice;
   TMvSmartPtr<IMvFlexEngine>    m_pJFlexEngine;
   TMvSmartPtr<IMvFlex3DHelpers> m_pJFlex3DHelpers;

   SMvEngineProfileInfo   m_sEngineProfileInfo;
   SMvEffectCapabilities  m_sCapabilities;

private:
   HRESULT              _CreateTemporarySurfaces();

   //
   //Summary:
   // Performs a filter operation in downstream mode.
   //
   HRESULT              _BuildComposeMesh(IMvSurface *in_pISurfaceA,
                                          IMvSurface *in_pISurfaceB, 
                                          IMvSurface *in_pIOutput);
   HRESULT              _UpstreamComposeUsingAlphaMatte(
                                          IMvSurface *io_pIOutputSurface,
                                          IMvSurface *in_pISurfaceA,
                                          IMvSurface *in_pISurfaceB,
                                          IMvSurface *in_pISurfaceAlphaMatte);

   IMvFlex3DPixelShader  *m_pIPSBlendShapedOverShapedWithAlphaMatte;
   IMvFlex3DPixelShader  *m_pIPSBlendShapedOverUnshapedWithAlphaMatte;
   IMvFlex3DPixelShader  *m_pIPSBlendShapedOverOpaqueWithAlphaMatte;
   IMvFlex3DVertexBuffer *m_pIVB;
};
