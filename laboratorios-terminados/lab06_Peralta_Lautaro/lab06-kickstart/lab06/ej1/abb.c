#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool left_branch_valid(abb tree, abb_elem e){
    bool valid_branch = true;
    if (tree != NULL){
        valid_branch = elem_less(tree->elem,e) && left_branch_valid(tree->left, e) && left_branch_valid(tree->right, e);
    }

    return valid_branch;
}

static bool right_branch_valid(abb tree, abb_elem e){
    bool valid_branch = true;
    if (tree != NULL){
        valid_branch = elem_less(e, tree->elem) && right_branch_valid(tree->left, e) && right_branch_valid(tree->right, e);
    }

    return valid_branch;
}

static bool invrep(abb tree) {
    bool valid_tree = false;
    if (tree == NULL){
        valid_tree = true;
    } else {
        valid_tree = left_branch_valid(tree->left, tree->elem) && right_branch_valid(tree->right, tree->elem) && invrep(tree->left) && invrep(tree->right);
    }

    return valid_tree;
}

abb abb_empty(void) {
    abb tree = malloc(sizeof(struct _s_abb));
    tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else {
        if (elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right, e);
        } else if (elem_less(e, tree->elem)){
            tree->left = abb_add(tree->left, e);
        }
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));

    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));

    if (tree != NULL){
        if (elem_eq(tree->elem, e)){
            exists = true;
        } else if(elem_less(tree->elem, e)){
            exists = abb_exists(tree->right, e);
        } else if(elem_less(e, tree->elem)) {
            exists = abb_exists(tree->left, e);
        }
    }

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0u;
    assert(invrep(tree));

    if (tree != NULL){
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree != NULL){
        if (elem_eq(tree->elem, e)){
            if ((tree->left == NULL) && (tree->right == NULL)){
                free (tree);
                tree = NULL;
            } else if(abb_is_empty(tree->left) && !abb_is_empty(tree->right)){
                tree = tree->right;
            } else if(abb_is_empty(tree->right) && !abb_is_empty(tree->left)){
                tree = tree->left;
            } else {
                tree->elem = abb_max(tree->left);
                tree->left = abb_remove(tree->left, abb_max(tree->left));
            }

        } else if (elem_less(tree->elem,e)){
            tree->right = abb_remove(tree->right, e);
        } else if (elem_less(e, tree->elem)){
            tree->left = abb_remove(tree->left, e);
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));

    root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    while (tree->right != NULL){
        tree = tree->right;
    }
    max_e = tree->elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    while (tree->left != NULL){
        tree = tree->left;
    }
    min_e = tree->elem;

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (tree != NULL){
        abb_destroy(tree->right);
        abb_destroy(tree->left);
        
        free(tree);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}

