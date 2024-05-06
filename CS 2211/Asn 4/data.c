#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Input: ’in_name’: a string ends with ’\0’
// ’in_num’: an integer
// Output: a Key,
// Effect: copy in_name to Key’s name
// set Key’s num to be in_num
Key key_construct(char *in_name, int in_num) {
    Key key;
    key.name = malloc(strlen(in_name) + 1);
    strcpy(key.name, in_name);
    key.num = in_num;
    
    return key;
}

// if return value > 0, then key1 > key2,
// Note: use strcmp() to compare key1.name and key2.name
// if key1.name = key2.name, then compare key1.num with key2.num
int key_comp(Key key1, Key key2) {
   // printf("*comp*\n");
    
    int result = strcmp(key1.name, key2.name);
    //printf("%d\n", result);
    if (result == 0) {
        printf("Same \n");
    }
    else if (result > 0) {
        printf("key 1 > 2 \n");
    }
    else {
        printf("key 1 < 2 \n");
    }
    return result;

}
// Input: ’key’: a Key
// Effect: key.num key.name are printed
void print_key(Key key) {
    //printf("*print*\n");
    printf("Key number %d, name: %s \n", key.num, key.name);
}

// Input: ’node’: a node
// Effect: node.key is printed and then the node.data is printed
void print_node(Node node) {
    printf("Node key: %s \n", node.key);
    //printf("why is not printing");
    printf("Node data: %d \n", node.data);
}
