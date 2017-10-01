FILES = main.cpp Image.cpp
CC = g++
CFLAGS = -Wall -O2

pa8: Image.o main.o
	$(CC) $(CFLAGS) -I. $(FILES) -o pa8

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp

clean:
	-rm -f pa8 *.o
