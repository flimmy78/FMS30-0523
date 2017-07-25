//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2005. All rights reserved.
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
//                    IMVPAUSEPOSITIONNOTIFICATION.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             May 16, 2005
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef IMVPAUSEPOSITIONNOTIFICATION_H
#define IMVPAUSEPOSITIONNOTIFICATION_H

/**
 * This interface is used to get notified after pausing the graph once the pause position is determined.
 * Called by the graph and implemented by an application.
 * @interface
 */
interface IMvPausePositionNotification : public IUnknown
{
public:

   /**
    * This is called by the graph to notify the application once the pause position is determined.
    *
    * <br><b>Remark:</b>
    * <ul><li>.
    *     <li>.
    * </ul>
    *
    * <b>Return Type:</b>
    * <ul><li>HRESULT</ul>
    *
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if operation succeeded.
    *     <li>HRESULT error code, if operation failed.
    * </ul>    
    * @param uint64_t            in_ui64TimelinePosition:    Timeline position of the pause position.   
    */
   virtual HRESULT __stdcall NotifyPausePosition( uint64_t      in_ui64TimelinePosition) = 0;
   
};



#endif //IMVPAUSEPOSITIONNOTIFICATION_H




