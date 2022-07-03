#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>


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
    if(argc != 3){
        printf("Quantidade de argumentos invalido. Esperado: 3 \n");
        printf("[0] Nome do arquivo \n");
        printf("[1] Quantidade de Elementos \n");
        printf("[2] Quantidade de threads \n");
        printf("Quantidade de arugmentos recebidos: (%d)\n", argc);
        return 0;
    }else{
        double total_time = 0.0;
        int number_of_elem = atoi(argv[1]);


        int vetor[number_of_elem], i;
        //Gera o vetor aleatoriamente
        for (i = 0; i < number_of_elem; i++)
        {
            vetor[i] = rand() % number_of_elem;
        }

        
        
        omp_set_num_threads(atoi(argv[2]));
        total_time -= omp_get_wtime();
        
        #pragma omp parallel
        {
            //Definindo variáveis 
            int id, i, start, end, threads, contador=0, k, aux, p;
            
            //Definindo começo e fim do vetor que cada thread irá percorrer.
            id = omp_get_thread_num();
            threads = omp_get_num_threads();
            start = id * number_of_elem / threads;
            end = (id+1) * number_of_elem / threads;
            if(id == threads-1) end = number_of_elem;

            //Bubble sort
            //pragma para construção de laço
            #pragma omp parallel for
            for (contador = start; contador < end; contador++)
            {
                for (k = 0; k < end - 1; k++)
                {
                    //Uso o vetor global que está definido fora da região paralela, então é considerada shared
                    if (vetor[k] > vetor[k + 1])
                    {
                        aux = vetor[k];
                        vetor[k] = vetor[k + 1];
                        vetor[k + 1] = aux;
                    }
                }
            }  
            // printf("\n\nValores ordenados\n");
            // for(p = start; p < end; p++)
            // {
            //     printf(" %d | %d\n", id, vetor[p]);
            // }
        }
        
        int *sorted_array = malloc(number_of_elem * sizeof(int));
            
        mergeSort(vetor, sorted_array, 0, (number_of_elem - 1));
        total_time += omp_get_wtime();
        printf("Elapsed: %lf \n", total_time);
        // printf("Vetor ordenado: ");
        // for(int i = 0; i < number_of_elem; i++) {
        //     printf("%d ", sorted_array[i]);
        // }
        // printf("\n");
            
        free(sorted_array);

        return 0;
    }
}
