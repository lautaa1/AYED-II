#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct _node {
    list_elem elem;
    struct _node *next;
};

//constructors

list empty(void){
    list l = NULL;
    return l;
}

list addl(list_elem e, list l){
    list new_item = NULL;
    new_item = malloc(sizeof(struct _node));
    new_item->elem = e;
    new_item->next = l;
    
    return new_item;
}

//destroy

list destroy(list l){
    list l2;
    while (!is_empty(l)){
        l2 = l;
        l = l->next;
        free(l2);
    }
    return l;
}

//operations

bool is_empty(list l){
    return (l == NULL);
}

list_elem head(list l){
    assert(!is_empty(l));
    return (l->elem);
}

list tail(list l){
    assert(!is_empty(l));
    list p = l;
    l = l->next;
    free(p);
    return l;
}

list addr(list l, list_elem e){
    list new_item = NULL;
    new_item = malloc(sizeof(struct _node));
    new_item->elem = e;
    new_item->next = NULL;
    if (!is_empty(l)){
        list l2 = NULL;
        l2 = l;
        while (l2->next != NULL){
            l2 = l2->next;
        }
        l2->next = new_item;
    } else {
        l = new_item;
    }
    return l;
}

unsigned int length(list l){
    unsigned int n = 0u;
    list l2 = NULL;
    l2 = l;
    while (l2 != NULL){
        l2 = l2->next;
        n = n + 1;
    }
    return n;
}

list concat(list l0, list l1){
    list p = NULL;
    p = l0;
    if (is_empty(l0)){
        p = l1;
    } else {
        while (p->next != NULL){
            p = p->next;
        }
        p->next = l1;
    }
    return l0;
}

list_elem index(list l, unsigned int n){
    assert(length(l) >= n);
    unsigned int i = 0u;
    list p = l;
    while (i < n){
        p = p->next;
        i++;
    }
    return p->elem;
}

list take(list l, unsigned int n){
    list p = NULL;
    list q = NULL;
    unsigned int c = 0u;
    p = l;
    if (!is_empty(l)){
        while (p != NULL){
            q = p;
            p = p->next;
            c++;
            if (c > n){
                free(q);
            }
        }
    }
    return p;
}

list drop(list l, unsigned int n){
    unsigned int i = 0u;
    while (i < n && l!=NULL){
        list p = l;
        l = l->next;
        free (p);
        ++i;
    }
    return l; 
}

list copy_list(list l1){
    list l2 = malloc(sizeof(struct _node));
    if (!is_empty(l1)){
        list p = l1;
        while (p != NULL){
            l2->elem = p->elem;
            l2->next = p->next;
            p = p->next;
        }
    }
    return l2;
}
