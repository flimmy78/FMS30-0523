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
//                    IMVGRAPHCONTROL.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVGRAPHCONTROL_H
#define IMVGRAPHCONTROL_H
#include "mvUnknown.h"
#include "IMvPausePositionNotification.h"

/**
 * Graph state control interface.
 * @interface
 */
interface IMvGraphStateControl : public IUnknown
{
public:

   /**
    *  Seeks the graph to a certain timeline position.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * <li>
    * </ul>
    * @param <i>uint64_t in_ui64TimelinePositionInFrames</i>: Position to seek to.
    * @param <i>unsigned long in_ulCutlistID</i>: Cutlist ID. Used to know if we can flush
    *  the previous seek or not. When the ID's do not match there is no buffer cancellation.
    */
   virtual HRESULT __stdcall Seek( uint64_t in_ui64TimelinePositionInFrames,
                                   unsigned long in_ulCutlistID) = 0;

   /**
    *  Similar to a seek, except no data is loaded, and no rendering is done. Called by the OEM/end user to position the effect parameters.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport Command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>long in_ui64TimelinePositionInFrames </i>: Position to seek to.
    * @param <i>long in_ulCutlistID</i>: Cutlist ID. Used to know if we can flush the previous seek or not. When the ID's do not match there is no buffer cancellation.
    */
   virtual HRESULT __stdcall AnalysisSeek( uint64_t in_ui64TimelinePositionInFrames,
                                           unsigned long in_ulCutlistID) = 0;

   /**
    *  Pauses the graph for a playback operation.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport Command.
    * <li> The Looping flag setting will override the subsequent PlayAt looping flag.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t in_ui64PositionInFrames</i>: Position to begin playback from.
    * @param <i>bool     in_bLoop</i>               : Looping flag.
    * @param <i>double   in_dbRate</i>              : Playback rate.
    */
   virtual HRESULT __stdcall CuePlayback
   (
      uint64_t in_ui64TimelinePositionInFrames,
      bool     in_bLoop,
      double   in_dbRate
   ) = 0;

   /**
    *  Plays the graph at a certain time. The active Cutlist and PlayRegion apply to this call.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    * <li> Transport command.
    * <li> If a Pause command, with or without time designation, arrives before the PlayAt time has arrived (no buffer has been played), the next valid command is Stop.
    * <li> If this function is called right after a CuePlayback call, the Graph State Control module will ignore this looping flag, and will continue to use the looping flag set by the prior CuePlayback call. Only a stop state will reset this condition.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t   in_ui64SystemTimeToStart</i>: Time at which the graph should begin playback.
    * @param <i>uint64_t   in_ui64TimelinePositionInFrames</i>: Timeline position in frames.  
    * @param <i>bool       in_bLoop</i>: Looping flag.  
    */
   virtual HRESULT __stdcall PlayAt
   (
      uint64_t   in_ui64SystemTimeToStart,
      uint64_t   in_ui64TimelinePositionInFrames,
      bool       in_bLoop
   ) = 0;

   /**
    *  Used to pause the graph at a certain system time. This call should follow a Play command.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t in_ui64SystemTimeToPause</i>: System time at which to pause the graph.
    */
   virtual HRESULT __stdcall PauseAt
   (
      uint64_t in_ui64SystemTimeToPause
   ) = 0;

   /**
    *  Stops the graph.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport command.
    * <li> See IMvGraphStateControl for more information.
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
   virtual HRESULT __stdcall Stop() = 0;

   /**
    * Compiles the graph. The active Cutlist and PlayRegion apply to this call.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t in_ui64StartTimelinePositionInFrames</i>: The timeline position at which the compilation will start.
    */
   virtual HRESULT __stdcall Compile
   (
      uint64_t   in_ui64StartTimelinePositionInFrames
   ) = 0;

   /**
    * Compiles the graph with a realtime preview.
    * This implies that the output can limit the compile speed, however
    * if the compilation cannot be done in realtime, no frames will be dropped from the exported file.
    * The active Cutlist and PlayRegion apply to this call.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport Command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t in_ui64StartTimelinePositionInFrames</i>: The timeline position at which the compilation will start.
    */
   virtual HRESULT __stdcall RealtimeCompile
   (
      uint64_t   in_ui64StartTimelinePositionInFrames
   ) = 0;

   /**
	 * Playback with the live input active in the tree. For parameter description, see PlayAt.
    * The active Cutlist and PlayRegion apply to this call. 
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport Command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t   in_ui64SystemTimeToStart</i>: Time at which the graph should begin playback.
    * @param <i>uint64_t   in_ui64TimelinePositionInFrames</i>:  Timeline position in frames.  
    * @param <i>bool       in_bLoop</i>: Looping flag.  
    */
   virtual HRESULT __stdcall PlayAtAndCapture
   (
      uint64_t   in_ui64SystemTimeToStart,
      uint64_t   in_ui64TimelinePositionInFrames,
      bool       in_bLoop
   ) = 0;


   /**
	 * Shuttles the graph.
    * The active Cutlist and PlayRegion apply to this call.
    * <br><b>Remarks:</b>
    * <ul><i><li> Transport Command.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t   in_ui64SystemTimeToStart</i>: Time at which the graph should begin outputting.
    * @param <i>uint64_t   in_ui64TimelinePositionInFrames</i>: Timeline position in frames.
    * @param <i>bool       in_bLoop</i>: Looping flag.
    * @param <i>double     in_dblSpeed</i>: Rate at which to shuttle.
    */
   virtual HRESULT __stdcall Shuttle
   (
      uint64_t   in_ui64SystemTimeToStart,
      uint64_t   in_ui64TimelinePositionInFrames,
      bool       in_bLoop,
      double     in_dblSpeed
   ) = 0;

   /**
    *  Sets the playback shuttling rate.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>double in_dblSpeed</i>: New rate
    * @param <i>long   out_ui64ExpectedChangeTimelinePosition</i>: Position in the timeline at which the new rate is being used. 
    */
   virtual HRESULT __stdcall SetShuttleSpeed
   (
      double    in_dblSpeed,
      uint64_t& out_ui64ExpectedChangeTimelinePosition
   )  = 0;

   /**
    *  Gets the current playback rate.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>double out_dblSpeed</i>: Current rate. 
    */
   virtual HRESULT __stdcall GetShuttleSpeed
   (
         double &out_refdblSpeed
   )  = 0;

   /**
    *  Sets the valid region and cutlist for all playback type operations.
    *
    * <br><b>Remarks:</b>
    * <ul><li> Graph Settings and Properties.
    *  <li>Transport commands for which the playback region and Cutlist are used:
    *  <DIR>
    *  <li>CuePlayback
    *  <li>PlayAt
    *  <li>Compile
    *  <li>RealTimeCompile
    *  <li>Shuttle
    *  <li>PlayAtAndCapture
    *  </DIR>
    *  <li> Transport commands for which the Playback Region and Cutlist are not used:
    *  <DIR>
    *  <li>Seek
    *  <li>AnalysisSeek
    *  </DIR>
    *  <li> The inpoint is always inclusive and the outpoint is always exclusive in frames, regardless of the ERes and directions.
    * <li> See IMvGraphStateControl for more information.
    *  </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT 
  	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *  @param <i>uint64_t in_ui64RegionInInFrames </i>: Region In inclusive frame unit
    *  @param <i>uint64_t in_ui64RegionOutInFrames </i>: Region Out exclusive frame unit
    *  @param <i>unsigned long   in_ulCutlistID</i>: Cutlist ID
    */
   virtual HRESULT __stdcall SetPlaybackRegionAndCutlist
   (
      uint64_t in_ui64RegionInInFrames,
      uint64_t in_ui64RegionOutInFrames,
      unsigned long   in_ulCutlistID
   ) = 0;
    
   /**
    * Used to recover the current Playback Region and Cutlist.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t out_refui64RegionInInFrames</i>:  Region In.
    * @param <i>uint64_t out_refui64RegionOutInFrames</i>:  Region Out. 
    * @param <i>unsigned long out_refulCutlistID</i>:  Cutlist ID.
    */
   virtual HRESULT __stdcall GetPlaybackRegionAndCutlist
   (
      uint64_t &out_refui64RegionInInFrames,
      uint64_t &out_refui64RegionOutInFrames,
      unsigned long   &out_refulCutlistID
   ) = 0;

   /**
    *  Sets the output display mode for seek and pause.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>EMvOutputDisplayMode in_eMvOutputDisplayMode</i>:  Display mode to use.
    */
   virtual HRESULT __stdcall  SetDisplayModeForSeekAndPause
   (
      EMvOutputDisplayMode in_eMvOutputDisplayMode
   ) = 0;
    
   /**
    *  Gets the display mode for seek and pause.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>EMvOutputDisplayMode in_refeMvOutputDisplayMode</i>:  Display mode in use.
    */
   virtual HRESULT __stdcall  GetDisplayModeForSeekAndPause
   (
      EMvOutputDisplayMode& in_refeMvOutputDisplayMode
   ) = 0;

   /**
    *  Sets the seek preroll and postroll values for audio seeking.
    *
    * <br><b>Remarks:</b>
    * <ul>
    * <li> Graph Settings and Properties.
    * <li> Sets the seek preroll and postroll values for audio seeking. 
    * <li> See IMvGraphStateControl for more information.
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t in_ui64PreRollValueInFrames</i>:  Audio seek preroll value.
    * @param <i>uint64_t in_ui64PostRollValueInFrames</i>:  Audio seek postroll value.
    */
   virtual HRESULT __stdcall SetAudioSeekValues
   (
      uint64_t in_ui64PreRollValueInFrames,
      uint64_t in_ui64PostRollValueInFrames
   ) = 0;

   /**
    *  Retrieves the current seek preroll postroll values from the audio transform.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long out_refulPreRollValueInFrames</i>:  Audio seek preroll value.
    * @param <i>unsigned long out_refulPostRollValueInFrames</i>:  Audio seek postroll value.
    */
   virtual HRESULT __stdcall GetAudioSeekValues
   (
      uint64_t& out_refui64PreRollValueInFrames,
      uint64_t& out_refui64PostRollValueInFrames
   ) = 0;

   /**
    *  Retrieves the current mode and state of the graph.
    *
    * <br><b>Remarks:</b>
    * <ul>
    * <li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * <li> Modes:
    *<DIR>
    * <li>keMvModeNone
    * <li>keMvModePlayback
    * <li>keMvModeShuttle
    * <li>keMvModeSeeking
    * <li>keMvModeCapture
    * <li>keMvModeCompile
    * <li>keMvModeRealtimeCompile
    * </DIR>
    *
    * <li> States:
    * <DIR>
    * <li>keMvStateIntermediate
    * <li>keMvStateStopped
    * <li>keMvStateRunning
    * <li>keMvStatePaused
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
    * @param <i>EMvGraphMode  out_refemvdCurrentMode</i>:  Current mode.
    * @param <i>EMvGraphState out_refemvdCurrentState</i>:  Current state.
    */
   virtual HRESULT __stdcall GetModeAndState
   (
      EMvGraphMode&  out_refemvdCurrentMode,
      EMvGraphState& out_refemvdCurrentState
   ) = 0;

   /**
    * Sets the filter to be used as the position master of the graph.
    * Must be a Matrox filter.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IBaseFilter in_pIFilterToUse</i>:  Filter to use. Must be a Matrox filter.
    */
   virtual HRESULT __stdcall SetPositionMaster
   (
         IBaseFilter* in_pIFilterToUse
   ) = 0;
            
   /**
    *  Returns the current position and cutlist of the position master filter.
    *  
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long out_ulCutlistID</i>:  Current Cutlist ID.
    * @param <i>uint64_t out_ui64CurrentPositionAtOutputInFrames</i>:  Current position.
    */
   virtual HRESULT __stdcall GetCurrentPosition
   (
      unsigned long& out_ulCutlistID,
      uint64_t &out_ui64CurrentPositionAtOutputInFrames
   ) = 0;

   /**
 	 * Retrieves the Cutlist duration of the Cutlist specified.
    * If the Cutlist does not exist, then this function will return an error.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long in_ulCutlistID</i>:  Cutlist ID.
    * @param <i>uint64_t out_refui64CutlistDurationInFrames</i>:  Cutlist Duration.
    */
   virtual HRESULT __stdcall GetGraphDuration
   (
      unsigned long in_ulCutlistID,
      uint64_t &out_refui64CutlistDurationInFrames
   ) = 0;

    /**
	* Returns the current GraphID. A graph ID is 
    * unique within the process.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>unsigned long out_refulGraphID</i>:  Graph ID.
    */
   virtual HRESULT __stdcall GetGraphID
   (
      unsigned long& out_refulGraphID
   ) = 0;

   /**
    * Gets the time at which the first buffer from a given play will be shown.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t out_refui64LastPlayTime</i>:  System time at which the first buffer was shown.
    */
   virtual HRESULT __stdcall GetLastPlayTime
   (
         uint64_t& out_refui64LastPlayTime
   ) = 0;

   /**
    *  Retrieves the time at which the last buffer from a given play/pause transition will be shown.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t out_refui64LastPlayTime</i>:  System time at which the last buffer was shown.
    */
   virtual HRESULT __stdcall GetLastPauseTime
   (
         uint64_t& out_refui64LastPauseTime
   ) = 0;

   /**
    *   Recovers when the buffer from the last seek was shown.
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Graph Settings and Properties.
    * <li> See IMvGraphStateControl for more information.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>uint64_t out_refui64LastSeekTime</i>:  System time at which the buffer was shown.
    */
   virtual HRESULT __stdcall GetLastSeekTime
   (
         uint64_t& out_refui64LastSeekTime
   ) = 0;

   /**
    *   Enables the reporting of performance factor at each frame.     
    *
    * <br><b>Remarks:</b>
    * <ul><i><li> Performance factor will be reported asynchronously as a graph message at each frame scrubbed or played back. The Performance Factor is a value between 0.0 and 1.0 that measures the ability of the system's processor to play back the segment in real time. A value of 0.0 indicates that the processor is idle, and a value of 1.0 indicates that the system processor has barely enough performance to deliver the frame in real time.   
    * </i></ul>
    *  
    * <b>Return type:</b>
    * <ul><li>HRESULT
    * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>bool in_bDisableRenderers</i>:  This option can be used to disable the final delivery of the renderers (output to break-out-box, live window, etc.) without removing them from the processing path.
    */
   virtual HRESULT __stdcall EnablePerformanceReporting
   (
      bool in_bDisableRenderers
   ) = 0;

   /**
    *   Disables the reporting of performance factor.   *  
    * 
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
   virtual HRESULT __stdcall DisablePerformanceReporting() = 0;

   /**
   *   Register a callback interface to get notified once the pause position is determined (after calling PauseAt).   
   *   Only one interface can be registered at a time.
   * 
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
   * @param <i>IMvPausePositionNotification in_pIMvPausePositionNotification</i>:  Callback interface to use for the pause position notification.
   */
   virtual HRESULT __stdcall RegisterPausePositionNotificationCallbackInterface(IMvPausePositionNotification *in_pIMvPausePositionNotification) = 0;

   /**
   *   Unregister the callback interface 
   * 
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
   * @param <i>IMvPausePositionNotification in_pIMvPausePositionNotification</i>:  Callback interface to unregister.
   */
   virtual HRESULT __stdcall UnRegisterPausePositionNotificationCallbackInterface(IMvPausePositionNotification *in_pIMvPausePositionNotification) = 0;

   /**
   *  Seeks the graph to a certain timeline position with no seek cancellation and does
   *  seeks as fast as possible (can be faster than realtime)
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> Transport command.
   * <li> See IMvGraphStateControl for more information.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>HRESULT error code, if failed.
   * <li>
   * </ul>
   * @param <i>uint64_t in_ui64TimelinePositionInFrames</i>: Position to seek to.
   * @param <i>unsigned long in_ulCutlistID</i>: Cutlist ID. Used to know if we can flush
   *  the previous seek or not. When the ID's do not match there is no buffer cancellation.
   */
   virtual HRESULT __stdcall SeekForCompile( uint64_t in_ui64TimelinePositionInFrames,
      unsigned long in_ulCutlistID) = 0;

   virtual HRESULT GetGraphMode(EMvGraphMode&  out_mvdCurrentMode) = 0;

};
#endif //IMVGRAPHCONTROL_H
