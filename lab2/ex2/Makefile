CC=gcc
CFLAGS=-Wall

mcopy: mcopy.o
	$(CC) $(CFLAGS) $< -o $@

mcat: mcat.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o mcat mcopy