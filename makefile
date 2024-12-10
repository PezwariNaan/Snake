CC = gcc
LIBS = -lSDL3 -Wl,-rpath,/usr/local/lib
CFLAGS = -g -Wall -Wextra

all: main run

main: main.c
	$(CC) $(LIBS) $(CFLAGS) $^ -o $@

run: main
	./main

clean:
	rm main

PHONY: all clean run
