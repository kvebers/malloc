#include "../malloc.h"

static void *updateChunk(chunk_t *chunk, size_t size)
{
    chunk->size = size;
    return (void*)((char*)chunk + sizeof(chunk_t) + 1);
}

void *realloc(void *ptr, size_t size)
{

    if (ptr == NULL) return malloc(size);
    if (size == 0) { free(ptr); return NULL;}
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return NULL;
    size_t totalSize = size + sizeof(chunk_t);
    if (chunk->maxSize == TINY && totalSize <= TINY) return updateChunk(chunk, size);
    if (chunk->maxSize == SMALL && totalSize <= SMALL) return updateChunk(chunk, size);
    if (chunk->maxSize > SMALL && totalSize <= chunk->maxSize) return updateChunk(chunk, size);
    void *newPtr = malloc(size);
    if (newPtr == NULL) return NULL;
    for (size_t i = 0; i < chunk->size; i++) ((char*)newPtr)[i] = ((char*)ptr)[i];
    free(ptr);
    return (void*)((char*)newPtr + sizeof(chunk_t) + 1);;
}