/**
 * Parallel Hello World with pthread library.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hello_work (void* argument);

/**
 * Main function
 * @param argc argument count
 * @param argv argument vector
 * @return status
 */
int main (int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <thread_number>\n", argv[0]);
        return 1;
    }

    int thread_count = atoi(argv[1]) - 1; // we have also master thread

    // Allocate memory for threads and threads' arguments
    pthread_t* threads = malloc(thread_count * sizeof(pthread_t));
    int* thread_args = malloc(thread_count * sizeof(int));
    unsigned i;

    // Create threads
    for (i = 0; i < thread_count; i++) {
        thread_args[i] = i;
        pthread_create(threads + i, NULL, hello_work, thread_args + i);
    }

    hello_work(NULL);

    // Wait for each thread to finish the work
    for (i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Deallocate the allocated memory
    free(threads);
    free(thread_args);

    pthread_exit(NULL);
}

/**
 * Hello work (routine) function
 * @param arg argument for the thread
 * @return NULL
 */
void* hello_work (void* arg) {
    if (arg != NULL) {
        int index = *((int*) arg);
        printf("Hello World from Thread <%d>\n", index);
    } else {
        printf("Hello World from Master Thread\n");
    }

    pthread_exit(NULL);
}
