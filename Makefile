# -*- Makefile -*-

CC = gcc
CFLAGS = -lpthread

output: main.o gpio/gpio_lib.o tmp125/tmp125.o 
	${CC} main.o gpio/gpio_lib.o tmp125/tmp125.o -o output ${CFLAGS}

main.o: main.c tmp125/tmp125.h
	${CC} -c main.c ${CFLAGS}

gpio_lib.o: gpio_lib.c
	${CC} -c gpio_lib.c ${CFLAGS}

# ptm.o: ptm/ptm.c
#     ${CC} -c ptm/ptm.c ${CFLAGS}

tmp125.o: tmp125/tmp125.c gpio/gpio_lib.h
	${CC} -c tmp125.c ${CFLAGS}

clean:
	rm -f *.o output
