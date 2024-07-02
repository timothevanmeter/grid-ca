CC 	= gcc
CS 	= gcc -c
CFLAGS 	= -Wall -pedantic
RM 	= rm

default: all

all: gnuplot_i grid run

gnuplot_i: gnuplot_i.c
	$(CS) gnuplot_i.c -o gnuplot_i.o

grid: grid-ca.c
	$(CC) $(CFLAGS) grid-ca.c -o grid.o gnuplot_i.o

run:
	./grid.o

clean:
	$(RM) *.o
	$(RM) *.dat
	$(RM) *.png

