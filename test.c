#include <stdlib.h>

int main()
{
    for (int i = 0; i < 2; i++)
    {
        void *ptr = malloc(1000);
        free(ptr);
    }
}