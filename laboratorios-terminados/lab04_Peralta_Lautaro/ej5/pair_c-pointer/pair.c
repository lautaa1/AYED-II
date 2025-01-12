#include <stdlib.h>
#include <stdio.h>
#include "pair.h"
#include <assert.h>

pair_t pair_new(int x, int y){
    pair_t new_pair = malloc (sizeof(pair_t));
    new_pair->fst = x;
    new_pair->snd = y;
    return new_pair;
}

int pair_first(pair_t p){
    assert(p!=NULL);
    return p->fst;
}

int pair_second(pair_t p){
    assert(p!=NULL);
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    assert(p!=NULL);
    pair_t swap_pair = malloc (sizeof(pair_t));
    swap_pair->fst = p->snd;
    swap_pair->snd = p->fst;
    return swap_pair;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return p;
}
