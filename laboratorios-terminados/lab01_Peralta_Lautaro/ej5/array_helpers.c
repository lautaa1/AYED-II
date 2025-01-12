#include "array_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mybool.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {

    unsigned int size;
    FILE * fp;
    fp = fopen (filepath, "r");
    fscanf(fp,"%u", &size);

    if (size > max_size){
    printf ("tamaño superado\n");
    exit (EXIT_FAILURE);
    }
    if (fp == NULL){
    printf ("Error al abrir el archivo\n");
    exit (EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < size; i++){
        fscanf (fp, "%d", &array[i]);
        if (!feof(fp)==0){
        printf ("Tamaño superado\n");
        exit (EXIT_FAILURE);
        }
    }
    fclose(fp);
    return size;
}

void array_dump(int a[], unsigned int length) {  
    printf ("[");
    for (unsigned int i = 0 ; i < length ; i++){
    printf (" %d ", a[i]);
    }
    printf ("]\n");
}

mybool array_is_sorted(int a[], unsigned int length){
    mybool resultado = true;
    for (unsigned int i = 1; i < length; i++){
        if (a[i-1] > a[i]){
            resultado = false;
        }
    }
    return resultado;
}
