#include "matrix.h"
#include <stdio.h>

int main() {
    Matrix my_matrix = matrix_construction();

    printf("Enter integer string pairs (Ctrl+D to terminate input):\n");

    int num;
    char str[100];

    while (scanf("%d", &num) != EOF) {
        scanf(" %[^\n]", str); 


        char index[100];
        sprintf(index, "%d %s", num, str);
        if (matrix_index_in(my_matrix, index, num)) {
            Value* count = matrix_get(my_matrix, index, num);
            (*count)++;
        } else {
            matrix_set(my_matrix, index, num, 1);
        }
    }

    printf("\nNumber Street Occurrence\n");
    matrix_list(my_matrix);

    matrix_destruction(my_matrix);

    return 0;
}

