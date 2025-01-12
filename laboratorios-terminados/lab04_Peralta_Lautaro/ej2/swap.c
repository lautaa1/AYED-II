#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void swap(int *a, int *b){
    int aux = 0;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main (void){
    int x = 0, y = 0;
    x = 6;
    y = 4;
    printf ("valor de x: %d, valor de y: %d\n", x,y);
    swap(&x,&y);
    printf ("valor de x: %d, valor de y: %d\n", x,y);
    return 0;
}