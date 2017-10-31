#include <stdio.h> // for printf
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf
#include <math.h>

#define NUMBER_OF_ITERATIONS 1e8 * 3

double picalculate() {
	double pi;
	long long n;
	for (n = 0; n < NUMBER_OF_ITERATIONS; n++) {
		pi += pow(-1, n) / (2*n + 1);
	}
	return pi*4;
}

// times(1) calculates working time of process

int main() {
	struct tms start, end;
	long clocks_per_sec = sysconf(_SC_CLK_TCK);
	long clocks;

	times(&start);
	double pi = picalculate();
	times(&end);

	clocks = end.tms_utime - start.tms_utime;
	printf("Time taken: %lf sec.\n",
	(double)clocks / clocks_per_sec);
	// printf("Pi = %lf\n", pi);
	return 0;
}