//$Archive: /VP/END-USER/DLLS/mvCentralManager/inc/mvManagerSingleton.h $
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

#ifndef CMvManagerSingleton_h_h
#define CMvManagerSingleton_h_h

#include "mvMessageManagerIF.h"
#include "mvDefinitions.h" // For MV_DECLSPEC_x macros

/**
* This is the singleton to access the message manager.
* It is used by OEMS and allows the caller to retrieve only public
* interfaces. These are:
* IMvMessageManager.
*/
class MV_DECLSPEC_DLLEXPORT CMvManagerSingleton 
{
	//Friend class responsible for destroying the Singleton
	friend class CMvManagerSingletonDestroyer;


protected:
	//
	// Constructor & destructor
	//

	CMvManagerSingleton(  );
	~CMvManagerSingleton( );

	static void DestroySingleton();

public:
	IMvMessageManager* __stdcall GetIMvMessageManager( );

	//Two method to retrive the singleton
	static CMvManagerSingleton* __stdcall GetInstance();

	static CMvManagerSingleton* __stdcall GetManagerSingleton();

private:
	IMvMessageManager*				m_pIMvMessageManager;

	HRESULT							m_hrFromCoInit;

	static CMvManagerSingleton*		m_poCentralManagerInstance;	
};

#endif
