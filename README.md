# C-Concurrency

Lev Bernstein

C program demonstrating the benefits--and diminishing returns--of dividing a task into multiple concurrent processes using fork().

In this case, the task is to find all primes whose digits add up to 13 between 1 and 10000000.

There are some major inefficiencies here; every time the program finds a number that meets our criteria, it opens, writes to, and closes the output file.
It would be far more efficient to open and close output only once. However, opening and closing every time causes the program to spend more time on I/O, allowing us to
get a real measurement of speed.

## Sample output:

* Duration for single process: 16 seconds
* Duration for 2 processes: 10 seconds
* Duration for 3 processes: 7 seconds 
* Duration for 4 processes: 6 seconds 
* Duration for 5 processes: 4 seconds 
* Duration for 6 processes: 4 seconds 
* Duration for 7 processes: 4 seconds 
* Duration for 8 processes: 4 seconds 
* Duration for 9 processes: 3 seconds 
* Duration for 10 processes: 3 seconds 
* Duration for 11 processes: 3 seconds 
* Duration for 12 processes: 3 seconds 
* Duration for 13 processes: 4 seconds 
* Duration for 14 processes: 3 seconds 

... (15-24 were all 3 seconds as well)
* Duration for 25 processes: 3 seconds

## Analysis

As per the [keisan Online Calculator](https://keisan.casio.com/exec/system/14059931777261), the time (y) it takes to accomplish the task using x processes can be modeled using the following equation: y = 11.5x^-.478. The power regression chart based on the data:

![Power Regression Chart](https://github.com/LevBernstein/C-Concurrency/blob/main/chart.png)

|r| = 0.922, indicating strong correlation.

The clear diminishing returns indicate that maximum efficiency is achieved around 9 or 10 processes, though this is limited due to accuracy being restricted to whole-second increments.