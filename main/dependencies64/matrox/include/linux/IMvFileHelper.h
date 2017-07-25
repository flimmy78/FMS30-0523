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
//                    IMVFILEHELPER.H
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

#ifndef IMVFILEHELPER_H
#define IMVFILEHELPER_H

/**
* Allows access to the SDK File tools at a filter graph level.
*
* @interface 
*/
interface IMvFileHelper : public IUnknown
{
public:

   virtual HRESULT __stdcall GetMatroxGraphicFileInfo ( IMvMGFFileInfo **out_ppIMGFInfo ) = 0;

   /**
    * Gets an interface that exposes graphic writing to upper levels.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference count, caller should release interface when done.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvMGFWriter **out_ppIMGFWriter:</i> Pointer to a graphic writer interface.
    */
   virtual HRESULT __stdcall GetGraphicWriter( IMvMGFWriter  **out_ppIMGFWriter ) = 0;



   /**
    * Gets an interface that exposes Matrox graphic writer to upper levels.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference count, caller should release interface when done.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvMGFWriter **out_ppIMGFWriter:</i> Pointer to a Matrox graphic writer interface.
    */
   virtual HRESULT __stdcall GetMatroxGraphicFileWriter( IMvMGF2Writer **out_ppIMGFWriter ) = 0;

   /**
    * Gets an interface that exposes graphic reader to upper levels.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference count, caller should release interface when done.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvMGFReader **out_ppIMGFReader:</i> Pointer to a graphic reader interface.
    */
   virtual HRESULT __stdcall GetGraphicReader( IMvMGFReader **out_ppIMGFReader ) = 0;


   /**
    * Gets an interface that exposes Matrox graphic reader to upper levels.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Returned interface will have an extra reference count, caller should release interface when done.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvMGFReader **out_ppIMGFReader:</i> Pointer to a graphic reader interface.
    */
   virtual HRESULT __stdcall GetMatroxGraphicFileReader( IMvMGF2Reader **out_ppIMGFReader ) = 0;
   
   /**
    * Gets an interface through which the user can access audio/video files.
    *
    * <br><b>Remarks:</b>
    * <ul><li>
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvAVFileReader** out_ppIAVFileReader:</i> The interface to the file reader module.
    */
   virtual HRESULT __stdcall GetAVFileReader(IMvAVFileReader** out_ppIAVFileReader) = 0;


   /**
    * Gets an interface through which the user can access RIFF chunk meta data IO.
    *
    * <br><b>Remarks:</b>
    * <ul><li> Returns the IMvRIFFChunkIO interface to allow second level riff meta data chunk IO 
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>IMvRIFFChunkIO ** out_ppIMvRIFFChunkIO:</i> The interface to the IMvRIFFChunkIO module.
    */
   virtual HRESULT __stdcall GetRIFFChunkIO(IMvRIFFChunkIO ** out_ppIMvRIFFChunkIO) = 0;

};

#endif   // IMVFILEHELPER_H
