#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initialize M as given in the example
    int **M = (int **)malloc(2 * sizeof(int *));
    M[0] = (int *)malloc(5 * sizeof(int));
    M[1] = (int *)malloc(5 * sizeof(int));

    // Assign values to M[0] and M[1]
    M[0][0] = 1; M[0][1] = 2; M[0][2] = 3; M[0][3] = 4; M[0][4] = 5;
    M[1][0] = 5; M[1][1] = 6; M[1][2] = 7; M[1][3] = 8; M[1][4] = 9;

    // Function to swap the arrays along axis 0
    for (int i = 0; i < 5; ++i) {
        int temp = *(*(M + 0) + i);
        *(*(M + 0) + i) = *(*(M + 1) + (4 - i));
        *(*(M + 1) + (4 - i)) = temp;
    }

    // Display the swapped arrays
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d ", *(*(M + i) + j));
        }
        printf("\n");
    }

    // Free allocated memory
    free(M[0]);
    free(M[1]);
    free(M);

    return 0;
}
