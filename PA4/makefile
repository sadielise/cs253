FILES = main.cpp Image.cpp ModifyImage.cpp
CC = g++
CFLAGS = -Wall

pa4: ModifyImage.o Image.o main.o
	$(CC) $(CFLAGS) -g -I. $(FILES) -o pa4

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp

ModifyImage.o: ModifyImage.cpp ModifyImage.h
	$(CC) $(CFLAGS) -c ModifyImage.cpp
