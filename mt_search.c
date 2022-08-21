#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include <string.h>
#define MALLOC_BYTE 256
#define MAX 255
#define MAX_THREADS 100

sem_t sem;
pthread_mutex_t mutex;
pthread_t* thread_Ids;
char* file_name;
int* array_numbers;
int* line;
int number_threads;
int number_search;
int num_lines;

// Prints the argument
void PrintArguments(int argc, char *args[]) {
    int i;
    printf("Number of arguments: %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("Argument %d: %s\t", i, args[i]);
        if (i == 0) {
            printf("<Executable binary name>\n");
        } else if (i == 1) {
            printf("<File name>\n");
        } else if (i == 2) {
            printf("\t<Number to search for>\n");
        } else if (i == 3) {
            printf("\t<Number of threads>\n");
        } else {
            printf("\t<Num lines>\n");
        }
    }
    printf("\n");
}

// Reading the file and get the array
// which convert the numbers to the array in the file
void ReadFile(char* file_name) {
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error opening file\n");
        return;
    }
    int i;
    char* num_from_line = (char*)malloc(sizeof(*num_from_line));
    for (i = 0; i < num_lines; i++) {
        fgets(num_from_line, MAX, fp);
        array_numbers[i] = atoi(num_from_line);
    }
    free(num_from_line);
    fclose(fp);
}

// Each threads search the speicifc number
// If the number was found than changed the number to -1 in the array
// in right index
void* SearchNumber(void* args) {
    ReadFile(file_name);
    char* message = malloc(MALLOC_BYTE);
    if (message == NULL) {
        printf("ERROR: could not malloc\n");
    }
    sleep(1);
    sem_wait(&sem);
    int each_threads = *(int*)args;
    pthread_mutex_lock(&mutex);
    int each_search_amount = num_lines / number_threads;
    int search_from = each_threads * each_search_amount;
    int search_to = (each_threads + 1) * each_search_amount;
    printf("Search from %d to %d\n", search_from, search_to);
    int i;
    for (i = search_from; i < search_to; i++) {
        if (array_numbers[i] == number_search) {
            array_numbers[i] = -1;
        }
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&sem);
    free(message);
    return NULL;
}

// Create threads, run threads and join threads
void CreateAndJoinThreads(pthread_t* thread_Ids) {
    printf("Spawn threads\n");
    int i;
    int args[MAX_THREADS];
    for (i = 0; i < number_threads; i++) {
        printf("Executing thread: %d thread\n", i);
        args[i] = i;
        pthread_create(&(thread_Ids[i]), NULL, SearchNumber, &args[i]);
    }
    for (i = 0; i < number_threads; i++) {
        pthread_join(thread_Ids[i], NULL);
    }
    printf("Threads joined\n");
    printf("\n");
}

// Print the location(line) where the number was found
void FindLocationNumber() {
    printf("Show line numbers where the number to search for was found\n");
    printf("%d was found in line: ", number_search);
    int i;
    int count = 0;
    for (i = 0; i < num_lines; i++) {
        if (array_numbers[i] == -1) {
            int line_number = i + 1;
            printf("%d ", line_number);
            count += 1;
        }
    }
    printf("\n");
    printf("It was found in total %d location in the file.\n", count);
}

// free malloc and destory the sempahore and mutex
void teardown() {
    free(thread_Ids);
    free(file_name);
    free(array_numbers);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
}

int main(int argc, char *args[]) {
    PrintArguments(argc, args);
    // Malloc file_name and copies the string pointed by args[1]
    file_name = (char*)malloc(strlen(args[1]));
    snprintf(file_name, MALLOC_BYTE, "%s", args[1]);
    // Converts a character string to an integer value
    number_search = atoi(args[2]);
    number_threads = atoi(args[3]);
    num_lines = atoi(args[4]);
    // Malloc thread_ids and array_numbers
    // which converting to array of numbers in file
    thread_Ids = (pthread_t*)malloc(sizeof(*thread_Ids) * number_threads);
    array_numbers = (int*)malloc(sizeof(array_numbers) * num_lines);
    // Initializes the sempahore and mutex
    sem_init(&sem, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    // Create Threads and join threads
    CreateAndJoinThreads(thread_Ids);
    // Printing out the line numbers where the number to search for was found
    FindLocationNumber();
    // free malloc and destory the sempahore and mutex
    teardown();
    exit(0);
}
