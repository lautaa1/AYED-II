#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define ARRAY_SIZE 4


//funcion para solicitar arreglo
void pedirArreglo (int a[],int n_max){
    int i=0;
    while (i<n_max){
        printf ("Asignar un valor al indice %d: \n",i);
        scanf("%d",&a[i]);
        i+=1;
    }
}

//definir estructuras//
struct bound_data {
    bool is_upperbound; 
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

//funcion solicitada en el ejercicio (verifica si value es mayor, menor igual, si existe el elemento y en donde de un arreglo).
struct bound_data check_bound(int value, int arr[], unsigned int length) {
    //value es el numero a buscar, este debe ser mayor o igual a todos los elementos del arreglo.
    //cuando tenemos una estructura, debemos definir un elemento de ese tipo con un nombre, en este caso res, asignaremos a cada elemento de la estructura con un .
    struct bound_data res;
    res.is_lowerbound=false; //valor si es menor igual a todos los elementos del arreglo
    res.is_upperbound=false; //valor si es mayor igual a todos los elementos del arreglo
    res.exists=false; //valor que indica si el elemento existe en el arreglo
    res.where= 0; //valor que indica en que posicion se encuentra el elemento en el arreglo

    //creo contadores, para ver si es mayor o si es menor.
    unsigned int upper_counter = 0;    
    unsigned int lower_counter = 0;

    //me fijo si el value es mayor o igual, menor o igual y en que posicion esta y si es que existe
    for (unsigned int i = 0; i < length; i++){
        if (arr[i] < value){
            upper_counter += 1;
        } else if (arr[i] > value){
            lower_counter += 1;
        } else if (arr[i] == value){
            res.exists = true;
            res.where = i;
            upper_counter += 1;    
            lower_counter += 1;
        }
    }
    
    //busco que el contador sea igual al largo, si es igual elijo.
    if (upper_counter == length){
        res.is_upperbound=true;
    } else if (lower_counter == length){
        res.is_lowerbound=true;
    }
    return res;
}

int main(void) {

    //defino el arreglo
    int a[ARRAY_SIZE];

    //llamo la funcion pedir arreglo y su tamanio
    pedirArreglo(a,ARRAY_SIZE);

    //defino nuevamente un tipo de la estructura con nombre, al que lo  igualare segun el resultado que devuelva la funcion check_bound
    int value;
    printf ("seleccion el  valor a  buscar: ");
    scanf ("%d", &value);
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("%d \n", result.is_upperbound); // Imprime 1
    printf("%d \n", result.is_lowerbound); // Imprime 0
    printf("%u \n", result.exists);        // Imprime 1
    printf("%u \n", result.where);         // Imprime 2

    return EXIT_SUCCESS;
}

//gcc -Wall -Wextra -std=c99 bounds.c -o bounds
// ./bounds