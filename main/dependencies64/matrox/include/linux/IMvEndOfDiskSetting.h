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
//                    IMVENDOFDISKSETTING.H
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             AUGUST 2, 2004 - 12:46:13 PM
//   Operating System:       WinXP
//   Author:                 Yufei He
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVENDOFDISKSETTING_H
#define IMVENDOFDISKSETTING_H
//==========================================================================;
// Header files
//==========================================================================;

//==========================================================================;
// Forward declarations
//==========================================================================;

//==========================================================================;
// Interface IMv
//==========================================================================;

/**
* This interface.<br>
* <br><b>Remark:</b>
* <ul><li>Interface to for end of disk settings .</ul>
* @interface
*/
interface IMvEndOfDiskSetting : public IUnknown
{
public:
   //==========================================================================;
   // Public operations
   //==========================================================================;

   /**
   * Set reserved size for end of disk . Minimum is 50M .
   * <br><b>Remarks:</b>
   * <ul><li>This is to set the reserved disk free space of end of disk . 
   * <ul> System will stop writing when it reaches to this size.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if succeeded. 
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long in_ulReservedSize. 
   */
   virtual HRESULT __stdcall SetReservedSizeForEndOfDisk( unsigned long in_ulReservedSize ) = 0;

   /**
   * Get reserved size for end of disk . Minimum is 50M .
   * <br><b>Remarks:</b>
   * <ul><li>This is to get the reserved disk free space of end of disk . 
   * <ul> System will stop writing when it reaches to this size.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if succeeded. 
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long *out_pulReservedSize. 
   */
   virtual HRESULT __stdcall GetReservedSizeForEndOfDisk( unsigned long out_pulReservedSize ) = 0;

   /**
   * Set reserved size for close to end of disk . Minimum is 100M .
   * <br><b>Remarks:</b>
   * <ul><li>This is to set the reserved disk free space of close to end of disk . 
   * <ul> System will send warning messages when it reaches to this size.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if succeeded. 
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long in_ulReservedSize. 
   */
   virtual HRESULT __stdcall SetReservedSizeForCloseToEndOfDisk( unsigned long in_ulReservedSize ) = 0;

   /**
   * Get reserved size for close to end of disk . Minimum is 100M .
   * <br><b>Remarks:</b>
   * <ul><li>This is to get the reserved disk free space of close to end of disk . 
   * <ul> System will send warning messages when it reaches to this size.
   * </ul>
   *
   * <b>Return type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if succeeded. 
   *     <li>HRESULT error code, if failed.
   * </ul>
   * @param unsigned long *out_pulReservedSize. 
   */
   virtual HRESULT __stdcall GetReservedSizeForCloseToEndOfDisk( unsigned long *out_pulReservedSize ) = 0;

};


#endif //IMVDDISKINFO_H
