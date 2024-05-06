#include <stdio.h>

// calculates n for the denominator of the equation
long long factorial(int n) {
    // base case
    if (n == 0 || n == 1) {
        return 1;
    } 
    // recursive
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    double epsilon, e = 1.0;
    int n = 1;   // chosen n value 

    printf("Enter e: ");
    scanf("%lf", &epsilon);

    while (1.0 / factorial(n) >= epsilon) {
        e += 1.0 / factorial(n);
        n++;
    }

    printf("Approximation of e: %.20f\n", e);
    return 0;
}

