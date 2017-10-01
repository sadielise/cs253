# Makefile for R9
# Author: Fereydoon
# Date: March 29, 2015

CFLAGS = -Wall -I. -g -c
EXE = r9

all: r9

r9: main.o threeDshape.o threeDpoint.o threeDcircle.o sphere.o
	g++ main.o threeDshape.o threeDpoint.o threeDcircle.o sphere.o -o $(EXE) -lgtest

main.o: main.cpp
	g++ $(CFLAGS) main.cpp

threeDshape.o: threeDshape.cpp threeDshape.h
	g++ $(CFLAGS) threeDshape.cpp

threeDpoint.o: threeDpoint.cpp threeDpoint.h
	g++ $(CFLAGS) threeDpoint.cpp

threeDcircle.o: threeDcircle.cpp threeDcircle.h
	g++ $(CFLAGS) threeDcircle.cpp

sphere.o: sphere.cpp sphere.h
	g++ $(CFLAGS) sphere.cpp

clean:
	rm -f *.o $(EXE) *~
	clear

