CC=g++
CFLAGS=-I. -Wall
LINK=-lgtest
DEPS=fib.h
OBJS=fib.o main.o

all: | r6

clean:
	-rm -f r6 $(OBJS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LINK)

r6: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean
