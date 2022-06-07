#include <stdio.h>
#include <stdlib.h>
 
// receber isso via args
#define MAX 10

//definição do prototipo
void quick_sort(int *a, int left, int right);
 

int main(int argc, char** argv)
{
 // inicialização das variaveis
 int i, vet[MAX];
 
 // vetor gerado aleatoriamente 
 for(i = 0; i < MAX; i++)
 {
  vet[i] = (rand() % MAX);
 }
 

 quick_sort(vet, 0, MAX - 1);
 
 //output do quick sort 
 printf("\n\nValores ordenados\n");
 for(i = 0; i < MAX; i++)
 {
  printf("%d\n", vet[i]);
 }

 return 0;
}
 

void quick_sort(int *a, int left, int right) {
    //inicializaçao das variaveis
    int i, j, x, y;

    //associaçao doo indice esquerda e direita  
    i = left;
    j = right;

    //escolha do pivot
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
    //chamadas recursivas do vetor a esquerda e a direita 
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}