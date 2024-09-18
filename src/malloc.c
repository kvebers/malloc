#include "../malloc.h"
#include <stdio.h>

// void *gPtr = NULL;
// size_t gSize = 0;

static void debug(void *ptr, size_t size)
{
    write(1, "\n", 1);
    write(1, "\n", 1);
    write(1, "Malloc: ", 6);
    writePointer(ptr);
    write(1, " - ", 3);
    writePointer(ptr + size);
    write(1, " | Size: ", 9);
    writeInt(size);
    write(1, " bytes\n", 7);
}


static void *allocateMemory(size_t size)
{
    void *ptr;
    //0 for the system to choose adress, but you can specify an adress
    //size
    //read and write acsess will be readable, will be writable
    //memory mapping flags mapping is private, changes to the mapped memory will be private and set to 0
    //file descriptor, when -1 no filedescriptor is used if used 2 for example it will use the fd but it will lagg the program
    //offset of memory this should be 4096 * some_value
    ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    // example that shows page reclaims method has faults
    // gSize = size;
    // gPtr = ptr;
    if (DEBUG) debug(ptr, size);
    if (ptr == MAP_FAILED) return NULL;
    return ptr;
}

static void *allocateTiny(size_t size)
{
    void *ptr = findFreeChunk(TINY);
    if (ptr != NULL)
    {
        chunk_t *chunk = (chunk_t*)(ptr);
        chunk->free = 0;
        chunk->size = size;
        return (void*)((char*)ptr + sizeof(chunk_t));
    }
    if (ptr == NULL) ptr = allocateMemory(TINYSIZE);
    if (ptr == NULL) return NULL;
    createLinkedList(ptr, TINY);
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->free = 0;
    return (void*)((char*)ptr + sizeof(chunk_t));
}

static void *allocateSmall(size_t size)
{
    void *ptr = findFreeChunk(SMALL);
    if (ptr != NULL)
    {
        chunk_t *chunk = (chunk_t*)(ptr);
        chunk->free = 0;
        chunk->size = size;
        return (void*)((char*)ptr + sizeof(chunk_t));
    }
    if (ptr == NULL) ptr = allocateMemory(SMALLSIZE);
    if (ptr == NULL) return NULL;
    createLinkedList(ptr, SMALL);
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->maxSize = SMALL;
    chunk->free = 0;
    return (void*)((char*)ptr + sizeof(chunk_t));
}

static void *allocateLarge(size_t size)
{
    void *ptr;
    size_t pageSize = getpagesize();
    size_t alignedMemory = GETMEMORYSIZE(size + sizeof(chunk_t), pageSize);
    ptr = allocateMemory(alignedMemory);
    if (ptr == NULL) return NULL;
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = alignedMemory;
    chunk->free = 0;
    chunk->zoneOfAllocation = getAllocationZone();
    chunk->next = NULL;
    chunk->maxSize = alignedMemory;
    chunk->prev = gChunks.next;
    appendChunk(chunk);
    return (void*)((char*)ptr + sizeof(chunk_t));
}

void *malloc(size_t size)
{
    void *ptr;
    if (size <= 0) return NULL;
    if (size >= MAXXSIZE) return NULL;
    size_t totalSize = size + sizeof(chunk_t);
    if (totalSize <= TINY) ptr = allocateTiny(size);
    else if (totalSize <= SMALL) ptr = allocateSmall(size);
    else ptr = allocateLarge(size);
    return ptr;
}