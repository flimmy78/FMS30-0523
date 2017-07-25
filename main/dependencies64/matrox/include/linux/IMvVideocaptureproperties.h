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
//                    IMVVIDEOCAPTUREPROPERTIES.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVVIDEOCAPTUREPROPERTIES_H
#define IMVVIDEOCAPTUREPROPERTIES_H


/** Exposed by the universal muxer, this interface allows the user to select the 
   encoding method by calling the associating method in the interface. 
   The encoding method should only be changed once the graph is in a Stop state. 
@interface 
*/
interface IMvVideoCaptureProperties : public IUnknown
{
public:

   /**
    * Sets the D10 capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *     <li>This method only selects the encoding method. To select MXF or AVI file type See IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if D10 capture is not available in the current configuration.
    * </ul>
    * @param in_smvD10CaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetD10Capture( SMvD10CaptureProperties in_smvD10CaptureProperties ) = 0;

   /**
    * Gets the D10 capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvD10CaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetD10Capture( SMvD10CaptureProperties * out_psmvD10CaptureProperties ) = 0;

   /**
    * Sets the SetUncompressedCapture capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, See IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param in_smvUncompressedCaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetUncompressedCapture( SMvUncompressedCaptureProperties  in_smvUncompressedCaptureProperties ) = 0;

   /**
    * Gets the uncompressed capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvUncompressedCaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetUncompressedCapture( SMvUncompressedCaptureProperties * out_psmvUncompressedCaptureProperties ) = 0;

   /**
    * Sets the MPEG-2 capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, see IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if MPEG2 capture is not available in the current configuration.
    * </ul>
    * @param in_smvMPEG2CaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetMPEG2Capture( SMvMPEG2CaptureProperties in_smvMPEG2CaptureProperties ) = 0;

   /**
    * Gets the MPEG-2 capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvMPEG2CaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetMPEG2Capture( SMvMPEG2CaptureProperties * out_psmvMPEG2CaptureProperties ) = 0;

   /**
    * Sets the DV capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, use the IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if DV capture is not available in the current configuration.
    * </ul>
    * @param in_smvDVCaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetDVCapture( SMvDVCaptureProperties in_smvDVCaptureProperties ) = 0;

   /**
    * Gets the DV capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvDVCaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetDVCapture( SMvDVCaptureProperties * out_psmvDVCaptureProperties ) = 0;


   /**
    * Sets the HD Offline capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, use the IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if HD Offline is not available in the current configuration.
    * </ul>
    * @param in_smvHDOfflineCaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetHDOfflineCapture( SMvHDOfflineCaptureProperties in_smvHDOfflineCaptureProperties ) = 0;

   /**
    * Gets the HD Offline capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvHDOfflineCaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetHDOfflineCapture( SMvHDOfflineCaptureProperties * out_psmvHDOfflineCaptureProperties ) = 0;

   /**
    * Sets pull down sequence type.
    *
    * <br><b>Remarks:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if HD Offline is not available in the current configuration.
    * </ul>
    * @param in_ePullDownSequence  : enumerator of pull down sequence.
	*/
   virtual HRESULT __stdcall SetPullDownSequence( EMvPullDownSequence in_ePullDownSequence ) = 0;

   /**
    * Gets pull down sequence type.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param io_refePullDownSequence : reference to the pull down seqeuence type.
	*/
   virtual HRESULT __stdcall GetPullDownSequence( EMvPullDownSequence& io_refePullDownSequence ) = 0;

   /**
    * Sets the HDV capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, use the IMvMuxingType.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if HDV   is not available in the current configuration.
    * </ul>
    * @param in_smvHDV CaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetHDVCapture( SMvMPEG2CaptureProperties in_smvHDVCaptureProperties ) = 0;

   /**
    * Gets the HDV capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvHDV CaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetHDVCapture( SMvMPEG2CaptureProperties * out_psmvHDVCaptureProperties ) = 0;

   /**
    * Sets the SetXDCamHD capture properties.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>This method only selects the encoding method. To select the file type, use the IMvMuxingType.
    *        <li>XDCam HD is IBP based encoding, it has 15 25 35 Mbps main profile high level variation 
    *        <li>Put zero in the bitrate if is not known in case of  source to sink
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if HDV   is not available in the current configuration.
    * </ul>
    * @param in_smvHDV CaptureProperties  : Structure of the properties.
	*/
   virtual HRESULT __stdcall SetXDCamHDCapture( SMvMPEG2CaptureProperties in_smvHDVCaptureProperties ) = 0;

   /**
    * Gets the HDV capture properties.
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
    * </ul>
    * @param out_psmvHDV CaptureProperties : Structure of the properties.
	*/
   virtual HRESULT __stdcall GetXDCamHDCapture( SMvMPEG2CaptureProperties * out_psmvHDVCaptureProperties ) = 0;

   /**
   * Gets the AVC capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvAVCCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetAVCCapture( SMvAVCCaptureProperties * out_psmvAVCCaptureProperties ) = 0;

   /**
   * Set the AVC capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvAVCCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetAVCCapture( SMvAVCCaptureProperties in_psmvAVCCaptureProperties ) = 0;


   /**
   * Gets the ProRes capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvProResCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetProResCapture( SMvProResCaptureProperties * out_psmvProResCaptureProperties ) = 0;

   /**
   * Set the ProRes capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param in_psmvProResCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetProResCapture( SMvProResCaptureProperties in_psmvProResCaptureProperties ) = 0;

   /**
   * Gets the AVCIntra capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvProResCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetAVCIntraCapture( SMvAVCIntraCaptureProperties * out_psmvAVCIntraCaptureProperties ) = 0;

   /**
   * Set the AVCIntra capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param in_psmvAVCIntraCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetAVCIntraCapture( SMvAVCIntraCaptureProperties in_psmvAVCIntraCaptureProperties ) = 0;

         /**
   * Gets the DNxHD capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvDNxHDCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetDNxHDCapture( SMvDNxHDCaptureProperties * out_psmvDNxHDCaptureProperties ) = 0;

   /**
   * Set the DNxHD capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param in_psmvDNxHDCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetDNxHDCapture( SMvDNxHDCaptureProperties in_psmvDNxHDCaptureProperties ) = 0;


            /**
   * Gets the MPEG-4 Simple Studio Profile capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_psmvMPEG4SStPCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetMPEG4SStPCapture( SMvMPEG4SStPCaptureProperties * out_psmvMPEG4SStPCaptureProperties ) = 0;

   /**
   * Set the MPEG-4 SStP capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param in_psmvMPEG4SStPCaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetMPEG4SStPCapture( SMvMPEG4SStPCaptureProperties in_psmvMPEG4SStPCaptureProperties ) = 0;


      /**
   * Gets the H264SWEncoder2 capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param out_pSMvH264CaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall GetH264CaptureProperties( SMvH264CaptureProperties * out_pSMvH264CaptureProperties ) = 0;

   /**
   * Set the H264SWEncoder2 capture properties.
   *
   * <br><b>Remark:</b>
   * <ul><li>None.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul>
   *  <li>return type HRESULT
   * </ul>
   *
   * <b>Return values:</b>
   * <ul>
   *     <li>MV_NOERROR, if completed successfully.
   * </ul>
   * @param in_pSMvH264CaptureProperties : Structure of the properties.*/
   virtual HRESULT __stdcall SetH264CaptureProperties( SMvH264CaptureProperties in_pSMvH264CaptureProperties ) = 0;

};



#endif //IMVVIDEOCAPTUREPROPERTIES_H




