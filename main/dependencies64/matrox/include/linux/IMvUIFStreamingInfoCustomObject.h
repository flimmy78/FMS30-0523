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
//                    IMvUIFStreamingInfoCustomObject.h
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



#ifndef IMVUIFSTREAMINGINFOCUSTOMOBJECT_H
#define IMVUIFSTREAMINGINFOCUSTOMOBJECT_H


/** @interface */
interface IMvUIFStreamingInfoCustomObject : public IUnknown
{
public:

   /**
   * Get the internal structure pointer (SMvUIFStreamingInfo)<br>
   *
   * <br><b>Remark:</b>
   * <ul><li> 
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR:          Succeeded.
   *     <li>ERROR CODE:          A module called reported an error.
   * </ul>
   *
   * @param None.
   */
   virtual HRESULT __stdcall GetUIFStreamingInfo(SMvUIFStreamingInfo** out_psUIFStreamingInfo) = 0;   


   /**
   * Set the internal structure content (SMvUIFStreamingInfo)<br>
   *
   * <br><b>Remark:</b>
   * <ul><li> 
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * <ul><li>MV_NOERROR:          Succeeded.
   *     <li>ERROR CODE:          A module called reported an error.
   * </ul>
   *
   * @param None.
   */
   virtual HRESULT __stdcall SetUIFStreamingInfo(SMvUIFStreamingInfo* in_psUIFStreamingInfo) = 0;   

   /**
   * This operation reinitializes everything in the object in order to make it ready to be reused.<br>
   *
   * <br><b>Remark:</b>
   * <ul><li>Set all fields to 0 except for size
   * </ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b>
   * </ul>
   *
   * @param None.
   */
   virtual void __stdcall ResetContent() = 0;   

};


#endif //IMVUIFSTREAMINGINFOCUSTOMOBJECT_H

