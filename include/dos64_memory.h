#ifndef DOS64_MEMORY_API_H
#define DOS64_MEMORY_API_H

#include "dos64_api.h"
#include <stddef.h>

/* Each translation unit using these helpers must call memory_init. */
static const DOS64_HEAP *dos64_memory_heap;

static inline int memory_init(const DOS64_API *Api)
{
    dos64_memory_heap = NULL;
    if (!Api || Api->Version < 16 ||
        Api->Size < offsetof(DOS64_API, Heap) + sizeof(Api->Heap) ||
        !Api->Heap.Allocate || !Api->Heap.AllocateZeroed ||
        !Api->Heap.Reallocate || !Api->Heap.Free) return -1;
    dos64_memory_heap = &Api->Heap;
    return 0;
}

static inline void *memory_alloc(size_t Size)
{
    return dos64_memory_heap ? dos64_memory_heap->Allocate(Size) : NULL;
}

static inline void *memory_calloc(size_t Count, size_t Size)
{
    return dos64_memory_heap ? dos64_memory_heap->AllocateZeroed(Count, Size) : NULL;
}

static inline void *memory_realloc(void *Pointer, size_t Size)
{
    return dos64_memory_heap ? dos64_memory_heap->Reallocate(Pointer, Size) : NULL;
}

static inline int memory_free(void *Pointer)
{
    return dos64_memory_heap ? dos64_memory_heap->Free(Pointer) : -1;
}

#endif
