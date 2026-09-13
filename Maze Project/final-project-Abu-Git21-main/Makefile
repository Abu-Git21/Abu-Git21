CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
TARGET = lily_maze
SOURCES = main.c maze.c stack.c queue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o
