
#ifndef IMVMULTISINKFILE_H
#define IMVMULTISINKFILE_H
#include "mvUnknown.h"
#include "mvTypes.h"

/**
* Sets (and releases) the file to capture on the Sink Switcher filter.
* @interface
* 
*/
interface IMvMultiSinkFile : public IUnknown
{
public:   

   /**
    * Loads the file for subsequent file-write operations and for receiving the 
    * cookie that refers to this operation.
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul> 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>MV_E_FAIL, if failed. 
	 *</ul>
    * @param <i>SMvSinkSwitcherLoadInfo in_sFileInfo</i>: Defines all the parameters the sink switcher use to load a file
    * @param <i>unsigned long * out_pulCookie</i>: Output cookie to use for further operations.
    */
   virtual HRESULT __stdcall Load
   (
      const SMvSinkSwitcherLoadInfo    in_sFileInfo,
      unsigned long           *out_pulCookie
   ) = 0;



   /**
    * Gets the information for the current loaded file. 
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
	 *     <li>MV_E_FAIL, if failed.    
	 * </ul>
    * @param <i>const unsigned long in_ulCookie</i>: The cookie.
    * @param <i>SMvSinkSwitcherLoadInfo *out_pSFileInfo</i>: Pointer to the information about the cookie.
    */
   virtual HRESULT __stdcall GetCurFile
   (
      const unsigned long        in_ulCookie,
      SMvSinkSwitcherLoadInfo   *out_pSFileInfo
   ) = 0;

   /**
    * Removes the Sink Switcher filter according to the cookie ID sent by the filter graph. As a result,
    * the file on the Sink Switcher filter will NOT have data appended to it. If this function
    * is not called and no file switch occurs, all subsequent captures
    * will be appended to the same file.
    * <br><b>Remarks:</b>
    * <ul><li><i>This call is valid only in the Stop state. All .WAV files will be automatically released
    * since .WAV files can not have additional data appended to them.
    * </i></ul>
    * <b>Return type:</b>
    * <ul><li><i>HRESULT</i>
    * </ul>
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if the file handle was successfully closed.
    *     <li>HRESULT error code, if something failed while closing the file.
    * </ul>
    */
   virtual HRESULT __stdcall ReleaseFile
   (
      const unsigned long  in_ulCookie
   ) = 0;
};
#endif //IMVMULTISINKFILE_H