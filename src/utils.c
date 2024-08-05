#include "../malloc.h"

chunk_t g_chunks = {
    .size = 0,
    .free = 0,
    .zone_of_allocation = 0,
    .next = NULL,
    .prev = NULL,
};

void appendChunk(chunk_t *chunk)
{
    if (g_chunks.next == NULL) {
        g_chunks.next = chunk;
    } else {
        chunk_t *current = g_chunks.next;
        while (current->next != NULL) current = current->next;
        current->next = chunk;
    }
}

chunk_t *findChunk(void *ptr)
{
    chunk_t *current = g_chunks.next;
    while (current != NULL) {
        if ((void*)((char*)current + sizeof(chunk_t) + 1) == ptr) return current;
        current = current->next;
    }
    return NULL;
}

chunk_t *findFreeChunk(size_t size)
{
    chunk_t *current = g_chunks.next;
    while (current != NULL) {
        if (current->free == 1 && current->size == size) return current;
        current = current->next;
    }
    return NULL;
}


// void removeChunk(chunk_t *chunk)
// {

// }