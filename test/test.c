#include "../malloc.h"
#include <stdio.h>

int main()
{
    {
    void *ptr = malloc(10);
    (void)ptr;
    }
    {
        printf("test\n");
    }
}
