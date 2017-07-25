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
//                    IMVPROFILELOADER.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVPROFILELOADER_H
#define IMVPROFILELOADER_H

/** Profile Loader interface. After InitializeProfile is called, one could query IMvHardwareProfileEnumerator, IMvGraphStateControl, IMvFlexHelper and IMvCodecProfileInfo interfaces from it.
@interface */
interface IMvProfileLoader : public IUnknown 
{
public:   

   /**
    *  Used to initialize a profile on the Profile loader. 
    *
    * <br><b>Remarks:</b>
    * <ul>
	 * <li>Profile Loader interface is the entry point of DirectDShow graph control. 
	 * <li>IMvProfileLoader interface is queried from the filter graph IGraphBuilder interface.
	 * <li>One could Query the following interfaces from IMvProfileLoader after the InitializeProfile is called:
 	 *	<DIR> 
	 * <li>IMvHardwareProfileEnumerator
	 * <li>IMvGraphStateControl
	 * <li>IMvFlexHelper
	 * <li>IMvCodecProfileInfo
	 * </DIR>
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvHardwareProfileInfo in_refsMvHWProfileInfo</i>: Hardware profile info.
    * @param <i>SMvResolutionInfo in_refsMvEres</i>: Editing resolution.
    * @param <i>SMvInputOutputResolutions io_asIOResolutions[]</i>: Input and Output resolution array.
    * @param <i>unsigned int in_uiIOResolutionCount</i>: Count of array of input and output resolutions.
    * @param <i>SMvResolutionInfo in_psGenlockResolution</i>: Pointer to the Genlock resolution.
    * @param <i>unsigned int in_uiGenlockMasterIODeviceIndex</i>: Index of the Genlock master.
    * @param <i>unsigned int in_uiAudioCaptureIODeviceIndex</i>: Index of the Audio capture device.
    * @param <i>unsigned int in_uiAudioSynchSourceIODeviceIndex</i>: Index of the Audio synch source.
    */    
   virtual HRESULT __stdcall InitializeProfile(SMvHardwareProfileInfo& in_refsMvHWProfileInfo,
                                               SMvResolutionInfo& in_refsMvEres,
                                               SMvInputOutputResolutions io_asIOResolutions[],
                                               unsigned int in_uiIOResolutionCount,
                                               SMvResolutionInfo* in_psGenlockResolution,
                                               unsigned int in_uiGenlockMasterIODeviceIndex,
                                               unsigned int in_uiAudioCaptureIODeviceIndex,
                                               unsigned int in_uiAudioSynchSourceIODeviceIndex,
											   bool	in_bUseHardwareIO) = 0;

   /**
    * Gets the current Profile and editing resolution. To get the currrent IO resolution,
    * you must use the interface returned by the call to GetIOControlInterface. 
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *   @param SMvHardwareProfileInfo out_psMvHWProfileInfo: The current hardware profile, or NULL if you do not care about the current HW profile
    *   @param SMvResolutionInfo out_psMvEres: The current resolution, or NULL if you do not care about the current resolution.
    */
   virtual HRESULT __stdcall GetCurrentProfile(SMvHardwareProfileInfo* out_psMvHWProfileInfo, SMvResolutionInfo* out_psMvEres) = 0;

   /**
    * Closes the current Profile. Note: The graph must be stopped and be devoid of all filters.
    * If that is not the case, then this function will fail.
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall CloseProfile() = 0;

   /**
    * Gets the file validation interface. 
    * This can be done at any time - ie before or after the profile has been set.
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvFileValidation out_ppIFileValidation</i>:  File validation interface.
    */
   virtual HRESULT __stdcall GetFileValidation(IMvFileValidation** out_ppIFileValidation) = 0;

   /**
    * Gets the flex clock. 
    * This can only be done once the Profile has been initialized.
    * <br><b>Remarks:</b>
    * <ul><i><li> 
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvClock out_ppIMvClock</i>:  Flex clock interface.
    */
   virtual HRESULT __stdcall GetFlexIMvClock(IMvClock ** out_ppIMvClock) = 0;

};

/** Profile Loader interface 2. Allow changing the ORes of the profile.
@interface */
interface IMvProfileLoader2 : public IMvProfileLoader 
{
public:   

   virtual HRESULT __stdcall ChangeOutputResolution(SMvResolutionInfo *in_psOutputResolutionInfo) = 0;

   virtual HRESULT __stdcall GetLiveWindowInfo(RECT * out_pRectSource) = 0;

   virtual HRESULT __stdcall GetLiveWindowInfoDependingOnScalingMode(EMvScalingMode in_eOutputScalingMode, RECT * out_pRectValidSourceWhenCalling_SetClientRegionOfSource) = 0;

};

interface IMvProfileLoader3 : public IMvProfileLoader2 
{
public:   

   /**
   *  Used to switch profile on the Profile loader. 
   *
   * <br><b>Remarks:</b>
   * <ul>
   * <li>Profile Loader interface is the entry point of DirectDShow graph control. 
   * <li>IMvProfileLoader interface is queried from the filter graph IGraphBuilder interface.
   * <li>One could Query the following interfaces from IMvProfileLoader after the InitializeProfile is called:
   *	<DIR> 
   * <li>IMvHardwareProfileEnumerator
   * <li>IMvGraphStateControl
   * <li>IMvFlexHelper
   * <li>IMvCodecProfileInfo
   * </DIR>
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>SMvHardwareProfileInfo in_refsMvHWProfileInfo</i>: Hardware profile info.
   * @param <i>SMvResolutionInfo in_refsMvEres</i>: Editing resolution.
   * @param <i>SMvInputOutputResolutions io_asIOResolutions[]</i>: Input and Output resolution array.
   * @param <i>unsigned int in_uiIOResolutionCount</i>: Count of array of input and output resolutions.
   * @param <i>SMvResolutionInfo in_psGenlockResolution</i>: Pointer to the Genlock resolution.
   * @param <i>unsigned int in_uiGenlockMasterIODeviceIndex</i>: Index of the Genlock master.
   * @param <i>unsigned int in_uiAudioCaptureIODeviceIndex</i>: Index of the Audio capture device.
   * @param <i>unsigned int in_uiAudioSynchSourceIODeviceIndex</i>: Index of the Audio synch source.
   */    
   virtual HRESULT __stdcall SwitchProfile(  SMvHardwareProfileInfo& in_refsMvHWProfileInfo,
                                             SMvResolutionInfo& in_refsMvEres,
                                             SMvInputOutputResolutions io_asIOResolutions[],
                                             unsigned int in_uiIOResolutionCount,
                                             SMvResolutionInfo* in_psGenlockResolution,
                                             unsigned int in_uiGenlockMasterIODeviceIndex,
                                             unsigned int in_uiAudioCaptureIODeviceIndex,
                                             unsigned int in_uiAudioSynchSourceIODeviceIndex) = 0;


   /**
   *  Used to unload all IO buffers and interfaces from profile so they may be used in another profile
   *
   * <br><b>Remarks:</b>
   * <ul>
   * </DIR>
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   */    
   virtual HRESULT __stdcall UnloadIOBuffersAndInterfacesFromProfile() = 0;

   /**
   *  Used to Load all IO buffers and interfaces on profile from a previously unloaded profile.
   *
   * <br><b>Remarks:</b>
   * <ul>
   * </DIR>
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   */    
   virtual HRESULT __stdcall LoadIOBuffersAndInterfacesFromProfile() = 0;

   /**
   * This method is used when different hardware profiles are running at the same time. Only one of them can use the 3d engine at 
   * a time, so the other must release it 
   *
   */   
   virtual HRESULT __stdcall Load3DEngineExtension() = 0;

   virtual HRESULT __stdcall Unload3DEngineExtension() = 0;


};

interface IMvProfileLoader4 : public IMvProfileLoader3 
{
public:   

   /**
   *  Used to initialize a profile on the Profile loader. Same as InitializeProfile except for added parameter of Secondary output resolution
   *
   * <br><b>Remarks:</b>
   * <ul>
   * <li>Profile Loader interface is the entry point of DirectDShow graph control. 
   * <li>IMvProfileLoader interface is queried from the filter graph IGraphBuilder interface.
   * <li>One could Query the following interfaces from IMvProfileLoader after the InitializeProfile is called:
   *	<DIR> 
   * <li>IMvHardwareProfileEnumerator
   * <li>IMvGraphStateControl
   * <li>IMvFlexHelper
   * <li>IMvCodecProfileInfo
   * </DIR>
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>SMvHardwareProfileInfo in_refsMvHWProfileInfo</i>: Hardware profile info.
   * @param <i>SMvResolutionInfo in_refsMvEres</i>: Editing resolution.
   * @param <i>SMvInputOutputResolutions io_asIOResolutions[]</i>: Input and Output resolution array.
   * @param <i>unsigned int in_uiIOResolutionCount</i>: Count of array of input and output resolutions.
   * @param <i>SMvResolutionInfo in_psGenlockResolution</i>: Pointer to the Genlock resolution.
   * @param <i>unsigned int in_uiGenlockMasterIODeviceIndex</i>: Index of the Genlock master.
   * @param <i>unsigned int in_uiAudioCaptureIODeviceIndex</i>: Index of the Audio capture device.
   * @param <i>unsigned int in_uiAudioSynchSourceIODeviceIndex</i>: Index of the Audio synch source.
   * @param <i>SMvResolutionInfo* in_psSecondaryOutputResolution</i>: Pointer to the Secondary output resolution.
   */    
   virtual HRESULT __stdcall InitializeProfile2(SMvHardwareProfileInfo& in_refsMvHWProfileInfo,
      SMvResolutionInfo& in_refsMvEres,
      SMvInputOutputResolutions io_asIOResolutions[],
      unsigned int in_uiIOResolutionCount,
      SMvResolutionInfo* in_psGenlockResolution,
      unsigned int in_uiGenlockMasterIODeviceIndex,
      unsigned int in_uiAudioCaptureIODeviceIndex,
      unsigned int in_uiAudioSynchSourceIODeviceIndex,
      SMvResolutionInfo*		in_psSecondaryOutputResolution,
	  bool						in_bUseHardwareIO) = 0;


   /**
   *  Used to switch profile on the Profile loader. Same as SwitchProfile except for added parameter of Secondary output resolution.
   *
   * <br><b>Remarks:</b>
   * <ul>
   * <li>Profile Loader interface is the entry point of DirectDShow graph control. 
   * <li>IMvProfileLoader interface is queried from the filter graph IGraphBuilder interface.
   * <li>One could Query the following interfaces from IMvProfileLoader after the InitializeProfile is called:
   *	<DIR> 
   * <li>IMvHardwareProfileEnumerator
   * <li>IMvGraphStateControl
   * <li>IMvFlexHelper
   * <li>IMvCodecProfileInfo
   * </DIR>
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>SMvHardwareProfileInfo in_refsMvHWProfileInfo</i>: Hardware profile info.
   * @param <i>SMvResolutionInfo in_refsMvEres</i>: Editing resolution.
   * @param <i>SMvInputOutputResolutions io_asIOResolutions[]</i>: Input and Output resolution array.
   * @param <i>unsigned int in_uiIOResolutionCount</i>: Count of array of input and output resolutions.
   * @param <i>SMvResolutionInfo in_psGenlockResolution</i>: Pointer to the Genlock resolution.
   * @param <i>unsigned int in_uiGenlockMasterIODeviceIndex</i>: Index of the Genlock master.
   * @param <i>unsigned int in_uiAudioCaptureIODeviceIndex</i>: Index of the Audio capture device.
   * @param <i>unsigned int in_uiAudioSynchSourceIODeviceIndex</i>: Index of the Audio synch source.
   * @param <i>SMvResolutionInfo* in_psSecondaryOutputResolution</i>: Pointer to the Secondary output resolution.
   */    
   virtual HRESULT __stdcall SwitchProfile2(  SMvHardwareProfileInfo& in_refsMvHWProfileInfo,
      SMvResolutionInfo& in_refsMvEres,
      SMvInputOutputResolutions io_asIOResolutions[],
      unsigned int in_uiIOResolutionCount,
      SMvResolutionInfo* in_psGenlockResolution,
      unsigned int in_uiGenlockMasterIODeviceIndex,
      unsigned int in_uiAudioCaptureIODeviceIndex,
      unsigned int in_uiAudioSynchSourceIODeviceIndex,
      SMvResolutionInfo*			in_psSecondaryOutputResolution) = 0;
};


#endif //IMVPROFILELOADER_H