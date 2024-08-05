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


// struct to store the data related to single chunk of memory
typedef struct chunk {
    struct chunk *next;
    struct chunk *prev;
    size_t size;
    size_t zone_of_allocation;
    int free; // 1 if free, 0 if not
} chunk_t;

// struct to stroe the data related all chunks of memory

extern chunk_t g_chunks;
// utils.c
void appendChunk(chunk_t *chunk);
void removeChunk(chunk_t *chunk);

// defines
# define TINY 256
# define SMALL 4096
# define LARGE (SMALL + 1)
# define ALLOC_COUNT 100
#define TINY_SIZE (100 * (TINY + sizeof(chunk_t)))
#define SMALL_SIZE (100 * (SMALL + sizeof(chunk_t)))
#define GET_MEMORY_SIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment) - 1)) // Operation (and) and operation (not)

#endif