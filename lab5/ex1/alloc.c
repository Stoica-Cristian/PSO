#include <stdio.h>
#include <stdlib.h>

#define	MAX		100
#define CHUNK		10
#define SEED		23
#define STOP		17

int main(void)
{
	int nr, count = 0;
	int *buffer;

	buffer = malloc(CHUNK * sizeof(int));

	srand(SEED);
	do {
		nr = 1 + rand()%MAX;
		buffer[count] = nr;
		count++;

		if (count % CHUNK == 0) {
			printf("Resize buffer to fit %d elements\n", count);

			free(buffer);

			buffer =  malloc((count + CHUNK) * sizeof(int));
		}

		printf("buffer[%d]=%d\n", count - 1, buffer[count-1]);
	} while (buffer[count-1] != STOP);

	free(buffer);

	return 0;
}