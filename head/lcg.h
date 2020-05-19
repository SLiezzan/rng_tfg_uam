#ifndef _LCG_H
#define _LCG_H

/* Recurrence parameters */
#define A 1664525

/* Buffer */
#define T 256

void lcg_sgenrand(unsigned long seed);
unsigned long lcg_genrand();

#endif