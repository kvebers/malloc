#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "../malloc.h"


static int getAllocationZone()
{
    static int zone = 0;
    return zone++;
}

static void *allocateMemory(size_t size)
{
    void *ptr;
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // read/write and memory mapping flags and file descriptor and offset of memory
    if (ptr == MAP_FAILED)
        return NULL;
    return ptr;
}

static void createLinkedList(void *ptr, size_t size)
{
    int zone = getAllocationZone();
    for (size_t i = 0; i < size; i += TINY + sizeof(chunk_t)) {
    }
}

static void *allocateTiny(size_t size)
{
    void *ptr = findFreeChunk(TINY);
    if (ptr != NULL) {
        chunk_t *chunk = (chunk_t*)((char*)ptr + sizeof(chunk_t) + 1);
        chunk->free = 0;
        chunk->size = size;
        return ptr;
    }
    if (ptr == NULL) ptr = allocateMemory(TINY_SIZE);
    if (ptr == NULL) return NULL;
    createLinkedList(ptr, TINY);
    return NULL;
}

static void *allocateSmall(size_t size)
{
    return NULL;
}

static void *allocateLarge(size_t size)
{
    void *ptr;
    size_t alignedMemory = GET_MEMORY_SIZE(size + sizeof(chunk_t), TINY);
    ptr = allocateMemory(alignedMemory);
    if (ptr == NULL) return NULL;
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->free = 0;
    chunk->zone_of_allocation = getAllocationZone();
    chunk->next = NULL;
    chunk->prev = g_chunks.next;
    appendChunk(chunk);
    return (void*)((char*)ptr + sizeof(chunk_t) + 1);
}

void *malloc(size_t size)
{
    void *ptr;

    if (size <= 0) return NULL;
    size_t totalSize = size + sizeof(chunk_t);
    if (totalSize <= TINY) ptr = allocateTiny();
    else if (totalSize <= SMALL) ptr = allocateSmall();
    else ptr = allocateLarge(size);
    return ptr;
}