CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

sim01 : mainprog.o
	$(CC) $(LFLAGS) mainprog.o -o sim01

mainprog.o : main.c myMethods.h myQueue.h
	$(CC) $(CFLAGS) main.c

clean:
	\rm *.o sim01

