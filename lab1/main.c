#include <stdio.h>
#include "lib/mymath.h"

#define NAME "student"
#define NR (10)

void my_asm_func(int);

int main()
{
    int i;

    putchar('\n');
    my_asm_func(NR);
    printf("\n");
    putchar('\n');

    // print the NAME NR times
    for (i = 0; i < NR; i++)
        printf("Hello, %s\n", NAME);

    putchar('\n');

    for (i = 0; i < NR; i++)
    {
        int res = add(i, 1);
        my_asm_func(res);
        putchar('\n');
    }

    return 0;
}