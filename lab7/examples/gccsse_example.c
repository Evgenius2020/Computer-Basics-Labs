#include <stdio.h>
#define SIZE 4

typedef int v4si __attribute__((vector_size(4*SIZE)));

float scal_sum(v4si left, v4si right)
{
    float r = 0;
    left *= right;
    for (int i = 0; i < SIZE; ++i) {
        r +=  left[i];
    }

    return r;
}

int main() {
    v4si left;
    v4si right;
    for (int i = 0; i < SIZE; ++i) {
        left[i] = i + 1;
        right[i] = i + 1;
    }

    float res = scal_sum(left, right);
    printf("%f\n", res);

    return 0;
}