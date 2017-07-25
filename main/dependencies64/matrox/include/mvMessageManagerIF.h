//$Archive: /VP/END-USER/DLLS/mvCentralManager/inc/mvMessageManagerIF.h $
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


#ifndef IMvMessageManager_h_h
#define IMvMessageManager_h_h

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <initguid.h> //For DEFINE_GUID
   #include <unknwn.h> //For IUnknown
   #include <winerror.h> //For HRESULT
#endif

#include "mvMessageIF.h" //For IMvMessage
#include "mvMessageStackIF.h" //For IMvMessageStack
#include "mvTypes.h" //For uint16_t



//Message Manager GUID
#ifndef DEFINED_Message_MANAGER_GUID
#define DEFINED_Message_MANAGER_GUID
// {F1407402-96E7-497E-BA73-778F45C30077}
DEFINE_GUID(CLSID_IMvMessageManager, 
			0xf1407402, 0x96e7, 0x497e, 0xba, 0x73, 0x77, 0x8f, 0x45, 0xc3, 0x0, 0x77);
#endif

// {9E1C3E1D-C1D7-4619-B8C4-E6A82973B1F9}
DEFINE_GUID(IID_IMvMessageManager, 
			0x9e1c3e1d, 0xc1d7, 0x4619, 0xb8, 0xc4, 0xe6, 0xa8, 0x29, 0x73, 0xb1, 0xf9);

/**
* Public interface used for dealing with our messages inside OEM modules. It exposes a porint of the functions of IMvMessageManagerInternal. Basically, it allows OEMS to retrieve errors and messages but not to add any.
*/
interface IMvMessageManager : public IUnknown
{
public:
	/**
	* Empties and deletes the message stack of the calling thread. The calling thread will no longer retrieve any messages. The user calls this method when he has no need for any of the messages inside (i.e. has fixed an error inside).
	* [Click here and type/paste your function's code example]
	* Parameters
	* None
	* Return values
	* None
	*/
	virtual void __stdcall FlushMessageStack( ) = 0;
	/**
	* Retrieves the last message associated with the calling thread.
	* [Click here and type/paste your function's code example]
	* Parameters
	* out_ppIMessage
	* Pointer to the pointer of the interface that will contain the message. If no such message exists, NULL will the pointer will point to NULL.
	* Return values
	* HRESULT values:
	* ?	NOERROR if the message was successfully retrieved, even no such message exists.
	* ?	E_INVALIDARG if a NULL parameter was passed.
	*/
	virtual HRESULT __stdcall GetLastMessage( IMvMessage** out_ppIMessage ) = 0;
	/**
	* Retrieves the message stack associated with the calling thread. After having retrieved it, the user will have access to functions to navigate through all messages of the stack. See IMvMessageStack interface.
	* [Click here and type/paste your function's code example]
	* Parameters
	* out_ppIMessageStack
	* Pointer to the pointer to the interface that will contain the Message stack.
	* Return values
	* HRESULT values:
	* ?	NOERROR if the stack was successfully retrieved, even if it does not contain any messages.
	* ?	E_INVALIDARG if a NULL parameter was passed.
	*/
	virtual HRESULT __stdcall GetMessageStack( IMvMessageStack** out_ppIMessageStack ) = 0;
};



#endif
