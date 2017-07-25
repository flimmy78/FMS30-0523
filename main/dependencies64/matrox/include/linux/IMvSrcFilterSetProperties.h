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
//                    IMVSRCFILTERSETPROPERTIES.H
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


#ifndef IMVSRCFILTERSETPROPERTIES_H
#define IMVSRCFILTERSETPROPERTIES_H

/**
* Sets the properties of a Source filter.
* @interface
* 
*/
interface IMvSrcFilterSetProperties : public IUnknown
{
public:   

   /**
    * Determines whether or not the Source filter needs to check for data in cached memory before loading.
    * If set to FALSE, the Source filter always loads data from disk.
    *
    * <br><b>Remark:</b>
	* <ul><li>
	* </ul>
    * <b>Return Type:</b>
    * 
    * <ul><li>HRESULT
	* </ul>
    * <b>Return Values:</b>
    * <ul><li>MV_NOERROR, if completed successfully.
	* <li>MV_E_FAIL, if failed.
	* </ul>
    * @param <i>const bool	in_bUseCache </i>: TRUE to use cache recovery. FALSE, otherwise.
    */
   virtual HRESULT __stdcall UseCache
   (
   	const bool	in_bUseCache
   ) = 0;
};



#endif //IMVSRCFILTERSETPROPERTIES_H
