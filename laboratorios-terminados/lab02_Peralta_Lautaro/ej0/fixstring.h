#ifndef _FIXSTRING_H_ // si no esta definido
#define _FIXSTRING_H_ //definir

#include <stdbool.h> //libreria para usar bool

#define FIXSTRING_MAX 100 //definir el maximo de la cadena

typedef char fixstring [FIXSTRING_MAX]; //definir fixstring como un arreglo de caracteres

unsigned int fstring_length(fixstring s); //devuelve la longitud de la cadena guardada

bool fstring_eq(fixstring s1, fixstring s2); //definir si dos cadenas son iguales

bool fstring_less_eq(fixstring s1, fixstring s2); //definir si una cadena es menor o igual a otra

#endif //fin del if

