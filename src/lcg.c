#include <stdio.h>

#include "lcg.h"

static unsigned long lcg[T];
static int lcgi=T+1;

void lcg_sgenrand(unsigned long seed) {
	lcg[T-1] = seed & 0xffffffff;
	lcgi=T;
}

unsigned long lcg_genrand() {
	if (lcgi >= T) {
		int i;

		if (lcgi == T+1) {
			lcg_sgenrand(4357);
		}

		lcg[0] = (A * lcg[T-1]) & 0xffffffff;

		for (i=1; i<T; i++) {
			lcg[i] = (A * lcg[i-1]) & 0xffffffff;
		}

		lcgi = 0;
	}

	return lcg[lcgi++];
}