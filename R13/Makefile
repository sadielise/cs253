FILES = main.cpp Image.tpp Pixel.tpp
CC = g++
CFLAGS = -Wall -std=c++11 -I.

r13: main.o
	$(CC) $(CFLAGS) main.cpp -o r13

main.o: main.cpp Image.tpp Pixel.tpp
	$(CC) $(CFLAGS) -c main.cpp
