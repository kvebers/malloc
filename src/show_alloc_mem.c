#include "../malloc.h"

static void writeInt(int n) {
    char buf[20];
    int len = 0;
    if (n == 0) { write(1, "0", 1); return; }
    if (n < 0) { write(1, "-", 1); n = -n; }
    while (n > 0) { buf[len++] = '0' + (n % 10); n /= 10; }
    while (len--) write(1, &buf[len], 1);
}

static void writePointer(void *ptr) {
    intptr_t p = (intptr_t)ptr;
    char hex_digits[] = "0123456789abcdef";
    char buf[18] = "0x0000000000000000";
    int i;
    for (i = 17; p > 0 && i > 1; i--) { buf[i] = hex_digits[p % 16]; p /= 16;}
    write(1, buf, 18);
}

static void writeInfo(void *main_ptr, void *value_ptr, size_t size, int zoneOfAllocation)
{
    write(1, "Ptr: ", 5);
    writePointer(main_ptr);
    write(1, " - ", 3);
    writePointer(value_ptr);
    write(1, " | Allocation size: ", 20);
    writeInt(size);
    write(1, " bytes ", 7);
    write(1, " Zone of Allocation: ", 21);
    writeInt(zoneOfAllocation);
    write(1, "\n", 1);
}

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
            writeInfo((void*)current, (void *)current + sizeof(chunk_t) + 1, current->size, current->zoneOfAllocation);
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