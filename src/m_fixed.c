#include "m_fixed.h"

// Fixed Point Multiplication
inline static fixed_t FixedMul(fixed_t const a, fixed_t const b) { return a * b >> FRACBITS; }

// https://stackoverflow.com/questions/34187171/fast-integer-square-root-approximation
// Newton-Raphson
inline static uint64_t uint64_sqrt(uint64_t val)
{
	if(val < 2) {
		return val; /* avoid div/0 */
	}

	uint64_t a = 1255LL; /* starting point is relatively unimportant */

	// number of loops is arbitrary
	for(unsigned int i = 0; i < 6; i++) {
		uint64_t b = val / a;

		a = (a + b) / 2;
	}

	return a;
}

inline static int64_t max(int64_t const a, int64_t const b) { return a > b ? a : b; }
inline static int64_t min(int64_t const a, int64_t const b) { return a < b ? a : b; }

inline static int64_t int64_abs(int64_t x) { return x < 0 ? -x : x; }

// https://www.nullhardware.com/blog/fixed-point-sine-and-cosine-for-embedded-systems/
/*
 * Implements the 5-order polynomial approximation to sin(x).
 * @param i   angle (with 2^15 units/circle)
 * @return    16 bit fixed point Sine value (4.12) (ie: +4096 = +1 & -4096 = -1)
 *
 *The result is accurate to within +- 1 count. ie: +/-2.44e-4.
 */
int16_t fpsin(int16_t i)
{
	// Convert (signed) input to a value between 0 and 8192. (8192 is pi/2, which is the region of the curve fit).
	i         <<= 1;
	uint8_t c   = i < 0; // set carry for output pos/neg

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

	uint32_t y = (C1 * ((uint32_t)i)) >> n;

	y = B1 - (((uint32_t)i * y) >> r);
	y = (uint32_t)i * (y >> n);
	y = (uint32_t)i * (y >> n);
	y = A1 - (y >> (p - q));
	y = (uint32_t)i * (y >> n);
	y = (y + (1UL << (q - a - 1))) >> (q - a); // Rounding

	return c ? -y : y;
}

// Cos(x) = sin(x + pi/2)
#define fpcos(i) fpsin((int16_t)(((uint16_t)(i)) + 8192U))
