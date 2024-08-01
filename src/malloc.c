#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



void *malloc(size_t size)
{
    (void)size;
    return NULL;
}