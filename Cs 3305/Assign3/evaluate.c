#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


// input: none, read from stdin
// Effect: get the next operator (+,-,'\n') of the expression
// output: return the next op
char get_op(void) {

    int c;
    bool found = false;

    // Iterate through the input
    while (!found) {
        c = getchar();

        if (c == EOF) {
           // printf("[]\n");
            return '\n'; // End of input
        } else if (c == '\n') {
            //printf("&&\n");
            return '\n';
        } else if (c == ' ') {
            //printf("bb\n");
            continue; // Skip spaces
        } else {
            found = true;
            //printf("from get_op function: %c \n", c);
            return (char)c;
        }
    }
}

// input: none, read from stdin
// effect: get the next numeric value of the expression
// output: return the next numeric value of the express
float get_num(void) {
    float num;
    scanf("%f", &num);
    return num;
}

//Input: sub_exp - value of current sub simple arithmetic expression left of the next operator
// effect: arithmetic is evaluated using recursion
// output: returns the value of the simple arithmetic expression
float sub_sim_exp(float sub_exp) {
    char next_op = get_op();

    if (next_op == '\n') {
        return sub_exp;  // Base case: End of input, return the result
        
    } else if (next_op == '+' || next_op == '-') {
        float next_num = get_num();
            
        if (next_op == '+') {
            sub_exp += next_num;
        } else if (next_op == '-') {
            sub_exp -= next_num;
        }
        return sub_sim_exp(sub_exp); // Recursive call
    }   
    else {
        printf("Error: Invalid operator '%c'\n", next_op);
        exit(EXIT_FAILURE);
        }
}

//evaluate the simple arithmetic expression
float sim_exp(void) {
    float num = get_num();
    return sub_sim_exp(num);
}

int main() {
    char answer;
    while (true) {
        printf("Type arithmetic equation: ");
        float result = sim_exp();
        printf("Result: %f\n", result);
        printf("Type Y to continue or N to quit: \n");
        scanf("%c",&answer);
        if (answer == 'Y') {
            printf("Continue...\n");
        }
        else if (answer == 'N'){
            printf("Quitting... \n");
            return false;
        }
    }
    return 0;
}

