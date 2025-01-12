#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

//p1>=p2>=...>=pn
struct s_pstack {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
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


static bool invrep(pstack s) {
    bool res = true;
    if (!pstack_is_empty(s)){
        struct s_node *p = NULL;
        p = s->front;
        while (p->next != NULL && res){
            res = p->priority >= p->next->priority;
            p = p->next;
        }
    }
    return res;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->front = NULL;
    s->size = 0u;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *p_aux1 = NULL;
    struct s_node *p_aux2 = NULL;

    if (pstack_is_empty(s)){
        s->front = new_node;
    } else {
        bool highpriority = true;
        p_aux1 = s->front;
        p_aux2 = s->front;
        if (new_node->priority >= p_aux1->priority){
            s->front = new_node;
            new_node->next = p_aux1;
        } else {
            while (p_aux1->next != NULL && highpriority){
                if (new_node->priority >= p_aux1->priority){
                    highpriority = false;
                } else {
                    p_aux2 = p_aux2;
                    p_aux1 = p_aux1->next;
                }
            }
            if (highpriority == false){
                new_node->next = p_aux1;
                p_aux2->next = new_node;
            } else if (new_node->priority < p_aux2->priority && new_node->priority > p_aux1->priority){
                new_node->next = p_aux1;
                p_aux2->next = new_node;   
            } else{
                p_aux1->next = new_node;
            }
        }
    }
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return (s->size == 0);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    pstack_elem e = s->front->elem;
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t p = s->front->priority;
    return p;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size=0;
    size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *p = s->front;
    s->front = s->front->next;
    destroy_node(p);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *p = NULL;
    while (s->front != NULL){
        p = s->front;
        s->front = s->front->next;
        destroy_node(p);
        s->size--;
    } 
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

