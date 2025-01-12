#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;
};

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->next = NULL;
    s->size = 0;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack s1;
    s1 = malloc (sizeof(struct _s_stack));
    s1->elem = e;
    s1->next = s;
    s1->size = s->size + 1;
    return s1;
}

stack stack_pop(stack s){
    assert(s != NULL);
    stack s1;
    s1 = s;
    s = s->next;
    s->size = s1->size -1;
    free(s1);
    return s;
}

unsigned int stack_size(stack s){
    return s->size;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s){
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s){
    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    if (s != NULL){
        stack p = s;
        for (unsigned int i = 0; i < s->size; i++){
            array[i] = p->elem;
            p = p->next;
        }
    }
    return array;
}
stack stack_destroy(stack s){
    while (s != NULL){
        stack p = s;
        s = s->next;
        free(p);
    }
    free(s);
    return s;
}