CC = gcc
CFLAGS = -Wall
TARGET = bin/con
SRC = main.c

build:
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: build
	@./$(TARGET)

clean:
	rm -f *.o *.out
	rm -rf bin
