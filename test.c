#include <stdlib.h>
#include "malloc.h"

int main()
{
    for (int i = 0; i < 100; i++)
    {
        void *ptr = malloc(2000);
        ptr = realloc(ptr, 1000);
        free(ptr);
        //free(ptr);
    }
    show_alloc_mem();
}