CC := gcc
CFLAGS := -fPIC
TARGET = demo
LIB = mymath
LIBRARY = lib$(LIB).so
OBJS = add.o sub.o

# Default target
all: $(TARGET)

$(TARGET): $(LIBRARY) $(OBJS)
	$(CC) $(TARGET).c -o $(TARGET) -l$(LIB) -L .

$(LIBRARY): $(OBJS)
	$(CC) -shared $(OBJS) -o $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(LIBRARY) $(TARGET)

clean_obj:
	rm -f *.o

.PHONY: clean clean_obj all
