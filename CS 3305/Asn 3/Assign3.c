#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 27
#define GRID_SIZE 9

int sudoku_grid[GRID_SIZE][GRID_SIZE];
int valid[NUM_THREADS] = {0};

// Function to check the validity of rows in the Sudoku grid
void *check_rows(void *arg) {
    int row = *(int *)arg;
    int seen[GRID_SIZE] = {0};

    for (int col = 0; col < GRID_SIZE; col++) {
        int num = sudoku_grid[row][col];
        if (seen[num - 1]) {
            valid[row] = 0;
            pthread_exit(NULL);
        } else {
            seen[num - 1] = 1;
        }
    }

    valid[row] = 1;
    pthread_exit(NULL);
}

// Function to check the validity of columns in the Sudoku grid
void *check_columns(void *arg) {
    int col = *(int *)arg;
    int seen[GRID_SIZE] = {0};

    for (int row = 0; row < GRID_SIZE; row++) {
        int num = sudoku_grid[row][col];
        if (seen[num - 1]) {
            valid[GRID_SIZE + col] = 0;
            pthread_exit(NULL);
        } else {
            seen[num - 1] = 1;
        }
    }

    valid[GRID_SIZE + col] = 1;
    pthread_exit(NULL);
}

// Function to check the validity of subgrids in the Sudoku grid
void *check_subgrid(void *arg) {
    int subgrid = *(int *)arg;
    int seen[GRID_SIZE] = {0};
    int start_row = (subgrid / 3) * 3;
    int start_col = (subgrid % 3) * 3;

    for (int i = start_row; i < start_row + 3; i++) {
        for (int j = start_col; j < start_col + 3; j++) {
            int num = sudoku_grid[i][j];
            if (seen[num - 1]) {
                valid[2 * GRID_SIZE + subgrid] = 0;
                pthread_exit(NULL);
            } else {
                seen[num - 1] = 1;
            }
        }
    }

    valid[2 * GRID_SIZE + subgrid] = 1;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file containing the Sudoku grid
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("File opening failed");
        return 1;
    }

    // Read the Sudoku grid from the file
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            fscanf(file, "%d", &sudoku_grid[i][j]);
        }
    }
    fclose(file);

    // Declare arrays for thread IDs and thread arguments
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Create threads to check rows, columns, and subgrids
    for (int i = 0; i < GRID_SIZE; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, check_rows, &thread_args[i]);
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        thread_args[i] = i;
        pthread_create(&threads[GRID_SIZE + i], NULL, check_columns, &thread_args[i]);
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        thread_args[i] = i;
        pthread_create(&threads[2 * GRID_SIZE + i], NULL, check_subgrid, &thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Check if the Sudoku solution is valid
    int valid_solution = 1;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (!valid[i]) {
            valid_solution = 0;
            break;
        }
    }

    // Print results for each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i < GRID_SIZE) {
            printf("Thread # %2d (row %d) is %s\n", i + 1, i + 1, valid[i] ? "valid" : "INVALID");
        } else if (i < 2 * GRID_SIZE) {
            printf("Thread # %2d (column %d) is %s\n", i + 1, i - GRID_SIZE + 1, valid[i] ? "valid" : "INVALID");
        } else {
            printf("Thread # %2d (subgrid %d) is %s\n", i + 1, i - 2 * GRID_SIZE + 1, valid[i] ? "valid" : "INVALID");
        }
    }

    // Print overall validation result
    if (valid_solution) {
        printf("\nThe Sudoku solution in %s is valid.\n", argv[1]);
    } else {
        printf("\nThe Sudoku solution in %s is INVALID.\n", argv[1]);
    }

    return 0;
}

