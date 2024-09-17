#include "../malloc.h"
#include <stdio.h>

int getAllocationZone()
{
    static int zone = 0;
    return zone++;
}

chunk_t gChunks = {
    .size = 0,
    .free = 0,
    .zoneOfAllocation = 0,
    .next = NULL,
    .prev = NULL,
};

void appendChunk(chunk_t *chunk)
{
    if (gChunks.next == NULL) {
        gChunks.next = chunk;
    } else {
        chunk_t *current = gChunks.next;
        while (current->next != NULL) current = current->next;
        current->next = chunk;
        chunk->prev = current;
    }
}

chunk_t *findChunk(void *ptr)
{
    chunk_t *current = gChunks.next;
    while (current != NULL) {
        if ((void*)((char*)current + sizeof(chunk_t) + 1) == ptr) return current;
        current = current->next;
    }
    return NULL;
}

chunk_t *findFreeChunk(size_t size)
{
    chunk_t *current = gChunks.next;
    while (current != NULL) {
        if (current->free == 1 && current->size == size) return current;
        current = current->next;
    }
    return NULL;
}

void createLinkedList(void *ptr, size_t size) {
    int zone = getAllocationZone();
    chunk_t *current = &gChunks;
    while (current->next != NULL) current = current->next;
    for (size_t i = 0; i < ALLOC_COUNT; i += 1)
    {
        chunk_t *chunk = (chunk_t*)((char*)ptr + (size + sizeof(chunk_t)) * i);
        chunk->size = size;
        chunk->maxSize = size;
        chunk->free = 1;
        chunk->zoneOfAllocation = zone;
        chunk->next = NULL;
        chunk->prev = current;
        if (current != &gChunks) current->next = chunk;
        else gChunks.next = chunk;
        current = chunk;
    }
}
