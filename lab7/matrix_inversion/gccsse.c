#include <stdio.h>
#include <stdlib.h>

#define N 8
#define M 10

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

void vector_mult_scal(vector v1, float scal)
{
    for (int i = 0; i < N / 4; i++)
    {
        v1[i] *= scal;
    }
}

void vector_sum(vector v1, vector v2)
{
    for (int i = 0; i < N / 4; i++)
    {
        v1[i] += v2[i];
    }
}

vector r_buf;
float vector_reduce(vector v)
{
    vector_assign(r_buf, v);
    for (int i = 1; i < N / 4; i++)
    {
        r_buf[0] += r_buf[i];
    }
    float res = 0;
    for (int i = 0; i < 4; i++)
    {
        res += r_buf[0][i];
    }
    return res;
}

void matrix_transpose(matrix m, matrix buf)
{
    for (int i = 0; i < N * N; i++)
    {
        matrix_setxy(buf, i % N, i / N, matrix_getxy(m, i / N, i % N));
    }
}

void matrix_abs(matrix m, matrix buf)
{
    for (int i = 0; i < N * N; i++)
    {
        float val = matrix_getxy(m, i / N, i % N);
        matrix_setxy(buf, i % N, i / N, val >= 0 ? val : -val);
    }
}

void matrix_mult_scal(matrix a, matrix buf, float scal)
{
    for (int i = 0; i < N; i++)
    {
        vector_assign(buf[i], a[i]);
        vector_mult_scal(buf[i], scal);
    }
}

vector curr_line;
matrix bT;

void matrix_mult(matrix a, matrix b, matrix buf)
{
    matrix_transpose(b, bT);

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            vector_assign(curr_line, a[k]);
            vector_mult(curr_line, bT[i]);
            float reduce = vector_reduce(curr_line);
            matrix_setxy(buf, k, i, reduce);
        }
    }
}

void matrix_set(matrix m, matrix init)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix_setxy(m, j, i, matrix_getxy(init, j, i));
        }
    }
}

void matrix_add(matrix a, matrix b, matrix buf)
{
    for (int i = 0; i < N; i++)
    {
        vector_assign(buf[i], a[i]);
        vector_sum(buf[i], b[i]);
    }
}

void matrix_print(matrix m)
{
    for (int i = 0; i < N * N; i++)
    {
        printf("%e ", matrix_getxy(m, i % N, i / N));
        if (!((i + 1) % N))
        {
            printf("\n");
        }
    }
    printf("\n");
}

matrix Aabs, AT;
float calculate_q(matrix A)
{
    matrix_abs(A, Aabs);
    matrix_transpose(Aabs, AT);
    float sum, sumT, max = 0, maxT = 0;
    for (int i = 0; i < N; i++)
    {
        sum = vector_reduce(Aabs[i]);
        if (sum > max)
        {
            max = sum;
        }
        sumT = vector_reduce(AT[i]);
        if (sumT > maxT)
        {
            maxT = sumT;
        }
    }
    float q = max * maxT;
}

matrix A, B, BA, R, E, buf, R_degrees, SUM;

int main()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //float rand_val = (float)rand() * 2 - (float)RAND_MAX;
            float rand_val = 1;
            matrix_setxy(A, j, i, i == j ? 4 : 0);
        }
    }
    float q = calculate_q(A);
    matrix_transpose(A, B);
    matrix_mult_scal(B, B, 1 / q);
    matrix_mult(B, A, BA);
    matrix_mult_scal(BA, BA, -1);

    // E
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix_setxy(E, i, j, (i == j) ? 1 : 0);
        }
    }

    matrix_add(E, BA, R);
    matrix_set(SUM, E);
    matrix_set(R_degrees, R);

    for (int i = 0; i < M; i++)
    {
        matrix_add(SUM, R_degrees, SUM);
        matrix_mult(R_degrees, R, buf);
        matrix_set(R_degrees, buf);
    }

    matrix_mult(SUM, B, buf);
    matrix_print(buf);
}