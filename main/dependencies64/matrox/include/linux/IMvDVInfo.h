//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//                    IMVINPUTDEVICES.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:            Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVDVINFO_H
#define IMVDVINFO_H


interface IMvDVInfo : public IUnknown
{
public:

   virtual HRESULT __stdcall getLastTimecode( 
      unsigned long * out_pulTimeCodeInBCD) = 0;

   virtual HRESULT __stdcall getTapeProperties( 
      bool* out_pbIsDropFrame,
      EMvSurfaceFormat* out_peSurfaceFormat) = 0;

   virtual HRESULT __stdcall isTapeDropFrame( 
      bool* out_pbIsDropFrame) = 0;

};



#endif //IMVDVINFO_H

