#include <stdio.h>

#include "tests.h"
#include "lcg.h"
#include "mt.h"

int count_ones(unsigned long word) {
	int c;

	for (c = 0; word; word >>= 1)	{
		c += word & 0x1;
	}

	return c;
}

int count_pair(unsigned long word, unsigned long pair) {
	int i, c;
	int n_pairs = BITS_PER_WORD / 2;

	for (c = 0, i = 0; i < n_pairs; i++, word >>= 2) {
		if ((word & 0x3) == pair) {
			c++;
		}
	}

	return c;
}

int run_test_digits(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed) {
	int i, j, index;
	char buf[TEST_DIGITS_K + 1];
	float obs[TEST_DIGITS_K];
	float esp[TEST_DIGITS_K];
	float b = 0.0;
	unsigned long n;

	for (i = 0; i < TEST_DIGITS_K; i++) {
		obs[i] = 0.0;
		esp[i] = (float)N_EXTRACTIONS * (float)DIGITS_PER_NUMBER / (float)TEST_DIGITS_K;
	}

	(*s)(seed);
	for (i = 0; i < N_EXTRACTIONS; i++) {
		n = (*f)();
		sprintf(buf, "%010lu", n);
		for (j = 0; j < TEST_DIGITS_K; j++) {
			index = (int)buf[j] - 48;
			obs[index]++;
		}
	}

	for (i = 0; i < TEST_DIGITS_K; i++) {
		b += (obs[i] - esp[i]) * (obs[i] - esp[i]) / esp[i];
	}

	return b > CHICUAD_9_5;
}

int run_test_dig_fix(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed) {
	int i, j, index;
	char buf[TEST_DIGITS_K - 1];
	float obs[TEST_DIGITS_K];
	float esp[TEST_DIGITS_K];
	float b = 0.0;
	unsigned long n;

	for (i = 0; i < TEST_DIGITS_K; i++) {
		obs[i] = 0.0;
		esp[i] = (float)N_EXTRACTIONS * (float)(DIGITS_PER_NUMBER - 2) / (float)TEST_DIGITS_K;
	}

	(*s)(seed);
	for (i = 0; i < N_EXTRACTIONS; i++) {
		n = (*f)();
		n = n % 100000000;
		sprintf(buf, "%08lu", n);
		for (j = 0; j < TEST_DIGITS_K - 2; j++) {
			index = (int)buf[j] - 48;
			obs[index]++;
		}
	}

	for (i = 0; i < TEST_DIGITS_K; i++) {
		b += (obs[i] - esp[i]) * (obs[i] - esp[i]) / esp[i];
	}

	return b > CHICUAD_9_5;
}

int run_test_pairs(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed) {
	int i, count;
	float obs[TEST_BINARY_PAIRS];
	float esp[TEST_BINARY_PAIRS];
	float b = 0.0;
	unsigned long n;

	for (i = 0; i < TEST_BINARY_PAIRS; i++) {
		obs[i] = 0.0;
		esp[i] = (float)N_EXTRACTIONS * ((float)BITS_PER_WORD / 2.0) / (float)TEST_BINARY_PAIRS;
	}

	(*s)(seed);
	for (i = 0; i < N_EXTRACTIONS; i++) {
		n = (*f)();
		count = count_pair(n, 0x0);
		obs[0] += (float)count;

		count = count_pair(n, 0x1);
		obs[1] += (float)count;

		count = count_pair(n, 0x2);
		obs[2] += (float)count;
		
		count = count_pair(n, 0x3);
		obs[3] += (float)count;
	}

	for (i = 0; i < TEST_BINARY_PAIRS; i++) {
		b += (obs[i] - esp[i]) * (obs[i] - esp[i]) / esp[i];
	}

	return b > CHICUAD_3_5;
}

int run_test_binary(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed) {
	int i, n_ones, n_zeros;
	float obs[TEST_BINARY];
	float esp[TEST_BINARY];
	float b = 0.0;
	unsigned long n;

	for (i = 0; i < TEST_BINARY; i++) {
		obs[i] = 0.0;
		esp[i] = (float)N_EXTRACTIONS * (float)BITS_PER_WORD / (float)TEST_BINARY;
	}

	(*s)(seed);
	for (i = 0; i < N_EXTRACTIONS; i++) {
		n = (*f)();
		n_ones = count_ones(n);
		n_zeros = BITS_PER_WORD - n_ones;
		obs[0] += (float)n_zeros;
		obs[1] += (float)n_ones;
	}

	for (i = 0; i < TEST_BINARY; i++) {
		b += (obs[i] - esp[i]) * (obs[i] - esp[i]) / esp[i];
	}

	return b > CHICUAD_1_5;
}