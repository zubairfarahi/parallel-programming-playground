/**
 * BBM 442 Parallel Processing
 * Homework 1
 * Producer–Consumer problem with pthread & semaphores.
 *
 * Compile: make
 * Run:     ./main <buffer_size> [<producer_count> <consumer_count>]
 *
 * Note:    The program will run forever when you start it.
 *          There is no timeout, you should terminate / kill.
 *
 * Tags: Producer-consumer, pthread, semaphore
 * @author Halil Ibrahim Sener <b21328447@cs.hacettepe.edu.tr>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "main.h"

#define PRODUCER_SLEEP_TIME 200000 // 200 ms
#define CONSUMER_SLEEP_TIME 200000 // 200 ms

/**
 * Main function
 * Operates cli arguments and calls produce_consume function.
 * @param argc  argument count
 * @param argv  argument vector
 * @return status value as integer
 */
int main (int argc, char** argv) {
    if (argc < 2 || argc > 4) {
        printf("Usage: %s <buffer_size> [<producer_count> <consumer_count>]\n", argv[0]);
        printf("Default value of <producer_count> and <consumer_count> is 1.\n");
        return 1;
    }

    srand(time(NULL));

    int buffer_size = atoi(argv[1]);
    int producer_count = (argc > 2) ? atoi(argv[2]) : 1;
    int consumer_count = (argc == 4) ? atoi(argv[3]) : 1;

    produce_consume(buffer_size, producer_count, consumer_count);

    return 0;
}

/**
 * Creates argument struct that will pass to threads and then
 * creates producer and consumer threads.
 * @param buffer_size       size of buffer threads will use
 * @param producer_count    number of producer threads that will be created
 * @param consumer_count    number of consumer threads that will be created
 */
void produce_consume (int buffer_size, int producer_count, int consumer_count) {
    pthread_t* threads = malloc((producer_count + consumer_count) * sizeof(pthread_t));
    unsigned i;

    thread_args_t* thread_args = malloc(sizeof(thread_args_t));
    argument_init(thread_args, buffer_size);

    for (i = 0; i < producer_count; i++) {
        thread_args_t* copy_args = malloc(sizeof(thread_args_t));
        memcpy(copy_args, thread_args, sizeof(thread_args_t)); // waste of memory
        copy_args->id = i; // only one different value
        pthread_create(threads + i, NULL, produce_work, (void*) copy_args);
    }
    for (; i < producer_count + consumer_count; i++) {
        thread_args_t* copy_args = malloc(sizeof(thread_args_t));
        memcpy(copy_args, thread_args, sizeof(thread_args_t)); // waste of memory again
        copy_args->id = i;
        pthread_create(threads + i, NULL, consume_work, (void*) copy_args);
    }

    pthread_exit(NULL);
}

/**
 * Produce work
 * Simply creates a random integer and push it to the buffer.
 * Creating a random integer takes SLEEP_TIME microsecond.
 * @param args  arguments as void pointer
 * @return nothing
 * @see PRODUCER_SLEEP_TIME
 */
void* produce_work (void* args) {
    thread_args_t* thread_args = (thread_args_t*) args;

    while (1) {
        // produce first
        usleep(PRODUCER_SLEEP_TIME);
        int item = rand();

        sem_wait(thread_args->empty);
        sem_wait(thread_args->mutex);

        thread_args->buffer[*(thread_args->in)] = item;
        *(thread_args->in) = (*(thread_args->in) + 1) % *(thread_args->size);
        printf("Thread#%d produced %d\n", thread_args->id, item);

        sem_post(thread_args->mutex);
        sem_post(thread_args->full);
    }
}

/**
 * Consume work
 * Simply takes an integer from buffer and prints it to the console.
 * Processing an integer takes SLEEP_TIME microsecond.
 * @param args  arguments as void pointer
 * @return nothing
 * @see CONSUMER_SLEEP_TIME
 */
void* consume_work (void* args) {
    thread_args_t* thread_args = (thread_args_t*) args;

    while (1) {
        sem_wait(thread_args->full);
        sem_wait(thread_args->mutex);

        int item = thread_args->buffer[*(thread_args->out)];
        *(thread_args->out) = (*(thread_args->out) + 1) % *(thread_args->size);

        sem_post(thread_args->mutex);
        sem_post(thread_args->empty);

        // consume last
        usleep(CONSUMER_SLEEP_TIME);
        printf("Thread#%d consumed %d\n", thread_args->id, item);
    }
}

/**
 * Initialize thread argument struct
 * @param thread_args   pointer of thread argument type
 * @param buffer_size   size of buffer threads will use
 */
void argument_init (thread_args_t* thread_args, int buffer_size) {
    thread_args->buffer = (int*) malloc(sizeof(int) * buffer_size);
    thread_args->empty = (sem_t*) malloc(sizeof(sem_t));
    thread_args->full = (sem_t*) malloc(sizeof(sem_t));
    thread_args->mutex = (sem_t*) malloc(sizeof(sem_t));
    thread_args->in = (int*) calloc(1, sizeof(int)); // calloc because initial value 0.
    thread_args->out = (int*) calloc(1, sizeof(int));
    thread_args->size = (int*) malloc(sizeof(int));
    *(thread_args->size) = buffer_size;

    // Initialize semaphores
    sem_init(thread_args->empty, 0, (unsigned) buffer_size); // counting semaphore
    sem_init(thread_args->full, 0, 0); // counting semaphore
    sem_init(thread_args->mutex, 0, 1); // binary semaphore
}
