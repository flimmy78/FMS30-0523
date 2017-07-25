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
//                    IMVOUTPUTAUDIONODE.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 23, 2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVOUTPUTAUDIONODE_H
#define IMVOUTPUTAUDIONODE_H
#include "IMvTreeNode.h"

/**
 * 
 * Sets or gets an output rate. All interfaces implemented in the output audio nodes are derived from this base interface.
 * 
 * 
 * 
 */
interface IMvOutputAudioNode : public IMvTreeNode
{
public:

   /**
    * Sets the skipping rate of an output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Rate is expressed with a fraction of elements to keep over a sequence of elements.
    * </i></ul>
    *
    * <b>Return type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvRateDescription &in_refsMvRateDescription: Rate structure.
    */
   virtual HRESULT __stdcall SetSkippingRate( SMvRateDescription &in_refsMvRateDescription ) = 0;

   /**
    * Gets the skipping rate of an output stream.
    *
    * <br><b>Remark:</b>
    * <ul><i><li>Rate is expressed with a fraction of elements to keep over a sequence of elements.
    * </i></ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
    *     <li>HRESULT error code, if failed.
    * </ul>
    * @param SMvRateDescription &io_refsMvRateDescription: Rate structure (should be valid).
    */
   virtual HRESULT __stdcall GetSkippingRate( SMvRateDescription &io_refsMvRateDescription ) = 0;
};



#endif //IMVOUTPUTAUDIONODE_H




