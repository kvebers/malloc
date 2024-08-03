# malloc

Allowed function:

mmap(2)
◦ munmap(2)
◦ getpagesize(2 or 3 depending on OS)
◦ getrlimit(2)

and libft

## mmap

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

Flags

PROT_NONE Pages may not be accessed.
PROT_READ Pages may be read.
PROT_WRITE Pages may be written.
PROT_EXEC Pages may be executed.
MAP_ANONYMOUS Synonym for MAP_ANON.
MAP_ANON Map anonymous memory not associated with any specific file. The offset argument is ignored. Mac OS X specific: the file descriptor used for creating MAP_ANON regions can be used to pass some Mach VM flags,
and can be specified as -1 if no such flags are associated with the region.  
MAP_FILE Mapped from a regular file. (This is the default mapping type, and need not be specified.)

MAP_FIXED Do not permit the system to select a different address than the one specified. If the specified address cannot be used, mmap() will fail. If MAP_FIXED is specified, addr must be a multiple of the pagesize.
If a MAP_FIXED request is successful, the mapping established by mmap() replaces any previous mappings for the process' pages in the range from addr to addr + len. Use of this option is discouraged.

MAP_HASSEMAPHORE Notify the kernel that the region may contain semaphores and that special handling may be necessary.

MAP_PRIVATE Modifications are private (copy-on-write).

MAP_SHARED Modifications are shared.

MAP_NOCACHE Pages in this mapping arqe not retained in the kernel's memory cache. If the system runs low on memory, pages in MAP_NOCACHE mappings will be among the first to be reclaimed. This flag is intended for map-
pings that have little locality and provides a hint to the kernel that pages in t

RETURN VALUES
Upon successful completion, mmap() returns a pointer to the mapped region. Otherwise, a value of MAP_FAILED is returned and errno is set to indicate the error.

## munmap

munmap(void \*addr, size_t len);

The munmap() system call deletes the mappings for the specified address range, causing further references to addresses within the range to generate invalid memory references.

## getpagesize

int getpagesize(void);

DESCRIPTION
The getpagesize() function returns the number of bytes in a page. Page granularity is the granularity of many of the memory management calls.

     The page size is a system page size and may not be the same as the underlying hardware page size.

## getrlimit

NAME
getrlimit, setrlimit -- control maximum system resource consumption

SYNOPSIS
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit \*rlp);
