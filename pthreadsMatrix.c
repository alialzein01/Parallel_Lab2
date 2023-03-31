#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 4 // Max number of matrices size

// Each thread computes single element in the resultant matrix
void *mult(void *arg)
{
    int *data = (int *)arg;
    int k = 0, i = 0;
    int x = data[0];
    for (i = 1; i <= x; i++)
        k += data[i] * data[i + x];
    int *p = (int *)malloc(sizeof(int));
    *p = k;
    pthread_exit(p);
}

int main()
{
    int matA[MAX][MAX];
    int matB[MAX][MAX];
    int i, j, k;
    // Inserting Random Values in Matrix A
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            matA[i][j] = rand() % 10;

    // Inserting Random Values in Matrix B
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            matB[i][j] = rand() % 10;

    // Printing Values of Matrix A
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", matA[i][j]);
        printf("\n");
    }

    // Printing Values of Matrix B
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", matB[i][j]);
        printf("\n");
    }

    int maxmax = MAX * MAX;

    // declaring array of threads of size MAX*MAX
    pthread_t *threads;
    threads = (pthread_t *)malloc(maxmax * sizeof(pthread_t));

    int count = 0;
    int *data = NULL;
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
        {

            // storing row and column elements in data
            data = (int *)malloc((20) * sizeof(int));
            data[0] = MAX;

            for (k = 0; k < MAX; k++)
                data[k + 1] = matA[i][k];

            for (k = 0; k < MAX; k++)
                data[k + MAX + 1] = matB[k][j];

            // creating threads
            pthread_create(&threads[count++], NULL,
                           mult, (void *)(data));
        }

    printf("Results: \n");
    for (i = 0; i < maxmax; i++)
    {
        void *k;

        // Joining all threads and collecting return value
        pthread_join(threads[i], &k);

        int *p = (int *)k;
        printf("%d ", *p);
        if ((i + 1) % MAX == 0)
            printf("\n");
    }

    return 0;
}
