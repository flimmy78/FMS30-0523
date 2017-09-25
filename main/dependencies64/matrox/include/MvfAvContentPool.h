//==========================================================================;
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
//==========================================================================;
//                    MvfAVContentPool.h
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             December 6, 2004 - 8:07:40 AM
//   Operating System:       WinXP
//   Author:                 Stephane Parent
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#pragma once

#ifndef CMVFAVCONTENTPOOL_H
#define CMVFAVCONTENTPOOL_H

#include "MvFlexAPI.h"
#include "mvErrors.h"
#include "mvUtility.h"

interface IMvAvContentPool : public IUnknown
{
   virtual HRESULT __stdcall GetAlias( IMvAudioSamples**    in_ppISrcAudioSamples,
                                       const unsigned long  in_kulArraySize,
                                       IMvAudioSamples**    out_ppIAudioSamplesAlias ) = 0;

   virtual HRESULT __stdcall GetAlias( IMvSurface**         in_ppISrcSurface,
                                       const unsigned long  in_kulArraySize,
                                       IMvSurface**         out_ppISurfaceAlias ) = 0;
};

class CMvfAvContentPool : public IMvAvContentPool, public CMvLightUnknown
{
   public:
      CMvfAvContentPool( IMvFlexEngine * in_pFlexEngine );
      virtual ~CMvfAvContentPool() ;

      virtual HRESULT __stdcall GetAlias( IMvAudioSamples**    /*in_ppISrcAudioSamples*/,
                                          const unsigned long  /*in_kulArraySize*/,
                                          IMvAudioSamples**    /*out_ppIAudioSamplesAlias*/ ) { return MV_E_FAIL; }

      virtual HRESULT __stdcall GetAlias( IMvSurface**         /*in_ppISrcSurface*/,
                                          const unsigned long  /*in_kulArraySize*/,
                                          IMvSurface**         /*out_ppISurfaceAlias*/ ) { return MV_E_FAIL; }

      //--------------------------------------------------------------------------;
      // IUnknown Overloads
      //--------------------------------------------------------------------------;
      MVDECLARE_IUNKNOWN;

   protected:
      virtual HRESULT _AddAvContent(IMvAVContent ** out_ppIAVContent) = 0;
      
      HRESULT _GetAvContent( IMvAVContent** out_ppIAvContent );
      
   private:
      HRESULT _EmptyPool();

   protected:
      IMvFlexEngine * m_pFlexEngine;
      
      TMvSmartPtr<IMvAVContentPoolManager> m_pJPool;

      unsigned long m_ulTotalNumberOfContents;

      char m_aszName[255];

   private:
      CMvfAvContentPool(CMvfAvContentPool &);
      void operator=(CMvfAvContentPool &);      
};

class CMvfAvContentPoolAudioSamplesAlias : public CMvfAvContentPool
{
   public:
      CMvfAvContentPoolAudioSamplesAlias( IMvFlexEngine * in_pFlexEngine );

      virtual ~CMvfAvContentPoolAudioSamplesAlias() {;}
      
      HRESULT __stdcall GetAlias(   IMvAudioSamples**    in_ppISrcAudioSamples,
                                    const unsigned long  in_kulArraySize,
                                    IMvAudioSamples**    out_ppIAudioSamplesAlias );

   protected:
      HRESULT _AddAvContent(IMvAVContent ** out_ppIAVContent);
};

class CMvfAvContentPoolSurfaceAlias : public CMvfAvContentPool
{
   public:
      CMvfAvContentPoolSurfaceAlias( IMvFlexEngine * in_pFlexEngine );

      virtual ~CMvfAvContentPoolSurfaceAlias() {;}

      HRESULT __stdcall GetAlias(   IMvSurface**         in_ppISrcSurface,
                                    const unsigned long  in_kulArraySize,
                                    IMvSurface**         out_ppISurfaceAlias );

   protected:
      HRESULT _AddAvContent(IMvAVContent ** out_ppIAVContent);
};

#endif // CMVFAVCONTENTPOOL_H

