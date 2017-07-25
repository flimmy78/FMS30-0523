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
//                    IMvReversePulldown.h
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:            Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVREVERSEPULLDOWN_H
#define IMVREVERSEPULLDOWN_H


/** 
* Does the reverse pulldown from input surfaces of Uncompressed fields and
* of DV frames.  This interface expects to receive the uncompressed NTSC fields or c
* compressed DV frames from which 23.98 frames should be extracted.
* @interface 
*/
interface IMvReversePulldown : public IUnknown
{
public:

   /**
   * Used to set pulldown settings to know how to extract original frames from input surfaces
   * when input surfaces do not explicity say which frame of sequence they are.  In these cases
   * the timecode information is used to determine which frame of sequence the input surface is.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> When the input surfaces contain explicit information about which frame of sequence it
   * it is then the information passed in this method would not be used.  The explicit information
   * that is needed are the last four fields of the structure gotten from the call to the method,
   * GetFrameInfo, on the custom object, IMvSourceDeviceFrameInfoCustomObject. These fields of the 
   * structure give the exact information about which frame of sequence it is and which type of 
   * pulldown sequence it is.
   *
   * 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>EMvPullDownSequence in_ePullDownSeq</i>: The type of pulldown sequence.
   * @param <i>unsigned long in_ulTimeCodeForSequence</i>:The timecode for the frame of 
   * sequence that is passed in the next parameter.
   * @param <i>EMvFrameOfSequence in_eFrameSeqAtTimeCode</i>:The frame of sequence for the timecode 
   * that is specified in the previous parameter.
   */
   virtual HRESULT __stdcall SetDefaultPulldownSettings( EMvPullDownSequence in_ePullDownSeq,
                                                         unsigned long in_ulTimeCodeForSequence,
                                                         EMvFrameOfSequence in_eFrameSeqAtTimeCode 
                                                         ) = 0;

   /**
   * Used to get pulldown settings that were either set, through the SetDefaultPulldownSettings
   * method, or the default settings.  
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> The default settings if SetDefaultPulldownSettings is not called would have this
   * method return that at a timecode of 0, the sequence starts (first frame of sequence), with a 
   * pulldown type of regular 3-2.
   *
   * 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>EMvPullDownSequence * out_pePullDownSeq</i>: The type of pulldown sequence.
   * @param <i>unsigned long * out_pulTimeCodeForSequence</i>:The timecode for the frame of 
   * sequence that is in the next parameter.
   * @param <i>EMvFrameOfSequence * out_peFrameSeqAtTimeCode</i>:The frame of sequence for the timecode 
   * that is returned in the previous parameter.
   */
   virtual HRESULT __stdcall GetDefaultPulldownSettings( EMvPullDownSequence * out_pePullDownSeq,
      unsigned long * out_pulTimeCodeForSequence,
      EMvFrameOfSequence * out_peFrameSeqAtTimeCode 
      ) = 0;

   /**
   * Returns the fields to re-create the original frame from input surfaces of NTSC to
   * that of the original frame rate of 23.98frames/sec. In the case of uncompressed input
   * surfaces, it will return the first and second field to re-create the frame.  In the case 
   * of DV it will either return only one frame, or return the two frames, indicating which 
   * field of the frame is needed to re-create the original frame. 
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li> This method will not return output surfaces at each call.  The object that
   * implements this method will hold input surfaces passed as a parameter until both fields
   * that re-create the original frame have been passed to this method.
   *
   * The input surface passed as a parameter contains the IMvSourceDeviceFrameInfoCustomObject
   * which describes which field/frame of sequence it is. 
   * 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully and returns output surface/s.
   * <li>MV_FALSE, if completed successfully but no output surface/s to return at the moment.
   * <li>HRESULT error code, if failed.
   * </ul>
   * @param <i>IMvSurface * in_pIMvSurfaceInput</i>: The input surface.
   * @param <i>bool * out_bOutputFrameFromBothOutputSurfaces</i>: true if both output surfaces
   * parameters filled to re-create frame
   * @param <i>IMvSurface ** out_ppIMvSurfaceFirstOutput</i>: The first field of the output frame
   * , or the frame of the output.  In the case of DV, and out_bOutputFrameFromBothOutputSurfaces is true,
   * then first field of the DV frame is the one needed to recreate original frame.
   * @param <i>IMvSurface * * out_ppIMvSurfaceSecondOutput</i>: The second field of the output 
   * frame. In the case of DV, the second field of the DV frame is the is the one needed to recreate 
   * original frame.
   */
   virtual HRESULT __stdcall ProcessSurfaceForReversePulldown( IMvSurface * in_pIMvSurfaceInput,
                                                               bool * out_bOutputFrameFromBothOutputSurfaces,
                                                               IMvSurface * * out_ppIMvSurfaceFirstOutput,
                                                               IMvSurface * * out_ppIMvSurfaceSecondOutput 
                                                               ) = 0;

   /**
   * Reset the module to release any surfaces it may be holding.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><li> The module implementing this interface may have references to surfaces depending
   * where in the sequence it has reached.  This method should be called when finished using
   * it, so that it may release any surfaces that may still be referenced.  
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul>
   * <li>MV_NOERROR, if completed successfully.
   * <li>HRESULT error code, if failed.
   * </ul>
   */
   virtual HRESULT __stdcall Reset() = 0;
};



#endif //IMVINPUTDEVICES_H

