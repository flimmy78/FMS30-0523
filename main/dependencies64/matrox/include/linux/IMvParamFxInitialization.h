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
//                    IMVPARAMFXINITIALIZATION.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             JULY 23, 2003 - 6:03:35 PM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVPARAMFXINITIALIZATION_H
#define IMVPARAMFXINITIALIZATION_H

//==========================================================================;
// Header files
//==========================================================================;

#include "mvUnknown.h"
#include "IMvParametersProvider.h"

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMv
//==========================================================================;

/**
 * This interface is used to initialize a Parametric Effect once it is created.<br>
 * <br><b>Remark:</b>
 * <ul><li>Even if an effect is split into many segments, only one Parametric Effect is created for all of them, and
 * is referenced into the effect tree of each segment. The Parametric Effect is initialized for the whole region it
 * covers by calling the SetTimelineRegion function.</ul>
 * <ul><li>Once your Parametric Effect is fully initialized and referenced in the effect tree of one
 * or more segments, you must call the (TBD AnalyseSeek TBD) function for each of these segments.</ul>
 * @interface
*/
interface IMvParamFxInitialization : public IUnknown
{
   //==========================================================================;
   // Public operations
   //==========================================================================;
public:

   /**
    * Indicates in which cutlist and over which timeline period the Parametric Effect will be
    * used. Basically, this function indicates all timeline positions for which your effect will generate Effect Settings.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>Even if the effect is split over many segments, the timeline region refers to the overall region
    * (including all the segments) covered by the effect.</ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_EMPTY_RANGE, if the range specified is empty.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module reported an error.
    * </ul>
    * @param in_ulCutlistID: ID of the cutlist containing the effect tree(s) that reference the Parametric Effect.
    * @param in_ui64TimelineInPointInFrames: Frame position of the beginning of the first segment referencing the Parametric Effect. This value is inclusive.
    * @param in_ui64TimelineOutPointInFrames: Frame position of the end of the last segment referencing the Parametric Effect. This value is exclusive. */
   virtual HRESULT __stdcall SetTimelineRegion( unsigned long in_ulCutListID,
                                                uint64_t in_ui64TimelineInPointInFrames,
                                                uint64_t in_ui64TimelineOutPointInFrames) = 0;

   /**
   * Indicates in which cutlist the Parametric Effect will be used.
   * 
   * <br><b>Remark:</b>
   * <ul><li></ul>
   * 
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation completed successfully.
   * <li>MV_E_INVALIDARG, if a parameter is invalid.
   * <li>MV_E_EMPTY_RANGE, if the range specified is empty.
   * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
   * <li>ERROR CODE, if a module reported an error.
   * </ul>
   * @param in_ulCutlistID: ID of the cutlist containing the effect tree(s) that reference the Parametric Effect. */
   virtual HRESULT __stdcall SetCutListID( unsigned long in_ulCutListID ) = 0;

   /**
   * Indicates over which timeline period the Parametric Effect will be used.
   * Basically, this function indicates all timeline positions for which your effect will generate Effect Settings.<br>
   * 
   * <br><b>Remark:</b>
   * <ul><li>Even if the effect is split over many segments, the timeline region refers to the overall region
   * (including all the segments) covered by the effect.</ul>
   * 
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation completed successfully.
   * <li>MV_E_INVALIDARG, if a parameter is invalid.
   * <li>MV_E_EMPTY_RANGE, if the range specified is empty.
   * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
   * <li>ERROR CODE, if a module reported an error.
   * </ul>
   * @param in_ui64TimelineInPointInFrames: Frame position of the beginning of the first segment referencing the Parametric Effect. This value is inclusive.
   * @param in_ui64TimelineOutPointInFrames: Frame position of the end of the last segment referencing the Parametric Effect. This value is exclusive. */
   virtual HRESULT __stdcall SetTimelineRegion( uint64_t in_ui64TimelineInPointInFrames,
                                                uint64_t in_ui64TimelineOutPointInFrames) = 0;

   /**
    * Sets the Parameters Provider interface that the Parametric Effect uses to obtain the parameters.<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>The same Parameters Provider can be attached to many Parametric Effects as long as they are compatible. If they are incompatible, the function will fail. To be compatible, two Parametric Effects must at least have the same GUID. Also, depending on the implementation, the Parameters Provider may validate some other specific information before accepting to be attached to multiple Parametric Effects </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module called reported an error.
    * </ul>
    * @param in_pIParamProvider: Pointer to the Parameters Provider interface to attach.
   */
   virtual HRESULT __stdcall AttachParametersProvider(IMvParametersProvider * in_pIParamProvider) = 0;

   /**
   * Indicates over which values the provider will be used. 
   * The time line region will be mapped to the values provided here whenever calling the provider.<br>
   * 
   * <br><b>Remark:</b>
   * <ul><li>Because the Parameters Provider can generate parameters over a period of time, you have to specify which region (Trim-In and Trim-Out) of the Parameters Provider will map to the timeline region set on the Parametric Effect to which you attach it.</ul>
   * 
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   * 
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR, if operation completed successfully.
   * <li>MV_E_EMPTY_RANGE, if the specified range is empty.
   * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
   * <li>ERROR CODE, if a module called reported an error.
   * </ul>
   * @param in_ui64TrimInInFrames: Frame position, in the Parameters Provider, that maps to the In point of the timeline region set in the Parametric Effect.
   * @param in_ui64TrimOutInFrames: Frame position, in the Parameters Provider, that maps to the Out point of the timeline region set in the Parametric Effect.
   */
   virtual HRESULT __stdcall SetParametersProviderRegion(uint64_t in_ui64TrimInInFrames,
                                                         uint64_t in_ui64TrimOutInFrames) = 0;

   /**
    * Modifies the content of the currently attached Parameters Provider based on the content of the supplied Parameters Provider (source).<br>
    * 
    * <br><b>Remark:</b>
    * <ul><li>A Parameters Provider must already be attached to the Parametric Effect before calling this method.</ul>
    * <ul><li>The supplied Parameters Provider will NOT be modified. Only the attached Parameters Provider is modified.</ul>
    * <ul><li>This function is useful when converting from older versions of the Parametric Effect, of from another type of Parametric Effect.</ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    * <li>MV_E_INVALIDARG, if a parameter is invalid.
    * <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    * <li>ERROR CODE, if a module called reported an error.
    * </ul>
    * @param in_pISourceParamProv: Pointer to the Parameters Provider to be used as a source. */
   virtual HRESULT __stdcall UpdateAttachedParametersProvider(IMvParametersProvider * in_pISourceParamProv) = 0;

};


#endif //IMVPARAMFXINITIALIZATION_H
