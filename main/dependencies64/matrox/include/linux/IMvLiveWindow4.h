//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvLiveWindow4.h $

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
//   Author:                 AXIO team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVLIVEWINDOW4_H
#define IMVLIVEWINDOW4_H


/** This interface provides access to live window settings on the Matrox DirectShow Live Window filter.
* @interface */
interface IMvLiveWindow4 : public IMvLiveWindow3
{
public:   
	/**
	* Sets the rate of update of the LiveWindow.
   * The livewindow will play one out of the parameter passed.
   * Eg. if passed 2, will play one of every two buffers received.
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
	* @param <i>uint32_t in_ulOneOverThisParameter:</i> Rate will equal to one over this parameter.*/
	virtual HRESULT __stdcall SetPlaybackRate(uint32_t in_ui32Denominator) = 0;

};

#endif //IMVLIVEWINDOW4_H
