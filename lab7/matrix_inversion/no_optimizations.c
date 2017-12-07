#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 2048

float A[N][N];
static float elements[M + 1][N][N];
static float B[N][N];
static float R[N][N];
static float buf[N][N];
static float AI[N][N];
static int i, j;

void matrixMultiply(float a[N][N], float b[N][N])
{
    float s;
    int k;

    for (i = 0; i < N; i++)
    {
        for (k = 0; k < N; k++)
        {
            s = 0;
            for (j = 0; j < N; j++)
            {
                s += a[i][j] * b[j][k];
            }
            buf[i][k] = s;
        }
    }
}

void matrixAdd(float a[N][N], float b[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = a[i][j] + b[i][j];
        }
    }
}

void clearBuf()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = 0;
        }
    }
}

void transpose(float matrix[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = A[j][i];
        }
    }
}

void setMatrix(float matrix[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matrix[i][j] = buf[i][j];
        }
    }
}

int main()
{
    union ticks {
        uint64_t t64;
        struct s32
        {
            uint32_t th, tl;
        } t32;
    } start, end;
    double cpu_Hz = 2.1e9;
    int i, j;
    float q;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = (float)rand() * 2 - (float)RAND_MAX;
        }
    }

    asm("rdtsc\n"
        : "=a"(start.t32.th), "=d"(start.t32.tl));
    // Calculating q
    float q1 = 0, qinf = 0;
    int s;
    for (i = 0; i < N; i++)
    {
        s = 0;
        for (j = 0; j < N; j++)
        {
            s += A[i][j] > 0 ? A[i][j] : -A[i][j];
        }
        if (s > q1)
        {
            q1 = s;
        }
    }
    transpose(A);
    for (i = 0; i < N; i++)
    {
        s = 0;
        for (j = 0; j < N; j++)
        {
            s += buf[i][j] > 0 ? buf[i][j] : -buf[i][j];
        }
        if (s > qinf)
        {
            qinf = s;
        }
    }
    q = q1 * qinf;

    // Calculating B
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            B[i][j] = buf[i][j] / q;
        }
    }

    // Calculating R
    matrixMultiply(B, A);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            R[i][j] = -buf[i][j];
        }
    }
    for (i = 0; i < N; i++)
    {
        R[i][i] += 1;
    }

    // Calculating elements [1, R, R^2 ..]
    for (i = 0; i < N; i++)
    {
        elements[0][i][i] = 1;
    }
    for (i = 1; i < M; i++)
    {
        matrixMultiply(elements[i - 1], R);
        setMatrix(elements[i]);
    }

    //  (1 + R + R^2 + ..)B
    clearBuf();
    for (i = 0; i < M; i++)
    {
        matrixAdd(buf, elements[i]);
    }
    matrixMultiply(buf, B);
    setMatrix(AI);
    asm("rdtsc\n"
        : "=a"(end.t32.th), "=d"(end.t32.tl));
    printf("Calculation Time = %f sec\n", (end.t64 - start.t64) / cpu_Hz);
    for (int i = 0; i < N * N; i++)
    {
        if (i && !(i % N)) {
            printf("\n");
        }
        printf("%e ", AI[i / N][i % N]);
    }
    printf("\n");

    return 0;
}