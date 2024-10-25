/**
 * SO
 * Lab #6, Virtual Memory
 *
 * Task #5, Linux
 *
 * Changing page access protection
 */
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "utils.h"

static int pageSize;
static struct sigaction old_action;
char *p;
int how[3] = {PROT_NONE, PROT_READ, PROT_WRITE};

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	char *addr;
	int page_fault_offset;
	int rc;

	/**
	 * Calling the old signal handler by default for TODO 1
	 * Comment the line below when solving TODO 2
	 */
	// old_action.sa_sigaction(signum, info, context);


	/* TODO 2 - Check if the signal is SIGSEGV */

	if (signum != SIGSEGV) {
		old_action.sa_sigaction(signum, info, context);
		return;
	}

	/**
	 * TODO 2 - Obtain from siginfo_t the memory location
	 * which caused the page fault
	 */

	addr = (char*)info->si_addr;

	/**
	 * TODO 2 - Obtain the page which caused the page fault
	 * Hint: use the address returned by mmap
	 */

	page_fault_offset = (addr - p) / pageSize;

	/* TODO 2 - Increase protection for that page */

	if (how[page_fault_offset] == PROT_NONE)
	{
		rc = mprotect(addr, pageSize, PROT_READ);
		DIE(rc == MAP_FAILED, "mprotect");
	}

		if (how[page_fault_offset] == PROT_READ)
	{
		rc = mprotect(addr, pageSize, PROT_READ | PROT_WRITE);
		DIE(rc == MAP_FAILED, "mprotect");
	}

}

static void set_signal(void)
{
	struct sigaction action;
	int rc;

	action.sa_sigaction = segv_handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, &old_action);
	DIE(rc == -1, "sigaction");
}

static void restore_signal(void)
{
	struct sigaction action;
	int rc;

	action.sa_sigaction = old_action.sa_sigaction;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, NULL);
	DIE(rc == -1, "sigaction");
}

int main(void)
{
	int rc;
	char ch;

	pageSize = getpagesize();

	/**
	 * TODO 1 - Map 3 pages with the desired memory protection
	 * Use global 'p' variable to keep the address returned by mmap
	 * Use mprotect to set memory protections based on global 'how' array
	 * 'how' array keeps protection level for each page
	 */

	p = mmap(NULL, 3 * pageSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	DIE(p == MAP_FAILED, "mmap");

	rc = mprotect(p, pageSize, how[0]);
	DIE(rc == -1, "mprotect page 1");
	rc = mprotect(p + pageSize, pageSize, how[1]);
	DIE(rc == -1, "mprotect page 2");
	rc = mprotect(p + 2 * pageSize, pageSize, how[2]);
	DIE(rc == -1, "mprotect page 3");

	set_signal();

	/* TODO 1 - Access these pages for read and write */

	printf("Accesare pagină 1 (fără drepturi)...\n");
	ch = p[0];

	printf("Accesare pagină 2 (doar citire)...\n");
	ch = p[pageSize];

	printf("Accesare pagină 3 (doar scriere)...\n");
	p[2 * pageSize] = 'X';


	restore_signal();

	/* TODO 1 - Unmap */

	rc = munmap(p, 3 * pageSize);
	DIE(rc == -1, "munmap");

	return 0;
}
