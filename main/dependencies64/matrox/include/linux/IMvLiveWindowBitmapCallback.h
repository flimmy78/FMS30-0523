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


#ifndef IMVLIVEWINDOWBITMAPCALLBACK_H
#define IMVLIVEWINDOWBITMAPCALLBACK_H
#include "mvUnknown.h"

interface IDirect3DTexture9;

/** Called by the live window engine before updating the live window image on the filter's window.
 * @interface */
interface IMvLiveWindowBitmapCallback : public IUnknown
{
public:
   /**
    * This function is called to update the overlay bitmap on the live window.
    *
    * <br><b>Remarks:</b>
    * <ul><li>To avoid dropping frames on the live window, this call should be fast on the application side (should not hold it).
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t        in_ui64FramePosition:</i>   Current position that is updated.
    * @param <i>uint8_t    out_ui8RegionCount:</i>   Number of regions in texture that are updated. Maximum of 32 regions.
    * @param <i>RECT       out_paRegionsToUpdate:</i>   Array of regions in texture that are updated.
    * @param <i>IDirect3DTexture9  io_pIOverlayTexture:</i> The texture to draw on.  This texture will be overlayed over live window.
    */
   virtual HRESULT __stdcall ExecuteBitmapUpdate(uint64_t in_ui64FramePosition, uint8_t &out_ui8RegionCount, RECT *out_paRegionsToUpdate, IDirect3DTexture9 *io_pIOverlayTexture) = 0;
};

#endif //IMVLIVEWINDOWBITMAPCALLBACK_H
