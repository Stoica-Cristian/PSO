#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

static void* (*real_malloc)(size_t) = NULL;

void* malloc(size_t size)
{
    if (!real_malloc)
    {
        real_malloc = (void* (*)(size_t)) dlsym(RTLD_NEXT, "malloc");
    }

    void* ptr = real_malloc(size);

    if (!ptr)
    {
        fprintf(stderr, "[malloc(size_t)] : %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // fprintf(stderr, "[malloc] - Allocated %zu bytes at %p\n", size, ptr);

    char buffer[100];
    int length = snprintf(buffer, sizeof(buffer), "[malloc(size_t)] : Allocated %zu bytes at %p\n", size, ptr);
    write(1, buffer, length);

    return ptr;
}