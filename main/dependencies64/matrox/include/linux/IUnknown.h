
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
//                    
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IUNKNOWN_H
#define IUNKNOWN_H

// Include the real IUnknown from Microsoft
#ifdef DEFINE_MICROSOFT_IUNKNOWN
#include "Unknwn.h"

// Definition for external use
#else

/** @interface */
interface IUnknown
{
public:

   virtual HRESULT __stdcall QueryInterface( REFIID riid, LPVOID * ppvObj ) = 0;

   virtual ULONG __stdcall AddRef() = 0;

   virtual ULONG __stdcall Release() = 0;
};

#endif //DEFINE_MVD_IUNKNOWN

#endif //IUNKNOWN_H
