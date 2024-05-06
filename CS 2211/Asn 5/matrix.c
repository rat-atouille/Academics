#include "matrix.h"

Matrix matrix_construction(void) {
    return bstree_ini();
}

unsigned char matrix_index_in(Matrix m, Index1 index1, Index2 index2) {
    return bstree_search(m, (Key) new_node(index1, index2)) != NULL;
}

const Value* matrix_get(Matrix m, Index1 index1, Index2 index2) {
    Key search_key = (Key) new_node(index1, index2);
    Data result = bstree_search(m, search_key);
    return (result != NULL) ? result : NULL;
}

void matrix_set(Matrix m, Index1 index1, Index2 index2, Value value) {
    Key set_key = (Key) new_node(index1, index2);
    Data set_data = data_ini();
    *set_data = value;
    bstree_insert(m, set_key, set_data);
}

void matrix_list(Matrix m) {
    if (m != NULL && *m != NULL) {
        bstree_traverse_helper(*m);
    }
}

void matrix_destruction(Matrix m) {
    bstree_free(m);
}

