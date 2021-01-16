#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<fcntl.h>
#include<sys/wait.h>

//Author: Lev Bernstein
//Purpose: Find all prime numbers whose digits add up to 13 within a given range.
//Do this with one process and then with a varying number of individual processes. Measure the elasped time for each.
//This should demonstrate the efficiency gained by dividing a problem up and running those divisions concurrently, and the point at which efficiency ceases to increase.
//This program is an expansion of an earlier program I wrote in Computer Systems Organization.
//TO COMPILE AND RUN: do "make run_conc"

/* Checks if an integer is both prime and has digits that all add up to 13.
   Parameters:
    num - the integer to check.
   Return value:
    1 if the integer is a prime whose digits add up to 13; or
    0 otherwise.
 */
int divisible(int num) { //MUST compile with -lm because of math.h! Just use the Makefile to compile.
  int i = 2; //Don't start at 0 for obvious reasons (let's not divide by 0); don't start at 1 because 1 divides everything.
  for (i; i <= (int) sqrt(num) + 1; i++) { //Sieve of Eratosthenes can stop checking after sqrt of max; I add 1 just in case casting to int creates any issues.
    if (num % i == 0) { //If i evenly divides num, num is not prime. While 2 is indeed prime, we can ignore it because its digits do not add up to 10.
      return 0; //This is a composite number. Return 0.
    }
  }
  i = 0; //i now represents the sum of all digits
  while (num > 0) { //While the remainder after doing mod 10 is more than 0:
    i += (num % 10); //Use mod 10 to look at just the last digit
    num /= 10; //Then divide the remainder by 10. Because num is an int, this simply truncates the decimal.
  }
  if (i != 13) { //If that sum is not 13, then num is not a number we want. Return 0.
    return 0;
  }
  return 1; //If we made it here, then num is a number we want. Return 1.
}

int main() {
  int count = 0;
  time_t time1 = time(NULL); //Use time(NULL) to get the seconds since Jan 1st 1970
  int phil = creat("output.txt", 0775); //From The C Programming Language: "0775 specifies read, write, and execute permission for the owner, and read and execute permission for the group and everyone else."
  //By running creat here, I truncate output.txt, just in case there's still something left in it. Alternatively, run "make clean"
  close(phil);
  FILE * phil2;
  char temp[12]; //If you want to increase goal above 999999999 (which you probably should not do; I wouldn't go beyond 30000000), increase the length of temp accordingly, by one per extra digit on goal.
  int goal = 20000000; //The number to check up to. As this number increases, the improvements from using more processes increase as well, though they do level off at a point. On my system, for a goal of 20000000, that point is 9 or 10 processes.
  char nam[15];
  int i;
  int j;
  int k = 2;
  FILE * phil3;
  int trials = 25; //trials is the maximum number of processes the task will be divided into. Do not use more than 99 processes. That's the hard limit, as specified by the size of nam.
  //If for some reason you want to use 100+ processes, increase the size of nam by 1 per digit you're adding.
  int status = 0;
  pid_t waitpid;
  
  //Single process implementation, the baseline:
  printf("Starting the search, please wait...\n");
  for (count; count <= goal; count++) {
    if (divisible(count)) { //If the number fits the conditions:
      phil2 = fopen("output.txt", "a"); //Open the output file in append mode
      sprintf(temp, "%d", count); //Convert the number to a string
      fprintf(phil2, "%s\n", temp); //Write it to the file along with a newline character
      fclose(phil2); //Close the file. This is incredibly inefficient, but it means that we will spend some real time on I/O. To make this more efficient, we could just have the open and close outside the for loop.
      //If you feel like increasing goal up to some ludicrously high number, then you'll want to move as much I/O as possible out of the loops, in order to cut down on that time. Otherwise you'll be waiting a while.
    }
  }
  time1 = time(NULL) - time1; //The elapsed time is equal to the current time minus the start time. Limited to seconds in accuracy.
  printf("Duration for single process: %ld seconds\n", time1);

  //Multi-process implementation:
  for (k; k <= trials; k++) {
    time1 = time(NULL); //Set a new start time.
    phil = creat("output.txt", 0755); //Truncate the file once more for a clean slate.
    for (i = 0; i < k; i++) { //We need k output files, one for each child process. They are named output0.txt through output(k-1).txt.
      //We need to truncate them all. This can be accomplished fairly efficiently through the use of a for loop.
      sprintf(nam, "output%d.txt", i);
      phil = creat(nam, 0755); //Truncate the mini-output files
    }
    //close(phil);
    for (i = 0; i < k; i++) {
      if ((fork()) == 0) { //If the return value of fork() is 0, then this is a child process.
	j = (i * goal)/k; //We need to divide the counting up into k processes that each check 1/k of the numbers to be checked.
	//This could be more efficient; instead of dividing everything up evenly, weighting the number to look through towards the back would be faster, as the later forks will have fewer hits and thus less I/O.
	for (j; j < ((i + 1) * goal)/k; j++) { //This searches through 1/k of the max number we are going up to (goal).
	  if (divisible(j)) {
	    sprintf(nam, "output%d.txt", i); //Same thing here as the truncation for the mini-output files, but this time it just opens them in append mode.
	    //Then open and write to those files in the exact same way as was done for the single-process implementation:
	    phil2 = fopen(nam, "a");
	    sprintf(temp, "%d", j);
	    fprintf(phil2, "%s\n", temp);
	    fclose(phil2);
	    //And close after writing.
	  }
	}
	exit(0); //Have the child process exit.
      }
    }
    while(waitpid=wait(&status)>0); //Wait for all the children to exit.
    phil3 = fopen("output.txt", "w"); //Finally, open the main output once more.
    for (i = 0; i < k; i++) {  
      sprintf(nam, "output%d.txt", i);
      phil2 = fopen(nam, "r"); //Open them in read mode
      while (fgets(temp, 12, phil2) != NULL) { //While there are still unread lines in the mini-output:
	fputs(temp, phil3); //Write those lines to the main output.
      }
      //fclose(phil2); //Close the mini-output. Advance to the next one.
    }
    //fclose(phil3); //Close the main output.
    time1 = time(NULL) - time1; //Time elapsed = current time - start time. Limited to seconds in accuracy.
    printf("Duration for %d processes: %ld seconds \n", k, time1);
  }
  //Close the files at the end.
  close(phil);
  fclose(phil2);
  fclose(phil3);
  return 0;
}
