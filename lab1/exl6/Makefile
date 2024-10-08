CC=gcc
CFLAGS=-fPIC
LDFLAGS=-shared -fPIC
LDLIBS=-ldl

TARGET=libwrapper.so
SRC=wrapper_malloc.c wrapper_free.c
OBJ=$(SRC:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ) *.o main

test: $(TARGET) main
	rm -f *.o
	LD_PRELOAD=./$(TARGET) ./main

main: main.o
	gcc main.o -o main
