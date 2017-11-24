#include <xmmintrin.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 12

float inner2(float *x, float *y, int n)
{
    __m128 *xx, *yy;
    __m128 p, s;
    xx = (__m128 *)x;
    yy = (__m128 *)y;
    s = _mm_setzero_ps();
    for (int i = 0; i < n / 4; ++i)
    {
        p = _mm_mul_ps(xx[i], yy[i]);
        s = _mm_add_ps(s, p);
    }
    p = _mm_movehl_ps(p, s);
    s = _mm_add_ps(s, p);
    p = _mm_shuffle_ps(s, s, 1);
    s = _mm_add_ss(s, p);
    float sum;
    _mm_store_ss(&sum, s);
    
    return sum;
}

int main()
{
    float *left = malloc(sizeof(float) * SIZE);
    float *right = malloc(sizeof(float) * SIZE);

    for (int i = 0; i < SIZE; ++i)
    {
        left[i] = i + 1;
        right[i] = i + 1;
    }
    float sum = inner2(left, right, SIZE);
    printf("%f\n", sum);

    free(left);
    free(right);
    return 0;
}
