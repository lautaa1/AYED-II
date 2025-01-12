#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

bool goes_before(int x, int y);
/* Abstract total order for sorting algorithms 
   Returns true if x goes before y in the order, false otherwise
   Devuelve verdadero si x va antes que y en el orden, falso en caso contrario
*/


bool array_is_sorted(int a[], unsigned int length);
/* Checks if the array 'a' is in ascending order 
   Devuelve verdadero si el array 'a' esta en orden ascendente
*/

void swap(int a[], unsigned int i, unsigned int j);
/* Exchanges elements of array 'a' in the given positions 'i' and 'j'
   Array remains the same if the two positions are the same
   Intercambia elementos del array 'a' en las posiciones 'i' y 'j'
   El array permanece igual si las dos posiciones son iguales
*/

#endif
