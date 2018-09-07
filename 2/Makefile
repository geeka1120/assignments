CC = gcc
TARGET = hello
OBJECTS = hello.o
CFLAGS = -Wall -ansi -pedantic -Qunused-arguments

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

