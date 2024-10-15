/**
 * SO
 * Lab #4
 *
 * Task #5, Linux
 *
 * Creating zombies
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define TIMEOUT		20

int main(void)
{
	pid_t pid;

	/* TODO - create child process without waiting */
	pid = fork();

	switch(pid)
	{
		case -1:
			perror("main(void) ");
			exit(EXIT_FAILURE);
		case 0:
			printf("Procesul copil: PID=%d\n", getpid());
			exit(EXIT_SUCCESS);
		default:
			printf("Procesul parinte: PID=%d, copilul creat: PID=%d\n", getpid(), pid);

		/* TODO - sleep */
			sleep(TIMEOUT);

			printf("Procesul parinte termina executia\n");
			exit(EXIT_SUCCESS);
	}

	return 0;
}
