#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

//prop fundamental p1<=p2<=..<=pn
//si se usa la misma prioridad, el TAD se comporta
//como una cola comun.
struct s_pqueue {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool valid = true;
    //si pqueue tiene un solo elemento, es un pqueue valido, si es NULL, igualmente
    if (!pqueue_is_empty(q) && q->size>1){
        struct s_node *aux = NULL;
        aux = q->front;
        while (aux->next != NULL && valid){
            valid = aux->priority <= aux->next->priority; //chequeo que la prioridad del elem sig sea mayor, si es menor, retorno false;
            aux = aux->next;
        }
    }
    return valid;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->front = NULL;
    q->size = 0u;
    
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *p_aux1 = NULL;
    struct s_node *p_aux2 = NULL;
    if (pqueue_is_empty(q)){
        q->front = new_node;
    } else{
        bool higher_priority = true;
        p_aux1 = q->front;
        p_aux2 = q->front;
        if (new_node->priority < p_aux1->priority){ //caso primer nodo tiene prioridad menor al nuevo nodo.
            q->front = new_node;
            new_node->next = p_aux1;
        } else{
            while (p_aux1->next != NULL && higher_priority){ //encontrar la posicion del que tenga la prioridad menor
                if (new_node->priority < p_aux1->priority){
                    higher_priority = false;
                } else {
                    p_aux2 = p_aux1;
                    p_aux1 = p_aux1->next;
                }
            }
            if (higher_priority == false){ // se encontro una posicion
                new_node->next = p_aux1;
                p_aux2->next = new_node;
            } else if (new_node->priority > p_aux2->priority && new_node->priority < p_aux1->priority){
                new_node->next = p_aux1;
                p_aux2->next = new_node;
            } else { // no se encontro otra posicion, es la prioridad mas "chica"
                p_aux1->next = new_node;
            }
        }
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return (q->size == 0u);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q));
    pqueue_elem e = q->front->elem;
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int priority = q->front->priority;
    return priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size= q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *p = q->front;
    if (p!=NULL){
        q->front = p->next;
        p->next = NULL;
        destroy_node(p);
        q->size--;
    }
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while (q->front != NULL){
        q = pqueue_dequeue(q);  
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
