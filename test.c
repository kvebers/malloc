#include <stdlib.h>

int main()
{
    void *ptr = malloc(1700);
    free(ptr);
}