//$Archive: /VP/END-USER/DLLS/mvCentralManager/inc/mvManagerSingletonDestroyer.h $
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

#ifndef CMvManagerSingletonDestroyer_h_h
#define CMvManagerSingletonDestroyer_h_h

#define REGISTER_INTERNAL_MANAGER_SINGLETON     CMvManagerSingletonDestroyer::RegisterDestruction();
#define UNREGISTER_INTERNAL_MANAGER_SINGLETON   CMvManagerSingletonDestroyer::UnRegisterDestruction();

#include "mvDefinitions.h" // For MV_DECLSPEC_x macros
	
class MV_DECLSPEC_DLLEXPORT CMvManagerSingletonDestroyer
{
public:
	static void RegisterDestruction();
	static void UnRegisterDestruction();

protected:
	~CMvManagerSingletonDestroyer();
};


#endif
