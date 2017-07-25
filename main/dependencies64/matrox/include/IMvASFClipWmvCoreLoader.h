//$Archive: /VP/FLEXVIDEO/DLLS/mvFlexReader/_inc/IMvASFClipWmvCoreLoader.h $
//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2004. All rights reserved.
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
//                    IMvASFClipWmvCoreLoader.H
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

#ifndef IMVASFCLIPWMVCORELOADER_H
#define IMVASFCLIPWMVCORELOADER_H

#include <wmsdk.h>

//==========================================================================;
// Interface IMvASFClipWmvCoreLoader
//==========================================================================;
interface IMvASFClipWmvCoreLoader : public IUnknown 
{
   // WmvCore function
   virtual HRESULT __stdcall WMCreateIndexer(IWMIndexer **ppIndexer) = 0;
   virtual HRESULT __stdcall WMCreateReader(IUnknown* pUnkCert, DWORD dwRights, IWMReader **ppReader) = 0;
   virtual HRESULT __stdcall WMCreateSyncReader(IUnknown* pUnkCert, DWORD dwRights, IWMSyncReader **ppSyncReader) = 0;
   virtual HRESULT __stdcall WMCreateWriterFileSink(IWMWriterFileSink **ppSink) = 0;
   virtual HRESULT __stdcall WMCreateWriter(IUnknown* pUnkCert, IWMWriter **ppWriter) = 0;
   virtual HRESULT __stdcall WMCreateEditor(IWMMetadataEditor **ppEditor) = 0;
   virtual HRESULT __stdcall WMCreateProfileManager(IWMProfileManager **ppProfileManager) = 0;
};

#endif //IMVASFCLIPWMVCORELOADER_H