#include "../malloc.h"

void removeNotLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
}

void freeNotLargeChunks(size_t chunk_index, chunk_t *chunk) {
    size_t countFreeChunks = 0;
    chunk_t *current = gChunks.next;
    while (current != NULL) {
        if (current->zoneOfAllocation == chunk_index && current->free == 1) countFreeChunks++;
        current = current->next;
    }
    if (countFreeChunks == ALLOC_COUNT) {
        current = gChunks.next;
        while (current != NULL) {
            chunk_t *next = current->next;
            if (current->zoneOfAllocation == chunk_index) removeNotLargeChunk(current);
            current = next;
        }
        munmap(chunk, (chunk->maxSize) * ALLOC_COUNT);
    }
}
void removeLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
    if (gChunks.next == chunk) gChunks.next = chunk->next;
    if (gChunks.prev == chunk) gChunks.prev = chunk->prev;
    munmap(chunk, chunk->maxSize + sizeof(chunk_t));
    
}

void free(void *ptr) {
    if (ptr == NULL) return;
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return;
    chunk->free = 1;
    chunk->size = chunk->maxSize;
    if (chunk->maxSize == TINY || chunk->maxSize == SMALL) freeNotLargeChunks(chunk->zoneOfAllocation, chunk);
    else removeLargeChunk(chunk);
}
