// IMvInputCaptureSettings.h

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2013. All rights reserved. 
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
//-------------------------------------------------------------------------------

#ifndef __IMVDINPUTCAPTURESETTINGS__
#define __IMVDINPUTCAPTURESETTINGS__

#ifdef __cplusplus
extern "C" {
#endif


    //
    // IMvInputCaptureSettings interface GUID
    //
    // {4D6D4889-7072-4014-9D44-85A569C195D1}
    DEFINE_GUID(IID_IMvInputCaptureSettings, 
        0x4d6d4889, 0x7072, 0x4014, 0x9d, 0x44, 0x85, 0xa5, 0x69, 0xc1, 0x95, 0xd1);

    //
    // IMvInputCaptureSettingsInitializer interface GUID
    //
    // {A697500A-B28D-4FB0-BBB9-F2831760D5CF}
    DEFINE_GUID(IID_IMvInputCaptureSettingsInitializer, 
        0xa697500a, 0xb28d, 0x4fb0, 0xbb, 0xb9, 0xf2, 0x83, 0x17, 0x60, 0xd5, 0xcf);

    //
    // IMvInputCaptureSettingsDetection interface GUID
    //
    // {E96F4492-E40A-42E4-8EF3-9A471D6B7391}
    DEFINE_GUID(IID_IMvInputCaptureSettingsDetection, 
       0xe96f4492, 0xe40a, 0x42e4, 0x8e, 0xf3, 0x9a, 0x47, 0x1d, 0x6b, 0x73, 0x91);

    //
    // Video filter GUID
    //
    // {857B8E90-0E40-4959-8654-982F6710B236}
    DEFINE_GUID(CLSID_MatroxMXO2DirectShowVideoCaptureFilter, 
        0x857b8e90, 0xe40, 0x4959, 0x86, 0x54, 0x98, 0x2f, 0x67, 0x10, 0xb2, 0x36);

    //
    // Audio filter GUID
    //
    // {9229F90A-A822-4a24-BAD3-5E4841290BFD}
    DEFINE_GUID(CLSID_MatroxMXO2DirectShowAudioCaptureFilter, 
        0x9229f90a, 0xa822, 0x4a24, 0xba, 0xd3, 0x5e, 0x48, 0x41, 0x29, 0xb, 0xfd);

    //
    // Video filter GUID For VS4 Input 1
    //
    // {13F5C7B3-3B25-4FBC-BC94-F9A3DEB937CE}
    DEFINE_GUID(CLSID_MatroxVS4Input1DirectShowVideoCaptureFilter, 
       0x13f5c7b3, 0x3b25, 0x4fbc, 0xbc, 0x94, 0xf9, 0xa3, 0xde, 0xb9, 0x37, 0xce);

    //
    // Video filter GUID For VS4 Input 2
    //
    // {F84C1368-19DF-4888-A4D0-1D405568C094}
    DEFINE_GUID(CLSID_MatroxVS4Input2DirectShowVideoCaptureFilter, 
       0xf84c1368, 0x19df, 0x4888, 0xa4, 0xd0, 0x1d, 0x40, 0x55, 0x68, 0xc0, 0x94);

    //
    // Video filter GUID For VS4 Input 3
    //
    // {364B54E9-F114-4404-B742-327A8A593B33}
    DEFINE_GUID(CLSID_MatroxVS4Input3DirectShowVideoCaptureFilter, 
       0x364b54e9, 0xf114, 0x4404, 0xb7, 0x42, 0x32, 0x7a, 0x8a, 0x59, 0x3b, 0x33);

    //
    // Video filter GUID For VS4 Input 4
    //
    // {8C0F573F-E717-4312-AA7E-874BA23C160D}
    DEFINE_GUID(CLSID_MatroxVS4Input4DirectShowVideoCaptureFilter, 
       0x8c0f573f, 0xe717, 0x4312, 0xaa, 0x7e, 0x87, 0x4b, 0xa2, 0x3c, 0x16, 0xd);

    //
    // Video filter GUID For VS4 Input 5
    //
    // {A8DEED29-4C9F-47BB-9B5A-D100C4E1B3B2}
    DEFINE_GUID(CLSID_MatroxVS4Input5DirectShowVideoCaptureFilter, 
       0xa8deed29, 0x4c9f, 0x47bb, 0x9b, 0x5a, 0xd1, 0x0, 0xc4, 0xe1, 0xb3, 0xb2);

    //
    // Video filter GUID For VS4 Input 6
    //
    // {3B8CD5F1-0A9A-4CDC-B797-1FFD7146D135}
    DEFINE_GUID(CLSID_MatroxVS4Input6DirectShowVideoCaptureFilter, 
       0x3b8cd5f1, 0xa9a, 0x4cdc, 0xb7, 0x97, 0x1f, 0xfd, 0x71, 0x46, 0xd1, 0x35);

    //
    // Video filter GUID For VS4 Input 7
    //
    // {ACC038DF-FC33-429A-A155-59ED1AEC8D42}
    DEFINE_GUID(CLSID_MatroxVS4Input7DirectShowVideoCaptureFilter, 
       0xacc038df, 0xfc33, 0x429a, 0xa1, 0x55, 0x59, 0xed, 0x1a, 0xec, 0x8d, 0x42);

    //
    // Video filter GUID For VS4 Input 8
    //
    // {C00CFEC9-74D6-44B4-85AC-BD62B5ED2CE0}
    DEFINE_GUID(CLSID_MatroxVS4Input8DirectShowVideoCaptureFilter, 
       0xc00cfec9, 0x74d6, 0x44b4, 0x85, 0xac, 0xbd, 0x62, 0xb5, 0xed, 0x2c, 0xe0);

    //
    // Audio filter GUID For VS4 Input 1
    //
    // {D718A520-C876-4FE9-8D93-0494B70ACE05}
    DEFINE_GUID(CLSID_MatroxVS4Input1DirectShowAudioCaptureFilter, 
       0xd718a520, 0xc876, 0x4fe9, 0x8d, 0x93, 0x4, 0x94, 0xb7, 0xa, 0xce, 0x5);

    //
    // Audio filter GUID For VS4 Input 2
    //
    // {960BC286-AC42-467F-9DD4-7855350A3FB2}
    DEFINE_GUID(CLSID_MatroxVS4Input2DirectShowAudioCaptureFilter, 
       0x960bc286, 0xac42, 0x467f, 0x9d, 0xd4, 0x78, 0x55, 0x35, 0xa, 0x3f, 0xb2);


    //
    // Audio filter GUID For VS4 Input 3
    //
    // {A0C46570-F2BF-41B5-8278-981CBE38E603}
    DEFINE_GUID(CLSID_MatroxVS4Input3DirectShowAudioCaptureFilter, 
       0xa0c46570, 0xf2bf, 0x41b5, 0x82, 0x78, 0x98, 0x1c, 0xbe, 0x38, 0xe6, 0x3);


    //
    // Audio filter GUID For VS4 Input 4
    //
    // {05284CE8-E3C0-47E3-968A-43E12E94D311}
    DEFINE_GUID(CLSID_MatroxVS4Input4DirectShowAudioCaptureFilter, 
       0x5284ce8, 0xe3c0, 0x47e3, 0x96, 0x8a, 0x43, 0xe1, 0x2e, 0x94, 0xd3, 0x11);


    //
    // Audio filter GUID For VS4 Input 5
    //
    // {89737496-7BC7-4DE7-9709-5EFEC80D0E53}
    DEFINE_GUID(CLSID_MatroxVS4Input5DirectShowAudioCaptureFilter, 
        0x89737496, 0x7bc7, 0x4de7, 0x97, 0x9, 0x5e, 0xfe, 0xc8, 0xd, 0xe, 0x53);

    //
    // Audio filter GUID For VS4 Input 6
    //
    // {37FA98B1-E7A7-4B0C-99A6-B7FB46B8F063}
    DEFINE_GUID(CLSID_MatroxVS4Input6DirectShowAudioCaptureFilter, 
        0x37fa98b1, 0xe7a7, 0x4b0c, 0x99, 0xa6, 0xb7, 0xfb, 0x46, 0xb8, 0xf0, 0x63);

    //
    // Audio filter GUID For VS4 Input 7
    //
    // {910C304B-AA1A-45B0-A49C-DCB87FC357C4}
    DEFINE_GUID(CLSID_MatroxVS4Input7DirectShowAudioCaptureFilter, 
        0x910c304b, 0xaa1a, 0x45b0, 0xa4, 0x9c, 0xdc, 0xb8, 0x7f, 0xc3, 0x57, 0xc4);

    //
    // Audio filter GUID For VS4 Input 8
    //
    // {6B183F12-FA20-4ECB-9028-FC02D97AAD97}
    DEFINE_GUID(CLSID_MatroxVS4Input8DirectShowAudioCaptureFilter, 
        0x6b183f12, 0xfa20, 0x4ecb, 0x90, 0x28, 0xfc, 0x2, 0xd9, 0x7a, 0xad, 0x97);

    enum MV_VIDEO_STANDARD
    {
        keMvVideoStandard_Invalid,
        keMvVideoStandard_NTSC,
        keMvVideoStandard_PAL,
        keMvVideoStandard_720p_50_fps,
        keMvVideoStandard_720p_60_fps,
        keMvVideoStandard_720p_59_94_fps,
        keMvVideoStandard_1080i_25_fps,
        keMvVideoStandard_1080psf_25_fps,
        keMvVideoStandard_1080p_25_fps,
        keMvVideoStandard_1080i_29_97_fps,
        keMvVideoStandard_1080psf_29_97_fps,
        keMvVideoStandard_1080p_29_97_fps,
        keMvVideoStandard_1080p_30_fps,
        keMvVideoStandard_1080psf_23_98_fps,
        keMvVideoStandard_1080p_23_98_fps,
        keMvVideoStandard_1080psf_24_fps,
        keMvVideoStandard_1080p_24_fps,
        keMvVideoStandard_Last
    };

    enum MV_VIDEO_INPUT
    {
        keMvVideoInput_Invalid,
        keMvVideoInput_Composite,
        keMvVideoInput_S_Video,
        keMvVideoInput_Component,
        keMvVideoInput_SDI,
        keMvVideoInput_HDMI,
        keMvVideoInput_Last
    };

    enum MV_AUDIO_INPUT
    {
        keMvAudioInput_Invalid,
        keMvAudioInput_SDI_Channel_1_2,
        keMvAudioInput_SDI_Channel_3_4,
        keMvAudioInput_SDI_Channel_5_6,
        keMvAudioInput_SDI_Channel_7_8, 
        keMvAudioInput_RCA_Channel_1_2, 
        keMvAudioInput_XLR_Channel_1_2,
        keMvAudioInput_XLR_Channel_3_4,
        keMvAudioInput_AESEBU_Channel_1_2,
        keMvAudioInput_AESEBU_Channel_3_4,
        keMvAudioInput_HDMI_Channel_1_2,
        keMvAudioInput_Last
    };

    enum MV_VIDEO_FRAMESIZE
    {
        keMvVideoFrameSize_Invalid,
        keMvVideoFrameSize_160x90,
        keMvVideoFrameSize_160x120,
        keMvVideoFrameSize_320x180,
        keMvVideoFrameSize_320x240,
        keMvVideoFrameSize_368x208,
        keMvVideoFrameSize_480x270,
        keMvVideoFrameSize_640x272,
        keMvVideoFrameSize_640x360,
        keMvVideoFrameSize_640x480,
        keMvVideoFrameSize_720x480,
        keMvVideoFrameSize_720x576,
        keMvVideoFrameSize_960x540,
        keMvVideoFrameSize_1024x576,
        keMvVideoFrameSize_1024x768,
        keMvVideoFrameSize_1280x720,
        keMvVideoFrameSize_1440x1080,
        keMvVideoFrameSize_1920x1080,
        keMvVideoFrameSize_720x486,
        keMvVideoFrameSize_Last
    };

    enum MV_VIDEO_FRAMERATE
    {
        keMvVideoFrameRate_Invalid,
        keMvVideoFrameRate_11_99 = 11,
        keMvVideoFrameRate_12    = 12,
        keMvVideoFrameRate_12_5  = 13,
        keMvVideoFrameRate_14_98 = 14,
        keMvVideoFrameRate_15    = 15,
        keMvVideoFrameRate_23_98 = keMvVideoFrameRate_11_99 * 2,
        keMvVideoFrameRate_24    = keMvVideoFrameRate_12 * 2,
        keMvVideoFrameRate_25    = keMvVideoFrameRate_12_5 * 2,
        keMvVideoFrameRate_29_97 = keMvVideoFrameRate_14_98 * 2,
        keMvVideoFrameRate_30    = keMvVideoFrameRate_15 * 2,
        keMvVideoFrameRate_50    = keMvVideoFrameRate_25 * 2,
        keMvVideoFrameRate_59_94 = keMvVideoFrameRate_29_97 * 2,
        keMvVideoFrameRate_60    = keMvVideoFrameRate_30 * 2,
        keMvVideoFrameRate_Last,
    };
    
    
    //////////////////////////////////////////////////////////////////////////////////
    //
    // Summary: 
    //    Interface used to set all the Matrox A/V Input DirectShow filter properties.
    //
    //////////////////////////////////////////////////////////////////////////////////
    DECLARE_INTERFACE_(IMvInputCaptureSettings, IUnknown) {
        //
        // Summary:
        //    Gets the number of video input formats that are supported on the Matrox MXO2, Mojito MAX, or VS4 hardware. The number returned
        //    for the VS4 will always be one, representing the video input format last auto detected. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - This method is used to get the maximum number for the index value in the IMvInputCaptureSettings::GetAvailableVideoStandard() method.
        //
        STDMETHOD(GetNumberOfAvailableVideoStandards) (THIS_
            unsigned long * out_ulNumVideoStandards   // Indicates the total number of video input formats that can be used.
            ) PURE;

        //
        // Summary:
        //    Gets an available video input format on the Matrox MXO2, Mojito MAX, or VS4 hardware. There will only be one available video input format on
        //    the VS4; the video format that was last set with the auto-detect.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - VFW_S_NO_MORE_ITEMS, if the end of the video input formats list has been reached.
        // Remarks:
        //    - To get all the available video input formats, call the IMvInputCaptureSettings::GetAvailableVideoStandard() method the amount of times indicated by out_ulNumVideoStandards, which is returned by GetNumberOfAvailableVideoStandards(). 
        //      The index value passed should be zero to retrieve the first available video input format, and increased for each consecutive call, up to the value of out_ulNumVideoStandards minus one. 
        //
        STDMETHOD(GetAvailableVideoStandard) (THIS_
            unsigned long in_ulIndex,                      // Zero-based index value for the video input format.
            MV_VIDEO_STANDARD * out_peMvVideoStandard      // Pointer to the MV_VIDEO_STANDARD enum containing the video input format corresponding to the indicated index value.
            ) PURE;

        //
        // Summary:
        //    Gets the current video input format. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        STDMETHOD(GetCurrentVideoStandard) (THIS_
            MV_VIDEO_STANDARD * out_peMvVideoStandard     // Pointer to the MV_VIDEO_STANDARD enum containing the current video input format.
            ) PURE;

        //
        // Summary:
        //    Sets the current video input format. On the VS4, any call to Set with a video input format different from what was last auto-detected will fail.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - E_FAIL, if an invalid value was passed to the method.
        //    - MV_W_CAPTURE_SETTINGS_CHANGED, if any of the other filter properties have changed as a result of changing the video input format.
        //    - MV_W_NOT_SUPPORTED, if the method was called when the filter was running.
        // Remarks:
        //    - When a selected video input format is not compatible with a selected filter property, the incompatible filter property will be changed internally to the first setting that supports the video input format. 
        //      For example, if the selected video input format is NTSC and the current video input source is HDMI, the video input source will be changed internally to an input source that supports the NTSC video input format. 
        //      Call all the "Get" methods to determine all the new available and current settings.
        //
        STDMETHOD(SetCurrentVideoStandard) (THIS_
            MV_VIDEO_STANDARD in_eMvVideoStandard         // Indicates which video input format from the MV_VIDEO_STANDARD enum to set as the current video input format.
            ) PURE;

        //
        // Summary:
        //    Gets the number of video input sources that are available on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - The available video input sources depend on your selected video input format. 
        //    - This method is used to get the maximum number for the index value in the IMvInputCaptureSettings::GetAvailableVideoInput() method.
        //
        STDMETHOD(GetNumberOfAvailableVideoInputs) (THIS_
            unsigned long * out_ulNumVideoInputs          // Indicates the total number of video input sources that can be used.
            ) PURE;

        //
        // Summary:
        //    Gets an available video input source on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - VFW_S_NO_MORE_ITEMS, if the end of the video input sources list has been reached.
        // Remarks:
        //    - To get all the available video input sources, call the IMvInputCaptureSettings::GetAvailableVideoInput() method the amount of times indicated by out_ulNumVideoInputs, which is returned by GetNumberOfAvailableVideoInputs(). 
        //      The index value passed should be zero to retrieve the first available video input source, and increased for each consecutive call, up to the value of out_ulNumVideoInputs minus one.
        //
        STDMETHOD(GetAvailableVideoInput) (THIS_
            unsigned long in_ulIndex,                 // Zero-based index value for the video input source.
            MV_VIDEO_INPUT * out_peMvVideoInput       // Pointer to the MV_VIDEO_INPUT enum containing the video input source corresponding to the indicated index value.
            ) PURE;

        //
        // Summary:
        //    Gets the current video input source. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        STDMETHOD(GetCurrentVideoInput) (THIS_
            MV_VIDEO_INPUT * out_peMvVideoInput      // Pointer to the MV_VIDEO_INPUT enum containing the current video input source.
            ) PURE;

        //
        // Summary:
        //    Sets the current video input source.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - E_FAIL, if an invalid value was passed to the method.
        //    - MV_W_CAPTURE_SETTINGS_CHANGED, if any of the other filter properties have changed as a result of changing the video input source.
        //    - MV_W_NOT_SUPPORTED, if the method was called when the filter was running.
        // Remarks:
        //    - When a selected video input source is not compatible with a selected filter property, the incompatible filter property will be changed internally to the first setting that supports the video input source. 
        //      For example, if the selected video input source is HDMI and the audio input source is currently an SDI channel pair, the audio input source will be changed internally to an HDMI audio channel pair. 
        //      Call all the "Get" methods to determine all the new available and current settings.
        //
        STDMETHOD(SetCurrentVideoInput) (THIS_
            MV_VIDEO_INPUT in_eMvVideoInput          // Indicates which video input source from the MV_VIDEO_INPUT enum to set as the current video input source.
            ) PURE;

        //
        // Summary:
        //    Gets the number of audio input sources that are available on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - The available audio input sources depend on your selected video input source. 
        //    - For audio with multiple channels, such as embedded audio from an SDI input source, the audio channels are separated into different input pairs.
        //    - This method is used to get the maximum number for the index value in the IMvInputCaptureSettings::GetAvailableAudioInput() method.
        //
        STDMETHOD(GetNumberOfAvailableAudioInputs) (THIS_
            unsigned long * out_ulNumAudioInputs     // Indicates the total number of audio input sources that can be used.
            ) PURE;

        //
        // Summary:
        //    Gets an available audio input source on the Matrox MXO2, Mojito MAX, or VS4 hardware hardware in the current configuration.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - VFW_S_NO_MORE_ITEMS, if the end of the audio input sources list has been reached.
        // Remarks:
        //    - To get all the available audio input sources, call the IMvInputCaptureSettings::GetAvailableAudioInput() method the amount of times indicated by out_ulNumAudioInputs, which is returned by GetNumberOfAvailableAudioInputs(). 
        //      The index value passed should be zero to retrieve the first available audio input source, and increased for each consecutive call, up to the value of out_ulNumAudioInputs minus one. 
        //
        STDMETHOD(GetAvailableAudioInput) (THIS_
            unsigned long in_ulIndex,                // Zero-based index value for the audio input source.
            MV_AUDIO_INPUT * out_peMvAudioInput      // Pointer to the MV_AUDIO_INPUT enum containing the audio input source corresponding to the indicated index value.
            ) PURE;

        //
        // Summary:
        //    Gets the current audio input source. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        STDMETHOD(GetCurrentAudioInput) (THIS_
            MV_AUDIO_INPUT * out_peMvAudioInput      // Pointer to the MV_AUDIO_INPUT enum containing the current audio input source.
            ) PURE;

        //
        // Summary:
        //    Sets the current audio input source. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - E_FAIL, if an invalid value was passed to the method.
        STDMETHOD(SetCurrentAudioInput) (THIS_
            MV_AUDIO_INPUT in_eMvAudioInput          // Indicates which audio input source from the MV_AUDIO_INPUT enum to set as the current audio input source.
            ) PURE;

        //
        // Summary:
        //    Gets the number of video frame sizes that are available on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. The number returned
        //    for the VS4 will always be one, representing the video frame size of the video input format last auto detected. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - The available video frame sizes depend on your selected video input format, with the largest video frame size resolution corresponding to the video input format. 
        //    - This method is used to get the maximum number for the index value in the IMvInputCaptureSettings::GetAvailableVideoScaledFrameSize() method.
        //
        STDMETHOD(GetNumberOfAvailableVideoScaledFrameSizes) (THIS_
            unsigned long * out_ulNumVideoScaledFrameSizes             // Indicates the total number of video frame sizes that can be used.
            ) PURE;

        //
        // Summary:
        //    Gets an available video frame size on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. There will only be one available video frame size on
        //    the VS4; the video frame size of the video input format that was last set with the auto-detect.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - VFW_S_NO_MORE_ITEMS, if the end of the video frame sizes list has been reached.
        // Remarks:
        //    - To get all the available video frame sizes, call the IMvInputCaptureSettings::GetAvailableVideoScaledFrameSize() method the amount of times indicated by out_ulNumVideoScaledFrameSizes, which is returned by GetNumberOfAvailableVideoScaledFrameSizes(). 
        //      The index value passed should be zero to retrieve the first available video frame size, and increased for each consecutive call, up to the value of out_ulNumVideoScaledFrameSizes minus one.
        //
        STDMETHOD(GetAvailableVideoScaledFrameSize) (THIS_
            unsigned long in_ulIndex,                              // Zero-based index value for the video frame size.
            MV_VIDEO_FRAMESIZE * out_peMvVideoScaledFrameSize      // Pointer to the MV_VIDEO_FRAMESIZE enum containing the video frame size corresponding to the indicated index value.
            ) PURE;

        //
        // Summary:
        //    Gets the current video frame size.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        STDMETHOD(GetCurrentVideoScaledFrameSize) (THIS_
            MV_VIDEO_FRAMESIZE * out_peMvVideoScaledFrameSize      // Pointer to the MV_VIDEO_FRAMESIZE enum containing the current video frame size.
            ) PURE;

        //
        // Summary:
        //    Sets the current video frame size. On the VS4, any call to Set with a video frame size different from what was last auto-detected will fail.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - E_FAIL, if an invalid value was passed to the method.
        //    - MV_W_NOT_SUPPORTED, if the method was called when the filter was running.
        // Remarks:
        //    - The video frame size is the resolution of the buffer that is output on the video output pin.
        //    - The video is captured at the resolution of the video input format, and if the selected video frame size is smaller than the video input format (for the Matrox MXO2 or Mojito MAX, not VS4), the video is scaled down to the lower resolution using the onboard scaler. 
        //      If you do not want to scale the video, select a video frame size that corresponds to the video input format. For example, if the video input format is 1080p @ 30 fps, select a frame size that is 1920 × 1080.
        //    - You can only select a video frame size that is equal to or less than the video input format.
        //
        STDMETHOD(SetCurrentVideoScaledFrameSize) (THIS_
            MV_VIDEO_FRAMESIZE in_eMvVideoScaledFrameSize        // Indicates which video frame size from the MV_VIDEO_FRAMESIZE enum to set as the current video frame size.
            ) PURE;

        //
        // Summary:
        //    Gets the number of video frame rates that are available on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. The number returned
        //    for the VS4 will always be one, representing the video frame rate of the video input format last auto detected. 
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - The available video frame rates depend on the video input format. 
        //    - The video frame rate can be the same or half the frame rate of the selected video input format. 
        //      If the selected video input format has a frame rate of 50 or 59.94 fps, however, the video frame rate can be the same, half, or one-quarter of the video input format's frame rate. 
        //    - This method is used to get the maximum number for the index value in the IMvInputCaptureSettings::GetAvailableVideoScaledFrameRate() method.
        //
        STDMETHOD(GetNumberOfAvailableVideoScaledFrameRates) (THIS_
            unsigned long * out_ulNumVideoScaledFrameRates       // Indicates the total number of video frame rates that can be used.
            ) PURE;

        //
        // Summary:
        //    Gets an available video frame rate on the Matrox MXO2, Mojito MAX, or VS4 hardware in the current configuration. There will only be one available video frame rate on
        //    the VS4; the video frame rate of the video input format that was last set with the auto-detect.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - VFW_S_NO_MORE_ITEMS, if the end of the video frame rates list has been reached.
        // Remarks:
        //    - To get all the available video frame rates, call the IMvInputCaptureSettings::GetAvailableVideoScaledFrameRate() method the amount of times indicated by out_ulNumVideoScaledFrameRates, which is returned by GetNumberOfAvailableVideoScaledFrameRates(). 
        //      The index value passed should be zero to retrieve the first available video frame rate, and increased for each consecutive call, up to the value of out_ulNumVideoScaledFrameRates minus one.
        //
        STDMETHOD(GetAvailableVideoScaledFrameRate) (THIS_
            unsigned long in_ulIndex,                            // Zero-based index value for the video frame rate.
            MV_VIDEO_FRAMERATE * out_peMvVideoScaledFrameRate    // Pointer to the MV_VIDEO_FRAMERATE enum containing the video frame rate corresponding to the indicated index value.
            ) PURE;

        //
        // Summary:
        //    Gets the current video frame rate.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //
        STDMETHOD(GetCurrentVideoScaledFrameRate) (THIS_
            MV_VIDEO_FRAMERATE * out_peMvVideoScaledFrameRate     // Pointer to the MV_VIDEO_FRAMERATE enum containing the current video frame rate.
            ) PURE;

        //
        // Summary:
        //    Sets the current video frame rate.  On the VS4, any call to Set with a video frame rate different from what was last auto-detected will fail.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        //    - E_FAIL, if an invalid value was passed to the method.
        //    - MV_W_NOT_SUPPORTED, if the method was called when the filter was running.
        // Remarks:
        //    - The video frame rate is the rate at which buffers are output on the video output pin.
        //    - The video is captured at the frame rate of the video input format, and if the selected video frame rate is lower than the frame rate of the video input format, the video is downsampled to the lower frame rate. 
        //      If you do not want to downsample the video, select a video frame rate that corresponds to the video input format. For example, if the video input format is 1080p @ 30 fps, select a frame rate of 30 fps.
        //    - The video frame rate can be the same or half the frame rate of the selected video input format for the Matrox MXO2 or Mojito Max (not VS4). 
        //      If the selected video input format has a frame rate of 50 or 59.94 fps, however, the video frame rate can be the same, half, or one-quarter of the video input format's frame rate.
        //
        STDMETHOD(SetCurrentVideoScaledFrameRate) (THIS_
            MV_VIDEO_FRAMERATE in_eMvVideoScaledFrameRate        // Indicates which video frame rate from the MV_VIDEO_FRAMERATE enum to set as the current video frame rate.
            ) PURE;

        //
        // Summary:
        //    Indicates whether or not the video settings can be changed in the current state.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - This method can be used to determine if MV_W_NOT_SUPPORTED will be returned if a Set() method is called when the filter is running. 
        STDMETHOD(CanVideoSettingsBeChangedInCurrentState) (THIS_
            bool * out_bvideoSettingsCanbeChanged                 //  Pointer to the boolean indicating whether or not the settings can be changed. If true, the settings can be changed because the filter is in a stopped state. Otherwise, false.
            ) PURE;

    };

    //////////////////////////////////////////////////////////////////////////////////
    //
    // Summary: 
    //    Interface used to initialize all the Matrox A/V Input DirectShow or Matrox VS4 Input filter properties
    //    specific to the Matrox hardware installed.
    //
    //////////////////////////////////////////////////////////////////////////////////
    DECLARE_INTERFACE_(IMvInputCaptureSettingsInitializer, IUnknown) {
        //
        // Summary:
        //    Initializes the Matrox A/V Input DirectShow filter or Matrox VS4 Input filter properties that are specific to the type of Matrox MXO2, Mojito MAX or VS4 hardware installed.
        // Return value:
        //    - MV_NOERROR, if completed successfully. 
        // Remarks:
        //    - This method is used so that the Matrox A/V Input DirectShow filter properties are valid for the specific type of Matrox MXO2 or Mojito MAX hardware installed.
        //    - This method is used so that the Matrox VS4 Input DirectShow filter properties are valid for the Matrox VS4 installed.
        //    - This method should be called prior to using the IMvInputCaptureSettings interface so that the correct settings for your specific hardware are correctly represented with the IMvInputCaptureSettings interface.
        //    - This method needs to be called only if you are not using the Matrox A/V Input or Matrox VS4 Input DirectShow filter property page and using the IMvInputCaptureSettings interface to create your own settings page.  This method is
        //      internally called when the property page of the filter is shown.
        //    - This method needs to be called only once after installing the Matrox MXO2, Mojito MAX or VS4 hardware but can be called every time prior to using the IMvInputCaptureSettings interface.
        //    - This method will also auto detect the video input format (for the VS4 hardware only) and set the correct settings according to that video input format detected.
        STDMETHOD(InitializeMatroxCaptureSettings) () PURE;

    };

    //////////////////////////////////////////////////////////////////////////////////
    //
    // Summary: 
    //    Interface used to auto detect video standards and retrieve video input status on 
    //    Matrox VS4 inputs on the Matrox VS4 DirectShow Input Filters.
    //
    //////////////////////////////////////////////////////////////////////////////////
    DECLARE_INTERFACE_(IMvInputCaptureSettingsDetection, IUnknown) {
       // Summary:
       //    Auto detects the video input format on the Matox VS4 input and sets the filter settings
       //    and filter's mediatype according to the video input format detected.
       // Return value:
       //    - MV_NOERROR, if completed successfully. 
       //    - E_FAIL, if an invalid value was passed to the method.
       //    - MV_W_NOT_SUPPORTED, if the method was called when the filter was running.
       // Remarks:
       //    - The IMvInputCaptureSettings interface is supported on the class of Matrox VS4 Directshow Input filters.  However, the settings
       //    - that are available are limited to the video input format detected.  Thus all settings except for the audio input will only 
       //    - provide one option representing the video input format. 
       //
       STDMETHOD(AutoDetectAndSetResolutionSettings) (        
          ) PURE;

       // Summary:
       //    Gets the input status of the Matrox VS4 input.
       // Return value:
       //    - MV_NOERROR, if completed successfully. 
       //    - E_FAIL, if an invalid value was passed to the method.
       // Remarks:
       //
       STDMETHOD(GetInputStatus) (THIS_
          bool * out_bIsConnected,                 //  Pointer to the boolean indicating whether or not the input is connected.
          bool * out_bIsInputResolutionMismatch    //  Pointer to the boolean indicating whether or not the input resolution programmed mismatches what is connected
          ) PURE;
    };

#ifdef __cplusplus
}
#endif

#endif // __IMVDINPUTCAPTURESETTINGS__

