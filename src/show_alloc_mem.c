#include "../malloc.h"

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
                ft_printf("Zone of allocation, %s\n", title);
            }
            ft_printf("%p - %p : %u bytes, %u current_zone_of_allocation\n",
                (void*)current, (void *)current + sizeof(chunk_t) + 1, current->size, current->zone_of_allocation);
        }
        current = current->next;
    }    
}


void show_alloc_mem() 
{
    show_alloc_helper("TINY", TINY, 0);
    show_alloc_helper("SMALL", SMALL, TINY);
    show_alloc_helper("LARGE", MAX_SIZE, SMALL);
}