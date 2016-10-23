#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: write comments

void* hello_work (void* argument);

int main (int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <thread_number>\n", argv[0]);
        exit(1);
    }

    int thread_count = atoi(argv[1]) - 1; // we have master thread also
    pthread_t* threads = malloc(thread_count * sizeof(pthread_t));
    int thread_args[thread_count];

    for (int i = 0; i < thread_count; i++) {
        thread_args[i] = i;
        pthread_create(threads + i, NULL, hello_work, thread_args + i);
    }

    hello_work(NULL);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* hello_work (void* argument) {
    if (argument != NULL) {
        printf("Hello World from Thread <%d>\n", *((int*) argument));
        return NULL;
    }

    printf("Hello World from Master Thread\n");

    return NULL;
}
