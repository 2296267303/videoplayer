#include "Cond.h"
//条件变量（condition variable）：

//条件变量是一种用于线程间通信的同步机制，它允许线程在特定条件下等待或被唤醒。
//条件变量通常与互斥锁一起使用，它依赖于互斥锁来确保线程间对条件的安全访问。
//当一个线程等待某个条件时，它会释放互斥锁并进入睡眠状态，直到另一个线程通过条件变量发出信号或广播来通知该条件已经满足，并唤醒等待的线程。
//使用条件变量可以避免忙等待（busy waiting），提高了线程的效率和性能。
Cond::Cond()
{
#if defined(WIN32) && !defined(MINGW)
    InitializeCriticalSection(&m_mutex);
    InitializeConditionVariable(&m_cond);
#else
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);
#endif

}

Cond::~Cond()
{
#if defined(WIN32) && !defined(MINGW)
    DeleteCriticalSection(&m_mutex);
#else
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
#endif

}

//加锁
int Cond::Lock()
{
#if defined(WIN32) && !defined(MINGW)
    EnterCriticalSection(&m_mutex);
    return 0;
#else
    return pthread_mutex_lock(&m_mutex);
#endif

}

//解锁
int Cond::Unlock()
{
#if defined(WIN32) && !defined(MINGW)
    LeaveCriticalSection(&m_mutex);
    return 0;
#else
    return pthread_mutex_unlock(&m_mutex);
#endif
}

int Cond::Wait()
{
#if defined(WIN32) && !defined(MINGW)
    DWORD ret = SleepConditionVariableCS((PCONDITION_VARIABLE)&m_cond, &m_mutex, INFINITE);
#else
    int ret = pthread_cond_wait(&m_cond, &m_mutex);
#endif

    return ret;

}

//固定时间等待
int Cond::TimedWait(int second)
{
#if defined(WIN32) && !defined(MINGW)
    SleepConditionVariableCS((PCONDITION_VARIABLE)&m_cond, &m_mutex, second*1000);
    return 0;
#else
    struct timespec abstime;
    //获取从当前时间，并加上等待时间， 设置进程的超时睡眠时间
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += second;
    return pthread_cond_timedwait(&m_cond, &m_mutex, &abstime);
#endif

}

int Cond::Signal()
{
#if defined(WIN32) && !defined(MINGW)
    int ret = 0;
    WakeConditionVariable((PCONDITION_VARIABLE)&m_cond);
#else
    int ret = pthread_cond_signal(&m_cond);
#endif
    return ret;
}

//唤醒所有睡眠线程
int Cond::Broadcast()
{
#if defined(WIN32) && !defined(MINGW)
    WakeAllConditionVariable((PCONDITION_VARIABLE)&m_cond);
    return 0;
#else
    return pthread_cond_broadcast(&m_cond);
#endif

}
