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
//                    IMVCODECPROFILEINFO.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             March 11, 2004
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVCODECPROFILE_H
#define IMVCODECPROFILE_H

/**
 * Allows access to query codec capabilities.
 *
 * @interface 
 */
interface IMvCodecProfileInfo : public IUnknown
{
public:
   /**
    * Initializes the internal lists so the codec capabilities can be queried.
    *
    * <br><b>Remarks:</b>
    * <ul><li>
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if we can initialize the list.
    *     <li>MV_E_OUT_OF_POOL_MEMORY, if memory requested is not available.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param <i>SMvHardwareProfileInfo  in_psHWProfileInfo:</i> Hardware profile required to query codec capabilities, can be set to NULL if profile is unknown.
    */
   virtual HRESULT __stdcall InitializeForQuery( SMvHardwareProfileInfo* in_psHWProfileInfo) = 0;
   
   /**
    * Gets the current item in the list and increments the pointer to next item.
    *
    * <br><b>Remarks:</b>
    * <ul><li>Fills the input structures array with the current items in the list. This is done
    * up to the maximum number asked or the maximum number available.
    * <li> See IMvCodecProfileInfo for more information.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if we can fill the structure with valid data.
    *     <li>MV_E_ELEMENT_NOT_FOUND, if we are at the end of the list.
    * </ul>
    *
    * @param <i>unsigned long         in_ulNbCodecCapsRequested:</i> Number of codec capabilities asked.
    * @param <i>SMvCodecCapabilities  io_pCodecCapsInfo:</i> The array of codec capabilities returned.
    * @param <i>unsigned long         out_pulCodecCapsFetched:</i> A pointer to the number of codec capabilities returned.
    *
    */
   virtual HRESULT __stdcall Next(unsigned long         in_ulNbCodecCapsRequested,
                                  SMvCodecCapabilities* io_pCodecCapsInfo,
                                  unsigned long        *out_pulCodecCapsFetched) = 0;

   /**
    * Resets the current position to the beginning of the list.
    *
    * <br><b>Remarks:</b>
    * <ul><li> See IMvCodecProfileInfo for more information.
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul>
    * <li>MV_TRUE, if we returned the requested amount of codec capabilities.
    * <li>MV_FALSE, if we returned less than the requested amount of codec capabilities.
    * <li>MV_E_OUTOFMEMORY, insufficient memory exists to perform the operation.
    * <li>MV_E_POINTER, if out_pCodecCapsInfo is not a valid pointer.
    * <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall Reset() = 0;

   /**
    * Used to skip a number of elements.
    *
    * <br><b>Remarks:</b>
    * <ul><li> None
    * </ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    */
   virtual HRESULT __stdcall Skip(unsigned long in_ulCount) = 0;
};



#endif //IMVCODECPROFILEINFO_H
