#include "Mutex.h"
//互斥锁（mutex）：

//互斥锁是一种用于保护临界区的同步机制，它确保在任何时刻只有一个线程可以访问被保护的资源或临界区。
//当一个线程获得了互斥锁时，其他线程必须等待该线程释放锁后才能获得锁并访问临界区。
//互斥锁通常用于保护共享资源，防止多个线程同时访问和修改，以确保数据的一致性和完整性。
Mutex::Mutex()
{
#if defined(WIN32)
    m_mutex = ::CreateMutex(NULL, FALSE, NULL);
#else
    pthread_mutex_init(&mutex, NULL);
#endif

}

Mutex::~Mutex()
{
#if defined(WIN32)
    ::CloseHandle(m_mutex);
#else
     pthread_mutex_destroy(&mutex);
#endif

}

int Mutex::Lock() const
{
#if defined(WIN32)
    DWORD ret = WaitForSingleObject(m_mutex, INFINITE);
#else
    int ret = pthread_mutex_lock((pthread_mutex_t*)&mutex);
#endif

    return ret;

}

int Mutex::Unlock() const
{
#if defined(WIN32)
    bool ret = ::ReleaseMutex(m_mutex);
#else
    int ret = pthread_mutex_unlock((pthread_mutex_t*)&mutex);
#endif
    return ret;
}

