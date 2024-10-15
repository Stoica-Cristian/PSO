/**
 * SO
 * Lab #4
 *
 * Task #6, Linux
 *
 * Timers usage
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <signal.h>
#include <sys/time.h>

#include "utils.h"

#define TIMEOUT		2

/*
 * SIGALRM handler - called when the timer expires
 */
static void timer_handler(int signo)
{
	time_t curr_time;
	curr_time = time(NULL);

	/* TODO - print time */
	printf("Timp curent: %s", ctime(&curr_time));
}

/*
 * set signal handlers
 */
static void set_signals(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	/* TODO - set handler for SIGALRM */

	sa.sa_handler = timer_handler;
	sigaction(SIGALRM, &sa, NULL);
}

/*
 * configure timer to generate SIGALRM when fired
 * the timer expires at every TIMEOUT seconds
 */
static void set_timer(void)
{
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;

	memset(&sev, 0, sizeof(sev));
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGALRM;
	sev.sigev_value.sival_ptr = &timerid;

	/* TODO - Create the timer */

	if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1)
	{
		perror("[set_timer(void)] ");
		exit(EXIT_FAILURE);
	}

	/* TODO - Start the timer */

	its.it_value.tv_sec = TIMEOUT;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = TIMEOUT;
	its.it_interval.tv_nsec = 0;

	if (timer_settime(timerid, 0, &its, NULL) == -1)
	{
		perror("[set_timer(void)] ");
		exit(EXIT_FAILURE);
	}
}

/*
 * use sigsuspend for waiting signals
 */
static void wait_for_signal(void)
{
    sigset_t old_mask;

    sigprocmask(SIG_BLOCK, NULL, &old_mask);
    printf("Waiting for SIGALRM...\n");

    sigsuspend(&old_mask);

    printf("Received SIGALRM!\n");
}


int main(void)
{
	set_signals();	/* configure handler for  SIGALRM */
	set_timer();   /* create and start timer */

	while (1)
		wait_for_signal();

	return 0;
}
