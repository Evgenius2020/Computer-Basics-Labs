#include <stdio.h>
#include <math.h>
#include <time.h>

#define NUMBER_OF_ITERATIONS 1e8 * 2

double picalculate() {
	double pi;
	long long n;
	for (n = 0; n < NUMBER_OF_ITERATIONS; n++) {
		pi += pow(-1, n) / (2*n + 1);
	}
	return pi*4;
}

int main() {
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	double pi = picalculate();

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printf("Pi = %lf\n", pi);
	printf("Time taken: %lf sec.\n", end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec));
	return 0;
}