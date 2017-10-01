#objects = main.o foo.o
#objects := $(wildcard *.o)
#$(warning Default goal is $(objects))

CXXFLAGS=-Wall -std=c++11

mt2: main.cpp 
	g++ $(CXXFLAGS) main.cpp -o mt2

clean:
	-rm -f mt2 *.o
	clear


