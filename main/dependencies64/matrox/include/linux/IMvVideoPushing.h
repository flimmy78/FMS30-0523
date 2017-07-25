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
//                    IMVVIDEOPUSHING.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 26, 2004
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVVIDEOPUSHING_H
#define IMVVIDEOPUSHING_H

/**
 * Pushes Flex surfaces into a user application.
 * Implemented by an application.
 * @interface
 */
interface IMvVideoPushing : public IUnknown
{
public:

   /**
    * Delivers a surface to an external module.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    *        <li>If some processing is needed, it can return the surface and signal the read completion later.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param uint64_t      in_ui64TimelinePosition:          Timeline position delivered in ERes unit.
    * @param unsigned long in_ulSubCutlistID:                Current sub-cutlist ID.
    * @param IMvSurface    in_pIMvSurface:                   Pointer to Flex surface interface container received in the RequestForAVContent call.
    * @param HANDLE        in_hCompletionEvent:              Event to signal when the CPU part of the delivering is completed.
    */
	virtual HRESULT __stdcall WakeUpYourThreadToProcessDeliver
	( 
		uint64_t      in_ui64TimelinePosition,
		unsigned long in_ulSubCutlistID,
		IMvSurface*   in_pIMvSurface,
		HANDLE        in_hCompletionEvent
	) = 0;


   /**
    * Cancels the delivery of a surface.
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
    *
    * @param uint64_t       in_ui64TimelinePosition:    Timeline position of the cancelled delivery. 
    * @param unsigned long  in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvSurface     in_pIMvSurface:             Surface to cancel.
    * @param HANDLE         in_hCompletionEvent:        Event to signal when the CPU part of the cancellation is completed.
    */
   virtual HRESULT __stdcall CancelDeliver
	( 
		uint64_t      in_ui64TimelinePosition,
		unsigned long in_ulSubCutlistID,
		IMvSurface*   in_pIMvSurface,
		HANDLE        in_hCompletionEvent
	) = 0;

   /**
    * Requests an AVContent to the application.
    *
    * <br><b>Remark:</b>
    * <ul><li>The application will return the requested AVContent through the provided callback function.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
	* @param uint64_t            in_ui64TimelinePosition:    Timeline position pushed in ERes unit.
	* @param uint64_t            in_ui64Duration:            Duration pushed in ERes unit.
	* @param double              in_dShuttlingSpeed:         Shuttling speed.
	* @param unsigned long       in_ulSubCutlistID:          Current sub-cutlist ID.
    * @param IMvAVContentReceiver in_pIMvAVContentReceiver:  Interface to call when the AVContent is available.
    */
	virtual HRESULT __stdcall RequestForAVContent
	(	uint64_t               in_ui64TimelinePosition,
		uint64_t               in_ui64Duration,
		double                 in_dShuttlingSpeed,
		unsigned long          in_ulSubCutlistID,
		IMvAVContentReceiver * in_pIMvAVContentReceiver
	) = 0;

   /**
    * Gets a Flex surface description from an external module.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param SMvSurfaceDescription io_psSurfaceDesc: Surface description
    */
   virtual HRESULT __stdcall GetSurfaceDescription
	( 
		SMvSurfaceDescription * io_psSurfaceDesc 
	) = 0;

   /**
    * Gets the maximum number of surfaces that are available at the same time.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param unsigned long out_refulMaxSurfaceCount: Surfaces maximum count.
    */
	virtual HRESULT __stdcall GetMaxSurfaceCount
	( 
		unsigned long & out_refulMaxSurfaceCount 
	) = 0;

	/**
	* Gets the preroll value for the current video pushing object
	*
	* <br><b>Remark:</b>
	* <ul><li>Host application should not hold the calling thread.
	* </ul>
	*
	* <b>Return Type:</b>
	* <ul><li>HRESULT</ul>
	*
	* <b>Return Values:</b>
	* <ul><li>MV_NOERROR, if operation succeeded.
	*     <li>HRESULT error code, if operation failed.
	* </ul>
	* @param unsigned long out_refui64PrerollValue: Preroll value
	*/
	virtual HRESULT __stdcall GetPreroll
	( 
		uint64_t & out_refui64PrerollValueInEResUnits
	) = 0;

};
#endif
