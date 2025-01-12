#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int contador = 0;
    while (s[contador] != '\0'){ //mientras no llegue al final de la cadena
        contador++; //cuento los caracteres
    }
return contador;    
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool iguales = true;
    unsigned int j = fstring_length(s1); //longitud de la cadena s1
    unsigned int k = fstring_length(s2); //longitud de la cadena s2
    if (j != k){ //si las longitudes son distintas, no son iguales
        iguales = false;
        return iguales;
    }
    for (unsigned int i=0; i < j ; i++){ //recorro las cadenas
        if (s1[i] != s2[i]){ //si los caracteres son distintos, no son iguales
            iguales = false;
        }
    }
return iguales;    
}

bool fstring_less_eq(fixstring s1, fixstring s2){
    bool res = true;                                  
    unsigned int i = 0;
    unsigned int lenght1 = fstring_length(s1); //longitud de la cadena s1
    unsigned int lenght2 = fstring_length(s2); //longitud de la cadena s2
    if (fstring_eq(s1,s2) == true){ //si las cadenas son iguales
        return res;
    } 
    while (i < lenght1 && i < lenght2){ //mientras no llegue al final de alguna de las cadenas
        if (s1[i] == s2[i]){ //si los caracteres son iguales
            i++;
        } else if (s1[i] > s2[i]){ //si el caracter de s1 es mayor que el de s2
            res = false;
            return res;
        } else if (s1[i] < s2[i]){ //si el caracter de s1 es menor que el de s2
            res = true;
            return res;
        }
    }
return res;
}
