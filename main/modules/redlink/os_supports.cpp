#include "os_supports.h"

CThreadObj::CThreadObj() :
	m_thread(0)
{

}

CThreadObj::~CThreadObj()
{
	WaitExit();
}

void CThreadObj::run() {
	return;
}

#if (defined(WIN32) || defined(WIN64))
DWORD WINAPI CThreadObj::os_thread_func(LPVOID o)
#else
void* CThreadObj::os_thread_func(void* o)
#endif    
{
	CThreadObj* This = reinterpret_cast<CThreadObj*>(o);
	This->run();

#if (defined(WIN32) || defined(WIN64))
	ExitThread(0);
	return S_OK;
#else    
	return This;
#endif
}

void CThreadObj::WaitExit()
{
	if (!m_thread)
		return;

#if (defined(WIN32) || defined(WIN64))
	WaitForSingleObject(m_thread, 0xffffffff);
#else    
	pthread_join(m_thread, NULL);
#endif    
}

bool CThreadObj::CreateAndRun()
{
	if (m_thread)
		return false;

#if (defined(WIN32) || defined(WIN64))
	m_thread = ::CreateThread(NULL, 0, os_thread_func, this, 0, NULL);
#else
	pthread_create(&m_thread, NULL, os_thread_func, this);
#endif

	return true;
}
