CC = g++
FLAGS = -Wall -g -I.

mt1: main.o BinaryNode.o
	$(CC) $(FLAGS) main.o BinaryNode.o -o mt1

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

BinaryNode.o: BinaryNode.cpp BinaryNode.h
	$(CC) $(FLAGS) -c BinaryNode.cpp

clean:
	-rm -f mt1 *.o


