#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

static void* (*real_free)(void *) = NULL;

void free(void* ptr)
{
    if (!real_free)
    {
        real_free = dlsym(RTLD_NEXT, "free");

        if (real_free == NULL) {
            fprintf(stderr, "[free(void*)] : %s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }

    real_free(ptr);

    char buffer[100];
    int length = snprintf(buffer, sizeof(buffer), "[free(void*)] : Deallocated memory at %p\n", ptr);
    write(1, buffer, length);
}