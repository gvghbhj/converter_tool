all: converter

clean:
	rm -vf *.o

CFLAGS := -Wall -Wextra -std=gnu11 -pedantic -Werror

converter: converter.o
converter.o: converter.c converter.h
