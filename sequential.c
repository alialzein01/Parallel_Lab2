#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000
#define N 1000
#define P 1000

int matrix1[M][N];
int matrix2[N][P];
int result[M][P];

void print_matrix(double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%6.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j, k;
    clock_t start, end;
    double e_time;
    srand(time(NULL));
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            matrix1[i][j] = rand() % 100;
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < P; j++)
        {
            matrix2[i][j] = rand() % 100;
        }
    }

    // Perform matrix multiplication
    start = clock();
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < P; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < N; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    end = clock();

    // Print resulting matrix
    printf("Resulting matrix: ");
    print_matrix(result, M, P);

    // Calculate and print elapsed time
    e_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %lf seconds\n", e_time);

    return 0;
}