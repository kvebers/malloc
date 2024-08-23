#include "../malloc.h"
#include <stdio.h>

int main()
{
    // {
    //     // this is the test case for large memory allocation
    //     void *ptr = malloc(4097);
    //     printf("ptr: %p\n", ptr);
    //     free(ptr);
    //     ptr = malloc(4098);
    //     void *new_ptr = malloc(4099);
    //     printf("ptr: %p\n", ptr);
    //     printf("new_ptr: %p\n", new_ptr);
    //     free(ptr);
    //     free(new_ptr);
    //     ptr = malloc(4098);
    //     printf("ptr: %p\n", ptr);
    //     free(ptr);
    //     printf("=====================================\n");
    // }
    // {
    //     // this is the test case for large memory allocation
    //     void *ptr = malloc(4097);
    //     free(ptr);
    //     ptr = malloc(4098);
    //     void *new_ptr = malloc(4099);
    //     free(ptr);
    //     ptr = malloc(4098);
    //     show_alloc_mem();
    //     free(new_ptr);
    //     free(ptr);
    //     printf("=====================================\n");
    // }
    // {
    //     void *ptr = malloc(180);
    //     printf("ptr: %p\n", ptr);
    //     void *ptr1 = malloc(190);
    //     printf("ptr: %p\n", ptr1);
    //     show_alloc_mem();
    //     free(ptr);
    //     free(ptr1);
    //     printf("=====================================\n");
    // }
    //
    {
        void *ptr = malloc(10);
        void *ptr1 = malloc(11);
        void *ptr2 = malloc(12);
        show_alloc_mem();
        free(ptr);
        free(ptr1);
        free(ptr2);
        printf("=====================================\n");
    }
    // {
    //     printf("=====================================\n");
    //     void *ptr = malloc(270);
    //     printf("ptr: %p\n", ptr);
    //     ptr = malloc(280);
    //     printf("ptr: %p\n", ptr);
    //     ptr = malloc(290);
    //     printf("ptr: %p\n", ptr);
    // }
    // {
    //     int		i;
	//     char	*test;

	//     i = 0;
	//     while (i < 1024)
	//     {
	// 	    i++;
	//     }
    // }
    // {
    //     int		i;
	//     char	*test;

	//     i = 0;
	//     while (i < 1024)
	//     {
	// 	    test = (char*)malloc(5000);
	// 	    test[0] = 42;
	// 	    i++;
    //         free(test);
	//     }
    // }
    // {
    //     int		i;
    //     char	*test;

    //     i = 0;
    //     while (i < 1024)
    //     {
    //         test = (char*)malloc(5000);
    //         test[0] = 42;
    //         i++;
    //         free(test);
    //     }
    // }
    // {
    //     printf("=====================================\n");
    //     show_alloc_mem();
    // }
}
