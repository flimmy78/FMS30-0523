//$Archive: /VP/DIRECTSHOW/LIBS/mvdAPI/INC/IMvLiveWindow3.h $

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
#ifndef IMVLIVEWINDOW3_H
#define IMVLIVEWINDOW3_H


/** This interface provides access to live window settings on the Matrox DirectShow Live Window filter.
* @interface */
interface IMvLiveWindow3 : public IMvLiveWindow2
{
public:   
	/**
	* Sets the client region that will be used to display action safe and title safe margins.
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
	* @param <i>RECT in_rcClientRegion:</i> Displays rectangle in client coordinates.*/
	virtual HRESULT __stdcall SetClientRegionForActionSafeAndTitleSafeMargins(RECT in_rcClientRegion) = 0;

   /**
   * Enables/disables the drawing of the action safe area.
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
   * @param <i>bool in_bEnable:</i> true to display the action safe margins and false to not diaplay it.
   * @param <i>float in_fPercentWidth:</i> percent representing the amount of horizontal margin to have. 0.1 for 10 percent.
   * @param <i>float in_fPercentHeight:</i> percent representing the amount of vertical margin to have. 0.1 for 10 percent.
   */
   virtual HRESULT __stdcall SetActionSafeMargins(
       bool in_bEnable,
       float in_fPercentWidth,
       float in_fPercentHeight
       ) = 0; 

   /**
   * Enables/disables the drawing of the Title safe area.
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
   * @param <i>bool in_bEnable:</i> true to display the title safe margins and false to not diaplay it.
   * @param <i>float in_fPercentWidth:</i> percent representing the amount of horizontal margin to have. 0.1 for 10 percent.
   * @param <i>float in_fPercentHeight:</i> percent representing the amount of vertical margin to have. 0.1 for 10 percent.
   */
   virtual HRESULT __stdcall SetTitleSafeMargins(
       bool in_bEnable,
       float in_fPercentWidth,
       float in_fPercentHeight
       ) = 0; 

};

#endif //IMVLIVEWINDOW3_H
