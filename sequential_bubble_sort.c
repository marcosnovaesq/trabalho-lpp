#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    
    int tamanho = atoi(argv[1]);
    int numeros[tamanho];
    int i, aux, contador;
    // vetor gerado aleatoriamente
    for (i = 0; i < tamanho; i++)
    {
        numeros[i] = (rand() % tamanho);
    }
    // Algoritmo de ordenação Bubblesort:
    clock_t begin = clock();
    for (contador = 1; contador < tamanho; contador++)
    {
        for (i = 0; i < tamanho - 1; i++)
        {
            if (numeros[i] > numeros[i + 1])
            {
                aux = numeros[i];
                numeros[i] = numeros[i + 1];
                numeros[i + 1] = aux;
            }
        }
    }

    //output do quick sort 
    // printf("\n\nValores ordenados\n");
    // for(i = 0; i < tamanho; i++)
    // {
    // printf("%d\n", numeros[i]);
    // }
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed: %f seconds\n", time_spent);
    return 0;
}