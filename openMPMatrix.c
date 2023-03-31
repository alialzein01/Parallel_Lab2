#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiply_matrices(double **A, double **B, double **C, int M, int N, int P)
{
#pragma omp parallel for
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < P; j++)
        {
            double sum = 0;
            for (int k = 0; k < N; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

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
    int M = 3;
    int N = 3;
    int P = 3;

    double **A = (double **)malloc(M * sizeof(double *));
    double **B = (double **)malloc(N * sizeof(double *));
    double **C = (double **)malloc(M * sizeof(double *));

    for (int i = 0; i < M; i++)
    {
        A[i] = (double *)malloc(N * sizeof(double));
    }

    for (int i = 0; i < N; i++)
    {
        B[i] = (double *)malloc(P * sizeof(double));
    }

    for (int i = 0; i < M; i++)
    {
        C[i] = (double *)malloc(P * sizeof(double));
    }

    // Initialize the matrices with random values
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            B[i][j] = rand() % 10;
        }
    }

    multiply_matrices(A, B, C, M, N, P);

    printf("Matrix A:\n");
    print_matrix(A, M, N);
    printf("\nMatrix B:\n");
    print_matrix(B, N, P);
    printf("\nMatrix C (result):\n");
    print_matrix(C, M, P);

    // Free the memory
    for (int i = 0; i < M; i++)
    {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < N; i++)
    {
        free(B[i]);
    }
    free(B);

    for (int i = 0; i < M; i++)
    {
        free(C[i]);
    }
    free(C);

    return 0;
}
