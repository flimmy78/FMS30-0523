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
//--------------------------------------------------------------------------;


//----------------------------------------------------------------
//                    mvdAPI.h
//----------------------------------------------------------------
// @module  Matrox Video DirectShow public interfaces.
//
//----------------------------------------------------------------
//   Birth Date:       April 2003
//   Operating System: WinXP
//   Author:           DirectShow team
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//----------------------------------------------------------------

#ifndef _MVDAPI_H_
#define _MVDAPI_H_

#ifdef LINUX_PLATFORM
#include "mvdAPILinux.h"
#else

#include <stdlib.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

// Flex public
#include <MvFlexAPIPublicSDK.h>

// DirectShow SDK
#include <strmif.h>

// Our defines
#include "mvdDef.h"

// Overide our definition of IUnknown to avoid any conflict
#define DEFINE_MICROSOFT_IUNKNOWN

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interfaces definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "IMvCutListElement.h"
#include "IMvCutList.h"
#include "IMvCutList2.h"
#include "IMvCutListManager.h"
#include "IMvFilterCutListManager.h"
#include "IMvPausePositionNotification.h"
#include "IMvGraphStateControl.h"
#include "IMvFileCutListElement.h"
#include "IMvTreeCutListElement.h"
#include "IMvPullingCutListElement.h"
#include "IMvVideoCutListElement.h"
#include "IMvAudioCutListElement.h"
#include "IMvInputCutListElementNode.h"
#include "IMvLiveWindow.h"
#include "IMvLiveWindow2.h"
#include "IMvLiveWindow3.h"
#include "IMvLiveWindow4.h"
#include "IMvLiveWindowBitmapCallback.h"
#include "IMvMultiSinkFile.h"
#include "IMvMultiSinkSwitch.h"
#include "IMvMultiSinkCapture.h"
#include "IMvMultiSinkNonNativeCapture.h"
#include "IMvSwitcherMetaDataSupport.h"
#include "IMvSrcFilterSetProperties.h"
#include "IMvPullingCallBack.h"
#include "IMvFileSystemIONotifyState.h"
#include "IMvCustomFileSystemIO.h"
#include "IMvSetFileSystem.h"
#include "IMvFileValidation.h"
#include "IMvProfileLoader.h"
#include "IMvRIFFChunkIO.h"
#include "IMvdSpannedFiles.h"

//
// Parametric Effect interfaces...
//

// ...for usage of Parametric Effects
#include "IMvParametricEffect.h"
#include "IMvParamFxInitialization.h"
#include "IMvParametersProvider.h"
#include "IMvGFXFileNameProvider.h"

#include "IMvParametricEffectInfo.h"
#include "IMvParametricEffectInfoEnumerator.h"
#include "IMvParametricEffectInfoList.h"
#include "IMvParametricEffectRegistration.h"

#include "IMvGfxFileNameHelperInit.h"
#include "IMvGfxFileNameHelper.h"

// ...for development of Parametric Effects
#include "IMvParamFxPositionInformation.h"

//
// Tree description interfaces
//

// Basic tree node interfaces
#include "IMvEnumTreeNodes.h"
#include "IMvTreeNode.h"
#include "IMvTreeNodeParentLink.h"

// Pulling - pushing interfaces
#include "IMvVideoPulling.h"
#include "IMvAudioPulling.h"
#include "IMvVideoPushing.h"
#include "IMvAudioPushing.h"
#include "IMvVideoClosedCaptioningPulling.h"

// Specific tree node interfaces
#include "IMvSymbolicRootNode.h"
#include "IMvMonoToStereoNode.h"
#include "IMvOneMonoToStereoNode.h"
#include "IMvStereoToMonoNode.h"
#include "IMvCompositorNode.h"
#include "IMvUpstreamCompositorNode.h"
#include "IMvDownstreamCompositorNode.h"
#include "IMvConfidencePreviewNode.h"
#include "IMvAudioEffectNode.h"
#include "IMvAudioMuxerNode.h"
#include "IMvVideoEffectNode.h"
#include "IMvFilterEffectNode.h"
#include "IMvTransitionEffectNode.h"
#include "IMvInputAudioSourceMonoNode.h"
#include "IMvInputAudioSourceStereoNode.h"
#include "IMvInputAudioGeneratedNode.h"
#include "IMvInputAudioPullingNode.h"
#include "IMvInputVideoGeneratedNode.h"
#include "IMvInputVideoPullingNode.h"
#include "IMvInputVideoSourceNode.h"
#include "IMvOutputAudioNode.h"
#include "IMvOutputAudioPushingNode.h"
#include "IMvOutputAudioRendererNode.h"
#include "IMvOutputAudioSinkMonoNode.h"
#include "IMvOutputAudioSinkStereoNode.h"
#include "IMvOutputAudioPushingStereoNode.h"
#include "IMvOutputAudioPushingMonoNode.h"
#include "IMvOutputVideoNode.h"
#include "IMvOutputVideoRendererNode.h"
#include "IMvOutputVideoSinkNode.h"
#include "IMvOutputVideoPushingNode.h"

// MGF Reader
#include "IMvMGFReader.h"
#include "IMvMGF2Reader.h"
// MGF Writer
#include "IMvMGFWriter.h"
#include "IMvMGF2Writer.h"

// GFX Reader
#include "IMvGFXReader.h"
// GFX Writer
#include "IMvGFXWriter.h"

// Flex access interface from profile loader
#include "IMvFlexHelper.h"

// standalone reader interface
#include "IMvAVFileReader.h"

// Codec info interface from profile loader
#include "IMvCodecProfileInfo.h"

// Input Devices interface on Unified Input Filter.
#include "IMvInputDevices.h"

// interfaces for Output filters
#include "IMvDVOutState.h"
#include "IMvOutputDevices.h"
#include "IMvOutputDeviceSelector.h"
#include "IMvOutputDeviceEnumerator.h"

// Capture Settings and control interface on Unified Input Filter.
#include "IMvCaptureSettingsAndControl.h"
#include "IMvDirectSoundCaptureSettings.h"

// interfaces for media file info .

#include "IMvAudioVideoFileInfo.h"
#include "IMvGFXFileInfo.h"
#include "IMvMGFFileInfo.h"
#include "IMvAVReader.h"

// Interface to query for services to access files
#include "IMvFileHelper.h"

// graphics cutlist element 

#include "IMvGraphicsCutlistElement.h"
#include "IMvScrollingCutlistElement.h"

// interfaces for universal muxer .

#include "IMvVideocaptureproperties.h"
#include "IMvAudiocaptureproperties.h"
#include "IMvMuxingType.h"

// interfaces for audio renderer .

#include "IMvAudioRendererProperties.h"

// interfaces for Message Info object .

#include "IMvMessageCutlistInfo.h"
#include "IMvMessageFileInfo.h"
#include "IMvMessageGraphInfo.h"
#include "IMvMessageTimingInfo.h"
#include "IMvMessageTreeInfo.h"
#include "IMvMessageDSFilterInfo.h"
#include "IMvMessagePerformanceInfo.h"
#include "IMvMessageAVType.h"

// interfaces for Device Control.

#include "IMvExtDevice.h"
#include "IMvExtTimecodeReader.h"
#include "IMvExtTransport.h"
#include "IMvUnifiedDeviceControlInit.h"
#include "IMvUnifiedDeviceControl.h"
#include "IMvEnumExtDeviceControl.h"
#include "IMvDVInfo.h"

// interface for doing reverse pulldown

#include "IMvReversePulldown.h"

// interface for frame information

#include "IMvSourceDeviceFrameInfoCustomObject.h"

#include "IMvUIFStreamingInfoCustomObject.h"

// interface for access to render an effect

#include "IMvRenderEffect.h"

// interface for Matrox A/V Input Capture filter
#include "IMvInputCaptureSettings.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface IID's
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MvFlexGuidsPublicSDK.h"
#include "mvdIDS.h"

#endif // #else of #ifdef LINUX_PLATFORM

#endif /* _MVDAPI_H_ */

