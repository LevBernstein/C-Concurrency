# C-Concurrency

Author: Lev Bernstein

C program demonstrating the benefits--and diminishing returns--of dividing a task into multiple concurrent processes using fork().

In this case, the task is to find all primes whose digits add up to 13 between 1 and 20000000.

There are some major inefficiencies here; every time the program finds a number that meets our criteria, it opens, writes to, and closes the output file.
It would be far more efficient to open and close output only once. However, opening and closing every time causes the program to spend more time on I/O, allowing us to
get a real measurement of speed. Still, fopen, fgets, and their ilk are extremely efficient; they only add a small amount of time to the total the program takes.
As a result, I increased the goal--the number to check up to--to 20000000, far beyond its original 100000. I chose 13 as the number whose digits the primes have to add up to
because, based on trials, there are quite a lot of primes that fit the bill. They are also relatively evenly distributed; other numbers work, but often result in the later
processes in each division doing no actual I/O. Even with just 10 trials, for instance, processes 9 and 10 often have nothing to do when checking against other numbers.
As a result, 13 was an easy choice.

## Sample output

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

  ...(15-24 were all 3 seconds as well)...
* Duration for 25 processes: 3 seconds

## Analysis

As per the [keisan Online Calculator](https://keisan.casio.com/exec/system/14059931777261), the time (y) it takes to accomplish the task using x processes can be modeled using the following equation: y = 11.5x^-.478. The power regression chart based on the data:

![Power Regression Chart](https://github.com/LevBernstein/C-Concurrency/blob/main/chart.png)

|r| = 0.922, indicating strong correlation. The duration for 13 processes, 4 seconds, is a clear outlier that cna be blamed on any number of factors that could cause a general slowdown on my local machine.

The clear diminishing returns indicate that maximum efficiency is achieved around 9 or 10 processes, though this is limited due to accuracy being restricted to whole-second increments. Time is measured based on the Unix epoch: seconds since January 1st 1970. I may change this in the future.