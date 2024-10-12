#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 16

int main (int argc, char** argv, char** environ)
{
    if(argc < 2)
    {
        fprintf(stderr, "[main(int, char**, char**)] : Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    
    if (fd == -1)
    {
        perror("[main(int, char**, char**)] ");
        return errno;
    }

    char* buffer = (char*)malloc(BUFFER_SIZE);
    ssize_t bytes_read = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
        {
            fprintf(stderr, "[main(int, char**, char**)] : Couldn't write whole buffer\n");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1)
    {
        fprintf(stderr, "[main(int, char**, char**)] : Error reading\n");
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1)
    {
        fprintf(stderr, "[main(int, char**, char**)] : Error closing input file\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
