#ifndef MALLOC_H
# define MALLOC_H


# include "libft/libft.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

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
    size_t max_size;
    size_t zone_of_allocation;
    int free; // 1 if free, 0 if not
} chunk_t;

// struct to stroe the data related all chunks of memory

extern chunk_t g_chunks;
// utils.c
void appendChunk(chunk_t *chunk);
void createLinkedList(void *ptr, size_t size);
chunk_t *findFreeChunk(size_t size);
chunk_t *findChunk(void *ptr);
int getAllocationZone();
void removeLargeChunk(chunk_t *chunk);
void freeNotLargeChunks(size_t chunk_index, chunk_t *chunk);
void removeNotLargeChunk(chunk_t *chunk);


// defines
# define TINY (256 - sizeof(chunk_t))
# define SMALL (2048 - sizeof(chunk_t))
# define LARGE (SMALL + 1)
# define ALLOC_COUNT 16 * 8
# define MAX_SIZE 4000000000
#define TINY_SIZE (ALLOC_COUNT * (TINY + sizeof(chunk_t)))
#define SMALL_SIZE (ALLOC_COUNT * (SMALL + sizeof(chunk_t)))
#define GET_MEMORY_SIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment) - 1)) // Operation (and) and operation (not)

#endif