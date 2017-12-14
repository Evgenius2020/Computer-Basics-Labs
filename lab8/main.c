#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define K 10
#define L 1000

float calculate_average_time(int *mass, int size)
{
    union ticks {
        uint64_t t64;
        struct s32
        {
            uint32_t th, tl;
        } t32;
    } start, end;

    double total_clocks = 0;
    int x = 0;
    
    for (int k = 0; k < K; k++)
    {
        asm("rdtsc\n"
            : "=a"(start.t32.th), "=d"(start.t32.tl));
        for (int j = 0; j < size / 1000; j++)
        {
            for (int i = 0; i < 1000; i++)
            {
                x = mass[x];
            }
        }
        asm("rdtsc\n"
            : "=a"(end.t32.th), "=d"(end.t32.tl));
        total_clocks += (end.t64 - start.t64);
    }

    return total_clocks / (size * K);
}

void main()
{
    int max = 2097152; /*6mb*/
    int step_size = max / L;
    for (int N = step_size; N <= max; N += step_size)
    {
        int *mass = malloc(sizeof(int) * N);

        printf("%d ", N);

        for (int i = 0; i < N - 1; i++)
        {
            mass[i] = i + 1;
        }
        mass[N - 1] = 0;
        printf("%f ", calculate_average_time(mass, N));

        for (int i = 1; i < N; i++)
        {
            mass[i] = i - 1;
        }
        mass[0] = N - 1;
        printf("%f ", calculate_average_time(mass, N));

        srand(time(NULL));
        for (int i = N - 1; i > 0; i--)
        {
            int j = rand() % i;
            if (i == j)
            {
                continue;
            }
            int buf = mass[i];
            mass[i] = mass[j];
            mass[j] = buf;
        }
        printf("%f ", calculate_average_time(mass, N));

        printf("\n");

        free(mass);
    }
}