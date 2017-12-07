#include <cblas.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define M 10
#define N 2048

float A[N][N];
float E[N][N];
float AT[N][N];
float SUM[N][N];
float R[N][N];
float BUF[N][N];

float calculate_q()
{
    float sum, sumT;
    float max, maxT;
    for (int i = 0; i < N; i++)
    {
        if (max < (sum = cblas_sasum(N, A[i], 1)))
        {
            max = sum;
        }
        if (maxT < (sumT = cblas_sasum(N, AT[i], 1)))
        {
            maxT = sumT;
        }
    }
    return 1 / (max * maxT);
}

void print_matrix(float matrix[N][N])
{
    for (int i = 0; i < N * N; i++)
    {
        if (i && !(i % N))
        {
            printf("\n");
        }
        printf("%e ", matrix[i / N][i % N]);
    }
    printf("\n");
}

int main()
{
    int i;
    for (i = 0; i < N * N; i++)
    {
        A[i/N][i%N] = (float)rand() * 2 - (float)RAND_MAX;
    }

    // E
    for (i = 0; i < N; E[i][i] = 1, i++)
        ;

    // AT
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, &A[0][0], N, &E[0][0], N, 1.0, &AT[0][0], N);
    float q = calculate_q();

    // R = -q * AT * A + E
    for (i = 0; i < N; R[i][i] = 1, i++)
        ;
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, -q, &AT[0][0], N, &A[0][0], N, 1.0, &R[0][0], N);

    // SUM = (I + R + R^2 + ...) * B , B = q * AT
    for (i = 0; i < N; SUM[i][i] = 1, i++)
        ;
    for (i = 0; i < M; i++)
    {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, &R[0][0], N, &E[0][0], N, 1.0, &SUM[0][0], N);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, &R[0][0], N, &R[0][0], N, 0.0, &BUF[0][0], N);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, &BUF[0][0], N, &E[0][0], N, 0.0, &R[0][0], N);
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, q, &SUM[0][0], N, &AT[0][0], N, 0.0, &BUF[0][0], N);

    return 0;
}