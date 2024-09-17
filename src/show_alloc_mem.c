#include "../malloc.h"

static void show_alloc_helper(char *title, size_t maxSize, size_t min_size)
{
    write(1, "Zone of allocation: ", 20);
    write(1, title, 6);
    size_t zone = 0;
    chunk_t *current = gChunks.next;
    while (current != NULL) {
        if (current->free == 0 && current->maxSize <= maxSize && current->size > min_size)
        {
            if (current->zoneOfAllocation != zone)
            {
                zone = current->zoneOfAllocation;
                write(1, "Diffrent Alloc Bloc: ", 21);
                writePointer(current);
                write(1, "\n", 1);
            }
            writeInfo((void*)current, (void *)current + sizeof(chunk_t), current->size, current->zoneOfAllocation);
        }
        current = current->next;
    }    
}

void show_alloc_mem() 
{
    show_alloc_helper("TINYY\n", TINY, 0);
    show_alloc_helper("SMALL\n", SMALL, TINY);
    show_alloc_helper("LARGE\n", MAXXSIZE, SMALL);
}