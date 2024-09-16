#include "../malloc.h"

static void *allocateMemory(size_t size)
{
    void *ptr;
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // read/write and memory mapping flags and file descriptor and offset of memory
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
        return (void*)((char*)ptr + sizeof(chunk_t) + 1);
    }
    if (ptr == NULL) ptr = allocateMemory(TINY_SIZE);
    if (ptr == NULL) return NULL;
    createLinkedList(ptr, TINY);
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->free = 0;
    return (void*)((char*)ptr + sizeof(chunk_t) + 1);
}

static void *allocateSmall(size_t size)
{
    void *ptr = findFreeChunk(SMALL);
    if (ptr != NULL)
    {
        chunk_t *chunk = (chunk_t*)(ptr);
        chunk->free = 0;
        chunk->size = size;
        return (void*)((char*)ptr + sizeof(chunk_t) + 1);
    }
    if (ptr == NULL) ptr = allocateMemory(SMALL_SIZE);
    if (ptr == NULL) return NULL;
    createLinkedList(ptr, SMALL);
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->max_size = SMALL;
    chunk->free = 0;
    return (void*)((char*)ptr + sizeof(chunk_t) + 1);
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
    chunk->max_size = size;
    chunk->prev = g_chunks.next;
    appendChunk(chunk);
    return (void*)((char*)ptr + sizeof(chunk_t) + 1);
}

void *malloc(size_t size)
{
    void *ptr;
    write(1, "malloc\n", 7);
    if (size >= MAX_SIZE) return NULL;
    if (size <= 0) return NULL;
    size_t totalSize = size + sizeof(chunk_t);
    if (totalSize <= TINY) ptr = allocateTiny(size);
    else if (totalSize <= SMALL) ptr = allocateSmall(size);
    else ptr = allocateLarge(size);
    return ptr;
}