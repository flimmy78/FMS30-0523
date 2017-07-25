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
//                    IMVCUSTOMFILESYSTEMIO.H
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



#ifndef IMVCUSTOMFILESYSTEMIO_H
#define IMVCUSTOMFILESYSTEMIO_H

interface IMvFileSystemIONotifyState;

/**
* @interface
* Allows the user to specify a custom I/O file system for each cutlist element.
*
* This system will be developed in conjunction with the file access object.
* */

interface IMvCustomFileSystemIO : public IUnknown
{

public:

   /**
    * Opens the specified file.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param  wchar_t  *in_pwszFileName: Pointer to the name of the file.
    * @param  unsigned long  in_ulDesiredAccess: Access to the object(read or write mode).
    * @param  unsigned long  in_ulShareMode: Sharing mode of the object.
    * @param  unsigned long  in_ulCreationDisposition: How to create the file.
    * @param  unsigned long  in_ulFlagsAndAttributes: File attributes.
    * @param  IMvFileSystemIONotifyState   *in_pINotifyState: Interface for the notification.
    * @param  unsigned long  *out_pulHandle: Handle of the file for further operations.
    */
   virtual HRESULT __stdcall Open
   (
      wchar_t  *in_pwszFileName,                      
      unsigned long  in_ulDesiredAccess,              
      unsigned long  in_ulShareMode,                  
      unsigned long  in_ulCreationDisposition,        
      unsigned long  in_ulFlagsAndAttributes,         
      IMvFileSystemIONotifyState   *in_pINotifyState, 
      unsigned long  *out_pulHandle                   
   ) = 0;

   /**
    * Closes the specified file.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param unsigned long in_ulHandle: File handle.
    */
   virtual HRESULT __stdcall Close( unsigned long in_ulHandle ) = 0;

   /**
    * Reserves the minimum disk space required when capturing a file.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param unsigned long  in_ulHandle: Handle returned from the Open() function. 
    * @param uint64_t       in_ui64ReserveSize: Size of disk space reserved.
    */
   virtual HRESULT __stdcall ReserveSize
   (
      unsigned long  in_ulHandle,      
      uint64_t       in_ui64ReserveSize
   ) = 0;

   /**
    * Reads the file specified by the file handle.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param None.
    * @param unsigned long  in_ulHandle:         Handle returned from the Open() function. 
    * @param byte           *in_pBuffer:         Pointer to the data buffers.
    * @param long           in_lBufferSize:       Size of the buffer to read.
    * @param SMvOverlapped  *in_psOvlp:           File offset location of the I/O operation.
    * @param unsigned long  in_ulFlag:            Flags the on-board memory.
    * @param EMvIOState     *out_peIOState:       Pointer to the current state of the command.
    * @param long           *out_plBytesRead:     Pointer to the total number of bytes read.
    */
   virtual HRESULT __stdcall Read
   (
      unsigned long  in_ulHandle,         
      byte           *in_pBuffer,         
      long           in_lBufferSize,      
      SMvOverlapped  *in_psOvlp,          
      unsigned long  in_ulFlag,           
      EMvIOState     *out_peIOState,      
      long           *out_plBytesRead     
   ) = 0;

   /**
    * Writes data to the file specified by the file handle.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param      unsigned long  in_ulHandle:          Handle returned from the Open() function. 
    * @param      byte           *in_pBuffer:          Pointer to the data buffers.
    * @param      long           in_lBufferSize:       Size of the buffer to write.
    * @param      SMvOverlapped  *in_psOvlp:           File offset location of the I/O operation.
    * @param      unsigned long  in_ulFlag:            Lazy Write flag.
    * @param      EMvIOState     *out_peIOState:       Pointer to the current state of the command.
    * @param      long           *out_plBytesWritten:  Pointer to the total number of bytes written.
    */
   virtual HRESULT __stdcall Write
   (
      unsigned long  in_ulHandle,         
      byte           *in_pBuffer,         
      long           in_lBufferSize,      
      SMvOverlapped  *in_psOvlp,          
      unsigned long  in_ulFlag,           
      EMvIOState     *out_peIOState,      
      long           *out_plBytesWritten  
   ) = 0;

   /**
    * Gets the disk drive information.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param unsigned long        in_ulHandle                  : Drive/path. 
    * @param unsigned long    * out_pulSectorsPerCluster      :Address of sectors per cluster. 
    * @param unsigned long    * out_pulBytesPerSector:         Address of bytes per sector. 
    * @param unsigned long    * out_pulNumberOfFreeClusters:   Address of number of free clusters.  
    * @param unsigned long    * out_pulTotalNumberOfClusters:   Address of total number of clusters.  
    */
   virtual HRESULT __stdcall GetDiskInfo
   (
      unsigned long          in_ulHandle,                  
      unsigned long    *     out_pulSectorsPerCluster,     
      unsigned long    *     out_pulBytesPerSector,        
      unsigned long    *     out_pulNumberOfFreeClusters,   
      unsigned long    *     out_pulTotalNumberOfClusters    
   ) = 0;

   /**
    * Gets the state of the command.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param unsigned long  in_ulHandle:       Handle returned from the Open() function. 
    * @param SMvOverlapped  *in_psOvlp:        File offset location of the I/O operation.
    * @param EMvIOState     *out_peIOState:    Pointer to the current state of the command.
    * @param HRESULT        *out_phr:          Pointer to the error code of the command.
    */
   virtual HRESULT __stdcall GetState
   (
      unsigned long  in_ulHandle,      
      SMvOverlapped  *in_psOvlp,       
      EMvIOState     *out_peIOState,   
      HRESULT        *out_phr          
   ) = 0;

   /**
    * Gets the last system file time that data was written to the file using the file handle name.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param DWORD       in_ulHandle:           Handle returned from the Open() function.
    * @param LPFILETIME  out_psCreationTime:    Pointer to the creation time.
    * @param LPFILETIME  out_psLastAccessTime:  Pointer to the last access time.
    * @param LPFILETIME  out_psLastWriteTime:   Pointer to the last write time.
    */
   virtual HRESULT __stdcall GetFileTime
   (
      DWORD                in_ulHandle,      
      LPFILETIME           out_psCreationTime,   
      LPFILETIME           out_psLastAccessTime, 
      LPFILETIME           out_psLastWriteTime   
   ) = 0;

   /**
    * Gets the file attributes of the specified file.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param       LPWSTR         in_lpFileName   :Pointer to the name of a file or directory.
    * @param	   unsigned long   *out_pulattrib: Pointer to the file attributes. 
	 */
   virtual HRESULT __stdcall GetFileAttributes
   (
      LPWSTR         in_lpFileName,   
      unsigned long  *out_pulAttrib
   ) = 0;

   /**
    * Gets the file size of the specified.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param LPWSTR         in_lpFileName: Pointer to the name of a file or directory.
	* @param unsigned long  *out_pulHigh: Pointer the the high part of the file offset.
    * @param unsigned long  *out_pulLow: Pointer to the low part of the file offset.
    */
   virtual HRESULT __stdcall GetFileSize
   (
      LPWSTR         in_lpFileName,   
      unsigned long  *out_pulHigh,
      unsigned long  *out_pulLow
   ) = 0;

   /**
    * Deletes the specified file.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if the parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param   wchar_t  *in_pwszFileName  : Pointer to the name of a file or directory.
    */
   virtual HRESULT __stdcall DeleteFile
   (
      wchar_t  *in_pwszFileName  
   ) = 0;

   /**
    * Determines if the specified file exists.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_TRUE,  if completed successfully.
    *     <li>MV_E_INVALIDARG, if the parameter is invalid.
    *     <li>MV_FALSE, if failed.
    * </ul>
    *
    * @param wchar_t  *in_pwszFileName  : Pointer to the name of a file or directory.
    */
   virtual HRESULT __stdcall IsFileExists
   (
      wchar_t  *in_pwszFileName  
   ) = 0;

   /**
    * Determines if the specified file can be written to.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_TRUE, if completed successfully.
    *     <li>MV_E_INVALIDARG, if the parameter is invalid.
    *     <li>MV_FALSE, if failed.
    * </ul>
    *
    * @param wchar_t  *in_pwszFileName: Pointer to the name of a file or directory.
    */
   virtual HRESULT __stdcall CanWrite
   (
      wchar_t  *in_pwszFileName  
   ) = 0;

   /**
    * Provides information about the clusters on the disk.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param wchar_t        *in_pwszRootPathName:           Pointer to the root path of the file system.
    * @param unsigned long  *out_pulSectorsPerCluster:      Pointer to the number of sectors per cluster.
    * @param unsigned long  *out_pulBytesPerSector:         Pointer to the number of bytes per sector.
    * @param unsigned long  *out_pulNumberOfFreeClusters:   Pointer to the number of free clusters.
    * @param unsigned long  *out_pulTotalNumberOfClusters:  Pointer to the total number of clusters.
   */
   virtual HRESULT __stdcall GetDiskFreeSpace
   (
      wchar_t        *in_pwszRootPathName,          
      unsigned long  *out_pulSectorsPerCluster,     
      unsigned long  *out_pulBytesPerSector,        
      unsigned long  *out_pulNumberOfFreeClusters,  
      unsigned long  *out_pulTotalNumberOfClusters  
   ) = 0;

   /**
    *  Provides information about the bytes on the disk.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully. 
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if failed.
    * </ul>
    *
    * @param wchar_t        *in_pwszDirectoryName:               Pointer to the directory name.
    * @param ULARGE_INTEGER *out_pULFreeBytesAvailableToCaller:  Receives the number of bytes on the disk that are available to the caller.
    * @param ULARGE_INTEGER *out_pULTotalNumberOfBytes:          Receives the number of bytes on the disk.
    * @param ULARGE_INTEGER *out_pULTotalNumberOfFreeBytes:      Receives the number of free bytes on the disk.
    */
   virtual HRESULT __stdcall GetDiskFreeSpaceEx
   (
      wchar_t        *in_pwszDirectoryName,              
      ULARGE_INTEGER *out_pULFreeBytesAvailableToCaller, 
      ULARGE_INTEGER *out_pULTotalNumberOfBytes,         
      ULARGE_INTEGER *out_pULTotalNumberOfFreeBytes      
   ) = 0;

   /**
    * Gets the last system file time that data was written to the file using the file name.<br>
    *
    * <br><b>Remark:</b>
    * <ul><li>None.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_INVALIDARG, if a parameter is invalid.
    *     <li>MV_E_UNINITIALIZED, if the current object is not initialized correctly.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    *
    * @param LPWSTR               *in_pszwFileName:       Pointer to the name of a file or directory.
    * @param LPFILETIME           *out_psCreationTime:    Pointer to the creation time.
    * @param LPFILETIME           *out_psLastAccessTime:  Pointer to the last access time.
    * @param LPFILETIME           *out_psLastWriteTime:   Pointer to the last write time.
    */
   virtual HRESULT __stdcall GetFileTimeWithName
   (
      LPWSTR               *in_pszwFileName,      
      LPFILETIME           *out_psCreationTime,    
      LPFILETIME           *out_psLastAccessTime,  
      LPFILETIME           *out_psLastWriteTime    
   ) = 0;   
};



#endif //IMVCUSTOMFILESYSTEMIO_H
