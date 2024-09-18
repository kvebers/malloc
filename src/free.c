#include "../malloc.h"
#include <stdio.h>

// extern void *gPtr;
// extern size_t gSize;

static void debug(void *ptr, size_t freeSize)
{
    write(1, "\n", 1);
    write(1, "\n", 1);
    write(1, "Munmap: ", 8);
    writePointer(ptr);
    write(1, " - ", 3);
    writePointer(ptr + freeSize);
    write(1, " | Size: ", 9);
    writeInt(freeSize);
    write(1, " bytes\n", 7);
}

void removeNotLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
}

static void *findZoneAllocationFirst(size_t zone)
{
    chunk_t *current = gChunks.next;
    while (current != NULL)
    {
        if (current->zoneOfAllocation == zone) return (void*)current;
        current = current->next;
    }
    return NULL;
}

void freeNotLargeChunks(size_t chunkIndex, chunk_t *chunk) {
    size_t countFreeChunks = 0;
    chunk_t *current = gChunks.next;
    while (current != NULL)
    {
        if (current->zoneOfAllocation == chunkIndex && current->free == 1) countFreeChunks++;
        current = current->next;
    }
    size_t freeSize = 0;
    if (chunk->maxSize == TINY) freeSize = TINYSIZE;
    else if (chunk->maxSize == SMALL) freeSize = SMALLSIZE;
    void *ptr = findZoneAllocationFirst(chunkIndex);
    if (countFreeChunks == ALLOC_COUNT) {
        current = gChunks.next;
        while (current != NULL)
        {
            chunk_t *next = current->next;
            if (current->zoneOfAllocation == chunkIndex) removeNotLargeChunk(current);
            current = next;
        }
    }
    if (DEBUG) debug(ptr, freeSize);
    if (ptr == NULL) return;
    munmap(ptr, freeSize);
}

void removeLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
    if (gChunks.next == chunk) gChunks.next = chunk->next;
    if (gChunks.prev == chunk) gChunks.prev = chunk->prev;
    if (DEBUG) debug(chunk, chunk->size);
    munmap((void*)chunk, chunk->size);
}

void free(void *ptr)
{
    if (ptr == NULL) return;
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return;
    chunk->free = 1;
    chunk->size = chunk->maxSize;
    if (chunk->maxSize == TINY || chunk->maxSize == SMALL) freeNotLargeChunks(chunk->zoneOfAllocation, chunk);
    else removeLargeChunk(chunk);
}
