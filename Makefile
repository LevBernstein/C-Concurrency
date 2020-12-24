#Makefile
#Author: Lev Bernstein

CC = gcc

CLIBS = -lm -w

conc: Conc.c
	rm -f nums.txt
	$(CC) $(CFLAGS) -o conc Conc.c -lm -w

clean:
	rm -f a.out conc nums.txt output*

run_conc: conc
	./conc
	cp output.txt nums.txt
	rm -f output*
