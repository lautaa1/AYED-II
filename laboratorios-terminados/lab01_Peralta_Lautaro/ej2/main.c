/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

//funcion que lee un archivo y lo guarda en un arreglo
unsigned int array_from_stdin(int a[], unsigned int max_size) {
    unsigned int size; //tamaño del arreglo
    printf ("Ingrese una longitud para el arreglo: \n"); //solicito el tamaño del arreglo
    fscanf (stdin, "%u", &size); //leo el tamaño del arreglo
    if (size > max_size){  //si el tamaño supera el maximo permitido
        printf ("Tamaño maximo superado");
        exit (EXIT_FAILURE) ;
    }
    for (unsigned int i = 0, j = 1; i < size; i++,j++){//solicito los valores del arreglo
        printf ("Agregue un valor para la posicion %d: ", j);
        fscanf (stdin, "%d", &a[i]);
    }
    return size;
}


void array_dump(int a[], unsigned int length){
    printf ("\n[ ");
    for (unsigned int i = 0; i < length; i++){
        printf("%d ", a[i]);
    }
    printf ("]\n");
}


int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}

//gcc -Wall -Werror -Wextra -pedantic -std=c99 -o reader main.c
//./reader ../input/example-easy.in
