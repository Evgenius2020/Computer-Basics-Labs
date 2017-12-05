#include <cblas.h>
#include <stdlib.h>
#include <stdio.h>

#define M 10
#define N 2

float A[N][N] = {{7, -4}, { 5, 3}};
float E[N][N];
float AT[N][N];
float SUM[N][N];
float R[N][N];
float RES[N][N];

float calculateQ()
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

int main()
{
    int i;
    // for (i = 0; i < N * N; i++)
    // {
    //     A[i / N][i % N] = i;
    // }

    // E
    for (i = 0; i < N; i++)
    {
        E[i][i] = 1;
    }

    // AT
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, &A[0][0], N, &E[0][0], N, 1.0, &AT[0][0], N);
    float q = calculateQ();
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, &A[0][0], N, &E[0][0], N, 1.0, &AT[0][0], N);
    
    // R = -q * AT * A + E
    cblas_ccopy(N * N, E, 1, R, 1);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, -q, &AT[0][0], N, &A[0][0], N, 1.0, &R[0][0], N);

    // SUM = (I + R + R^2 + ...) * B , B = q * AT
    cblas_ccopy(N * N, E, 1, SUM, 1);
    for (i = 0; i < M; i++)
    {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, &SUM[0][0], N, &R[0][0], N, 1.0, &SUM[0][0], N);
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, q, &SUM[0][0], N, &AT[0][0], N, 1.0, &RES[0][0], N);

    for (i = 0; i < N * N; i++)
    {
        if (i && !(i % N)) {
            printf("\n");
        }
        printf("%e ", RES[i / N][i % N]);
    }
    printf("\n");

    return 0;
}