#include <stdio.h> // for printf
#include <stdint.h>
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

int main(){
	union ticks {
		uint64_t t64;
		struct s32 {
			uint32_t th, tl;
		} t32;
	} start, end;
	double cpu_Hz = 2.1e9;

	asm("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
	double pi = picalculate();
	asm("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));

	printf("Time taken: %lf sec.\n",(end.t64-start.t64)/cpu_Hz);
	// printf("Pi = %lf\n", pi);
	return 0;
 }