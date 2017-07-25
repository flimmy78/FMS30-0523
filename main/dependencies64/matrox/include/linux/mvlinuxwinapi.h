#ifndef MVLINUXWINAPI_H_
#define MVLINUXWINAPI_H_

#include "mvLinuxDefinitions.h"
#include "mvThread.h"

// Windows API replacement
WINBASEAPI BOOL WINAPI SetEvent(IN HANDLE hEvent);
WINBASEAPI BOOL WINAPI ResetEvent(IN HANDLE hEvent);
WINBASEAPI DWORD WINAPI WaitForSingleObject(IN HANDLE hHandle, IN DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI WaitForMultipleObjects(IN DWORD nCount, IN CONST HANDLE *lpHandles, IN BOOL bWaitAll, IN DWORD dwMilliseconds);
WINBASEAPI HANDLE WINAPI CreateEvent(IN LPSECURITY_ATTRIBUTES lpEventAttributes, IN BOOL bManualReset, IN BOOL bInitialState, IN LPCWSTR lpName);
WINBASEAPI BOOL WINAPI CloseHandle(IN OUT HANDLE hObject);

/*
WINBASEAPI HANDLE WINAPI CreateEventA(IN LPSECURITY_ATTRIBUTES lpEventAttributes, IN BOOL bManualReset, IN BOOL bInitialState, IN LPCSTR lpName);
WINBASEAPI HANDLE WINAPI CreateEventW(IN LPSECURITY_ATTRIBUTES lpEventAttributes, IN BOOL bManualReset, IN BOOL bInitialState, IN LPCWSTR lpName);
#ifdef UNICODE
#define CreateEvent  CreateEventW
#else
#define CreateEvent  CreateEventA
#endif
*/

//WINBASEAPI BOOL WINAPI PulseEvent(IN HANDLE hEvent);

//WINBASEAPI BOOL WINAPI ReleaseSemaphore(IN HANDLE hSemaphore, IN LONG lReleaseCount, OUT LPLONG lpPreviousCount);

//WINBASEAPI BOOL WINAPI ReleaseMutex(IN HANDLE hMutex);



//WINBASEAPI HANDLE WINAPI CreateMutex(IN LPSECURITY_ATTRIBUTES lpMutexAttributes, IN BOOL bInitialOwner, IN LPCWSTR lpName);
/*
WINBASEAPI HANDLE WINAPI CreateMutexA(IN LPSECURITY_ATTRIBUTES lpMutexAttributes, IN BOOL bInitialOwner, IN LPCSTR lpName);
WINBASEAPI HANDLE WINAPI CreateMutexW(IN LPSECURITY_ATTRIBUTES lpMutexAttributes, IN BOOL bInitialOwner, IN LPCWSTR lpName);
#ifdef UNICODE
#define CreateMutex  CreateMutexW
#else
#define CreateMutex  CreateMutexA
#endif
*/

//WINBASEAPI HANDLE WINAPI OpenMutex(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
/*
WINBASEAPI HANDLE WINAPI OpenMutexA(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCSTR lpName);
WINBASEAPI HANDLE WINAPI OpenMutexW(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
#ifdef UNICODE
#define OpenMutex  OpenMutexW
#else
#define OpenMutex  OpenMutexA
#endif
*/



//WINBASEAPI HANDLE WINAPI OpenEventW(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
//
//WINBASEAPI HANDLE WINAPI OpenEvent(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCSTR lpName);
///*
//WINBASEAPI HANDLE WINAPI OpenEventA(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCSTR lpName);
//WINBASEAPI HANDLE WINAPI OpenEventW(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
//#ifdef UNICODE
//#define OpenEvent  OpenEventW
//#else
//#define OpenEvent  OpenEventA
//#endif
//*/
//
//WINBASEAPI HANDLE WINAPI CreateSemaphore(IN LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, IN LONG lInitialCount, IN LONG lMaximumCount, IN LPCWSTR lpName);
///*
//WINBASEAPI HANDLE WINAPI CreateSemaphoreA(IN LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, IN LONG lInitialCount, IN LONG lMaximumCount, IN LPCSTR lpName);
//WINBASEAPI HANDLE WINAPI CreateSemaphoreW(IN LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, IN LONG lInitialCount, IN LONG lMaximumCount, IN LPCWSTR lpName);
//#ifdef UNICODE
//#define CreateSemaphore  CreateSemaphoreW
//#else
//#define CreateSemaphore  CreateSemaphoreA
//#endif
//*/ 
//
//WINBASEAPI HANDLE WINAPI OpenSemaphore(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
///*
//WINBASEAPI HANDLE WINAPI OpenSemaphoreA(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCSTR lpName);
//WINBASEAPI HANDLE WINAPI OpenSemaphoreW(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN LPCWSTR lpName);
//#ifdef UNICODE
//#define OpenSemaphore  OpenSemaphoreW
//#else
//#define OpenSemaphore  OpenSemaphoreA
//#endif
//*/ 
//

//
//WINBASEAPI BOOL WINAPI DuplicateHandle
//(
//    IN HANDLE hSourceProcessHandle, 
//    IN HANDLE hSourceHandle,
//    IN HANDLE hTargetProcessHandle,
//    OUT LPHANDLE lpTargetHandle,
//    IN DWORD dwDesiredAccess,
//    IN BOOL bInheritHandle,
//    IN DWORD dwOptions
//);

#endif /*MVLINUXWINAPI_H_*/
