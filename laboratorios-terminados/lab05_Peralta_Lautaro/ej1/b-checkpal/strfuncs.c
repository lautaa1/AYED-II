#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str){
    size_t length = 0u;
    for (unsigned int i = 0; str[i] != '\0'; i++){
        length++;
    }
    return length;
}

char *string_filter(const char *str, char c){
    char *new_str = malloc(sizeof(char) * string_length(str) + 1);
    unsigned int index = 0u;
    for (unsigned int i = 0; str[i] != '\0'; i++){
        if (str[i] != c){
            new_str[index] = str[i];
            index++;
        }
    }
    new_str[index] = '\0';
    return new_str;
}

bool string_is_symmetric(const char *str){
    bool symmetric = true;
    size_t length = string_length(str);
    if (length != 0){
        for (unsigned int i = 0; str[i] != '\0' && symmetric; i++){
            if (str[i] != str[length-1]){
                symmetric = false;
            }
            length--;
        }
    }
    return symmetric;
}