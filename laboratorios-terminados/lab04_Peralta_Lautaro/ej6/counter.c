#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter new_c = NULL; 
    new_c = malloc(sizeof(counter));
    new_c->count = 0;
    return new_c;
}

void counter_inc(counter c) {
    c->count = c->count+1;
}

bool counter_is_init(counter c) {
    return (c->count == 0);
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count = c->count - 1;
}

counter counter_copy(counter c) {
    counter new_c = NULL; 
    new_c = malloc(sizeof(counter));
    new_c->count = c->count;
    return new_c;
}

void counter_destroy(counter c) {
    free(c);
}
