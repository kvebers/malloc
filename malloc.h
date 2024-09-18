#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

// malloc.c
void *malloc(size_t size);
// free.c
void free(void *ptr);
// realloc.c
void *realloc(void *ptr, size_t size);
// show_alloc_mem.c
void show_alloc_mem(void);


// struct to store the data related to single chunk of memory
typedef struct chunk {
    struct chunk *next;
    struct chunk *prev;
    size_t size;
    size_t maxSize;
    size_t zoneOfAllocation;
    int free; // 1 if free, 0 if not
} chunk_t;

// struct to stroe the data related all chunks of memory

extern chunk_t gChunks;
// utils.c
void appendChunk(chunk_t *chunk);
void createLinkedList(void *ptr, size_t size);
chunk_t *findFreeChunk(size_t size);
chunk_t *findChunk(void *ptr);
int getAllocationZone();
void removeLargeChunk(chunk_t *chunk);
void freeNotLargeChunks(size_t chunkIndex, chunk_t *chunk);
void removeNotLargeChunk(chunk_t *chunk);
void writeInfo(void *main_ptr, void *value_ptr, size_t size, int zoneOfAllocation);
void writePointer(void *ptr);
void writeInt(int n);

// defines
# define TINY (256 - sizeof(chunk_t))
# define SMALL (2048 - sizeof(chunk_t))
# define LARGE (SMALL + 1)
# define ALLOC_COUNT 16 * 8
# define MAXXSIZE 200000000
#define TINYSIZE (ALLOC_COUNT * (TINY + sizeof(chunk_t)))
#define SMALLSIZE (ALLOC_COUNT * (SMALL + sizeof(chunk_t)))
#define GETMEMORYSIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment) - 1)) // Operation (and) and operation (not)
#define DEBUG 1

#endif