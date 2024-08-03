#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "../malloc.h"


void *allocateTiny()
{
    
    return NULL;
}

void *allocateSmall()
{

    return NULL;
}

static void *splitBasedOnSizeAndAllocate(size_t size, size_t alignedMemory, int pageSize)
{
    void *ptr;
    (void)pageSize;
    if (size <= TINY) ptr = allocateTiny();
    else if (size <= SMALL) ptr = allocateSmall();
    else ptr = mmap(0, alignedMemory, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // read/write and memory mapping flags and file descriptor and offset of memory
    if (ptr == MAP_FAILED)
        return NULL;
    return ptr;
}

void *malloc(size_t size)
{
    void *ptr;
    if (size <= 0) return NULL;
    int pageSize = getpagesize(); // getting the page size of the system
    size_t alignedMemory = GET_MEMORY_SIZE(size, ALIGN_SIZE); // aligning the memory to improve the performance due to the cache size
    ptr = splitBasedOnSizeAndAllocate(size, alignedMemory, pageSize);
    printf("Allocated memory of size %p\n", ptr);
    return ptr;
}