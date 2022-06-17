#include <stdio.h>
#include "mpi.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>


void merge(int *a, int *b, int l, int m, int r) {
	
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	
	while((h <= m) && (j <= r)) {
		
		if(a[h] <= a[j]) {
			
			b[i] = a[h];
			h++;
			
			}
			
		else {
			
			b[i] = a[j];
			j++;
			
			}
			
		i++;
		
		}
		
	if(m < h) {
		
		for(k = j; k <= r; k++) {
			
			b[i] = a[k];
			i++;
			
			}
			
		}
		
	else {
		
		for(k = h; k <= m; k++) {
			
			b[i] = a[k];
			i++;
			
			}
			
		}
		
	for(k = l; k <= r; k++) {
		
		a[k] = b[k];
		
		}
		
	}

void mergeSort(int *a, int *b, int l, int r) {
	
	int m;
	
	if(l < r) {
		
		m = (l + r)/2;
		
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
		
		}
		
}


int main(int argc, char **argv)
{
    double total_time = 0.0;
    int number_of_elem = atoi(argv[1]);

    int rank, size;

    int vetor[number_of_elem], i;
    //Gera o vetor aleatoriamente
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

    MPI_Barrier(MPI_COMM_WORLD);
    total_time -= MPI_Wtime();

    //Divide o buffer de envio em partes iguais
    MPI_Scatter(vetor, chunk_size, MPI_INT, recv_buf, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    // for(int j = 0; j < chunk_size; j++)
    // {
    // printf("\n%d | %d \n", rank, recv_buf[j]);
    // }
    
    //Bubble Sort
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
    // printf("\n\nValores ordenados\n");
    // for(p = 0; p < chunk_size; p++)
    // {
    //     printf(" %d | %d\n", rank, recv_buf[p]);
    // }

    int *sorted_array = NULL;
	if(rank == 0) {
		
		sorted_array = malloc(number_of_elem * sizeof(int));
		
    }

    MPI_Gather(recv_buf, chunk_size, MPI_INT, sorted_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        int *other_array = malloc(number_of_elem * sizeof(int));
		mergeSort(sorted_array, other_array, 0, (number_of_elem - 1));
        total_time += MPI_Wtime();
        printf("Elapsed: %lf \n", total_time);
        // printf("Vetor ordenado: ");
		// for(int i = 0; i < number_of_elem; i++) {
		// 	printf("%d ", sorted_array[i]);
        // }
		printf("\n");
			
		free(sorted_array);
		free(other_array);
    }

    MPI_Finalize();
    return 0;
}
