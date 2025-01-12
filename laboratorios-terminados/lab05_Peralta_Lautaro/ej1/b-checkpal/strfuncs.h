#ifndef _STRFUNCS_H_
#define _STRFUNCS_H_
#include <stdbool.h>
#include <stddef.h>

size_t string_length(const char *str);
//  Que calcula la longitud de la cadena apuntada por str.
char *string_filter(const char *str, char c);
//  Que devuelve una nueva cadena en memoria dinámica que se obtiene tomando los caracteres de str
//  que son distintos del caracter c.
bool string_is_symmetric(const char *str);
//  Que indica si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el
//  último, el segundo con el penúltimo, etc; como por ejemplo las cadenas "aba", "abcba", "a", "".

#endif