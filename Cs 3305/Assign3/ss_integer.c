#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char segments[10][3][3] = {
       { {' ','_',' '},{'|',' ','|'},{'|','_','|'} }, //0
        { {' ',' ',' '},{' ','|',' '},{' ','|',' '} }, //1
        { {' ','_',' '},{' ','_','|'},{'|','_',' '} }, //2
        {{' ','_',' '},{' ','_','|'},{' ','_','|'} }, //3
        { {' ',' ',' '},{'|','_','|'},{' ',' ','|'} },  //4
        { {' ','_',' '},{'|','_',' '},{' ','_','|'} },  //5
        { {' ','_',' '},{'|','_',' '},{'|','_','|'} }, //6
        { {' ','_',' '},{' ',' ','|'},{' ',' ','|'} }, //7
        { {' ','_',' '},{'|','_','|'},{'|','_','|'} }, //8
        { {' ','_',' '},{'|','_','|'},{' ','_','|'} }, //9
    };

    char c;
    int x;
    char tmp[10];

    while (true) {
        printf("Enter an integer: ");
        scanf("%d",&x);
        sprintf(tmp, "%d", x);

        for (int m = 0; m < 3; m++) {
            for (int i = 0; i < strlen(tmp); i++) {
                for (int n = 0; n < 3; n++){
                    printf("%c ", segments[tmp[i]-'0'][m][n]);
                }
            }
            printf("\n");
        }

       printf("\nEnter Y to continue or N to quit: ");
       scanf(" %c", &c);
       
        if (c == 'Y'){
            printf("Continue \n");
        }
        else if (c == 'N'){
            printf("Quit");
            return false;
        }
   }
    return 0;
}

