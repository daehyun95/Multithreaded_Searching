-Name Dae Hyun Chung <br/>
-Info about your program: How to run it, expected output. <br/>
How to run it<br/>
<pre>
make - will do the mt_search which gcc -pthread mt_search.c -o mt_search
make run - will run ./mt_search file1.txt 5 10 50 
make run_valgrind - will run with valgrind checking the leak memory
make clean - will clean the mt_search file 
</pre><br/>
Expected output<br/>
The expected output will be like showing all the argument and each threads
searching number and which line were founded.<br/>
<pre>
Number of arguments: 5
Argument 0: ./mt_search	<Executable binary name>
Argument 1: file1.txt	<File name>
Argument 2: 5		<Number to search for>
Argument 3: 5		<Number of threads>
Argument 4: 50		<Num lines>

Spawn threads
Executing thread: 0 thread
Executing thread: 1 thread
Executing thread: 2 thread
Executing thread: 3 thread
Executing thread: 4 thread
Search from 0 to 10
Search from 20 to 30
Search from 30 to 40
Search from 40 to 50
Search from 10 to 20
Threads joined

Show line numbers where the number to search for was found
5 was found in line: 5 15 32 33 34 35 36 
It was found in total 7 location in the file.
</pre><br/>
-A few observations about running your program with varying number of threads.<br/> 
Interesting part was that even though I increase the number of threads, it didn't really affect the time since increasing the number of threads each threads will search smaller amount of number<br/>
-Also searching was not in order, it was kindof mixture order.<br/>
-How many hours did this assignment take you? About 18 hours<br/>
-Did you collaborate with anyone? Name them. Nope but did alot of research in internet<br/>
-Did you use external resources? List them.<br/>
<pre> 
1. https://github.com/angrave/SystemProgramming/wiki
2. https://www.geeksforgeeks.org/multithreading-c-2/
3. https://www.tutorialspoint.com/multithreading-in-c
4. https://northeastern.instructure.com/courses/111031/pages/threading-and-concurrency-readings
</pre>
