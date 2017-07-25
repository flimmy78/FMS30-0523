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
//                    IMVAUDIOPULLING.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 20, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVRIFFHEADERIO_H
#define IMVRIFFHEADERIO_H

/**
 * To retrive or set RIFF chunks meta data in the second chunk level
 * <br><b>Remarks:</b>
 * <ul><i>
 * <li> It could operate on both AVI or WAV files.
 * <li> The same instance of the interface could only work on one file at a time. After closing the previous file, one could open another file.
 * </i></ul>
 * @interface
 */
interface IMvRIFFChunkIO : public IUnknown
{
public:

   /**
    *  Init and set the file name to access the RIFF chunks.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    * <li> Call this before doing any operations.
    * <li> The caller allocates the pointer to the filename.
    * <li> The filename should contain the full path.
    * </i></ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *	    <li>MV_E_INVALID_POINTER, if the parameter out_ppwszFileName is an invalid pointer.
    *	    <li>MV_E_OUT_OF_MEMORY, if there is not sufficient memory available.
    *     <li>MV_E_FORMAT_NOT_SUPPORTED, if the file is either WAVE or AVI files.
    *     <li>MV_E_FILE_NOT_FOUND, if the file name or path is invalid
    *     <li>MV_E_FILE_ALREADY_OPENED, if there is share violation
    *     <li>MV_E_ALREADY_IN_USE, if the interface already in used
    *     <li>MV_E_NOT_INITIALIZED, if the interface's Open have not been called.
    *     <li>MV_E_NO_RESOURCE_FOUND, if there are too many opened files
    *     <li>MV_E_FAIL, unexpected error 
    * </ul>
    * @param <i>wchar_t in_pwszFileName </i>: The file names' pointer.
    */
   virtual HRESULT __stdcall Open(wchar_t * in_pwszFileName, bool in_bReadOnly) = 0;


   /**
    * Get the size of the RIFF chunk 
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param unsigned long       ulFOURCC: Four character code of the chunk ID
    * @param unsigned long *     pulChunkSize: Size of the chunk's data 
    * @param BOOL                out_pIsListChunk: The targer chunk is a LIST chunk
    */
   virtual HRESULT __stdcall GetChunkSize ( unsigned long in_ulFOURCC, unsigned long * out_pulChunkSize, BOOL * out_pIsListChunk ) = 0;


   /**
    * Read the RIFF chunk data
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>MV_E_NOT_INITIALIZED, if the file is not opened
    *     <li>MV_E_BUFFER_SIZE_MISMATCH, if the input buffer size does not equal to the chunk size in the file.
    *     <li>MV_E_OUT_OF_RANGE, if the not all data is read, possibly invalid chunk size or end of file.
    *     <li>MV_E_INVALID_DATA, no data is read.
    * </ul>
    * @param unsigned long       ulFOURCC: Four character code of the chunk ID
    * @param unsigned long       ulReadSize: Size of the buffer
    * @param unsigned char *     puchChunkData: chunk's data to be filled
    */
   virtual HRESULT __stdcall ReadChunk ( unsigned long in_ulFOURCC, unsigned long in_ulReadSize, char * out_puchChunkData) = 0;

   /**
    * Read the RIFF LIST chunk data
    *
    * <br><b>Remark:</b>
    * <ul><li>The interface will read and report the number of chunk in a list chunk.
    * <li>User need to use the information returned in this call to allcate the buffers for the 
     ReadListChunks call to actually getting the data chunks.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>MV_E_NOT_INITIALIZED, if the file is not opened
    *     <li>MV_E_BUFFER_SIZE_MISMATCH, if the input buffer size does not equal to the chunk size in the file.
    *     <li>MV_E_OUT_OF_RANGE, if the not all data is read, possibly invalid chunk size or end of file.
    *     <li>MV_E_INVALID_DATA, no data is read.
    * </ul>
    * @param unsigned long       in_ulFOURCC: Four character code of the chunk ID
    * @param unsigned long       in_ulSize: Size of the Array
    * @param unsigned long *     out_pChunkFourCC: User allocated array to store the 4CC for each of the chunk in the list
    * @param unsigned long *     out_pChunkSize: User allocated array to store the size for each of the chunk in the list
    * @param unsigned long *     out_pulSize: Number of chunks in the list
    */
   virtual HRESULT __stdcall ReadListChunks ( unsigned long in_ulFOURCC, unsigned long in_ulSize, unsigned long * out_pChunkFourCC, unsigned long * out_pChunkSize, long *  out_pulSize) = 0;

   /**
    * Read the RIFF LIST chunk data
    *
    * <br><b>Remark:</b>
    * <ul><li>The interface will retrive all the chunks read by the previous ReadListChunks call
    * <li>User will need to allocate the array of SMvRIFFChunksInLIST according to the size returned from the ReadListChunks
    * <li>The data is stored in the MvRIFFChunksInLIST's pBuffer and user is responsible to allocate it.
    * <li>This function should be called right after the previous ReadListChunks or the function will fail.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>MV_E_NOT_INITIALIZED, if the file is not opened
    *     <li>MV_E_BUFFER_SIZE_MISMATCH, if the input buffer size does not equal to the chunk size in the file.
    *     <li>MV_E_OUT_OF_RANGE, if the not all data is read, possibly invalid chunk size or end of file.
    *     <li>MV_E_INVALID_DATA, no data is read.
    * </ul>
    * @param unsigned long       in_ulFOURCC: Four character code of the chunk ID
    * @param unsigned long       in_ulSize: Size of the array
    * @param unsigned int *      out_puiNumberOfBuffers: Number of chunks in the LIST chunk
    */
   virtual HRESULT __stdcall GetListChunks ( unsigned long in_ulFOURCC, unsigned long in_ulSize, SMvRIFFChunksInLIST * in_pChunks) = 0;

   /**
    * Write the RIFF chunk data
    *
    * <br><b>Remark:</b>
    * <ul>
    * <li>It inserts the new chunk into "JUNK" chunk area. The JUNK chunk has to be large enoug to contain the new chunk
    * <li>If there is already a chunk exists in the file with the same ID, the first one that is found would be overwritten by the new data.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>MV_E_NOT_INITIALIZED, if the file is not opened
    *     <li>MV_E_OUT_OF_RANGE, No more free space to write the data.
    * </ul>
    * @param unsigned long       in_ulFOURCC: Four character code of the targer chunk ID
    * @param unsigned long       in_ulWriteSize: Size of the buffer
    * @param unsigned char *     in_puchChunkData: chunk buffer to be written to the file
    * 
    */
   virtual HRESULT __stdcall WriteChunk ( unsigned long in_ulFOURCC, unsigned long in_ulWriteSize, char * in_puchChunkData) = 0;

   /**
    * Write an array of the RIFF data chunks into a new LIST chunk
    *
    * <br><b>Remark:</b>
    * <ul>
    * <li>It inserts the new LIST chunk into "JUNK" chunk area. The JUNK chunk has to be large enough to contain the new chunk
    * <li>If there is already a LIST chunk exists in the file with the same ID, the first one that is found would be overwritten by the new data.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>MV_E_NOT_INITIALIZED, if the file is not opened
    *     <li>MV_E_OUT_OF_RANGE, No more free space to write the data.
    * </ul>
    * @param unsigned long       ulFOURCC: Four character code of the targer LIST chunk ID
    * @param unsigned char *     in_pChunks: Array of SMvRIFFChunksInLIST structure to be written to the file
    * @param unsigned long       in_NumberOfBuffers: Count of Array item of the SMvRIFFChunksInLIST to be written to the file
    * 
    */
   virtual HRESULT __stdcall WriteListChunks ( unsigned long in_ulFOURCC, SMvRIFFChunksInLIST * in_pChunks, unsigned long in_NumberOfBuffers) = 0;

   /**
    * Close the file
    *
    * <br><b>Remark:</b>
    * <ul>
    * <li> Data will be flushed to the file immediately.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    * </ul>
    */
   virtual HRESULT __stdcall Close (void) = 0;

};

#endif //IMVRIFFHEADERIO_H

