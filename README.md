# C-Concurrency

C program demonstrating the benefits--and diminishing returns--of dividing a task into multiple concurrent processes using fork().

In this case, the task is to find all primes whose digits add up to 10 between 1 and 10000000.

There are some major inefficiencies here; every time the program finds a number that meets our criteria, it opens, writes to, and closes the output file.
It would be far more efficient to open and close output only once. However, opening and closing every time causes the program to spend more time on I/O, allowing us to
get a real measurement of speed.