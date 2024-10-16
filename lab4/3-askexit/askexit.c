/**
 * SO
 * Lab #4
 *
 * Task #3, Linux
 *
 * Signal handling by asking questions
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

#define MY_MAX		32
#define TIMEOUT		1

static void print_next(void)
{
	static int n = 1;

	printf("n = %d\n", n);

	n = (n + 1) % MY_MAX;
}

/* signal handler */
static void ask_handler(int signo)
{
	char buffer[128];

	printf("Got signal %d  - Stop program? [Y/n] ", signo);
	fflush(stdout);

	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;
		if (buffer[0] == 'y' || buffer[0] == 'Y') {
			exit(EXIT_SUCCESS);
		}
	}}

/* configure handlers */
static void set_signals(void)
{
	struct sigaction sa;

	/* TODO - set handler in struct sigaction sa */

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ask_handler;
	sa.sa_flags = SA_RESTART;

	/* TODO - handle SIGINT, SIGQUIT and SIGUSR1 signals */

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
}

int main(void)
{
	set_signals();

	while (1) {
		print_next();
		sleep(TIMEOUT);
	}

	return 0;
}
