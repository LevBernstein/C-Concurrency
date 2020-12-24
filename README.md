# C-Concurrency

C program demonstrating the benefits--and diminishing returns--of dividing a task into multiple concurrent processes using fork().

In this case, the task is to find all primes whose digits add up to 13 between 1 and 10000000.

There are some major inefficiencies here; every time the program finds a number that meets our criteria, it opens, writes to, and closes the output file.
It would be far more efficient to open and close output only once. However, opening and closing every time causes the program to spend more time on I/O, allowing us to
get a real measurement of speed.

Sample output:
Duration for single process: 16 seconds

Duration for 2 processes: 10 seconds

Duration for 3 processes: 7 seconds 

Duration for 4 processes: 6 seconds 

Duration for 5 processes: 4 seconds 

Duration for 6 processes: 4 seconds 

Duration for 7 processes: 4 seconds 

Duration for 8 processes: 4 seconds 

Duration for 9 processes: 3 seconds 

Duration for 10 processes: 3 seconds 

Duration for 11 processes: 3 seconds 

Duration for 12 processes: 3 seconds 

Duration for 13 processes: 4 seconds 

Duration for 14 processes: 3 seconds 

Duration for 15 processes: 3 seconds 

Duration for 16 processes: 3 seconds 

Duration for 17 processes: 3 seconds 

Duration for 18 processes: 3 seconds 

Duration for 19 processes: 3 seconds 

Duration for 20 processes: 3 seconds 

Duration for 21 processes: 3 seconds 

Duration for 22 processes: 3 seconds 

Duration for 23 processes: 3 seconds 

Duration for 24 processes: 3 seconds 

Duration for 25 processes: 3 seconds