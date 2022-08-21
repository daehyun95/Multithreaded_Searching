The program will: <br/>
* create <<number of threads>> threads that will wait. 
* read the file <filename>, which contains <num lines>  of integers.
        a. Those integers are between 0 and 999. 
        b. There is one integer per row
        c. There are <num lines> rows in the file
* tell each thread which to search a disjoint portion of the input for the value <number to search for>. 
        a. Every time a thread finds an instance of the number, it should store the line number where that number was found, in an array shared by all the threads. 
        b. Be sure to use a synchronization primitive to protect this array so the value is correct. 
* When all threads are finished and joined, the main thread should print out the line numbers where the <number to search for> was found. 
<br/>
<br/>

The program has the following requirements:<br/>
* The main thread should spawn the worker threads prior to reading the file
* The worker threads should not read the input file. Pass a pointer to the array where the data will be when the threads are spawned, then signal the threads when the data has been read into that array. 
* Each thread should update an array storing line numbers where <number to search for> was found
* The main thread should join on all of the worker threads prior to printing out the line numbers where the <number to search for> was found
<br/>
<br/>
The program will be run like this: <br/>
./mt_search <filename> <number to search for> <number of threads> <num lines>
