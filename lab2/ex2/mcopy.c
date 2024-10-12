#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 16

int main (int argc, char** argv, char** environ)
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = 0;

    if(argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("\nUsage: %s old-file new-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if(argc != 3)
    {
        fprintf(stderr, "[main(int, char**, char**)] : Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    inputFd = open(argv[1], O_RDONLY);
    
    if (inputFd == -1)
    {
        perror("[main(int, char**, char**)] ");
        return errno;
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
    outputFd = open(argv[2], openFlags, filePerms);

    if (outputFd == -1)
    {
        perror("[main(int, char**, char**)] ");
        return errno;
    }

    while ((bytes_read = read(inputFd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(outputFd, buffer, bytes_read) != bytes_read)
        {
            fprintf(stderr, "[main(int, char**, char**)] : Couldn't write whole buffer\n");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1)
    {
        fprintf(stderr, "[main(int, char**, char**) : Error reading\n");
        exit(EXIT_FAILURE);
    }

    if (close(inputFd) == -1)
    {
        fprintf(stderr, "[main(int, char**, char**) : Error closing input file\n");
        exit(EXIT_FAILURE);
    }

    if (close(outputFd) == -1)
    {
        fprintf(stderr, "[main(int, char**, char**)] : Error closing output file\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
