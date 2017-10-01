FILES = main.cpp Image.cpp
CC = g++
CFLAGS = -Wall -lgtest

r7: Image.o main.o
	$(CC) $(CFLAGS) -g -I. $(FILES) -o r7

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp


