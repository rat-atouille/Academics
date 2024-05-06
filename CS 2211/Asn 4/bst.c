#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// Input: ’size’: size of an array
// Output: a BStree,
// Effect: allocate memory for a Node array of size+1 for member tree_nodes
// allocate memory for an unsigned char array of size+1 for member is_free
// set all entries of is_free to 1
// set member size to ’size’;
BStree bstree_ini(int size) {
    BStree bst;

    bst.tree_nodes = (Node*)malloc((size + 1) * sizeof(Node));
    bst.is_free = (unsigned char*)malloc((size + 1) * sizeof(unsigned char));

    for (int i = 0; i <= size; i++) {
        bst.is_free[i] = 1;
    }

    bst.size = size;
    return bst;
}

void insert_node(BStree bst, int index, Key key, int data) {
   // printf("11\n");
    if (index <= bst.size && bst.is_free[index]) {
       // printf("**\n");
        // insert the node
        bst.tree_nodes[index].key = key;
        bst.tree_nodes[index].data = data;
        bst.is_free[index] = 0;  
    } else {
        // Compare the key 
        int compare_result = key_comp(key, bst.tree_nodes[index].key);

        if (compare_result < 0) {
            // smaller, go left 
            insert_node(bst, 2 * index, key, data);
        } else if (compare_result > 0) {
            // larger, go right 
            insert_node(bst, 2 * index + 1, key, data);
        }
    }
}

// Input: ’bst’: a binary search tree
// ’key’: a Key
// ’data’: an integer
// Effect: ’data’ with ’key’ is inserted into ’bst’
// if ’key’ is already in ’bst’, do nothing

void bstree_insert(BStree bst, Key key, int data) {
    // Start the recursive insertion from the root node (index 1)
    insert_node(bst, 1, key, data);
}


void traversal(BStree bst, int index) {
    if (index <= bst.size && !bst.is_free[index]) {
        // left 
        traversal(bst, 2 * index);

        // current node
        print_node(bst.tree_nodes[index]);

        // Traverse right 
        traversal(bst, 2 * index + 1);
    }
}
 
// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) {
    traversal(bst, 1);  // start from the root    
}

// Input: ’bst’: a binary search tree
// Effect: all dynamic memory used by bst are freed
void bstree_free(BStree bst) {
    for (int i = 1; i <= bst.size; ++i) {
        if (bst.is_free[i] != 1) {
            free(bst.tree_nodes[i].key.name); 
        }
    }
    free(bst.tree_nodes);  
    free(bst.is_free); 
}

