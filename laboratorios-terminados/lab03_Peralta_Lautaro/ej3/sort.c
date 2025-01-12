/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return (x.rank <= y.rank);
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

static void swap (player_t a[], unsigned int i, unsigned int j){
    player_t tmp = a[i];
    a[i]=a[j];
    a[j]=tmp;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    unsigned int i = izq + 1;
    unsigned int j = der;
    while (i <= j) {
        if (goes_before(a[i], a[ppiv])) {
            i++;
        } else if (goes_before(a[ppiv], a[j])) {
            j--;
        } else { // Este else maneja el caso en que a[i] > a[ppiv] y a[j] < a[ppiv]
            swap(a, i, j);
            i++;
            j--;
        }
    }
    swap(a, ppiv, j);
    return j;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    if (der > izq) {
        unsigned int ppiv = partition(a, izq, der);
        if (ppiv > 0) { // Asegurarse de que ppiv no sea 0 para evitar underflow
            quick_sort_rec(a, izq, ppiv - 1);
        }
        quick_sort_rec(a, ppiv + 1, der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

