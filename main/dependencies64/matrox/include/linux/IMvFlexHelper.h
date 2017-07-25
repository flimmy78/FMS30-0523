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
//                    IMVFLEXHELPER.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             June 5, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVFLEXHELPER_H
#define IMVFLEXHELPER_H

/**
 * Allows access to the SDK Flex methods at a filter graph level.
 *
 * @interface 
 */
interface IMvFlexHelper : public IUnknown
{
public:
   /**
    * Requests an allocated video Flex surface from the Flex memory pool.  This call returns a surface with the same 
    * scan mode of the Editing Resolution.  Use <i>RequestFlexVideoMemoryWithScanMode</i> if you to specify a scan mode.
    * When the memory is available, the memory is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signaled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateSurfaceDescription  in_refsDescription:</i> Surface creation information structure.    
    * @param <i>IMvAVContentReceiver*        in_pIMvAVContentReceiver:</i> Pointer to the callback interface that will be used to receive the memory.
    */   
   virtual HRESULT __stdcall RequestFlexVideoMemory( SMvCreateSurfaceDescription  &in_refsDescription,
                                                     IMvAVContentReceiver*         in_pIMvAVContentReceiver ) = 0;   

   /**
    * Requests an allocated video Flex surface from the Flex memory pool with a specific scan mode.
    * When the memory is available, the memory is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signaled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateSurfaceDescription  in_refsDescription:</i> Surface creation information structure.
    * @param <i>EMvScanMode                  in_eScanMode:</i> Scan mode of the surface.
    * @param <i>IMvAVContentReceiver*        in_pIMvAVContentReceiver:</i> Pointer to the callback interface that will be used to receive the memory.
    */   
   virtual HRESULT __stdcall RequestFlexVideoMemoryWithScanMode( SMvCreateSurfaceDescription  &in_refsDescription,
                                                                 EMvScanMode                   in_eScanMode,
                                                                 IMvAVContentReceiver*         in_pIMvAVContentReceiver ) = 0;   
   /**
    * Requests an allocated video Flex surface alias.
    * When an alias is available, the alias is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvCreateSurfaceDescription in_refsDescription:       Surface creation information structure.
    * @param IMvAVContentReceiver        in_pIMvAVContentReceiver: Pointer to the callback interface that will be used to receive the alias.
    */
   virtual HRESULT __stdcall RequestFlexVideoAlias( SMvCreateSurfaceDescription  &in_refsDescription,
                                                    IMvAVContentReceiver*         in_pIMvAVContentReceiver ) = 0;

   /**
    * Request an allocated video Flex surface user buffer (empty content).  This call returns a surface with the same 
    * scan mode of the Editing Resolution.
    * When a user buffer is available, the user buffer is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>    
    * @param IMvAVContentReceiver in_pIMvAVContentReceiver: Pointer to the callback interface that will be used to receive the user buffer.
    */
   virtual HRESULT __stdcall RequestFlexVideoUserBuffer(IMvAVContentReceiver* in_pIMvAVContentReceiver ) = 0;
 

   /**
    * Request an allocated video Flex surface user buffer with a specific scan mode (empty content).  
    * When an user buffer is available, the user buffer is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>EMvScanMode       in_eScanMode:</i>         Scan mode of the surface.
    * @param IMvAVContentReceiver in_pIMvAVContentReceiver: Pointer to the callback interface that will be used to receive the user buffer.
    */
   virtual HRESULT __stdcall RequestFlexVideoUserBufferWithScanMode( EMvScanMode           in_eScanMode,
                                                                     IMvAVContentReceiver* in_pIMvAVContentReceiver ) = 0;

   /**
    * Gets an allocated video Flex surface from the Flex memory pool.  This call returns a surface with the same 
    * scan mode of the Editing Resolution.  Use <i>AllocateFlexVideoMemory2</i> if you to specify a scan mode.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateSurfaceDescription  in_refsDescription:</i> Surface creation information structure.
    * @param <i>IMvSurface                   out_ppIMvSurface:</i> Pointer to the Flex surface interface.
    */
   virtual HRESULT __stdcall AllocateFlexVideoMemory( SMvCreateSurfaceDescription  &in_refsDescription,
                                                      IMvSurface                  **out_ppIMvSurface ) = 0;

   /**
    * Gets an allocated video Flex surface from the Flex memory pool with a specific scan mode.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateSurfaceDescription  in_refsDescription:</i> Surface creation information structure.
    * @param <i>EMvScanMode                  in_eScanMode:</i> Scan mode of the surface.
    * @param <i>IMvSurface                   out_ppIMvSurface:</i> Pointer to the Flex surface interface.
    */
   virtual HRESULT __stdcall AllocateFlexVideoMemoryWithScanMode( SMvCreateSurfaceDescription  &in_refsDescription,
                                                                  EMvScanMode                   in_eScanMode,
                                                                  IMvSurface                  **out_ppIMvSurface ) = 0;

   /**
    * Gets an allocated video Flex surface alias.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvCreateSurfaceDescription  in_refsDescription: Surface creation information structure.
    * @param IMvSurface                   out_ppIMvSurface:   Pointer to Flex surface alias interface.
   */
   virtual HRESULT __stdcall AllocateFlexVideoAlias( SMvCreateSurfaceDescription  &in_refsDescription,
                                                     IMvSurface                  **out_ppIMvSurface ) = 0;

   /**
    * Gets an allocated video Flex surface user buffer (empty content).  This call returns a surface with the same 
    * scan mode of the Editing Resolution.  Use <i>AllocateFlexVideoUserBuffer2</i> if you to specify a scan mode.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvSurface out_ppIMvSurface:</i> Pointer to the Flex surface.
    */
   virtual HRESULT __stdcall AllocateFlexVideoUserBuffer( IMvSurface **out_ppIMvSurface ) = 0;

   /**
    * Gets an allocated video Flex surface user buffer with a specific scan mode (empty content).  
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>EMvScanMode   in_eScanMode:</i> Scan mode of the surface.
    * @param <i>IMvSurface    out_ppIMvSurface:</i> Pointer to the Flex surface.
    */
   virtual HRESULT __stdcall AllocateFlexVideoUserBufferWithScanMode( EMvScanMode  in_eScanMode,
                                                                      IMvSurface **out_ppIMvSurface ) = 0;
 

   /**
    * Requests an allocated audio Flex audio samples from the Flex memory pool with a specific scan mode.
    * When the memory is available, the memory is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signaled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvCreateAudioSamplesDescription in_refsDescription:    Audio samples creation information structure.
    * @param <i>IMvAVContentReceiver*         in_pIMvAVContentReceiver:</i> Pointer to the callback interface that will be used to receive the memory.
    */   
   virtual HRESULT __stdcall RequestFlexAudioMemory( SMvCreateAudioSamplesDescription  &in_refsDescription,                                                     
                                                     IMvAVContentReceiver*              in_pIMvAVContentReceiver ) = 0;
  
   /**
    * Requests an allocated audio Flex audio buffer alias.
    * When an alias is available, the alias is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateAudioSamplesDescription  in_refsDescription:</i> Audio samples creation information structure.
    * @param <i>IMvAVContentReceiver*             in_pIMvAVContentReceiver:</i> Pointer to the callback interface that will be used to receive the alias.
    */
   virtual HRESULT __stdcall RequestFlexAudioAlias( SMvCreateAudioSamplesDescription  &in_refsDescription,
                                                    IMvAVContentReceiver*              in_pIMvAVContentReceiver ) = 0;

   /**
    * Requests an allocated Flex audio samples user buffer (empty content).
    * When an user buffer is available, the user buffer is returned through the callback interface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface (by callback) will have an extra reference and should be released by caller.
    *     <li>Returned object (by callback) will return to its pool automatically on the last release. 
    *     <li>Returned object (by callback) can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvAudioSamples out_ppIMvAudioSamples:</i> Pointer to Flex audio buffer interface.
    */
   virtual HRESULT __stdcall RequestFlexAudioUserBuffer(IMvAVContentReceiver* in_pIMvAVContentReceiver) = 0;

    /**
     * Gets an allocated Flex audio buffer.
     *
     * <br><b>Remarks:</b>
     * <ul><li>Returned interface will have an extra reference and should be released by caller.
     *     <li>Returned object will return to its pool automatically on the last release. 
     *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
     * </ul>
     *
     * <b>Return type:</b>
     * <ul><li>HRESULT</ul>
     *
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully.
     *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
     *     <li>HRESULT error code, if failed.
     * </ul>
     * @param SMvCreateAudioSamplesDescription  in_refsDescription:    Audio samples creation information structure.
     * @param IMvAudioSamples                   out_ppIMvAudioSamples: Pointer to Flex audio buffer interface.
     */
   virtual HRESULT __stdcall AllocateFlexAudioMemory( SMvCreateAudioSamplesDescription  &in_refsDescription,
                                                      IMvAudioSamples                  **out_ppIMvAudioSamples ) = 0;

   /**
    * Gets an allocated audio Flex audio buffer alias.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvCreateAudioSamplesDescription  in_refsDescription:</i> Audio samples creation information structure.
    * @param <i>IMvAudioSamples                   out_ppIMvAudioSamples:</i> Pointer to the Flex audio buffer interface.
    */
   virtual HRESULT __stdcall AllocateFlexAudioAlias( SMvCreateAudioSamplesDescription  &in_refsDescription,
                                                     IMvAudioSamples                  **out_ppIMvAudioSamples ) = 0;

   /**
    * Gets an allocated Flex audio samples user buffer (empty content).
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference and should be released by caller.
    *     <li>Returned object will return to its pool automatically on the last release. 
    *     <li>Returned object can be recycled (returned to its pool) only when the write and read completion are signalled.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvAudioSamples out_ppIMvAudioSamples:</i> Pointer to Flex audio buffer interface.
    */
   virtual HRESULT __stdcall AllocateFlexAudioUserBuffer( IMvAudioSamples **out_ppIMvAudioSamples ) = 0;


   /**
    * Exposes the Flex video conversion function.
    *
    * <br><b>Remarks:</b>
    * <ul><li>This will perform an asynchronous memory copy.
    *     <li>Copy will start only when write completion is signaled on input surface.
    *     <li>Copy will be completed when the write completion is signaled on the output surface.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvSurface in_pIMvSurfaceSource:</i> Flex source surface.
    * @param <i>SMvRect    in_prcSource:</i> Region to copy "from" in source surface.
    * @param <i>IMvSurface in_pIMvSurfaceDestination:</i> Flex destination surface.
    * @param <i>SMvRect    in_prcDestination:</i> Region to copy "to" in destination surface.
    */
   virtual HRESULT __stdcall CopyFlexSurface( IMvSurface *in_pIMvSurfaceSource,
                                              SMvRect    *in_prcSource,
                                              IMvSurface *in_pIMvSurfaceDestination,
                                              SMvRect    *in_prcDestination ) = 0;

   /**
    * Exposes the Flex audio conversion function.
    *
    * <br><b>Remark:</b>
    * <ul><li>This will perform an asynchronous memory copy.
    *     <li>Copy will start only when write completion is signaled on input samples.
    *     <li>Copy will be completed when the write completion is signaled on the output samples.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvAudioSamples in_pIMvAudioSamplesSource:</i> Flex source audio buffer.
    * @param <i>IMvAudioSamples in_pIMvAudioSamplesDestination:</i> Flex destination audio buffer.    
    */
   virtual HRESULT __stdcall CopyFlexAudioSamples( IMvAudioSamples *in_pIMvAudioSamplesSource,
                                                   IMvAudioSamples *in_pIMvAudioSamplesDestination ) = 0;

   /**
    * Creates the parametric effect specified by the user.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param <i>GUID in_refParamFxGUID:</i> Guid of the Parametric effect to create.
    * @param <i>IUnknown in_pICreationInformation:</i> Pointer to the IMvCreationInformation interface provided to the parametric effect. 
    * @param <i>IMvParametricEffect out_ppIParamFx:</i> Interface to the Parametric effect created, or null if call failed.
    */
   virtual HRESULT __stdcall CreateParametricEffect(GUID                 &in_refParamFxGUID,
													             IUnknown             *in_pICreationInformation,
													             IMvParametricEffect **out_ppIParamFx) = 0;

   /**
    * Returns the ParametricEffectInfoList interface to the caller.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>REFCLSID                       in_rsParamFxArchitectureGUID:</i> Parametric Effect Architecture GUID.
    * @param <i>IMvParametricEffectInfoList    out_ppIParamFxInfoList:</i> Interface to the Parametric effect list, or null if call failed.
    */
   virtual HRESULT __stdcall GetParametricEffectInfoList
   ( 
      REFCLSID in_rsParamFxArchitectureGUID, 
      IMvParametricEffectInfoList **out_ppIParamFxInfoList 
   ) = 0;

   /**
    * Exposes the Flex video clear function.
    *
    * <br><b>Remarks:</b>
    * <ul><li>This will perform an asynchronous clear on the video surface.
    *     <li>Clear will start only when write completion is signaled on input surface.
    *     <li>Clear will be completed when the write completion is signaled on the output surface.
    *     <li>The request will be executed at the same or higher level as other internal jobs.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvSurface in_pIMvSurfaceDest:</i> Flex destination surface to clear.
    * @param <i>EMvColor in_eColor:</i> Color to clear to.
    * @param <i>float in_fAlphaValue:</i> alpha value.
    */
   virtual HRESULT __stdcall ClearFlexSurface( IMvSurface *in_pIMvSurfaceDestination,
                                               EMvColor   in_eColor,
                                               float      in_fAlphaValue
                                             ) = 0;

   /**
    * Exposes the Flex audio clear function.
    *
    * <br><b>Remark:</b>
    * <ul><li>This will perform an asynchronous memory clear.
    *     <li>Clear will start only when write completion is signaled on input samples.
    *     <li>Clear will be completed when the write completion is signaled on the output samples.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvAudioSamples in_pIMvAudioSamplesDestination:</i> Flex destination audio buffer to clear.    
    */
   virtual HRESULT __stdcall ClearFlexAudioSamples( IMvAudioSamples *in_pIMvAudioSamplesDestination ) = 0;

   /**
    * Exposes the Flex external user thread ID to use when calling clear on surface.
    *
    * <br><b>Remarks:</b>
    * <ul><li>This will return the thread ID to use when calling the clear on the surface it self.
    *     <li>The jobs executed with this thread ID will be at the lower level as other internal jobs.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>long *out_plThreadPoolID:</i> Thread pool ID to use.
    */
   virtual HRESULT __stdcall GetFlexUserThreadPoolID( unsigned long *out_plThreadPoolID ) = 0;

};

interface IMvFlexHelper2 : public IMvFlexHelper
{
public:
   /**
   * This method is used when the ERes is HD and ORes is SD and that the user is changing 
   * the aspect ratio (Anamorphic <--> Letterbox).
   *
    */   
   virtual HRESULT __stdcall ResetOutputAspectRatioUsage() = 0;   
};

interface IMvFlexHelper3 : public IMvFlexHelper2
{
public:
   /**
   * This method is used when different hardware profiles are running at the same time. Only one of them can use the 3d engine at 
	* a time, so the other must release it 
   *
    */   
	virtual HRESULT __stdcall Load3DEngineExtension() = 0;

   virtual HRESULT __stdcall Unload3DEngineExtension() = 0;
   
};

#endif //IMVFLEXHELPER_H



