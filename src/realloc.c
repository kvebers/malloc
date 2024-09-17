#include "../malloc.h"

void *realloc(void *ptr, size_t size)
{

    if (ptr == NULL) return malloc(size);
    if (size == 0) { free(ptr); return NULL;}
    chunk_t *chunk = findChunk(ptr);
    if (chunk == NULL) return NULL;
    if (chunk->maxSize >= size) return ptr;
    size_t totalSize = size + sizeof(chunk_t);
     (void)totalSize;
     void *ptr2 = NULL;
    return ptr2;
}