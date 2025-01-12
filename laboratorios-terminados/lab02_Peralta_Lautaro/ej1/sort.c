#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


/*
static bool goes_before2 (int x, int y){
    bool res = false;
    if (x < y){
        res = true;
    }
    return res;
}
*/

static void insert(int a[], unsigned int i) {
    unsigned int j = i;
    while (j > 0 && goes_before(a[j],a[j-1]) == true){
        swap(a,j-1,j);
        j--;
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; i++) {
        insert(a, i);
        assert (array_is_sorted (a,i));
    }
}

/* 
La relacion que implementa es de orden(<)
El criterio que usa es la comparacion de valores absolutos.
*/
