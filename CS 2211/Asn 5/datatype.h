#ifndef DATATYPE_H
#define DATATYPE_H

typedef char* Key1;
typedef int Key2;
typedef float* Data;

typedef struct {
    Key1 key1;
    Key2 key2;
} Key_struct;

typedef Key_struct* Key;

Data data_ini();
void data_set(Data data, float intdata);
void data_print(Data data);
void data_free(Data data);

Key key_ini();
void key_set(Key key, Key1 key1, Key2 key2);
int key_comp(Key key1, Key key2);
void key_print1(Key key);
void key_print2(Key key);
void key_free(Key key);

#endif 
