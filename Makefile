#Makefile
#Author: Lev Bernstein

CC = gcc

CLIBS = -lm -w

conc: Conc.c
	$(CC) $(CFLAGS) -o conc Conc.c -lm -w

run_conc: conc
	./conc

clean:
	rm -f a.out conc output*
