#include "../malloc.h"

int main()
{
    for (int i = 0; i < 200; i++)
    {
        void *ptr = malloc(100);
        void *ptr2 = realloc(ptr, 300);
        free(ptr2);
    }
    show_alloc_mem();
    return 0;
}
