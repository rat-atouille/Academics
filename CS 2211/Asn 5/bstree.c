#include "bstree.h"
#include <stdio.h>

BStree_node* new_node(Key key, Data data) {
    BStree_node* new_node = (BStree_node*)malloc(sizeof(BStree_node));
    if (new_node != NULL) {
        new_node->key = key;
        new_node->data = data;
        new_node->left = new_node->right = NULL;
    }
    return new_node;
}

BStree bstree_ini(void) {
    BStree new_tree = (BStree)malloc(sizeof(BStree_node*));
    if (new_tree != NULL) {
        *new_tree = NULL;
    }
    return new_tree;
}

void bstree_insert(BStree bst, Key key, Data data) {
    if (bst == NULL || *bst == NULL) {
        *bst = new_node(key, data);
    } else {
        BStree_node* current = *bst;
        while (1) {
            int cmp_result = key_comp(key, current->key);
            if (cmp_result < 0) {
                if (current->left == NULL) {
                    current->left = new_node(key, data);
                    break;
                }
                current = current->left;
            } else if (cmp_result > 0) {
                if (current->right == NULL) {
                    current->right = new_node(key, data);
                    break;
                }
                current = current->right;
            } else {
                break; // Key already exists
            }
        }
    }
}

Data bstree_search(BStree bst, Key key) {
    if (bst != NULL) {
        BStree_node* current = *bst;
        while (current != NULL) {
            int cmp_result = key_comp(key, current->key);
            if (cmp_result == 0) {
                return current->data;
            } else if (cmp_result < 0) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return NULL;
}

void bstree_traverse(BStree bst) {
    if (bst != NULL && *bst != NULL) {
        BStree_node* current = *bst;
        bstree_traverse_helper(current);
    }
}

void bstree_traverse_helper(BStree_node* root) {
    if (root != NULL) {
        bstree_traverse_helper(root->left);
        key_print1(root->key);
        data_print(root->data);
        bstree_traverse_helper(root->right);
    }
}

void bstree_free(BStree bst) {
    if (bst != NULL && *bst != NULL) {
        BStree_node* current = *bst;
        bstree_free_helper(current);
        free(bst);
    }
}

void bstree_free_helper(BStree_node* root) {
    if (root != NULL) {
        bstree_free_helper(root->left);
        bstree_free_helper(root->right);
        key_free(root->key);
        data_free(root->data);
        free(root);
    }
}

