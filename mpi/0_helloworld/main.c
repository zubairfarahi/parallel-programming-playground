/**
 * Parallel Hello World with OPEN MPI.
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define BUF_SIZE        50
#define MASTER          0
#define TAG             0

/**
 * Main function
 * @param argc argument count
 * @param argv argument vector
 * @return status
 */
int main (int argc, char** argv) {

    int comm_size, my_rank, i;
    char message[BUF_SIZE];

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == MASTER) {
        printf("Hello from %d / %d\n", my_rank, comm_size);

        for (i = 1; i < comm_size; i++) {
            MPI_Recv(message, BUF_SIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", message);
        }

    } else {
        sprintf(message, "Hello from %d / %d\n", my_rank, comm_size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, MASTER, TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
