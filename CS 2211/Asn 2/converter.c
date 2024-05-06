# include <stdio.h>
# include <stdbool.h>

float conver(int i);

int main()
{
        int i;
        char ch;
        bool flag = true;
        float x;

        while (flag){
          printf("Type an integer for a conversion: ");
          scanf("%d",&i);

          if (i==1) {
                //printf("Celcius and Fahrenheit Conversion - type C or F \n");
                printf("~Cel and Fahren Conversion~ \n");
                x = conver(i);
                printf("Converted: %f \n", x);
                flag = false;
          }

          else if (i==2) {
                printf("~Cm and In Conversion~ \n");
                x = conver(i);
                printf("Converted: %f \n", x);
                flag = false; 
          }

          else if (i==3) {
                printf("~Km and Mi Conversion~ \n");
                x = conver(i);
                printf("Converted: %f \n", x);
                flag = false;
          }

          else if (i==4) {
                printf("~Liter and Gallon~ \n");
                x = conver(i);
                printf("Converted: %f \n", x);
                flag = false;
          }

          else if (i==0) {
                printf("Quit \n");
                flag = false;}
        }

        return 0;
}



float conver(int i){
        float convert,f;
        bool flag = true;
        char ch;

        printf("Enter a floating number for desired conversion: ");
        scanf("%f",&f);
        
        while (flag == true) {
        
        printf("Enter a character: ");
        scanf(" %c",&ch);

        /* Cel and Faren*/
          if (i == 1) {
                /* C > F */
                if (ch == 'C') {
                convert = (f*(9.0f/5.0f))+32;
                flag = false;
                return convert;
                }

                /* F > C */
                else if (ch == 'F'){
                flag = false;
                return convert = (5.0f/9.0f)*(f-32);
                }
         }

        /* Cm and in */
          if (i==2) {
                /*Cm to inch */
                if (ch == 'C') {
                    flag = false;
                    return convert = (f/2.54);
                }


                /* inch to cm*/
                else if (ch == 'I') {
                    flag = false;
                    return convert = (f*2.54);
                }
          }

        /* Km and Mile */

            if (i==3) {

                /* km > mi */
                if (ch == 'K') {
                    flag = false;
                    return convert = f * 0.621371;
            }
                else if (ch=='M'){
                    flag = false;
                    return convert = f * 1.60934;    
                         }
            }

            /* Gallon and litre*/
            if (i==4) {
                 /* G > L */
                if (ch=='G') {
                    flag = false;
                    return convert = f*3.785412;
                }

                /* L > G */
                else if (ch=='L') {
                    flag = false;
                    return convert = f * 0.264172; }
            }
        
        }
}
