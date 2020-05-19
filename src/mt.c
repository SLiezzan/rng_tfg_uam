/** A C-program for MT19937: Real number version 
  * genrand() generates one pseudorandom real number (double)
  * which is uniformly distributed on [0,1]-interval, for each
  * call. sgenrand(seed) set initial values to the working area
  * of 624 words. Before genrand(), sgenrand(seed) must be
  * called once (seed is any 32-bit integer except for 0).
  * Integer generator is obtained by modifying two lines.
  *   Coded by Takuji Nishimura, considering the suggestions by
  * Topher Cooper and Marc Rieffel in July-Aug. 1997. Comments
  * should be addressed to: matumoto@math.keio.ac.jp
  */
#include <stdio.h>

#include "mt.h"

static unsigned long mt[N]; /* the array for the state vector */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/** setting initial seeds to mt[N] using
  * the generator Line 25 of Table 1 in
  * [KNUTH 1981, The Art of Computer Programming
  * Vol. 2 (2nd Ed.), pp102]
  */
void sgenrand(unsigned long seed) {
	mt[0] = seed & 0xffffffff;
	for (mti=1; mti<N; mti++) {
		mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
	}
}

unsigned long genrand() {
	unsigned long y;
	/* mag01[x] = x * MATRIX_A for x=0,1 */
	static unsigned long mag01[2]={0x0, MATRIX_A};

	if (mti >= N) { /* generate N words at one time */
		int kk;

		if (mti == N+1) { /* if sgenrand() has not been called, */
			sgenrand(4357); /* a default initial seed is used */
		}

		for (kk=0; kk<N-M; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		for (; kk<N-1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

		mti = 0;
	}

	y = mt[mti++];
	y ^= TEMPERING_SHIFT_U(y);
	y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
	y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
	y ^= TEMPERING_SHIFT_L(y);

	return y;
}