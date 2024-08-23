#include "../malloc.h"

void removeNotLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
}

void freeNotLargeChunks(size_t chunk_index, chunk_t *chunk) {
    size_t countFreeChunks = 0;
    chunk_t *current = g_chunks.next;

    while (current != NULL) {
        if (current->zone_of_allocation == chunk_index && current->free == 1) {
            countFreeChunks++;
        }
        current = current->next;
    }

    if (countFreeChunks == ALLOC_COUNT) {
        current = g_chunks.next;
        while (current != NULL) {
            chunk_t *next = current->next;
            if (current->zone_of_allocation == chunk_index) {
                removeNotLargeChunk(current);
            }
            current = next;
        }
        munmap(chunk, (chunk->size + sizeof(chunk_t)) * ALLOC_COUNT);
    }
}
void removeLargeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
    if (g_chunks.next == chunk) g_chunks.next = chunk->next;
    if (g_chunks.prev == chunk) g_chunks.prev = chunk->prev;
    munmap(chunk, chunk->max_size + sizeof(chunk_t));
    
}

void free(void *ptr) {
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return;
    chunk->free = 1;
    chunk->size = chunk->max_size;
    if (chunk->max_size == TINY || chunk->max_size == SMALL) freeNotLargeChunks(chunk->zone_of_allocation, chunk);
    else removeLargeChunk(chunk);
}
