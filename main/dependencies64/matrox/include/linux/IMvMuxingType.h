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
//                    IMVMUXINGTYPE.H
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


#ifndef IMVMUXINGTYPE_H
#define IMVMUXINGTYPE_H


/** Selects the file type and the stream multiplexing option.
@interface */
interface IMvMuxingType : public IUnknown
{
public:

   /**
    * Sets the file and muxing type.
    *
    * <br><b>Remarks:</b>
    * <ul><i>
    *        <li>See IMvVideoCaptureProperties for encoding selections.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul>
    *  <li>return type HRESULT
    * </ul>
    *
    * <b>Return values:</b>
    * <ul>
    *     <li>MV_NOERROR, if completed successfully.
	*	<li>MV_E_FAIL if, failed.
    * </ul>
    * @param in_emvMuxType : Structure with the muxing type properties.
	*/
   virtual HRESULT __stdcall SetMuxType( EMvMuxingType in_emvMuxType, bool in_bForceSingleBodyPartition = false ) = 0;
};



#endif //IMVMUXINGTYPE_H




