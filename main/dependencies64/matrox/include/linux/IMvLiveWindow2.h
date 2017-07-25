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
//                    
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVLIVEWINDOW2_H
#define IMVLIVEWINDOW2_H


struct MV_HOSTBUFFER_SIZETOALLOCATE 
{
   unsigned long ulWidth;
   unsigned long ulHeight;
   unsigned long ulPitchInBytes;
   unsigned long ulSizeInBytes;
};


/** This interface provides access to live window settings on the Matrox DirectShow Live Window filter.
* @interface */
interface IMvLiveWindow2 : public IMvLiveWindow
{
public:   
   /**
   * Returns the size of the host buffer the user must allocate to copy the last displayed buffer
   *
   * <br><b>Remarks:</b>
   * <ul><li> 
   * </ul>
   * 
   * <b>Return type:</b>
   * <ul><li>MV_HOSTBUFFER_SIZETOALLOCATE</ul>
   * 
   * <b>Return values:</b> 
   * <ul><li>MV_HOSTBUFFER_SIZETOALLOCATE filled with the host buffer size parameters
   * </ul>
   * @param <i>unsigned long in_ulWithAPitch:</i> A desired pitch larger than the normal pitch.
   */
   virtual MV_HOSTBUFFER_SIZETOALLOCATE __stdcall GetSizeOfBufferToAllocateForHostCopy(
      unsigned long in_ulWithAPitch = 0) = 0; 

   /**
   * Copies the last output buffer on the live window to the host buffer 
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
   * @param <i>BYTE* in_pbHostBuffer :</i> Byte pointer to the allocated host buffer to copy into.
   */
   virtual HRESULT __stdcall CopyLastOutputRGBAToHost(BYTE* in_pbHostBuffer = NULL) = 0; 

};

#endif //IMVLIVEWINDOW2_H
