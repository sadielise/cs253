FILES = main.cpp Image.cpp ModifyImage.cpp Morpher.cpp Mapping.cpp KeyPoint.cpp
CC = g++
CFLAGS = -Wall
LINK=-lgtest

pa5: ModifyImage.o Image.o Morpher.o Mapping.o KeyPoint.o main.o
	$(CC) $(CFLAGS) -g -I. $(FILES) -o pa5 $(LINK)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp

ModifyImage.o: ModifyImage.cpp ModifyImage.h
	$(CC) $(CFLAGS) -c ModifyImage.cpp

Morpher.o: Morpher.cpp Morpher.h
	$(CC) $(CFLAGS) -c Morpher.cpp

Mapping.o: Mapping.cpp Mapping.h
	$(CC) $(CFLAGS) -c Mapping.cpp

KeyPoint.o: KeyPoint.cpp KeyPoint.h
	$(CC) $(CFLAGS) -c KeyPoint.cpp

clean:
	-rm -f pa5 *.o
