#ifndef MALLOC_H
# define MALLOC_H


# include "libft/libft.h"

// malloc.c
void *malloc(size_t size);
// free.c
void free(void *ptr);
// realloc.c
void *realloc(void *ptr, size_t size);
// show_alloc_mem.c
void show_alloc_mem(void);

extern zone_t zones;

// struct to store the data related to single chunk of memory
typedef struct chunk {
    size_t size;
    struct chunk *next;
    int free;
} chunk_t;

// struct to stroe the data related all chunks of memory
typedef struct zone {
    chunk_t *tiny_chunks;
    chunk_t *small_chunks;
    chunk_t *large_chunks;
} zone_t;

// utils.c
void appendSmallChunk(chunk_t *smallChunk);
void appendTinyChunk(chunk_t *tinyChunk);
void appendLargeChunk(chunk_t *largeChunk);
void removeSmallChunk(chunk_t *smallChunk);
void removeTinyChunk(chunk_t *tinyChunk);
void removeLargeChunk(chunk_t *largeChunk);

// defines
# define TINY 256
# define SMALL 4096
# define LARGE (SMALL + 1)
# define ALLOC_COUNT 100
#define TINY_SIZE (100 * (TINY + sizeof(chunk_t)))
#define SMALL_SIZE (100 * (SMALL + sizeof(chunk_t)))
#define GET_MEMORY_SIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment) - 1)) // Operation (and) and operation (not)

#endif