#include <stdio.h>

float powerMinusOne(long long n) {
	if (n % 2 == 0) {
		return 1;
	}
	else {
		return -1;
	}
}

float getNthElement(long long n) {
	return (powerMinusOne(n) * 4) / (2*n + 1);
}

float picalculate() {
	float pi = 0;
	for (long long n = 0; n < 100000000; n++) {
		pi += getNthElement(n);
	}
	return pi;
}

int main() {
	float pi = picalculate();
	printf("Pi = %f\n", pi);
	return 0;
}