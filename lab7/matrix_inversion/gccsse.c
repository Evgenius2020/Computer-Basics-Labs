#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 10

#define matrix_initialize(m, value) \
    for (int i = 0; i < N; i++)     \
        for (int j = 0; j < N; j++) \
    matrix_setxy(m, i, j, value)

#define abs(value) value > 0 ? value : -value

typedef float __attribute__((vector_size(4 * 4))) vector[N / 4];
typedef vector matrix[N];

float matrix_getxy(matrix m, int x, int y)
{
    return m[y][x / 4][x % 4];
}

void matrix_setxy(matrix m, int x, int y, float value)
{
    m[y][x / 4][x % 4] = value;
}

float vector_getx(vector v, int k)
{
    return v[k / N][k % N];
}

void vector_clear(vector v)
{
    for (int i = 0; i < N; i++)
    {
        v[i / 4][i % 4] = 0;
    }
}

void vector_assign(vector v1, vector v2)
{
    for (int i = 0; i < N; i++)
    {
        v1[i / 4][i % 4] = v2[i / 4][i % 4];
    }
}

void vector_mult(vector v1, vector v2)
{
    for (int i = 0; i < N / 4; i++)
    {
        v1[i] *= v2[i];
    }
}

void vector_sum(vector v1, vector v2)
{
    for (int i = 0; i < N / 4; i++)
    {
        v1[i] += v2[i];
    }
}

float vector_reduce(vector v)
{
    vector buf;
    vector_assign(buf, v);
    for (int i = 1; i < N / 4; i++)
    {
        buf[0] += buf[i];
    }
    float res = 0;
    for (int i = 0; i < 4; i++)
    {
        res += buf[0][i];
    }
    return res;
}

void matrix_multiply(matrix a, matrix b, matrix buf)
{
    vector curr_line;

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            vector_assign(curr_line, a[k]);
            vector_mult(curr_line, b[i]);
            float reduce = vector_reduce(curr_line);
            matrix_setxy(buf, k, i, reduce);
        }
    }
}

int main()
{
    matrix A;
    for (int i = 0; i < N * N; i++)
    {
        matrix_setxy(A, i % N, i / N, i + 1);
    }
    matrix buf;
    matrix_multiply(A, A, buf);

    for (int i = 0; i < N * N; i++)
    {
        printf("%e ", matrix_getxy(buf, i % N, i / N));
        if (!((i + 1) % N))
        {
            printf("\n");
        }
    }
    printf("\n");
}