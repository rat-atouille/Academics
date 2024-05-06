#include "datatype.h"
#include <stdlib.h>
#include <string.h>

Data data_ini() {
    Data new_data = (Data)malloc(sizeof(float));
    if (new_data != NULL) {
        *new_data = 0.0;
    }
    return new_data;
}

void data_set(Data data, float intdata) {
    if (data != NULL) {
        *data = intdata;
    }
}

void data_print(Data data) {
    if (data != NULL) {
        printf("Data: %.2f\n", *data);
    }
}

void data_free(Data data) {
    free(data);
}

Key key_ini() {
    Key new_key = (Key)malloc(sizeof(Key_struct));
    if (new_key != NULL) {
        new_key->key1 = NULL;
        new_key->key2 = 0;
    }
    return new_key;
}

void key_set(Key key, Key1 key1, Key2 key2) {
    if (key != NULL) {
        free(key->key1);
        key->key1 = strdup(key1);
        key->key2 = key2;
    }
}

int key_comp(Key key1, Key key2) {
    if (key1 != NULL && key2 != NULL) {
        int cmp_result = strcmp(key1->key1, key2->key1);
        if (cmp_result != 0) {
            return cmp_result;
        }
        return key1->key2 - key2->key2;
    }
    return 0;
}

void key_print1(Key key) {
    if (key != NULL) {
        printf("Key1: %s\n", key->key1);
        printf("Key2: %d\n", key->key2);
    }
}

void key_print2(Key key) {
    if (key != NULL) {
        printf("Key2: %d\n", key->key2);
        printf("Key1: %s\n", key->key1);
    }
}

void key_free(Key key) {
    if (key != NULL) {
        free(key->key1);
        free(key);
    }
}

