#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char edata, etext, end;

int main()
{
    printf("%p\n", (char*)sbrk(0) - &end);
    sbrk(1);
    printf("%p\n", (char*)sbrk(0) - &end);

    return 0;
}
