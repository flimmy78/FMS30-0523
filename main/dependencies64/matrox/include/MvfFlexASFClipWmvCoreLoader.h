//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2005. All rights reserved.
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
//                    CMvfWmvCoreLoader.h
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             
//   Operating System:       
//   Author:                 
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#pragma once

#include "_mvfConfigUtility.h"
#include "mvThread.h"
#include "IMvASFClipWmvCoreLoader.h"
#include "mvUnknown.h"

typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateIndexer)(IWMIndexer **ppIndexer);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateReader)(IUnknown* pUnkCert, DWORD dwRights, IWMReader **ppReader);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateSyncReader)(IUnknown* pUnkCert, DWORD dwRights, IWMSyncReader **ppSyncReader);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateWriterFileSink)(IWMWriterFileSink **ppSink);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateWriter)(IUnknown* pUnkCert, IWMWriter **ppWriter);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateEditor)(IWMMetadataEditor **ppEditor);
typedef HRESULT (STDMETHODCALLTYPE* PROC_WMCreateProfileManager)(IWMProfileManager **ppProfileManager);

// CMvfWmvCoreLoader
class CMvfWmvCoreLoader: public IMvASFClipWmvCoreLoader, public CMvUnknown
{
public:
   // construction
   CMvfWmvCoreLoader( HRESULT *out_phr );

   static CMvfWmvCoreLoader * CreateNew( HRESULT *out_phr );

   /*  unsigned long AddRef(void);
   unsigned long Release(void);

   long GetRefCount();*/

   MVDECLARE_IUNKNOWN;
   virtual STDMETHODIMP_(unsigned long) NonDelegatingRelease();

   // WmvCore function
   HRESULT __stdcall  WMCreateIndexer(IWMIndexer **ppIndexer);
   HRESULT __stdcall  WMCreateReader(IUnknown* pUnkCert, DWORD dwRights, IWMReader **ppReader);
   HRESULT __stdcall  WMCreateSyncReader(IUnknown* pUnkCert, DWORD dwRights, IWMSyncReader **ppSyncReader);
   HRESULT __stdcall  WMCreateWriterFileSink(IWMWriterFileSink **ppSink);
   HRESULT __stdcall  WMCreateWriter(IUnknown* pUnkCert, IWMWriter **ppWriter);
   HRESULT __stdcall  WMCreateEditor(IWMMetadataEditor **ppEditor);
   HRESULT __stdcall  WMCreateProfileManager(IWMProfileManager **ppProfileManager);

private:
   // destruction
   virtual ~CMvfWmvCoreLoader();

   bool LoadLibraries();
   bool UnLoadLibraries();

   HMODULE m_hWmvCoreLib;

   PROC_WMCreateIndexer m_pfnWMCreateIndexer;
   PROC_WMCreateReader m_pfnWMCreateReader;
   PROC_WMCreateSyncReader m_pfnWMCreateSyncReader;
   PROC_WMCreateWriterFileSink m_pfnWMCreateWriterFileSink;
   PROC_WMCreateWriter m_pfnWMCreateWriter;
   PROC_WMCreateEditor m_pfnWMCreateEditor;
   PROC_WMCreateProfileManager m_pfnWMCreateProfileManager;

};
