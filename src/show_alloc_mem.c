#include "../malloc.h"

static void write_info(void *mainPtr, void *valuePtr, size_t size, int zone_of_allocation)
{
    
    write(1, " bytes\n", 7);
}

static void show_alloc_helper(char *title, size_t max_size, size_t min_size)
{
    int is_changed = 0;
    chunk_t *current = g_chunks.next;
    while (current != NULL) {
        if (current->free == 0 && current->max_size <= max_size && current->size > min_size)
        {
            if (is_changed == 0)
            {
                is_changed = 1;
                write(1, "Zone of allocation: ", 20);
                write(1, title, 6);
            }
            write_info((void*)current, (void *)current + sizeof(chunk_t) + 1, current->size, current->zone_of_allocation);
        }
        current = current->next;
    }    
}


void show_alloc_mem() 
{
    show_alloc_helper("TINYY\n", TINY, 0);
    show_alloc_helper("SMALL\n", SMALL, TINY);
    show_alloc_helper("LARGE\n", MAX_SIZE, SMALL);
}