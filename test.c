#include <stdlib.h>
#include "malloc.h"

int main()
{
    for (int i = 0; i < 100; i++)
    {
        void *ptr = malloc(2000);
        char *str = (char *)ptr;
        ptr = realloc(ptr, 1000);
        free(ptr);
    }
    show_alloc_mem();
}