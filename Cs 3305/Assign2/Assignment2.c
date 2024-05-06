#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int port1[2];
    int port2[2];
    pid_t pid;
    int X, Y, Z, A, B, C, D, total;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <4-digit integer> <4-digit integer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // input
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("Your integers are %d %d\n", a, b);
    
    int a1 = a / 100;
    int a2 = a % 100;
    int b1 = b / 100;
    int b2 = b % 100;
    
    int n = 4;
    
    //pipe(port); // pipeline
    
    if (pipe(port1) < 0 || pipe(port2) < 0){
        perror("pipe2 error");
        exit(0);
    }
    
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(0);
    }
    
    // parent
    if (pid > 0) {
        
        printf("Parent (PID %d): created child (PID %d)\n", getpid(), pid);

        // calculate X
        printf("\n###\nCalculate X\n###\n");

        // write a1 and b1 to pipe
        printf("Parent (PID %d): Sending %d to child \n", getpid(), a1);
        write(port1[1], &a1, sizeof(int));
        
        printf("Parent (PID %d): Sending %d to child \n", getpid(), b1);
        write(port1[1], &b1, sizeof(int));

        // Get X
        read(port2[0], &A, sizeof(int));
        printf("Parent (PID %d): Received %d from child\n", getpid(), A);
        
        // calculate X
        X = A * (10*10*10*10);
        
        // calculate Y
        printf("\n###\nCalculate Y\n###\n");

        // write a2 and b1 to pipe
        printf("Parent (PID %d): Sending %d to child \n", getpid(), a2);
        write(port1[1], &a2, sizeof(int));
        printf("Parent (PID %d): Sending %d to child \n", getpid(), b1);
        write(port1[1], &b1, sizeof(int));
        
        // Get B
        read(port2[0], &B, sizeof(int));
        printf("Parent (PID %d): Received %d from child\n", getpid(), B);

        // write a1 b2
        printf("Parent (PID %d): Sending %d to child \n", getpid(), a1);
        write(port1[1], &a1, sizeof(int));
        printf("Parent (PID %d): Sending %d to child \n", getpid(), b2);
        write(port1[1], &b2, sizeof(int));
        
        // Get C
        read(port2[0], &C, sizeof(int));
        printf("Parent (PID %d): Received %d from child\n", getpid(), C);
        
        // calculate Y
        Y = (B+C)* (10*10);
        
        // calculate Z
        printf("\n###\nCalculate Z\n###\n");

        // write a2 b2
        printf("Parent (PID %d): Sending %d to child \n", getpid(), a2);
        write(port1[1], &a2, sizeof(int));
        printf("Parent (PID %d): Sending %d to child \n", getpid(), b2);
        write(port1[1], &b2, sizeof(int));
        
        // Get D
        read(port2[0], &D, sizeof(int));
        printf("Parent (PID %d): Received %d from child\n", getpid(), D);

        // calculate Z
        Z = D*1;
        
        printf("\n %d * %d == %d + %d + %d == %d \n", a,b, X,Y,Z, X+Y+Z);
        
        // close
        close(port1[1]);
        close(port2[0]);
    }
        
    
    // child
    if (pid == 0){
        
    // get a1 and b1 from pipe
        read (port1[0], &a1, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), a1);
        
        read (port1[0], &b1, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), b1);

        // calculate A and send A to parent
        A = a1*b1;
        write(port2[1], &A, sizeof(int));
        printf("    Child (PID %d): Sending %d to parent\n", getpid(), A);

        // get a2 and b1 from pipe
        read (port1[0], &a2, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), a2);
        read (port1[0], &b1, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), b1);
        
        // calculate B and send B to parent
        B = a2 * b1;
        write(port2[1], &B, sizeof(int));
        printf("    Child (PID %d): Sending %d to parent\n", getpid(), B);

        // get a1 and b2 from pipe
        read (port1[0], &a1, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), a1);
        read (port1[0], &b2, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), b2);
        
        // calculate C and send C to parent
        C = a1 * b2;
        write(port2[1], &C, sizeof(int));
        printf("    Child (PID %d): Sending %d to parent\n", getpid(), C);
    
        // get a2 and b2 from pipe
        read (port1[0], &a2, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), a2);
        read (port1[0], &b2, sizeof(int));
        printf("    Child (PID %d): Received %d from parent \n", getpid(), b2);
        
        // calculate D and send D to parent
        D = a2 * b2;
        write(port2[1], &D, sizeof(int));
        printf("    Child (PID %d): Sending %d to parent\n", getpid(), D);
        
        // close
        close(port1[1]);
        close(port2[0]);
        
        exit(EXIT_SUCCESS);
    }
     
    return 0;
}

