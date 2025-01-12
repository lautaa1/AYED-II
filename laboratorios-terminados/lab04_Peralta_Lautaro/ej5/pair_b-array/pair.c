#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t new_pair;
    new_pair.values[0] = x;
    new_pair.values[1] = y;
    return new_pair;
}

int pair_first(pair_t p){
    return p.values[0];
}

int pair_second(pair_t p){
    return p.values[1];
}

pair_t pair_swapped(pair_t p){
    pair_t swap_pair;
    swap_pair.values[0] = p.values[1];
    swap_pair.values[1] = p.values[0];
    return swap_pair;
}

pair_t pair_destroy(pair_t p){
    p.values[0] = 0;
    p.values[1] = 0;
    return p;
}
