#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> /* flock */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> /* errno */

#define LOCK_FILE "/tmp/my_lock_file"

// #define first_method

static int fdlock = -1;

static void do_stuff(void)
{
	sleep(10);
}

static void check_lock(void)
{
	/* TODO - Open LOCK_FILE file */
	/* fdlock = open(...) */

	mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
	
#ifdef first_method
	fdlock = open(LOCK_FILE, O_RDWR | O_CREAT, filePerms);

	if (fdlock == -1)
	{
        perror("[check_lock(void)] : static void - ");
        exit(EXIT_FAILURE);
    }

	/**
	 * TODO - Lock the file using flock
	 * - flock must not block in any case !
	 *
	 * - in case of error - print a message showing
	 *   there is another instance running and exit
	 */

	if (flock(fdlock, LOCK_EX | LOCK_NB) == -1)
	{
		if ( errno == EWOULDBLOCK)
		{
			perror("[check_lock(void)] : static void - ");
			exit(EXIT_FAILURE);
		}
	}
#else
	if ((fdlock = open(LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, filePerms)) == -1)
	{
		if (errno == EEXIST)
		{
			perror("[check_lock(void)] ");
	        exit(EXIT_FAILURE);
		}
	}
#endif
	char pid[10];
	snprintf(pid, sizeof(pid), "%d\n", getpid());

	if (write(fdlock, pid, sizeof(pid)) == -1)
	{
		perror("[check_lock(void)] ");
		exit(EXIT_FAILURE);
	}

	printf("[check_lock(void)] : Got Lock\n");
}

static void clean_up(void)
{
	int rc;
	/* TODO - Unlock file, close file and delete it */

	flock(fdlock, LOCK_UN);

	if (close(fdlock) == -1)
	{
        fprintf(stderr, "[check_lock(void)] : Error closing file\n");
        exit(EXIT_FAILURE);
	}

	if (unlink(LOCK_FILE) == -1)
	{
		perror("[clean_up(void)] ");
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	check_lock();
	do_stuff();
	clean_up();
	return 0;
}
