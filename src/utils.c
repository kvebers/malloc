#include "../malloc.h"
#include <stdio.h>

int getAllocationZone()
{
    static int zone = 0;
    return zone++;
}

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
        chunk->prev = current;
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

void createLinkedList(void *ptr, size_t size) {
    int zone = getAllocationZone();
    chunk_t *current = &g_chunks;
    while (current->next != NULL) current = current->next;
    for (size_t i = 0; i < ALLOC_COUNT; i += 1)
    {
        chunk_t *chunk = (chunk_t*)((char*)ptr + (size + sizeof(chunk_t)) * i);
        chunk->size = size;
        chunk->max_size = size;
        chunk->free = 1;
        chunk->zone_of_allocation = zone;
        chunk->next = NULL;
        chunk->prev = current;
        if (current != &g_chunks) current->next = chunk;
        else g_chunks.next = chunk;
        current = chunk;
    }
}

void removeChunk(chunk_t *chunk)
{
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
    munmap(chunk, chunk->max_size + sizeof(chunk_t));
}

// void removeChunk(chunk_t *chunk)
// {

// }