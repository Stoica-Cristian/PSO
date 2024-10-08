#include <stdlib.h>

int main(int argc, char** argv) {
    char* ptr = (char*)malloc(100);
    free(ptr);

    return 0;
}
