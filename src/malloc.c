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

static void *createLinkedListOfChunks(chunk_t *chunk, size_t size)
{
    static size_t zone_of_application = 0;
    chunk_t *current = chunk;
    chunk_t *head = chunk;
    chunk_t *prev = g_chunks.next;
    zone_of_application++;
    for (size_t i = 0; i < ALLOC_COUNT; i++)
    {
        current->prev = prev;
        prev = current;
        current->size = size;
        current->free = 1;
        current->zone_of_allocation = zone_of_application;
        if (i < ALLOC_COUNT - 1) current->next = current + 1;
        else current->next = NULL;
        current++;
    }
    return head;
}

static void *allocateTiny(size_t size)
{
    void *ptr;
    (void) size;
    (void) ptr;
    return NULL;
}

static void *allocateSmall(size_t size)
{
    (void)size;
    return NULL;
}

void appendZone(chunk_t *chunk, size_t size)
{
    chunk_t *current = g_chunks.next;
    while (current->next != NULL) current = current->next;
    current->next = chunk;
    if (g_chunks.next == NULL) g_chunks.next = chunk;
}

static void *allocateLarge(size_t size)
{
    void *ptr;
    int pageSize = getpagesize(); 
    (void) pageSize;
    size_t alignedMemory = GET_MEMORY_SIZE(size + sizeof(chunk_t), TINY);
    ptr = allocateMemory(alignedMemory);
    if (ptr == NULL) return NULL;
    chunk_t *chunk = (chunk_t *)ptr;
    chunk->size = size;
    chunk->free = 0;
    chunk->zone_of_allocation = 0;
    chunk->next = NULL;
    chunk->prev = g_chunks.next;
    appendZone(chunk, size);
    return ptr + sizeof(chunk_t) + 1;
}

void *malloc(size_t size)
{
    void *ptr;

    if (size <= 0) return NULL;
    size_t totalSize = size + sizeof(chunk_t);
    if (totalSize <= TINY) ptr = allocateTiny(size);
    else if (totalSize <= SMALL) ptr = allocateSmall(size);
    else ptr = allocateLarge(size);
    return ptr;
}