#ifndef DOS64_QUEUE_H
#define DOS64_QUEUE_H

#include "dos64_thread.h"

#define QUEUE_OK 0
#define QUEUE_CLOSED 1
#define QUEUE_WOULD_BLOCK 2
#define QUEUE_ERROR (-1)

typedef struct DOS64_QUEUE {
    const DOS64_API *Api;
    unsigned char *Storage;
    unsigned int Capacity, ItemBytes, Head, Count, Users;
    int Closed;
    DOS64_MUTEX Mutex;
    DOS64_CONDITION Readable, Writable;
} DOS64_QUEUE;

static inline int queue_error(DOS64_QUEUE *Queue, const char *Message)
{
    Queue->Api->Write(Message);
    return QUEUE_ERROR;
}

/* Zero-initialize Queue; storage is caller-owned and must outlive all operations. */
static inline int queue_init(DOS64_QUEUE *Queue, const DOS64_API *Api, void *Storage,
                              unsigned int Capacity, unsigned int ItemBytes)
{
    if (thread_sync_init(Api) != 0) {
        if (Api && Api->Write) { Api->Write("QUEUE FAILED: synchronization unavailable\n"); }
        return QUEUE_ERROR;
    }
    if (!Queue || !Storage || !Capacity || !ItemBytes ||
        (unsigned long long)Capacity * ItemBytes > (~0ULL >> 1)) {
        Api->Write("QUEUE FAILED: invalid queue storage or dimensions\n");
        return QUEUE_ERROR;
    }
    if (Queue->Mutex || Queue->Readable || Queue->Writable) {
        Api->Write("QUEUE FAILED: queue already initialized\n");
        return QUEUE_ERROR;
    }
    Queue->Api = Api;
    Queue->Storage = Storage;
    Queue->Capacity = Capacity;
    Queue->ItemBytes = ItemBytes;
    Queue->Head = Queue->Count = Queue->Users = 0;
    Queue->Closed = 0;
    Queue->Mutex = Api->Sync.MutexCreate();
    if (Queue->Mutex) { Queue->Readable = Api->Sync.ConditionCreate(); }
    if (Queue->Readable) { Queue->Writable = Api->Sync.ConditionCreate(); }
    if (!Queue->Writable) {
        if (Queue->Readable && Api->Sync.ConditionDestroy(Queue->Readable) == 0) { Queue->Readable = 0; }
        if (Queue->Mutex && Api->Sync.MutexDestroy(Queue->Mutex) == 0) { Queue->Mutex = 0; }
        return queue_error(Queue, "QUEUE FAILED: synchronization allocation\n");
    }
    return QUEUE_OK;
}

static inline int queue_transfer(DOS64_QUEUE *Queue, void *Item, int Send, int Block)
{
    if (!Queue || !Queue->Api) { return QUEUE_ERROR; }
    if (!Queue->Mutex || !Queue->Readable || !Queue->Writable || !Item) {
        return queue_error(Queue, "QUEUE FAILED: invalid operation\n");
    }
    const DOS64_SYNC *Sync = &Queue->Api->Sync;
    if (Sync->MutexLock(Queue->Mutex) != 0) { return QUEUE_ERROR; }
    Queue->Users++;
    int Result = QUEUE_OK;
    while (!Queue->Closed && (Send ? Queue->Count == Queue->Capacity : Queue->Count == 0)) {
        if (!Block) { Result = QUEUE_WOULD_BLOCK; break; }
        if (Sync->ConditionWait(Send ? Queue->Writable : Queue->Readable, Queue->Mutex) != 0) {
            Queue->Users--;
            /* Condition failure may leave no ownership; unlock reports this explicitly. */
            (void)Sync->MutexUnlock(Queue->Mutex);
            return QUEUE_ERROR;
        }
    }
    if (Result == QUEUE_OK) {
        if ((Send && Queue->Closed) || (!Send && Queue->Count == 0)) { Result = QUEUE_CLOSED; }
        else {
            unsigned int Index = Send ? (unsigned int)(((unsigned long long)Queue->Head +
                                                       Queue->Count) % Queue->Capacity) : Queue->Head;
            unsigned char *Slot = Queue->Storage + (unsigned long long)Index * Queue->ItemBytes;
            unsigned char *Bytes = Item;
            for (unsigned int Byte = 0; Byte < Queue->ItemBytes; Byte++) {
                if (Send) { Slot[Byte] = Bytes[Byte]; }
                else { Bytes[Byte] = Slot[Byte]; }
            }
            if (Send) { Queue->Count++; }
            else { Queue->Head = (Queue->Head + 1) % Queue->Capacity; Queue->Count--; }
            if (Sync->ConditionSignal(Send ? Queue->Readable : Queue->Writable) != 0) {
                Result = QUEUE_ERROR;
            }
        }
    }
    Queue->Users--;
    if (Sync->MutexUnlock(Queue->Mutex) != 0) { Result = QUEUE_ERROR; }
    return Result;
}

static inline int queue_send(DOS64_QUEUE *Queue, const void *Item)
{
    return queue_transfer(Queue, (void *)Item, 1, 1);
}
static inline int queue_receive(DOS64_QUEUE *Queue, void *Item)
{
    return queue_transfer(Queue, Item, 0, 1);
}
static inline int queue_try_send(DOS64_QUEUE *Queue, const void *Item)
{
    return queue_transfer(Queue, (void *)Item, 1, 0);
}
static inline int queue_try_receive(DOS64_QUEUE *Queue, void *Item)
{
    return queue_transfer(Queue, Item, 0, 0);
}

/* Close rejects new sends, wakes blocked peers, and permits draining queued items. */
static inline int queue_close(DOS64_QUEUE *Queue)
{
    if (!Queue || !Queue->Api) { return QUEUE_ERROR; }
    const DOS64_SYNC *Sync = &Queue->Api->Sync;
    if (!Queue->Mutex) { return queue_error(Queue, "QUEUE FAILED: uninitialized close\n"); }
    if (Sync->MutexLock(Queue->Mutex) != 0) { return QUEUE_ERROR; }
    Queue->Closed = 1;
    int Result = Sync->ConditionBroadcast(Queue->Readable);
    if (Sync->ConditionBroadcast(Queue->Writable) != 0) { Result = QUEUE_ERROR; }
    if (Sync->MutexUnlock(Queue->Mutex) != 0) { Result = QUEUE_ERROR; }
    return Result;
}

/* Close and join all users first; no new operation may race destruction. */
static inline int queue_destroy(DOS64_QUEUE *Queue)
{
    if (!Queue || !Queue->Api) { return QUEUE_ERROR; }
    const DOS64_SYNC *Sync = &Queue->Api->Sync;
    if (Queue->Mutex) {
        if (Sync->MutexLock(Queue->Mutex) != 0) { return QUEUE_ERROR; }
        int Busy = Queue->Users != 0;
        if (Sync->MutexUnlock(Queue->Mutex) != 0) { return QUEUE_ERROR; }
        if (Busy) { return queue_error(Queue, "QUEUE FAILED: destroying queue with active users\n"); }
    }
    if (Queue->Readable) {
        if (Sync->ConditionDestroy(Queue->Readable) != 0) { return QUEUE_ERROR; }
        Queue->Readable = 0;
    }
    if (Queue->Writable) {
        if (Sync->ConditionDestroy(Queue->Writable) != 0) { return QUEUE_ERROR; }
        Queue->Writable = 0;
    }
    if (Queue->Mutex) {
        if (Sync->MutexDestroy(Queue->Mutex) != 0) { return QUEUE_ERROR; }
        Queue->Mutex = 0;
    }
    return QUEUE_OK;
}

#endif
