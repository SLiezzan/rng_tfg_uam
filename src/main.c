#include <stdio.h>
#include <stdlib.h>

#include "mt.h"
#include "lcg.h"
#include "tests.h"

#define N_TESTS 100000

int main(int argc, char **argv) {
	unsigned long seed = (unsigned long)atoi(argv[1]);
	int i;
	float count_mt_digits = 0.0, count_mt_binary = 0.0;
	float count_mt_pairs = 0.0, count_mt_dig_fix = 0.0;
	float count_lcg_digits = 0.0, count_lcg_binary = 0.0;
	float count_lcg_pairs = 0.0, count_lcg_dig_fix = 0.0;

	for (i = 0; i < N_TESTS; i++) {
		count_mt_digits   += (float)run_test_digits(genrand, sgenrand, seed);
		count_mt_binary   += (float)run_test_binary(genrand, sgenrand, seed);
		count_mt_pairs    += (float)run_test_pairs(genrand, sgenrand, seed);
		count_mt_dig_fix  += (float)run_test_dig_fix(genrand, sgenrand, seed);
		count_lcg_digits  += (float)run_test_digits(lcg_genrand, lcg_sgenrand, seed);
		count_lcg_binary  += (float)run_test_binary(lcg_genrand, lcg_sgenrand, seed);
		count_lcg_pairs   += (float)run_test_pairs(lcg_genrand, lcg_sgenrand, seed);
		count_lcg_dig_fix += (float)run_test_dig_fix(lcg_genrand, lcg_sgenrand, seed);

		seed = (seed * 69069) & 0xffffffff;
	}

	count_mt_digits = count_mt_digits * 100 / N_TESTS;
	count_mt_binary = count_mt_binary * 100 / N_TESTS;
	count_mt_pairs = count_mt_pairs * 100 / N_TESTS;
	count_mt_dig_fix = count_mt_dig_fix * 100 / N_TESTS;
	count_lcg_digits = count_lcg_digits * 100 / N_TESTS;
	count_lcg_binary = count_lcg_binary * 100 / N_TESTS;
	count_lcg_pairs = count_lcg_pairs * 100 / N_TESTS;
	count_lcg_dig_fix = count_lcg_dig_fix * 100 / N_TESTS;

	printf("Porcentaje rechazo MT dígitos: %.2f%%\n", count_mt_digits);
	printf("Porcentaje rechazo MT binario: %.2f%%\n", count_mt_binary);
	printf("Porcentaje rechazo MT parejas: %.2f%%\n", count_mt_pairs);
	printf("Porcentaje rechazo MT dígitos (fix): %.2f%%\n", count_mt_dig_fix);
	printf("Porcentaje rechazo LCG dígitos: %.2f%%\n", count_lcg_digits);
	printf("Porcentaje rechazo LCG binario: %.2f%%\n", count_lcg_binary);
	printf("Porcentaje rechazo LCG parejas: %.2f%%\n", count_lcg_pairs);
	printf("Porcentaje rechazo LCG dígitos (fix): %.2f%%\n", count_lcg_dig_fix);
}