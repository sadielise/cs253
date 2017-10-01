CC=g++
CFLAGS=-I. -Wall
LINK=

all: | r5

clean:
	-rm -f r5

r5: main.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

valgrind: r5
	valgrind --tool=memcheck ./r5

.PHONY: all clean valgrind
