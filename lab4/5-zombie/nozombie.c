/**
 * SO
 * Lab #4
 *
 * Task #5, Linux
 *
 * Avoid creating zombies using signals
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define TIMEOUT		20

/*
 * configure signal handler
 */
static void set_signals(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	/* TODO - ignore SIGCHLD */
	sa.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &sa, NULL);
}

int main(void)
{
	pid_t pid;

	set_signals();

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

            sleep(TIMEOUT);

            printf("Procesul părinte termina executia.\n");
            exit(EXIT_SUCCESS);
    }

	return 0;
}
