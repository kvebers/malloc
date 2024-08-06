#include "../malloc.h"

void free(void *ptr) {
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return;
    chunk->free = 1;
    chunk->size = chunk->max_size;
    if (chunk->max_size == TINY || chunk->max_size == SMALL)
    {
        printf("freeing chunk\n");
    }
    else
    {
        removeChunk(chunk);
    }
}