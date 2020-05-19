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
#ifndef _MT_H
#define _MT_H

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y) (y >> 11)
#define TEMPERING_SHIFT_S(y) (y << 7)
#define TEMPERING_SHIFT_T(y) (y << 15)
#define TEMPERING_SHIFT_L(y) (y >> 18)

void sgenrand(unsigned long seed);
unsigned long genrand();

#endif