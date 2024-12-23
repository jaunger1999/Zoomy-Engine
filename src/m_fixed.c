#include "m_fixed.h"
#include <stdbool.h>


// https://www.nullhardware.com/blog/fixed-point-sine-and-cosine-for-embedded-systems/
// TODO: make this work for 64 bit ints
/*
 * Implements the 5-order polynomial approximation to sin(x).
 * @param i   angle (with 2^15 units/circle)
 * @return    16 bit fixed point Sine value (4.12) (ie: +4096 = +1 & -4096 = -1)
 *
 *The result is accurate to within +- 1 count. ie: +/-2.44e-4.
 */
int64_t fpsin(int64_t i)
{
	// Convert (signed) input to a value between 0 and 8192 (WRONG!). (8192 is pi/2, which is the region of the curve fit).
	i <<= 1;

	bool c = i < 0; // set carry for output pos/neg

	if(i == (i | 0x4000)) { // flip input value to corresponding value in range [0..8192)
		i = (1 << 15) - i;
	}

	i = (i & 0x7FFF) >> 1;
	/* ------------------------------------------------------------------- */

	/* The following section implements the formula:
	 = y * 2^-n * ( A1 - 2^(q-p)* y * 2^-n * y * 2^-n * [B1 - 2^-r * y * 2^-n * C1 * y]) * 2^(a-q)
	Where the constants are defined as follows:
	*/
	enum { A1 = 3370945099UL, B1 = 2746362156UL, C1 = 292421UL };
	enum { n = 13, p = 32, q = 31, r = 3, a = 12 };

	uint64_t y = (C1 * ((uint64_t)i)) >> n;

	y = B1 - (((uint64_t)i * y) >> r);
	y = (uint64_t)i * (y >> n);
	y = (uint64_t)i * (y >> n);
	y = A1 - (y >> (p - q));
	y = (uint64_t)i * (y >> n);
	y = (y + (1UL << (q - a - 1))) >> (q - a); // Rounding

	return c ? -y : y;
}

