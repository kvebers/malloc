#include "../malloc.h"
#include <stdio.h>

int main()
{
    {
        void *ptr = malloc(4097);
        printf("ptr: %p\n", ptr);
        ptr = malloc(4098);
        printf("ptr: %p\n", ptr);
    }
    {
        printf("=====================================\n");
        void *ptr = malloc(10);
        printf("ptr: %p\n", ptr);
        ptr = malloc(11);
        printf("ptr: %p\n", ptr);
        ptr = malloc(12);
        printf("ptr: %p\n", ptr);
    }
    {
        printf("=====================================\n");
        void *ptr = malloc(270);
        printf("ptr: %p\n", ptr);
        ptr = malloc(280);
        printf("ptr: %p\n", ptr);
        ptr = malloc(290);
        printf("ptr: %p\n", ptr);
    }
    {
        int		i;
	    char	*test;

	    i = 0;
	    while (i < 1024)
	    {
		    i++;
	    }
    }
    {
        int		i;
	    char	*test;

	    i = 0;
	    while (i < 1024)
	    {
		    test = (char*)malloc(1000);
		    test[0] = 42;
		    i++;
	    }
    }
    {
        int		i;
        char	*test;

        i = 0;
        while (i < 1024)
        {
            test = (char*)malloc(1000);
            test[0] = 42;
            i++;
            //free
        }
    }
    {
        printf("=====================================\n");
        show_alloc_mem();
    }
}
