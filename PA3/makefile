FILES = main.cpp Image.cpp
CC = g++
CFLAGS = -Wall

pa3: Image.o main.o
	$(CC) $(CFLAGS) -g -I. $(FILES) -o pa3

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp


