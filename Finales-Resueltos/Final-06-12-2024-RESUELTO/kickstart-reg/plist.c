#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    struct s_node *atras;
    struct s_node *adelante;
    t_elem pivot;
    unsigned int size;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    /* COMPLETAR */
    if (node != NULL){
        node->next = NULL;
        free(node);
    }
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    /* COMPLETAR */
    return l!=NULL;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    /* COMPLETAR */
    struct s_plist *new_plist = malloc(sizeof(struct s_plist));
    assert(new_plist != NULL); 
    new_plist->atras = NULL;
    new_plist->adelante = NULL;
    new_plist->pivot = pivot;
    new_plist->size = 1u;
    return new_plist;
}

plist plist_add(plist l, t_elem e) {
    /* COMPLETAR */
    assert(l != NULL && e != l->pivot);
    struct s_node *new_elem = create_node(e);
    if (t_elem_less(e, l->pivot)){
        new_elem->next = l->atras;
        l->atras = new_elem;
    } else if (t_elem_greater(e, l->pivot)){
        new_elem->next = l->adelante;
        l->adelante = new_elem;
    }
    l->size++;
    return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
    return (l->size);
}

bool plist_is_empty(plist l) {
    return (l->size == 1);
}

t_elem plist_get_pivot(plist l) {
    return (l->pivot);
}

plist plist_delete_prev(plist l) {
    /* COMPLETAR */
    if (l->atras != NULL) {
        struct s_node *elim = l->atras;
        l->atras = l->atras->next;
        destroy_node(elim);
        l->size--;
    }
    return l;
}

plist plist_delete_next(plist l) {
    /* COMPLETAR */
    if (l->adelante != NULL) {
        struct s_node *elim = l->adelante;
        l->adelante = l->adelante->next;
        destroy_node(elim);
        l->size--;
    }
    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    unsigned int count_e = 0u;
    if (l != NULL){
        if (l->atras != NULL){
            struct s_node *a = l->atras;
            while (a != NULL){
                if (t_elem_eq(a->elem,e)){
                    count_e++;
                }
                a = a->next;
            }
        }
        if (l->adelante != NULL){
            struct s_node *b = l->adelante;
            while (b != NULL){
                if (t_elem_eq(b->elem,e)){
                    count_e++;
                }
                b = b->next;
            }
        }
        if (t_elem_eq(l->pivot,e)){
            count_e++;
        }
    }
    return count_e;
}

t_elem * plist_to_array(plist l) {
    unsigned int size_a = 0u;
    unsigned int size_b = 0u;
    if (l != NULL) {
        struct s_node *p_iter1 = l->atras;
        while (p_iter1 != NULL) {
            size_a++;
            p_iter1 = p_iter1->next;
        }
        struct s_node *p_iter2 = l->adelante;
        while (p_iter2 != NULL) {
            size_b++;
            p_iter2 = p_iter2->next;
        }
    }
    t_elem *array = calloc(size_a + size_b + 1, sizeof(t_elem));
    unsigned int index = 0;
    struct s_node *list_prev = l->atras;
    struct s_node *list_next = l->adelante;
    while (list_prev != NULL) {
        array[index++] = list_prev->elem;
        list_prev = list_prev->next;
    }
    array[index++] = l->pivot;
    while (list_next != NULL) {
        array[index++] = list_next->elem;
        list_next = list_next->next;
    }
    return array;
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    /* COMPLETAR */
    if (l!=NULL){
        while (l->adelante != NULL) {
            struct s_node *elim = l->adelante;
            l->adelante = l->adelante->next;
            destroy_node(elim);
        }
        while (l->atras != NULL) {
            struct s_node *elim = l->atras;
            l->atras = l->atras->next;
            destroy_node(elim);
        }
        free(l);
        l = NULL;
    }
    return l;
}
// ./plistload input/example-easy-005.in