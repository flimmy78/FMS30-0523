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
//                    IMVAVREADER.H
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


#ifndef IMVAVREADER_H
#define IMVAVREADER_H


/** @interface */
interface IMvAVReader : public IUnknown
{
public:
    /** Opens an audio video file.
     * <br>
     * <br><b>Remark:</b>
     * <ul><li>None.
     * </ul>
     * <b>Return type:</b>
     * <ul><li>HRESULT
     * </ul>
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully. 
     *     <li>HRESULT error code, if it's not a valid AV file.
     * </ul>
     * @param in_pwszFileName : Complete filename and the path of the file.
     */
    virtual HRESULT __stdcall OpenFile(  wchar_t *in_pwszFileName ) = 0;
   
    /** Gets the media file information of the AV file.
     * <br><b>Remark:</b>
     * <ul><li>None.
     * </ul>
     * <b>Return type:</b>
     * <ul><li>HRESULT
     * </ul>
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully.
     *     <li>HRESULT error code, if the function reported an error.
     * </ul>
     * @param out_pmvAVFileInfo : Pointer to the SMvAudioVideoFileInfo structure.
     */
    virtual HRESULT __stdcall GetAVFileInfo( SMvAudioVideoFileInfo * out_pmvAVFileInfo ) = 0;
   
    /**
     * Reads the data of the AV file to some surfaces and audio sample buffers.
     * <br><b>Remarks:</b>
     * <ul><li>The surfaces and audio samples buffers must be user buffers. The reader will attach the true data to it.
     * </ul>
     * <b>Return type:</b>
     * <ul><li>HRESULT
     * </ul>
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully.
     *     <li>HRESULT error code, if the function reported an error.
     * </ul>
     * @param  in_ui64Frame: Frame number to read.
     * @param  io_ppIMvSurface : Output video surface(s)
     * @param  in_ulVideoSurfaces: Count of surfaces.
     * @param  io_ppIMvAudioSamples: Output audio surface(s)
     * @param  in_ulAudios: Count of audio surfaces.
     */
    virtual HRESULT __stdcall ReadBuffer( uint64_t in_ui64Frame , IMvSurface** io_ppIMvSurface , unsigned long in_ulVideoSurfaces , IMvAudioSamples** io_ppIMvAudioSamples , unsigned long in_ulAudios  ) = 0;
   
    /**
     * Closes the file.
     *
     * <br><b>Remark:</b>
     * <ul><li>None.
     * </ul>
     * <b>Return type:</b>
     * <ul><li>HRESULT
     * </ul>
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully.
     *     <li>HRESULT error code, if the function reported an error.
     * </ul>
     */
    virtual HRESULT __stdcall Close() = 0;


    /** Opens an audio video file.
     * <br>
     * <br><b>Remark:</b>
     * <ul><li>None.
     * </ul>
     * <b>Return type:</b>
     * <ul><li>HRESULT
     * </ul>
     * <b>Return values:</b> 
     * <ul><li>MV_NOERROR, if completed successfully. 
     *     <li>HRESULT error code, if it's not a valid AV file.
     * </ul>
     * @param in_pwszFileName : Complete filename and the path of the file.
     */
    virtual HRESULT __stdcall OpenFileWithIndex(  wchar_t *in_pwszFileName, wchar_t *in_pwszIndexFileName  ) = 0;

};



#endif //IMVAVREADER_H




