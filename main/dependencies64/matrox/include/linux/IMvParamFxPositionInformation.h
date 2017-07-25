//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvParamFxPositionInformation.h $
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
//                    IMVPARAMFXPOSITIONINFORMATION.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             AUGUST 3, 2003 - 8:31:57 PM
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVPARAMFXPOSITIONINFORMATION_H
#define IMVPARAMFXPOSITIONINFORMATION_H

//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMvParamFxPositionInformation
//==========================================================================;

/**
 * Provides information on the position and Editing Resolution to the Parametric Effect.<br>
 * <br><b>Remark:</b>
 * <ul><li>None.</ul>
 * @interface
 */
interface IMvParamFxPositionInformation : public IUnknown
{
public:

   /**
    * Retrieves the CutList ID of the TimeLine associated with the Parametric Effect. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_pulTimelineCutListID: Pointer to receive the TimeLine CutList ID.
    */
   virtual HRESULT __stdcall GetTimelineCutListID(unsigned long * out_pulTimelineCutListID) = 0;

   /**
    * Retrieves the the TimeLine In-Point associated with the Parametric Effect. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if operation completed successfully.
    * </ul>
    * @param out_pui64TimelineInPointInFrames: Pointer to receive the TimeLine In-Point.
    */
   virtual HRESULT __stdcall GetTimelineInPoint(uint64_t * out_pui64TimelineInPointInFrames) = 0;

   /**
    * Retrieves the TimeLine Out-Point associated with the Parametric Effect. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_pui64TimelineOutPointInFrames: Pointer to receive the TimeLine Out-Point.
    */
   virtual HRESULT __stdcall GetTimelineOutPoint(uint64_t * out_pui64TimelineOutPointInFrames) = 0;

   /**
    * Retrieves the In-Point of the Parameter provider. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_pui64ParamProviderTrimInInFrames: Pointer to receive the Parameter Provider In-Point.
    */
   virtual HRESULT __stdcall GetParamProviderTrimIn(uint64_t * out_pui64ParamProviderTrimInInFrames) = 0;

   /**
    * Retrieves the Out-Point of the Parameter provider. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_pui64ParamProviderTrimOutInFrames: Pointer to receive the Parameter Provider Out-Point.
    */
   virtual HRESULT __stdcall GetParamProviderTrimOut(uint64_t * out_pui64ParamProviderTrimOutInFrames) = 0;

   /**
    * Retrieves the Granularity of the Parameter provider. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>The granularity is calculated by converting the range of Timeline to the Parameter Provider range. Thus it determines how much the granularity in the timeline corresponds to in the Parameter provider unit. 
    * <ul><li>In progressive, the granularity of the Timeline is 1.0 (every frame). In interlace, it is 0.5 (every field).
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_pdParamProvGranularityInFrames: Pointer to receive the granularity.
    */
   virtual HRESULT __stdcall GetParamProviderGranularity(double * out_pdParamProvGranularityInFrames) = 0;

   /**
    * Retrieves the Editing resolution set on the Parametric Effect. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if the parameter was invalid.
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_ppksEditingResInfo: Pointer to receive the editing resolution.
    */
   virtual HRESULT __stdcall GetEditingResolutionInfo( const SMvResolutionInfo ** out_ppksEditingResInfo ) = 0;

   /**
    * Converts the coordinates given from the Parameter Provider unit to Timeline frames. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if one of the parameters was invalid (position out of range, invalid out_pui64TimelinePosInFrames, or incorrect in_eRoundingType value).
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param in_dParamProvPosInFrames: Position to convert.
    * @param in_eRoundingType: Rounding type, in the case where the position given does not fall exactly into a timeline position.
    * @param out_pui64TimelinePosInFrames: Pointer to receive the position in TimeLine frames.
    */
   virtual HRESULT __stdcall ConvertPosFromParamProvToTimelineFrames(double in_dParamProvPosInFrames,
                                                                     EMvRoundingType in_eRoundingType,
                                                                     uint64_t * out_pui64TimelinePosInFrames) = 0;

   /**
    * Converts the coordinate given from Timeline frames to Parameter Provider unit. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if one of the parameters was invalid (position out of range, invalid out_pdParamProvPosInFrames, or incorrect in_eRoundingType value).
    * <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param in_ui64TimelinePosInFrames: Position to convert.
    * @param in_eRoundingType: Rounding type, in the case where the position given does not fall exactly into a Parameter Provider position.
    * @param out_pdParamProvPosInFrames: Pointer to receive the position in Parameter Provider unit.
    */
   virtual HRESULT __stdcall ConvertPosFromTimelineFramesToParamProv(uint64_t in_ui64TimelinePosInFrames,
                                                                     EMvRoundingType in_eRoundingType,
                                                                     double * out_pdParamProvPosInFrames) = 0;

   /**
    * Converts the coordinates given from Parameter Provider unit to ERes unit. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>In progressive, this function returns the same value as ConvertPosFromParamProvToTimelineFrames. Otherwise, it returns twice as much.
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if one of the parameters was invalid (position out of range, invalid out_pui64TimelinePosInERes, or incorrect in_eRoundingType value).
    * <li>MV_NOERROR, if operation completed successfully.
    * </ul>
    * @param in_dParamProvPosInFrames: Position to convert.
    * @param in_eRoundingType: Rounding type, in the case where the position given does not fall exactly into a timeline position.
    * @param out_pui64TimelinePosInERes: Pointer to receive the position in TimeLine frames.
    */
   virtual HRESULT __stdcall ConvertPosFromParamProvToTimelineERes(  double in_dParamProvPosInFrames,
                                                                     EMvRoundingType in_eRoundingType,
                                                                     uint64_t * out_pui64TimelinePosInERes) = 0;

   /**
    * Converts the coordinates given from Timeline ERes to Parameter Provider unit. 
    * 
    * <br><b>Remark:</b>
    * <ul><li>In progressive, this function returns the same value as _convertPosFromTimelineToParamProv. 
    * </ul>
    * 
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    * 
    * <b>Return Values:</b>
    * <ul><li>MV_E_FAIL, if one of the parameter was invalid (position out of range, invalid out_pdParamProvPosInFrames, or incorrect in_eRoundingType value).
    * <li>MV_NOERROR, if operation completed successfully.
    * </ul>
    * @param in_ui64TimelinePosInFrames: Position to convert.
    * @param in_eRoundingType: Rounding type, in the case where the position given does not fall exactly into a Parameter Provider position.
    * @param out_pdParamProvPosInFrames: Pointer to receive the position in Parameter Provider unit.
    */
   virtual HRESULT __stdcall ConvertPosFromTimelineEResToParamProv(  uint64_t in_ui64TimelinePosInERes,
                                                                     EMvRoundingType in_eRoundingType,
                                                                     double * out_pdParamProvPosInFrames) = 0;

};


#endif //IMVPARAMFXPOSITIONINFORMATION_H
