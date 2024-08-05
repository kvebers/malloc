#include "../malloc.h"
#include <stdio.h>

void show_alloc_mem() {
    chunk_t *current = g_chunks.next;
    while (current != NULL) {
        if (current->free == 0)
            printf("%p - %p : %lu bytes, %lu current_zone_of_allocation\n",
            (void*)current, (void *)current + sizeof(chunk_t) + 1,
            current->size, current->zone_of_allocation);
        current = current->next;
    }    
}