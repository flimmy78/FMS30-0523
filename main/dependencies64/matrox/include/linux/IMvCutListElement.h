
#ifndef IMVCUTLISTELEMENT_H
#define IMVCUTLISTELEMENT_H
#include "mvUnknown.h"

/**
*@interface
* Describes and implements the cutlist elements.
* All elements have a starting position and duration.
*/
interface IMvCutListElement : public IUnknown
{
public:    

   /**
    *  Gets the duration of the cutlist element.
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
	 *	    <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64FrameDuration</var> is an invalid pointer.
    * </ul>
    * @param <i>uint64_t out_pui64FrameDuration </i>: Pointer to the cutlist element duration in frames.
    */
   virtual HRESULT __stdcall GetElementDuration
   (
      uint64_t	*out_pui64FrameDuration
   ) = 0;

    /**
    *  Gets the start position of the cutlist element.
    *
    * <br><b>Remarks:</b>
    * <ul><li> 
    * </ul>
    * 
    * <b>Return type:</b>
    * <ul><li>HRESULT
	 * </ul>
    * <b>Return values:</b> 
    * <ul><li>MV_NOERROR, if completed successfully.
	 *	  <li>MV_E_INVALID_POINTER, if the parameter <var>out_pui64StartFrame</var> is an invalid pointer.
	 * </ul>
    * @param <i>uint64_t out_pui64StartFrame </i>: Pointer to the start position of the cutlist element in frames.
    */
   virtual HRESULT __stdcall GetElementStartPosition
   (
      uint64_t	*out_pui64StartFrame
   ) = 0;

};
#endif //IMVCUTLISTELEMENT_H