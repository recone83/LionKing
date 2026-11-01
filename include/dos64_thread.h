#ifndef DOS64_THREAD_API_H
#define DOS64_THREAD_API_H

#include "dos64_api.h"

static const DOS64_API *Dos64Threads;

static inline int thread_init(const DOS64_API *Api)
{
    Dos64Threads = Api;
    return Api && Api->Version >= 11 &&
        Api->Size >= __builtin_offsetof(DOS64_API, Threads) + sizeof(Api->Threads) &&
        Api->Threads.Create && Api->Threads.Yield && Api->Threads.Join && Api->Threads.Self ? 0 : -1;
}

/* Call thread_init and check its result before using these wrappers. */
static inline DOS64_THREAD thread_start(DOS64_THREAD_ENTRY Entry, void *Argument,
                                        unsigned int StackBytes)
{
    return Dos64Threads->Threads.Create(Entry, Argument, StackBytes);
}
static inline int thread_pause(void) { return Dos64Threads->Threads.Yield(); }
static inline int thread_wait(DOS64_THREAD Thread, void **Result)
{
    return Dos64Threads->Threads.Join(Thread, Result);
}
static inline DOS64_THREAD thread_current(void) { return Dos64Threads->Threads.Self(); }

static inline int thread_sync_init(const DOS64_API *Api)
{
    if (thread_init(Api) != 0) { return -1; }
    return Api->Version >= 12 &&
        Api->Size >= __builtin_offsetof(DOS64_API, Sync) + sizeof(Api->Sync) &&
        Api->Sync.MutexCreate && Api->Sync.MutexDestroy && Api->Sync.MutexLock &&
        Api->Sync.MutexUnlock && Api->Sync.ConditionCreate && Api->Sync.ConditionDestroy &&
        Api->Sync.ConditionWait && Api->Sync.ConditionSignal && Api->Sync.ConditionBroadcast &&
        Api->Sleep ? 0 : -1;
}
static inline DOS64_MUTEX mutex_create(void) { return Dos64Threads->Sync.MutexCreate(); }
static inline int mutex_destroy(DOS64_MUTEX Mutex) { return Dos64Threads->Sync.MutexDestroy(Mutex); }
static inline int mutex_lock(DOS64_MUTEX Mutex) { return Dos64Threads->Sync.MutexLock(Mutex); }
static inline int mutex_unlock(DOS64_MUTEX Mutex) { return Dos64Threads->Sync.MutexUnlock(Mutex); }
static inline DOS64_CONDITION condition_create(void) { return Dos64Threads->Sync.ConditionCreate(); }
static inline int condition_destroy(DOS64_CONDITION Condition)
{
    return Dos64Threads->Sync.ConditionDestroy(Condition);
}
static inline int condition_wait(DOS64_CONDITION Condition, DOS64_MUTEX Mutex)
{
    return Dos64Threads->Sync.ConditionWait(Condition, Mutex);
}
static inline int condition_signal(DOS64_CONDITION Condition)
{
    return Dos64Threads->Sync.ConditionSignal(Condition);
}
static inline int condition_broadcast(DOS64_CONDITION Condition)
{
    return Dos64Threads->Sync.ConditionBroadcast(Condition);
}
static inline void thread_sleep_ms(unsigned int Milliseconds) { Dos64Threads->Sleep(Milliseconds); }

#endif
