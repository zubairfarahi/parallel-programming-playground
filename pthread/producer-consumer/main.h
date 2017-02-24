#ifndef BBM442_HOMEWORK_1_H
#define BBM442_HOMEWORK_1_H

typedef struct thread_args {
    int id;
    int* buffer;
    sem_t* mutex;
    sem_t* empty;
    sem_t* full;
    int* in;
    int* out;
    int* size;
} thread_args_t;

void produce_consume (int buffer_size, int producer_count, int consumer_count);

void* produce_work (void* args);

void* consume_work (void* args);

void argument_init (thread_args_t* thread_args, int buffer_size);

#endif //BBM442_HOMEWORK_1_H
