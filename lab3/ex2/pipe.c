#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <errno.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

#define BUFSIZE 	100
#define EXIT_STR	"exit"
#define PIPE_READ	0
#define PIPE_WRITE	1

static bool check_for_exit(const char *input)
{
	if (strcmp(input, EXIT_STR) == 0) {
		return true;
	}

	return false;
}

static void child_loop(int readfd)
{
	char output[BUFSIZE];
	int rc;

	while (1) {
		rc = read(readfd, output, BUFSIZE);
		DIE(rc < 0, "read() failed");
		if (rc == 0) {
			/* TODO - Close pipe head used for reading */
			close(readfd);
			break;
		}
		
		printf("[Child received]: %s\n", output);
		fflush(stdout);
	}

	return;
}

static void parent_loop(int writefd)
{
	char input[BUFSIZE];
	int rc;
	
	while (1) {
		memset(input, 0, BUFSIZE);
		scanf("%s",  input);

		if (check_for_exit(input)) {
			/* TODO - Close pipe head used for writing */
			close(writefd);
			break;
		}

		rc = write(writefd, input, BUFSIZE);
		DIE(rc < 0, "write() failed");
	}

	return;
}

int main(void)
{
	pid_t pid;
	int rc;
	int fds[2];

	/* TODO - Create anonymous pipe */
	int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("[main(void)] ");
        exit(EXIT_FAILURE);
    }

	pid = fork();
	switch (pid) {
	case -1:
		/* Fork failed, cleaning up... */
		/* TODO - Close both heads of the pipe */
		close(pipe_fd[PIPE_READ]);
		close(pipe_fd[PIPE_WRITE]);

		DIE(pid, "fork() failed");
		return EXIT_FAILURE;
	case 0:
		/* Child process */
		/* TODO - Close unused pipe head by child */
		close(pipe_fd[PIPE_WRITE]);
		/* TODO - Call child loop and pass pipe head used for reading */
		child_loop(pipe_fd[PIPE_READ]);
		break;
	default:
		/* Parent process */
		/* TODO - Close unused pipe head by parent */
		close(pipe_fd[PIPE_READ]);
		/* TODO - Call parent loop and pass pipe head used for writing */
		parent_loop(pipe_fd[PIPE_WRITE]);
		/* Wait for child process to finish */
		wait(NULL);

		break;
	}

	return 0;
}
