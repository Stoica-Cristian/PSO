########### First attempt

# CC := gcc
# CFLAGS := -Wall

# demo_static: libmymath.a demo.c
# 	gcc demo.c -o demo_static -L . -lmymath

# libmymath.a: add.o sub.o
# 	ar rcs libmymath.a add.o sub.o

# add.o: add.c
# 	$(CC) $(CFLAGS) -c add.c -o add.o

# sub.o: sub.c
# 	$(CC) $(CFLAGS) -c sub.c -o sub.o


# .PHONY: clean
 
# clean:
# 	rm *.o demo_static 2> /dev/null


########### Better

CC := gcc
CFLAGS := -Wall
TARGET = demo
LIB = mymath
LIBRARY = lib$(LIB).a
OBJS = add.o sub.o
# OBJS = $(wildcard *.o) # Collect all .o files

# Default target
all: $(TARGET)

$(TARGET): $(LIBRARY) $(OBJS)
	$(CC) $(TARGET).c -o $(TARGET) -L . -l$(LIB)

$(LIBRARY): $(OBJS)
	ar rcs $(LIBRARY) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(LIBRARY) $(TARGET)

.PHONY: clean all
