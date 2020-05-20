#ifndef _TESTS_H
#define _TESTS_H

#define N_EXTRACTIONS 10000
#define CHICUAD_1_5 3.84
#define CHICUAD_3_5 7.82
#define CHICUAD_9_5 16.92

#define TEST_DIGITS_K 10
#define TEST_PAIRS_K 100
#define TEST_BINARY 2
#define TEST_BINARY_PAIRS 4

#define DIGITS_PER_NUMBER 10
#define BITS_PER_WORD 32

int run_test_digits(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed);
int run_test_dig_fix(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed);
int run_test_pairs(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed);
int run_test_binary(unsigned long (*f)(), void (*s)(unsigned long), unsigned long seed);

#endif