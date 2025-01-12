#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    unsigned int size;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    // COMPLETAR
    bool valid = true;
    if (dict != NULL && dict->first != NULL){
        struct _node_t *iter = dict->first;
        while (iter != NULL && valid){
            struct _node_t *check = iter->next;
            while (check != NULL && valid) {
                if (key_eq(iter->key, check->key)) {
                    valid = false;
                }
                check = check->next;
            }
            iter = iter->next;
        }
    }
    return valid;
}
// --- Interface functions ---

dict_t dict_empty(void) {
    dict_t new_dic = NULL;
    new_dic = malloc(sizeof(struct _s_dict));
    new_dic->first = NULL;
    new_dic->size = 0u;
    return new_dic;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    struct _node_t *new_word = create_node(word, def);
    bool exist = false;
    if (dict->first == NULL && dict->size == 0){
        dict->first = new_word;
    }else{
        struct _node_t *iterador = dict->first;
        while (iterador->next != NULL && !exist){
            if (key_eq(iterador->key,word)==true){
                iterador->value = def;
                exist = true;
            }
            iterador = iterador->next;
        }
        if (exist != true){
            iterador->next = new_word;
        }
    }
    dict->size++;
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t res = NULL;
    bool exist = false;
    if (dict->first != NULL){
        struct _node_t *iterador = dict->first;
        while (iterador != NULL && !exist){
            if (key_eq(word, iterador->key)==true){
                res = iterador->value;
                exist = true;
            }
            iterador = iterador->next;
        }
    }
    return res; 
}

bool dict_exists(dict_t dict, key_t word) {
    bool exist = false;
    if (dict->first != NULL){
        struct _node_t *iterador = dict->first;
        while (iterador != NULL && !exist){
            if (key_eq(word, iterador->key)==true){
                exist = true;
            }
            iterador = iterador->next;
        }
    }
    return exist; 
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    length = dict->size;
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    if (dict->first != NULL) {
        struct _node_t *iterador = dict->first;
        struct _node_t *anterior = NULL;
        bool exist = false;

        while (iterador != NULL && !exist) {
            if (key_eq(iterador->key, word)) {
                exist = true;
                if (anterior == NULL) {
                    // El nodo a eliminar es el primero
                    dict->first = iterador->next;
                } else {
                    // El nodo a eliminar no es el primero
                    anterior->next = iterador->next;
                }
                destroy_node(iterador);
                dict->size--;
            } else {
                anterior = iterador;
                iterador = iterador->next;
            }
        }
    }
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    if (dict->first != NULL){
        struct _node_t *iterador = NULL;
        while (dict->first != NULL){
            iterador = dict->first;
            dict->first = dict->first->next;
            destroy_node(iterador);
        }
    }
    dict->size = 0u;
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

