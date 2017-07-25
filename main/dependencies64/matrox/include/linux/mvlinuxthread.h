
#ifndef MVLINUXTHREAD_H_
#define MVLINUXTHREAD_H_

#pragma once

#include <string>

#define MV_MAX_THREAD_NAME_SIZE 128
//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base class for exception objects.
// Remarks:
//    - All exceptions in mvUtility derive from this class.
//
//////////////////////////////////////////////////////////////////////////
class CMvBaseException
{
public:
   //
   // Summary:
   //    Constructor without exception reason string.
   //
   CMvBaseException() {}

   //
   // Summary:
   //    Constructor with exception reason string.
   //
   explicit CMvBaseException(const std::string& in_strExceptionReason)
      : m_strReason(in_strExceptionReason) {}

   //
   // Summary:
   //    Returns the exception reason string (or empty string if it was not set).
   //
   const std::string& GetExceptionReason() const { return m_strReason; }

   //
   // Summary:
   //    Destructor.
   //
   virtual ~CMvBaseException() {}

private:
   std::string m_strReason;   // Error code
};

enum EMvSyncObjectType
{
	keMvSyncObjectTypeInvalid = 0,
	keMvSyncObjectTypeCriticalSection,
	keMvSyncObjectTypeMutex,
	keMvSyncObjectTypeSemaphore,
	keMvSyncObjectTypeEvent,
	keMvSyncObjectTypeIPCMutex,
	keMvSyncObjectTypeIPCSemaphore,
	keMvSyncObjectTypeIPCEvent,
	keMvSyncObjectTypeKernelEvent,
	keMvSyncObjectTypeLast
};
	
//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The base class of all synchronization objects (objects which support Wait()).
// Remarks:
//    - Objects derived from this class that support Release() can be used with CMvAutoLock. 
//
//////////////////////////////////////////////////////////////////////////
class CMvSynchronizationObject
{
public:
   // Default constructor.
   CMvSynchronizationObject();
   
   // Default destructor.
   virtual ~CMvSynchronizationObject() {};

   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the 
   //    object was available.
   // Remarks:
   //    - If the time-out period is not specified, the wait is infinite.
   //
   virtual bool Wait
      (
      unsigned long in_ulTimeOut = INFINITE     // Time out preiod in milliseconds.
      ) /*throw()*/ = 0;

   //
   // Summary:
   //    Most objects that were successfully "waited-on" need to be released before an other wait 
   //    can succeed.
   // Remarks:
   //    - Some objects cannot be released (like CMvEvent, CMvThread, and CMvThreadRedirector).
   //
   virtual void Release() /*throw()*/ = 0;

   //
   // Summary:
   //	Under Linux, the implementation differs from the one in Windows
   //	We need to be able to differentiate between each type of SyncObject.
   void SetMvSyncObjectType(EMvSyncObjectType in_eMvSyncObjectType)
   {
   		m_eMvSyncObjectType = in_eMvSyncObjectType;
   }
   
   EMvSyncObjectType GetMvSyncObjectType()
   {
   		return m_eMvSyncObjectType;
   }
   
private:
	EMvSyncObjectType	m_eMvSyncObjectType;   
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvAutoLock objects.
// See also:
//    CMvBaseException
//
//////////////////////////////////////////////////////////////////////////
class CMvAutoLockException : public CMvBaseException
{
public:
   // Build a CMvAutoLockException by initializing properly the CMvBaseException base class
   explicit CMvAutoLockException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class use a CMvSynchronizationObject to lock on construction and unlcok on
//    destruction.
// Description:
//    When objects of this type get destroyed, they automatically release their associated 
//    synchronization object.
// Remarks:
//    - Any object that derives from CMvSynchronizationObject and implements
//      the Release method can be passed to CMvAutoLock objects such as CMvCriticalSection, CMvMutex,
//      and CMvSemaphore.
//
//////////////////////////////////////////////////////////////////////////
class CMvAutoLock
{
public:
   //
   // Summary:
   //    Constructor calls in_poSyncObject->Wait().
   //
   explicit CMvAutoLock(CMvSynchronizationObject * in_poSyncObject);

   //
   // Summary:
   //    Destructor calls Release() on the in_poSyncObject that was passed in the constructor.
   //
   ~CMvAutoLock();

private:
   //
   // Summary:
   //    Object to use for locking mechanism.
   //
   CMvSynchronizationObject * m_poSyncObject;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvCriticalSection objects.
// See also:
//    CMvBaseException
//
//////////////////////////////////////////////////////////////////////////
class CMvCriticalSectionException : public CMvBaseException
{
public:
   // Build a CMvCriticalSectionException by initializing properly the CMvBaseException base class
   explicit CMvCriticalSectionException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class encapsulate a Win32 critical section.
// Remarks:
//    - When objects of this type get destroyed, they automatically release their associated
//      synchronization object.
//    - Any object that derives from CMvSynchronizationObject and implements the Release method can 
//      be passed to CMvAutoLock objects such as CMvCriticalSection, CMvMutex, and CMvSemaphore.
//
//////////////////////////////////////////////////////////////////////////
class CMvCriticalSection : public CMvSynchronizationObject
{
public:
   //
   // Summary:
   //    Default constructor.
   //
   CMvCriticalSection();

   //
   // Summary:
   //    Default destructor.
   //
   virtual ~CMvCriticalSection();

   //
   // Summary:
   //    Waits on this object until it becomes available. The time-out in milliseconds is optional.
   //
   bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvCriticalSectionException);

   //
   // Summary:
   //    Object becomes available.
   //
   void Release() throw();

private:
   // Critical section to handle.
   CRITICAL_SECTION m_oCriticalSection;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvHandleSyncObject 
//    objects (and from objects that derive from CMvHandleSyncObject that use its methods).
// See also:
//    CMvBaseException.
//
//////////////////////////////////////////////////////////////////////////
class CMvHandleSyncObjectException : public CMvBaseException
{
public:
   // Build a CMvHandleSyncObjectException by initializing properly the CMvBaseException base class
   explicit CMvHandleSyncObjectException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};

typedef struct
{
	size_t				size;		// has to be sizeof(SHANDLEBLOB)
	EMvSyncObjectType	eMvSyncObjectType;
} SHANDLEBLOB;   

	
//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The base class of all synchronization objects that are implemented using Win32 handles.
// Description:
//    All objects derived from this class can be passed to WaitForAll() or WaitforAny() functions. 
//
//    An object of this type can be created by passing a Win32 handle (like a Win32 event handle),
//    so that this handle can be used with other objects found in this library.
//
//////////////////////////////////////////////////////////////////////////
class CMvHandleSyncObject : public CMvSynchronizationObject
{
public:
   //
   // Summary:
   //    Default constructor.
   //
   CMvHandleSyncObject();

   //
   // Summary:
   //    Creates a synchronization object from a Win32 handle.
   // Description:
   //    This can be useful in cases where only a Win32 event is given to you and you want to use 
   //    it with a CMvMutex object in a call to WaitForAll().  A duplicate handle is created
   //    internally, so you must still call the Win32 CloseHandle() function with the original
   //    handle when you no longer need to refer to it
   //
   explicit CMvHandleSyncObject(HANDLE in_hObject);

   //
   // Summary:
   //    Calls the Win32 CloseHandle() function its internal Win32 handle.
   //
   virtual ~CMvHandleSyncObject();

   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   virtual bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvHandleSyncObjectException);

   //
   // Summary:
   //    Most objects that were successfully "waited-on" need to be released before an other wait
   //    can succeed.
   // Remarks:
   //    - Some objects cannot be released such as CMvEvent, CMvThread, and CMvThreadRedirector.
   //
   virtual void Release() throw(CMvHandleSyncObjectException);

   //
   // Summary:
   //    Waits for all CMvHandleSyncObject (and derived) objects to become available.
   // Description:
   //    This is a wrapper to the Win32 WaitForMultipleObjects (with bWaitAll set to TRUE) function
   //    that works with CMvHandleSyncObject (and derived) objects.
   // Return value:
   //   Returns true if successful, false if the time-out occurred.
   //
   friend bool WaitForAll
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut
      );

   //
   // Summary:
   //    Waits for any CMvHandleSyncObject (and derived) objects to become available.
   // Description:
   //    This is a wrapper to the Win32 WaitForMultipleObjects (with bWaitAll set to FALSE) 
   //    function that works with CMvHandleSyncObject (and derived) objects.
   // Return value:
   //    Returns the index into the array of the first object that became available,
   //    or -1 if the time-out occurred.
   //
   friend int WaitForAny
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut
      );

protected:
   // Copy constructor
   CMvHandleSyncObject(const CMvHandleSyncObject& in_oObject);

   // Assignement operator
   CMvHandleSyncObject& operator=(const CMvHandleSyncObject& in_oObject);
   
   HANDLE					m_hObject;

};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvMutex objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvMutexException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvMutexException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvMutexException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};

class CMvVirtualSyncObject;
class CMvVirtualEvent;

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 mutex.
//
//////////////////////////////////////////////////////////////////////////
class CMvMutex : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a mutex.
   //
   CMvMutex();

   //
   // Summary:
   //    Destructor of a mutex.
   //
   ~CMvMutex();
   
   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   virtual bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvMutexException);
   //
   // Summary:
   //    Release the object so that it becomes available.
   //
   void Release() throw(CMvMutexException);
   
private:
	CMvVirtualSyncObject		*m_pMutex;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvSemaphore objects. 
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvSemaphoreException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvSemaphoreException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvSemaphoreException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 semaphores.
// Description:
//    Behaves very much like a mutex except that there can be more than one successful wait on it 
//    (up to a predetermined count) without having any releases.
//
//////////////////////////////////////////////////////////////////////////
class CMvSemaphore : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a semaphore with an initial count of possible successful waits that can be made
   //    (i.e. that would not block).
   // Remarks: 
   //    - Initial count must be greater than or equal to zero and less than or equal to maximum count.
   //    - Maximum count is only defined in Windows API and is therefore IGNORED IN LINUX.
   //    - Trying to release a semaphore that had already reached its maximum count specified
   //      when the semaphore was created would cause a CMvSemaphoreException to be thrown.
   //    
   explicit CMvSemaphore(long in_lInitialCount, long in_lMaxCount);

   //
   // Summary:
   //    Destructor of a semaphore.
   //
   ~CMvSemaphore();
   
   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   virtual bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvSemaphoreException);
    //
   // Summary:
   //    Increments the count by one of successful waits that can be made.
   // Description:
   //    If the count becomes greater than zero, the object becomes available.
   //
   void Release() throw(CMvSemaphoreException);

private:
	CMvVirtualSyncObject		*m_pSemaphore;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvEvent objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvEventException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvEventException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvEventException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 events.
//
//////////////////////////////////////////////////////////////////////////
class CMvEvent : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a manual reset event by default.
   //
   explicit CMvEvent
      (
      bool in_bManualReset = true   // False to create an auto-reset event.
      );

	~CMvEvent();
	
   //
   // Summary:
   //    Sets the event.
   //
   void Set() throw(CMvEventException);

   //
   // Summary:
   //    Resets event.
   //
   void Reset() throw(CMvEventException);
  //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   virtual bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvEventException);
	
	friend WINBASEAPI DWORD WINAPI WaitForSingleObject(IN HANDLE in_hHandle, IN DWORD in_dwMilliseconds);
	friend WINBASEAPI DWORD WINAPI WaitForMultipleObjects(IN DWORD nCount, IN CONST HANDLE *lpHandles, IN BOOL bWaitAll, IN DWORD dwMilliseconds);
	
private:
	CMvVirtualEvent	*m_pVirtualEvent;	
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvThread objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvThreadException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvThreadException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvThreadException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 threads.
// Remarks:
//    - It is safe to call C run-time library functions from these threads.
//
//////////////////////////////////////////////////////////////////////////
class CMvThread : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a thread object that can do nothing until Create() is called.
   //
   CMvThread();

   // Destructor
   virtual ~CMvThread();

   // Defining the prototype of the user thread function.
   typedef unsigned int (__stdcall *PFNTHREAD_FUNCTION)(void* in_pThreadParameter);

   //
   // Summary:
   //    Creates a thread that will call the function passed to it along with a void* data parameter.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default 
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   //
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                        // Pointer to the function that the thread will call
      void *             in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool               in_bSuspended = false,                   // False to execute thread right away (default)   
      unsigned int       in_uiStackSize = ms_kuiDefaultStackSize, // Thread stack size (0 for OS default)   
      bool               in_bUseSecurityAttribute = false         // False to not use a security attribute (default)
      ) 
      throw(CMvThreadException);

   //
   // Summary:
   //    Sets a mask that tells Windows on which CPU/s this thread can run on (using the Win32
   //    SetThreadAffinityMask()).
   //
   void SetAffinityMask(unsigned int in_uiAffinityMask) throw(CMvThreadException);

   //
   // Summary:
   //    Suspends the thread (using the Win32 SuspendThread()).
   //
   void Suspend() throw(CMvThreadException);

   //
   // Summary:
   //    Resumes the thread (using the Win32 ResumeThread()).
   //
   void Resume() throw(CMvThreadException);

   //
   // Summary:
   //    Resumes the thread (using the Win32 ResumeThread()).
   //
   void WaitOnResume() throw(CMvThreadException);

   //
   // Summary:
   //    Changes the threads priority (using the Win32 SetThreadPriority()).
   //
   void SetPriority(int in_iPriority = THREAD_PRIORITY_NORMAL) throw(CMvThreadException);

   //
   // Summary:
   //    Gets the return value of the thread's associated function.
   // Remarks:
   //    - Call this once the thread has completed.
   //
   unsigned int GetExitCode() const throw(CMvThreadException);

   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvThreadException);

   //
   // Summary:
   //    Set the public name of the thread.
   // Remarks:
   //    - Does not work under Linux. This methods makes cross platform applications with less #ifdef.
   //
   void SetPublicThreadName(const char* in_kszThreadName);

   //
   // Summary:
   //    Gets the operating system thread ID
   // Remarks:
   //    - Call this once the thread has been created.
   //
   pthread_t GetThreadID() {return m_uiThreadID;}

   // Default stack size for the new threads
   //static const unsigned int ms_kuiDefaultStackSize = 128 * 1024;  // 128KB
   static const unsigned int ms_kuiDefaultStackSize = 524288;  // 512KB

   void	Entry();

protected:
#ifndef MAC_PLATFORM
   bool _SetAffinityMask();
#else
   bool _SetAffinityMask(unsigned int in_iIndex);
#endif
    
   // Summary:
   //    Internal use only.  Will set the name to the Public Thread Name.Not implemented on Linux
   void _setThreadName();
   
   bool _SetPriority();

protected:
   pthread_t m_uiThreadID;    // Operating system thread ID.
   CMvEvent m_eventStart;
   CMvEvent m_eventCompletion;
   int m_iPolicy;
   int m_iPriority;
   cpu_set_t m_AffinityMask;
   bool m_bAffinityMaskSet;
   unsigned int m_uiExitCode;

   PFNTHREAD_FUNCTION m_pfnUserProc;   // Function that the thread will call.
   void * m_pUserThreadParameter;      // Context data.
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvCOMThread objects.
// See also:
//    CMvThreadException
//
//////////////////////////////////////////////////////////////////////////
class CMvCOMThreadException : public CMvThreadException
{
public:
   // Build a CMvCOMThreadException by initializing properly the CMvThreadException base class
   explicit CMvCOMThreadException(const std::string& in_strExceptionReason)
      : CMvThreadException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 threads.
//
//////////////////////////////////////////////////////////////////////////
class CMvCOMThread : public CMvThread
{
public:
   // Default constructor
   CMvCOMThread();
      
   //
   // Summary:
   //    Creates a thread that will call the function passed to it along with a void* data parameter.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default 
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   // Remarks: 
   //    Call ::CoInitialize for COM initialization before calling the user thread function.
   //
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                  // Pointer to the function that the thread will call
      void *       in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool         in_bSuspended = false,                   // False to execute thread right away (default)
      unsigned int in_uiStackSize = ms_kuiDefaultStackSize, // Thread stack size
      bool         in_bMultithreadedCOM = false             // Flags to used with the CoInitiliazeEx call. 
      ) 
      throw(CMvHandleSyncObjectException, CMvEventException, CMvThreadException, CMvCOMThreadException);

};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is a template class that creates a thread that calls an object's method instead of 
//    calling a function.
// Remarks:
//    - Same as CMvThread except for Create().
// see also:
//    CMvThread 
//////////////////////////////////////////////////////////////////////////
template<class T>
class CMvThreadRedirector : public CMvThread
{
public:
   CMvThreadRedirector();

   //
   // Summary:
   //    Creates a thread that will call an object of type T through a method that returns an
   //    unsigned int.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   //
   void Create
      (
      T *          in_poObject, 
      unsigned int (T::*in_pfnMemberFunction)(), 
      bool         in_bSuspended = false, 
      unsigned int in_uiStackSize = ms_kuiDefaultStackSize
      ) 
      throw(CMvThreadException);

protected:
   T * m_poObject;	// Pointer to the object that the thread will call
   unsigned int (T::*m_pfnMemberFunction)();	// Pointer to the member function to call the object with
   static unsigned int __stdcall ThreadFunction(void* in_pThreadParameter);

private:
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                        // Pointer to the function that the thread will call
      void             * in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool               in_bSuspended = false,                   // False to execute thread right away (default)   
      unsigned int       in_uiStackSize = ms_kuiDefaultStackSize  // Thread stack size (0 for OS default)
      );
};

// Default constructor.
template<class T>
inline CMvThreadRedirector<T>::CMvThreadRedirector() : 
   CMvThread(), m_poObject(NULL), m_pfnMemberFunction(NULL) 
{
}

// Creates the thread.
template<class T>
inline void CMvThreadRedirector<T>::Create
   (
   T *          in_poObject,                    
   unsigned int (T::*in_pfnMemberFunction)(),   
   bool         in_bSuspended,                  
   unsigned int in_uiStackSize                  
   ) 
   throw(CMvThreadException)
{
   if (in_poObject == NULL || in_pfnMemberFunction == NULL)
   {
      throw CMvThreadException("CMvThreadRedirector<T>::Create -> invalid parameters");
   }

   m_poObject = in_poObject;
   m_pfnMemberFunction = in_pfnMemberFunction;
   CMvThread::Create(CMvThreadRedirector<T>::ThreadFunction, this, in_bSuspended, in_uiStackSize);
}

// Internal thread function
template<class T>
inline unsigned int __stdcall CMvThreadRedirector<T>::ThreadFunction(void* in_pThreadParameter)
{
   CMvThreadRedirector<T>* poThis = reinterpret_cast<CMvThreadRedirector<T>*>(in_pThreadParameter);
   return ((poThis->m_poObject)->*(poThis->m_pfnMemberFunction))();
}

#endif //#ifndef MVLINUXTHREAD_H_


