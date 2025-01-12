#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size; //size del array
    priority_t min_priority; //minima prioridad permitida (usado como capacity)
    struct s_node **array; //array dinamico
};

struct s_node {
    pqueue_elem elem; //elem del nodo
    struct s_node *next; //puntero a nodo siguiente
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    new_node->next = NULL;
    new_node->elem = e;
    assert(new_node!=NULL);
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pqueue q) {
    return q != NULL;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority+1, sizeof(struct s_node));
    q->min_priority = min_priority;
    q->size = 0u;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    unsigned int i = 0u;
    bool queued = false;
    struct s_node *new_node = NULL;
    new_node = create_node(e);
    while (i <= q->min_priority && !queued){
        if(i == priority){
            if (q->array[i] == NULL){
                q->array[i] = new_node;
                queued = true;
            } else {
                struct s_node *aux = q->array[i];
                while (aux->next != NULL){
                    aux = aux->next;
                }  
                aux->next = new_node;
                queued = true;
            }        
        }
        ++i;
    }
    ++q->size;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    bool is_empty = q->size == 0;
    return is_empty;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem elem;
    unsigned int i=0u;
    bool found = false;
    while (i <= q->min_priority && !found){
        if (q->array[i] != NULL){
            elem = q->array[i]->elem;
            found = true;
        }
        ++i;
    }
    return elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t prio = 0u;
    unsigned int i=0u;
    bool found = false;
    while (i <= q->min_priority && !found){
        if (q->array[i] != NULL){
            found = true;
            prio = i;
        }
        ++i;
    }
    return prio;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    size_t length = q->size;
    return length;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i=0u;
    bool dequeued = false;
    while (i <= q->min_priority && !dequeued){
        if (q->array[i] != NULL){
            struct s_node *aux = q->array[i];
            q->array[i] = q->array[i]->next;
            aux = destroy_node(aux);
            dequeued = true;
        }
        ++i;
    }
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    unsigned int i = 0u;
    while (i <= q->min_priority){
        if (q->array[i] != NULL){
            struct s_node *aux = NULL;
            while (q->array[i]->next != NULL){
                aux = q->array[i];
                q->array[i] = q->array[i]->next;
                aux = destroy_node(aux);
            }
        }
        q->array[i] = destroy_node(q->array[i]);
        ++i;
    }
    free(q->array);
    free(q);

    q = NULL;
    
    assert(q == NULL);
    return q;
}

