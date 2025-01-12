#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->next = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack s1;
    s1 = malloc (sizeof(struct _s_stack));
    s1->elem = e;
    s1->next = s;
    return s1;
}

stack stack_pop(stack s){
    assert(s != NULL);
    stack s1;
    s1 = s;
    s = s->next;
    free(s1);
    return s;
}

unsigned int stack_size(stack s){
    unsigned int size = 0;
    stack s1 = s;
    while (s1 != NULL){
        s1 = s1->next;
        size++;
    }
    return size;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    return s -> elem;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    unsigned int length = stack_size(s);
    stack_elem *array = calloc(length, sizeof(stack_elem));
    if (s != NULL){
        stack p = s;
        for (unsigned int i = 0; i < length; i++){
            array[i] = p->elem;
            p = p->next;
        }
    }
    return array;
}
stack stack_destroy(stack s){
    while (s != NULL){
        s = stack_pop(s);
    }
    return s;
}