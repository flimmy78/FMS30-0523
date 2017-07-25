//$Archive: /VP/END-USER/DLLS/mvCentralManager/inc/mvCentralManagerIF.h $
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


#ifndef IMvCentralManager_h_h
#define IMvCentralManager_h_h

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <initguid.h> //For DEFINE_GUID
   #include <unknwn.h> //For IUnknown

   #include <winerror.h> //For HRESULT
#endif

#include "mvMessageManagerIF.h"


#ifndef DEFINED_CENTRAL_MANAGER_GUID
#define DEFINED_CENTRAL_MANAGER_GUID
// {C0EE9D5B-67A9-4CFF-9CEB-2325FF092FE7}
DEFINE_GUID(CLSID_IMvCentralManager, 
			0xc0ee9d5b, 0x67a9, 0x4cff, 0x9c, 0xeb, 0x23, 0x25, 0xff, 0x9, 0x2f, 0xe7);
#endif



//////////////////////////////////////////////////////////////////////////////////
// IMvCentralManager interface
//////////////////////////////////////////////////////////////////////////////////

// {9C6AB2D0-5FEB-46E1-9750-4A189BBC644B}
DEFINE_GUID(IID_IMvCentralManager, 
			0x9c6ab2d0, 0x5feb, 0x46e1, 0x97, 0x50, 0x4a, 0x18, 0x9b, 0xbc, 0x64, 0x4b);

interface IMvCentralManager : public IUnknown
{
	
public:
	virtual HRESULT __stdcall GetIMvMessageManager( IMvMessageManager** out_ppIMvToReturn ) = 0;	
};

#endif
