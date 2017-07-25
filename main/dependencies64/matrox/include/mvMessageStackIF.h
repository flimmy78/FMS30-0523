//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvMessageStackIF.h $
/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/


#ifndef IMvMessageStack_h_h
#define IMvMessageStack_h_h

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <initguid.h> //For DEFINE_GUID
   #include <unknwn.h> //For IUnknown
   #include <winerror.h> //For HRESULT
#endif

#include "mvMessageIF.h" //For IMvMessage

/**
 * Interface given to users to manipulate a stack of messages.
 */
interface IMvMessageStack : public IUnknown
{
	
public:
	virtual void __stdcall FlushMessageStack( ) = 0;
	virtual HRESULT __stdcall GetFirst( IMvMessage** out_ppIMessage ) = 0;
	virtual HRESULT __stdcall GetLast( IMvMessage** out_ppIMessage ) = 0;
	virtual HRESULT __stdcall GetPrevious( IMvMessage** out_ppIMessage ) = 0;
	virtual HRESULT __stdcall GetNext( IMvMessage** out_ppIMessage ) = 0;
	
};

#endif
