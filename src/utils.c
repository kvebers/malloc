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
    int count = 0;
    while (current != NULL) {
        if ((void*)((char*)current + sizeof(chunk_t)) == ptr) return current;
        current = current->next;
        count++;
    }
    writeInt(count);
    write(1, "\n", 1);
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

void writeInt(int n) {
    char buf[20];
    int len = 0;
    if (n == 0) { write(1, "0", 1); return; }
    if (n < 0) { write(1, "-", 1); n = -n; }
    while (n > 0) { buf[len++] = '0' + (n % 10); n /= 10; }
    while (len--) write(1, &buf[len], 1);
}

void writePointer(void *ptr) {
    intptr_t p = (intptr_t)ptr;
    char hexDigits[] = "0123456789abcdef";
    char buf[18] = "0x0000000000000000";
    int i;
    for (i = 17; p > 0 && i > 1; i--) { buf[i] = hexDigits[p % 16]; p /= 16;}
    write(1, buf, 18);
}

void writeInfo(void *main_ptr, void *value_ptr, size_t size, int zoneOfAllocation)
{
    write(1, "Ptr: ", 5);
    writePointer(main_ptr);
    write(1, " - ", 3);
    writePointer(value_ptr);
    write(1, " | Allocation size: ", 20);
    writeInt(size);
    write(1, " bytes ", 7);
    write(1, " Zone of Allocation: ", 21);
    writeInt(zoneOfAllocation);
    write(1, "\n", 1);
}