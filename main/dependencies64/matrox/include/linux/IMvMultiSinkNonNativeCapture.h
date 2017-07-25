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
//                    IMVMULTISINKNONNATIVECAPTURE.H
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


#ifndef IMVMULTISINKNONNATIVECAPTURE_H
#define IMVMULTISINKNONNATIVECAPTURE_H

#include "mvUnknown.h"
#include "mvTypes.h"

/**
* Controls for non-native capture using the Sink Switcher Filter.
* @interface
* 
*/
interface IMvMultiSinkNonNativeCapture : public IUnknown
{
public:   

    /**
    * Returns a pointer to the internal filtergraph and expects
    * the user to add and connect DirectShow filters. The Switcher will
    * add a custom source splitter filter to the graph that outputs IMediaSamples.
    * The user should call this function to load a file to capture to.
    *
    * <b>Remark:</b><ul><li>None</ul>
    * <b>Return Type:</b>
    * <ul><li><i>HRESULT</i>
    * </ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if the call was successful.
    *     <li>HRESULT error code, if the function reported an error.
    * </ul>
    * @param <i>const uint64_t in_ui64DurationInFrames </i>: Duration of file to capture.
    * @param <i>IGraphBuilder **out_ppIGraphBuilder </i>: Pointer to IGraphBuilder.
    * @param <i>IBaseFilter **out_ppISourceSplitter </i>: Pointer to the Source Splitter filter.
    * @param <i>unsigned long *out_pulCookie </i>: Cookie of file to capture.
    */
   virtual HRESULT __stdcall PrepareFilterGraph
   (
      const uint64_t    in_ui64DurationInFrames,
      IGraphBuilder     **out_ppIGraphBuilder,
      IBaseFilter       **out_ppISourceSplitter,
      unsigned long     *out_pulCookie
   ) = 0;

	 /**
	 * Returns a pointer to the internal filtergraph according to the cookie.
	 * The user should call this function after a Switch Event and disassemble the switched out
    * graph as needed. Otherwise the file will remain open.
	 *
    * <b>Remark:</b><ul><li>None</ul>
	 * <b>Return Type:</b>
	 * <ul><li><i>HRESULT</i>
	 * </ul>
	 * <b>Return Values:</b>
	 * <ul><li>MV_NOERROR, if the call was successful.
    *     <li>HRESULT error code, if the function reported an error.
	 * </ul>
    * @param <i>const unsigned long	in_ulCookie </i>: Cookie of file
    * @param <i>IGraphBuilder	**out_ppIGraphBuilder </i>: Pointer to the IGraphBuilder
    */
   virtual HRESULT __stdcall GetFG
   (
   	const unsigned long	in_ulCookie,
      IGraphBuilder		**	out_ppIGraphBuilder
   ) = 0;
};



#endif //IMVMULTISINKNONNATIVECAPTURE_H
