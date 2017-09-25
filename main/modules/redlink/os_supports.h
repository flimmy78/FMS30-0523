#ifndef __OS_SUPPORTS_H__
#define __OS_SUPPORTS_H__

//CPrivateMutex:平台无关锁接口，需要进行跨平台实现
#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#include <assert.h>
#else
#include <pthread.h>
#include <assert.h>
#endif
#include <string.h>

class CPrivateMutex
{
#if (defined(WIN32) || defined(WIN64))
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif

public:

	CPrivateMutex()
	{
#if (defined(WIN32) || defined(WIN64))
		mutex = CreateMutex(NULL, false, NULL);
#else
		pthread_mutex_init(&mutex, NULL);
#endif        
	}

	~CPrivateMutex()
	{
#if (defined(WIN32) || defined(WIN64))
		CloseHandle(mutex);
#else
		pthread_mutex_destroy(&mutex);
#endif          
	}

	void lock()
	{
#if (defined(WIN32) || defined(WIN64))
		WaitForSingleObject(mutex, 0xffffffff);
#else
		pthread_mutex_lock(&mutex);
#endif          
	}

	void unlock()
	{
#if (defined(WIN32) || defined(WIN64))
		ReleaseMutex(mutex);
#else
		pthread_mutex_unlock(&mutex);
#endif          
	}
};

class CAutoLock
{
	CPrivateMutex* m_plock;
public:
	CAutoLock(CPrivateMutex* obj) :
		m_plock(obj)
	{
		assert(m_plock);
		m_plock->lock();
	}
	~CAutoLock()
	{
		m_plock->unlock();
	}
};

class CThreadObj
{

#if (defined(WIN32) || defined(WIN64))
	HANDLE m_thread;
#else
	pthread_t m_thread;
#endif         

#if (defined(WIN32) || defined(WIN64))
	static DWORD WINAPI os_thread_func(LPVOID o);
#else
	static void* os_thread_func(void* o);
#endif

protected:
	CThreadObj();
	virtual ~CThreadObj();

	virtual void run();
	bool CreateAndRun();
public:
	void WaitExit();
};



#endif
