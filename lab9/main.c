#include <stdint.h>
#include <stdio.h>

#define CACHE_SIZE 393216// 3mb
#define OFFSET (CACHE_SIZE * 2)
#define SIZE (OFFSET * 32)

int mass[SIZE];

float calculate_average_time()
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

    asm("rdtsc\n"
        : "=a"(start.t32.th), "=d"(start.t32.tl));
    for (int j = 0; j < SIZE / 1000; j++)
    {
        for (int i = 0; i < 1000; i++)
        {
            x = mass[x];
        }
    }
    asm("rdtsc\n"
        : "=a"(end.t32.th), "=d"(end.t32.tl));
    total_clocks += (end.t64 - start.t64);

    return total_clocks / SIZE;
}

void initialize_mass(int blocks)
{
    const int BLOCK_SIZE = CACHE_SIZE / blocks;
    for (int el = 0; el < BLOCK_SIZE; el++)
    {
        for (int block = 0; block < blocks - 1; block++)
        {
            mass[block * OFFSET + el] = (block + 1) * OFFSET + el;
        }
        mass[(blocks - 1) * OFFSET + el] = el + 1;
    }
    mass[(blocks - 1) * OFFSET + (BLOCK_SIZE - 1)] = 0;
}

void main()
{
    for (int blocks = 0; blocks < 32; blocks++) {
        initialize_mass(blocks + 1);
        printf("%d %f\n", blocks + 1, calculate_average_time());
    }
}