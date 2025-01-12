#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;

    //reemplazar scanf por fgets
    fgets(user_input, MAX_LENGTH, stdin);

    //eliminar \n del char
    size_t len = string_length(user_input);
    if (len > 0 && user_input[len - 1] == '\n') {
        user_input[len - 1] = '\0';
    }  
    filtered = string_filter(user_input, ignore_chars[0]);
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        char *temp = string_filter(filtered, ignore_chars[i]);
        free(filtered);
        filtered = temp;
    }
    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    free(filtered);
    return EXIT_SUCCESS;
}

