#include <stdio.h>
#include "mpi.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    int number_of_elem = atoi(argv[1]);

    int rank, size;

    int vetor[number_of_elem], i;
    for (i = 0; i < number_of_elem; i++)
    {
        vetor[i] = rand() % number_of_elem;
    }

    

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size = number_of_elem / size;
    int recv_buf[chunk_size];
    int aux, contador, k, p;

    MPI_Scatter(vetor, chunk_size, MPI_INT, recv_buf, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    // for(int j = 0; j < chunk_size; j++)
    // {
    // printf("\n%d | %d \n", rank, recv_buf[j]);
    // }
    
    for (contador = 1; contador < chunk_size; contador++)
    {
        for (k = 0; k < chunk_size - 1; k++)
        {
            if (recv_buf[k] > recv_buf[k + 1])
            {
                aux = recv_buf[k];
                recv_buf[k] = recv_buf[k + 1];
                recv_buf[k + 1] = aux;
            }
        }
    }
    printf("\n\nValores ordenados\n");
    for(p = 0; p < chunk_size; p++)
    {
    printf(" %d | %d\n", rank, recv_buf[p]);
    }

    MPI_Finalize();
    return 0;
}
