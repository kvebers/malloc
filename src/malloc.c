#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



void *malloc(size_t size)
{
    printf("malloc %zu\n", size);
    return NULL;
}