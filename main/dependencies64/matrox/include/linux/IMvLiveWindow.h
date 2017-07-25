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
#ifndef IMVLIVEWINDOW_H
#define IMVLIVEWINDOW_H

interface IMvLiveWindowBitmapCallback;

/** This interface provides access to live window settings on the Matrox DirectShow Live Window filter.
 * @interface */
interface IMvLiveWindow : public IUnknown
{
public:   

   /**
    * Assigns a new window to the Live Window filter.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Display region settings and overlay bitmap settings can only be set after this call.
    *        <li>The live window filter won't be operational until the display region is set.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if the window was accepted by the Live Window filter.
    *     <li>HRESULT error code, if there was a failure while assigning the window.
    * </ul>
    * @param <i>HWND in_hwnd:</i> Window handle.*/
   virtual HRESULT __stdcall AssignWindow(HWND in_hwnd) = 0;

   /**
    * Removes assignment to a window. The Live Window filter won't keep any link with the previous window assignment.    *
    * <br><b>Remarks:</b>
    * <ul><li>Back buffer for refresh will be lost for the removed window.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall RemoveWindowAssignment() = 0;

   /**
    * Sets the client region that will be used inside a window by the live window display.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Coordinates can take negative values to zoom the live window content.
    *        <li>The Live Window filter will not display anything until this function is called.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>RECT in_rcClientRegion:</i> Displays rectangle in client coordinates.*/
   virtual HRESULT __stdcall SetClientRegionForDisplay(RECT in_rcClientRegion) = 0;

   /**
    * Sets the portion of the source video that will be displayed in the live window display.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Coordinates should be inside the display region.
    *        <li>If this function is not called, the video will always use the entire source video.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_OUT_OF_RANGE, if input coordinates are invalid.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>HRESULT error code, if operation failed for another reason.
    * </ul>
    * @param <i>RECT in_rcClientRegion:</i> Rectangle in client coordinates that will show video inside the display region.
    */
   virtual HRESULT __stdcall SetClientRegionOfSource(RECT in_rcClientRegion) = 0;

   /**
    * Sets the default background color of the live window display region that does not contain video.
    *
    * <br><b>Remarks:</b>
    * <ul><li>This color is shown only in the live window display region, not in the entire window.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT 
    * </ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>COLORREF in_clrRefBackground:</i> RGB background color description (0x00bbggrr).*/
   virtual HRESULT __stdcall SetClientRegionBackgroundColor(COLORREF in_clrRefBackground) = 0;

   /**
    * Checks if the hardware gamma-corrected overlay display is available on the system for the current process.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if the hardware gamma-corrected overlay display is available and can be set on any Live Window filter.
    *     <li>MVD_W_HW_OVERLAY_NOT_AVAILABLE, if the hardware gamma-corrected overlay display is not available currently in the system.
    *     <li>HRESULT error code, if the hardware gamma-corrected overlay display hasn't been detected.
    * </ul>
    */
   virtual HRESULT __stdcall DetectHWGammaCorrectedOverlay() = 0;

   /**
    * Forces the Live Window filter to use the hardware gamma-corrected overlay for its display.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Operation will fail if the hardware gamma-corrected overlay cannot be detected.
    *        <li>Calling the detection function prior to this function will avoid an error if the overlay is not detected.
    *        <li>If another window was already using the hardware gamma-corrected overlay, the function will switch it to the window currently linked to the filter.
    *        <li>Back buffers for refresh will stay unchanged if the overlay is taken from another window.
    *        <li>Gamma correction will be lost in the previous window and the display color might change a bit in the current window.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if the hardware gamma-corrected overlay was set on the Live Window filter.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>MVD_E_HW_OVERLAY_NOT_AVAILABLE, if the hardware gamma-corrected overlay display is not available currently in the system.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall UseHWGammaCorrectedOverlay() = 0;

   /**
    * Sets a bitmap HDC (handle to a device context) or a DirectX surface that will be applied over the live window display region (on top of background color and video).
    *
    * <br><b>Remarks:</b>
    * <ul><li>A callback should be set on the filter if the application has to be called before updating the live window with the supplied bitmap.
    *        <li>Bitmap is always frame-based in interlaced video resolution.
    *        <li>See DirectX 8.1 (or later) documentation  for input parameters description.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if succeeded; supplied bitmap will be mixed with video display while streaming.
    *     <li>E_POINTER, if input parameter is NULL.
    *     <li>E_INVALIDARG, if there's a problem with the dwFlags member of the VMRALPHABITMAP structure, or failure to specify a valid HDC or DirectDraw 
	*         surface in the structure, or an invalid value for fAlpha.
    *     <li>E_OUTOFMEMORY, if the application could not create a destination DC or DIBSection for the bitmap.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param <i>VMRALPHABITMAP* in_psVMRAlphaBitmap:</i> DirectShow Video Mixing Renderer bitmap structure.
    */
   virtual HRESULT __stdcall SetOverlayBitmap(VMRALPHABITMAP* in_psVMRAlphaBitmap) = 0;

   /**
    * Sets a callback interface that will be called by the live window engine to check if the application wants
    * to update the overlay bitmap before updating the content of the live window.
    *
    * <br><b>Remark:</b>
    * <ul><li>The host application should operate fast when called through this interface. Otherwise,
    *            the video displayed in the window will be jerky.
    * <ul><li>in_pIMvLiveWindowBitmapCallback will be AddRef'd internally.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_NOT_INITIALIZED, if no bitmap was set on the window.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvLiveWindowBitmapCallback* in_pIMvLiveWindowBitmapCallback:</i> Callback interface provided by host application.
    */
   virtual HRESULT __stdcall SetOverlayBitmapCallback(IMvLiveWindowBitmapCallback* in_pIMvLiveWindowBitmapCallback) = 0;

   /**
    * Sets the display mode that the Live Window filter uses to select the fields to be displayed in interlaced editing resolution.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Has no effect in any progressive scan editing resolution.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>MVD_W_NOT_SUPPORTED, if the current editing resolution does not allow any field polarity selection.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>EMvOutputDisplayMode in_eMvOutputDisplayMode:</i> Display mode selection.
    */
   virtual HRESULT __stdcall SetDisplayMode(EMvOutputDisplayMode in_eMvOutputDisplayMode) = 0;

   /**
    * Refreshes the entire live window display area.
    *
    * <br><b>Remarks:</b>
    * <ul><li> This method should be called when the window attached to the Live Window filter receives a WM_PAINT message.
    *        <li> This won't update the overlay bitmap if it has changed; it only repaints the actual content of the window.
    *        <li> This won't repaint the entire window, only the display region.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MVD_E_NOT_INITIALIZED, if no window is currently linked to this filter; an assignment should have been done prior to this call.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall Refresh() = 0;

   /**
   * Restores all of the lost surfaces after Ctrl+Alt+Delete.
   *
   * <br><b>Remarks:</b>
   * <ul><li> 
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   */
   virtual HRESULT __stdcall RestoreAll() = 0;
};

#endif //IMVLIVEWINDOW_H
