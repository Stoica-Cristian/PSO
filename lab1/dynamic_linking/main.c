#define _XOPEN_SOURCE 700
#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
 
 
int main() {
    void *handle;
    int (*a)(int, int);
    int (*b)(int, int);
    char *error;
 
    handle = dlopen("libmymath.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    a = (int (*)(int, int)) dlsym(handle, "add");
    b = (int (*)(int, int)) dlsym(handle, "sub");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    printf("%d %d\n", a(1,2), b(1,2));
    dlclose(handle);
    return EXIT_SUCCESS;
}