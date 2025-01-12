#include <stdlib.h>
#include <stdio.h>
#include "pair.h"
#include <assert.h>

struct s_pair_t{
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y){
    pair_t new_pair = malloc (sizeof(pair_t));
    new_pair->fst = x;
    new_pair->snd = y;
    return new_pair;
}

elem pair_first(pair_t p){
    assert(p!=NULL);
    return p->fst;
}

elem pair_second(pair_t p){
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
