#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ACCOUNTS 4

int accounts[NUM_ACCOUNTS];
pthread_mutex_t mutex[NUM_ACCOUNTS];

// Function to process transactions for a specific ATM
void* process_transactions(void* arg) {
    FILE* file = (FILE*)arg;
    int account, amount;
    
    while (fscanf(file, "%d %d", &account, &amount) == 2) {
        pthread_mutex_lock(&mutex[account - 1]); // Lock the account being accessed
        if ((accounts[account - 1] + amount) >= 0) {
            accounts[account - 1] += amount;
            printf("\nThread %d:\n", account);
            if (amount >= 0) // if Deposit
                printf("    Deposit $%d to Account %d\n", amount, account);
            else // if Withdraw
                printf("    Withdraw $%d from Account %d\n", -amount, account);
            printf("    Account %d: $%d\n", account, accounts[account - 1]);
        } else { // if Insufficient funds
            printf("\nThread %d:\n", account);
            if (amount >= 0)
                printf("    Deposit $%d to Account %d\n", amount, account);
            else
                printf("    Withdraw $%d from Account %d\n", -amount, account);
            printf("    *** INSUFFICIENT FUNDS ***\n");
            printf("    Account %d: $%d\n", account, accounts[account - 1]);
        }
        pthread_mutex_unlock(&mutex[account - 1]); // release the lock
    }
    
    pthread_exit(NULL); // exit from all threads
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) { // take input from command line
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r"); // file open
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // read starting balances from the first line
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        fscanf(file, "%d", &accounts[i]);
    }
    
    // Initialize mutexes
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        pthread_mutex_init(&mutex[i], NULL);
    }
    
    // print starting balances
    printf("Initial Balances\n");
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        printf("    Account %d: $%d\n", i + 1, accounts[i]);
    }
    
    // launch threads to process transactions for each ATM
    pthread_t threads[NUM_ACCOUNTS];
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        pthread_create(&threads[i], NULL, process_transactions, file);
    }
    
    // wait for all threads to finish
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // print ending balances
    printf("\nFinal Balances\n");
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        printf("    Account %d: $%d\n", i + 1, accounts[i]);
    }

    // destroy mutexes
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        pthread_mutex_destroy(&mutex[i]);
    }

    fclose(file); // close file when done

    return 0;
}

