#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

char *parse_filepath(int argc, char *argv[]) {
    
/* Parse the filepath given by command line argument. */
char *result = NULL;
// Program takes exactly two arguments
// (the program's name itself and the input-filepath)
bool valid_args_count = (argc == 2);

if (!valid_args_count) {
exit(EXIT_FAILURE);
}

result = argv[1];

return result;
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    FILE *fp = fopen(path, "r");
    unsigned int lenght = 0u, check;
    int aux;
    //If para ver si el archivo no es nulo.
    if (fp == NULL){
        printf ("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i=0u;
    while (!feof(fp)){
        if (i >= max_size){
            printf("La cantidad de lineas del archivo leido supera el maximo admitido\n");
            exit(EXIT_FAILURE);
        }
        aux = fscanf(fp, "%u -> *%c*\n", &check, &letters[i]);
        if (aux != 2 ){
            printf("Error en la lectura\n");
            exit(EXIT_FAILURE);
        }
        
        if (check >= MAX_SIZE){
            printf ("El indice indicado en el archivo es mayor al indicado\n");
            exit(EXIT_FAILURE);
        } else {
            indexes[i] = check;
        }
        i++;
        lenght++;
    }
    fclose(fp);
    return lenght;
}

int main(int argc, char *argv[]) {
    
    FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    /* -- completar -- */
    char *filepath = NULL;

    filepath = parse_filepath(argc, argv);

    length = data_from_file(filepath,indexes,letters,MAX_SIZE);

    for(unsigned int i = 0; i<length;i++ ){
        sorted[indexes[i]] = letters[i];
    }


    dump(sorted, length);

    return EXIT_SUCCESS;
}

