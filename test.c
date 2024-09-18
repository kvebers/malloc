#include <stdlib.h>
#include "malloc.h"
int main()
{
    void *ptr = malloc(10);
    free(ptr);
    show_alloc_mem();
    return 0;    
}