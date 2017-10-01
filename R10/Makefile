#objects = main.o foo.o
#objects := $(wildcard *.o)
#$(warning Default goal is $(objects))

CXXFLAGS=-Wall -std=c++11

r10: main.cpp 
	g++ $(CXXFLAGS) main.cpp -o r10

clean:
	-rm -f r10 *.o
	clear


