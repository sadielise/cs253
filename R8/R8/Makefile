#objects = main.o foo.o
#objects := $(wildcard *.o)
#$(warning Default goal is $(objects))

CXXFLAGS=-Wall -std=c++11
LINK=-lgtest
matrix: main.o matrix.o
	g++ $(CXXFLAGS) main.o matrix.o -o matrix $(LINK)

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

matrix.o: matrix.h matrix.cpp
	g++ $(CXXFLAGS) -c matrix.cpp

clean:
	-rm -f matrix *.o
	clear


