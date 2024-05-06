#include <stdio.h>

unsigned long power(int n);


int main() {

        int n,i;
        unsigned long l;

        printf("Type an integer for the exponent: ");
        scanf("%d",&n);
        l = power(n);
        printf("2 power of %d is %lu \n", n, l);
        }


unsigned long power(int n) {
    
    // base case
    if (n == 0) {
        return 1;
    }
    
    //even
    else if (n % 2 == 0){
      return (power(n/2)* power(n/2));   }
      
    //odd
    else if (n % 2 != 0) {
       return (power((n-1)/2)*power((n-1)/2))*2;
       }

}


