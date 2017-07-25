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
//                    IMvRenderEffect.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             November 2004
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVRENDEREFFECT_H
#define IMVRENDEREFFECT_H

interface  IMvRenderEffect: public IUnknown 
{
public:

   virtual HRESULT __stdcall RenderEffect(IMvAVContent **in_ppAVContentIn,
                                          unsigned long in_ulAVContentCount,
                                          IMvAVContent *out_pAVContentOut,
                                          IMvParametricEffect *in_pParamFX,
                                          EMvParamFxFlexObjectType eParamFXObjectType,
                                          uint64_t  ui64PosInEres,
                                          unsigned long ulCutListID
                                          ) = 0;
};


#endif //IMVRENDEREFFECT_H
