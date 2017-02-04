CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

mainprog.o : sim1.c sim1.h
	$(CC) $(CFLAGS) sim1.c

clean:
	\rm *.o sim01

