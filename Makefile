all: mt_search

mt_search: mt_search.c
			gcc -pthread mt_search.c -o mt_search 
run: mt_search.c
	./mt_search file1.txt 5 5 50
run_valgrind: mt_search.c
	valgrind ./mt_search file1.txt 5 5 50

clean:
		rm mt_search
