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
//                    IMVVIDEOCLOSEDCAPTIONINGPULLING.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Feb 7, 2011
//   Operating System:       Windows 7
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVVIDEOCLOSEDCAPTIONINGPULLING_H
#define IMVVIDEOCLOSEDCAPTIONINGPULLING_H

/**
 * This interface is used to receive a video closed captioning from a host application.
 * Implemented by an application.
 * @interface
 */
interface IMvVideoClosedCaptioningPulling : public IUnknown
{
public:

   /**
    * Gets the closed captioning data at the timeline position requested.
    *
    * <br><b>Remark:</b>
    * <ul><li>Host application should not hold the calling thread.
    *     <li>It should have all the closed captioning data ready.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position pulled in ERes unit.
    * @param void **             out_ppClosedCaptioningData: Pointer to closed captioning data.
    * @param uint32_t *          out_pui32SizeOfClosedCaptioningData: size of closed captioning data.
    */
   virtual HRESULT __stdcall GetClosedCaptioning
   ( 
      uint64_t            in_ui64TimelinePosition,
      void              **out_ppClosedCaptioningData,
      uint32_t           *out_pui32SizeOfClosedCaptioningData
   ) = 0;

};


#endif //IMVVIDEOCLOSEDCAPTIONINGPULLING_H




