# -*- Makefile -*-

CC = gcc
CFLAGS = -lpthread

output: main.o ptm/ptm.o
	${CC} main.o ptm/ptm.o -o output ${CFLAGS}

main.o: main.c ptm/ptm.h
	${CC} -c main.c ${CFLAGS}

ptm.o: ptm/ptm.c
	${CC} -c ptm/ptm.c ${CFLAGS}

clean:
	rm -f *.o output
