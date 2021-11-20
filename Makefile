# -*- Makefile -*-

output: main.o ptm/ptm.o
	gcc main.o ptm/ptm.o -o output

main.o: main.c ptm/ptm.h
	gcc -c main.c

ptm.o: ptm.c
	gcc -c ptm/ptm.c

clean:
	rm -f *.o output
