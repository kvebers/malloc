#include "../malloc.h"
#include <stdio.h>

int main()
{
    {
    void *ptr = malloc(4097);
    printf("ptr: %p\n", ptr);
    ptr = malloc(4098);
    printf("ptr: %p\n", ptr);
    show_alloc_mem();
    }
    {
        printf("test\n");
    }
}
