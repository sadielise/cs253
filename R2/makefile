OBJS = main.o prog1.o
CC = g++
CFLAGS = -Wall

r2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o r2

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

prog1.o: prog1.cpp prog1.h
	$(CC) $(CFLAGS) prog1.cpp
clean:
	-rm -f executable *.o
tar:
	tar cvf r2.tar main.cpp prog1.cpp prog1.h
