#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "../malloc.h"

static void *allocateMemory(size_t size)
{
    void *ptr;
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // read/write and memory mapping flags and file descriptor and offset of memory
    if (ptr == MAP_FAILED)
        return NULL;
    return ptr;
}

static void *allocateTiny(size_t size)
{
    void *ptr;
    int pageSize = getpagesize();
    size_t alignedMemory = GET_MEMORY_SIZE(size + sizeof(chunk_t), TINY);
    if (ptr == NULL) return NULL;
    return ptr;
}

static void *allocateSmall(size_t size)
{
    void *ptr;
    int pageSize = getpagesize();
    size_t alignedMemory = GET_MEMORY_SIZE(size + sizeof(chunk_t), TINY);
    ptr = allocateMemory(alignedMemory);
    if (ptr == NULL) return NULL;
    return NULL;
}

static void *allocateLarge(size_t size)
{
    void *ptr;
    int pageSize = getpagesize(); 
    size_t alignedMemory = GET_MEMORY_SIZE(size + sizeof(chunk_t), TINY);
    ptr = allocateMemory(alignedMemory);
    if (ptr == NULL) return NULL;
    return ptr;
}

void *malloc(size_t size)
{
    void *ptr;
    size_t totalSize;

    if (size <= 0) return NULL;
    totalSize = size + sizeof(chunk_t);
    if (totalSize <= TINY) ptr = allocateTiny(size);
    else if (totalSize <= SMALL) ptr = allocateSmall(size);
    else ptr = allocateLarge(size);
    return ptr;
}