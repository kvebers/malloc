#ifndef MALLOC_H
# define MALLOC_H


# include "libft/libft.h"

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);


#define GET_MEMORY_SIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment) - 1)) // Operation (and) and operation (not)

typedef struct chunk {
    size_t size;
    struct chunk *next;
    int free;
} chunk_t;


# define ALIGN_SIZE 128
# define TINY 256
# define SMALL 4096
# define LARGE (SMALL + 1)
# define ALLOC_COUNT 100

#endif