#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 50

int main()
{
    int numeros[TAM];
    int i, aux, contador;
    // vetor gerado aleatoriamente
    for (i = 0; i < TAM; i++)
    {
        numeros[i] = (rand() % TAM);
    }
    // Algoritmo de ordenação Bubblesort:
    for (contador = 1; contador < TAM; contador++)
    {
        for (i = 0; i < TAM - 1; i++)
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
    printf("\n\nValores ordenados\n");
    for(i = 0; i < TAM; i++)
    {
    printf("%d\n", numeros[i]);
    }
    
    return 0;
}