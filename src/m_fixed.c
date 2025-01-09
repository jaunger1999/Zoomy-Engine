#include "m_fixed.h"
#include <stdbool.h>

double FastArcTan(double x) { return M_PI_4 * x - x * (fabs(x) - 1) * (0.2447 + 0.0663 * fabs(x)); }

double sin(double x)
{
	int    i    = 1;
	double cur  = x;
	double acc  = 1;
	double fact = 1;
	double pow  = x;
	while(fabs(acc) > .00000001 && i < 100) {
		fact *= ((2 * i) * (2 * i + 1));
		pow  *= -1 * x * x;
		acc   = pow / fact;
		cur  += acc;
		i++;
	}
	return cur;
}

// https://www.nullhardware.com/blog/fixed-point-sine-and-cosine-for-embedded-systems/
// TODO: make this work for 64 bit ints
/*
 * Implements the 5-order polynomial approximation to sin(x).
 * @param i   angle (with 2^63 units/circle)
 * @return    64 bit fixed point Sine value (32.32) (ie: +4294967296 = +1 & -4294967296 = -1)
 *
 *The result is accurate to within +- 1 count. ie: +/-2.44e-4. What does this mean ??
 */
int64_t fpsin(int64_t i)
{
	// Convert (signed) input to a value between 0 and 2^61. (2^61 is pi/2, the region of the curve fit).
	i <<= 1;

	bool const c = i < 0; // set carry for output pos/neg
	
	// 0x40000000 is the bit that marks pi/2
	if(i == (i | 0x4000000000000000)) { // flip input value to corresponding value in range [0..pi/2)
		i = (1LL << 63) - i;
	}

	i = (i & 0x7FFFFFFFFFFFFFFF) >> 1; // the absolute value divided by 2
	/* ------------------------------------------------------------------- */

	/* The following section implements the formula:
	 = y * 2^-n * ( A1 - 2^(q-p)* y * 2^-n * y * 2^-n * [B1 - 2^-r * y * 2^-n * C1 * y]) * 2^(a-q)
	Where the constants are defined as follows:
	*/
	uint64_t static const A1 = 3370945099ULL;
	uint64_t static const B1 = 2746362156ULL;
	uint64_t static const C1 = 292421ULL;
	enum { n = 13, p = 32, q = 31, r = 3, a = 12 };

	uint64_t y = (C1 * ((uint64_t)i)) >> n;

	y = B1 - (((uint64_t)i * y) >> r);
	y = (uint64_t)i * (y >> n);
	y = (uint64_t)i * (y >> n);
	y = A1 - (y >> (p - q));
	y = (uint64_t)i * (y >> n);
	y = (y + (1ULL << (q - a - 1))) >> (q - a); // Rounding

	return c ? -(int64_t)y : (int64_t)y;
}

/**
 * 64-bit fixed point four-quadrant arctangent. Given some Cartesian vector
 * (x, y), find the angle subtended by the vector and the positive x-axis.
 *
 * The value returned is in units of 1/65536ths of one turn. This allows the use
 * of the full 64-bit unsigned range to represent a turn. e.g. 0x0000 is 0
 * radians, 0x8000 is pi radians, and 0xFFFF is (65535 / 32768) * pi radians.
 *
 * Because the magnitude of the input vector does not change the angle it
 * represents, the inputs can be in any signed 64-bit fixed-point format.
 *
 * @param y y-coordinate in signed 64-bit
 * @param x x-coordinate in signed 64-bit
 * @return angle in (val / 32768) * pi radian increments from 0x0000 to 0xFFFF
 */
/* uint64_t fxpt_atan2(int64_t const y, int64_t const x) */
/* { */
/* 	if(x == y) {   // x/y or y/x would return -1 since 1 isn't representable */
/* 		if(y > 0) { // 1/8 */
/* 			return 8192; */
/* 		} */
/* 		else if(y < 0) { // 5/8 */
/* 			return 40960; */
/* 		} */
/* 		else { // x = y = 0 */
/* 			return 0; */
/* 		} */
/* 	} */
/**/
/* 	const int64_t nabs_y = -int64_abs(y), nabs_x = -int64_abs(x); */
/* 	if(nabs_x < nabs_y) { // octants 1, 4, 5, 8 */
/* 		int64_t const y_over_x   = FixedDiv(y, x); */
/* 		int64_t const correction = FixedMul(q15_from_double(0.273 * M_1_PI), -int64_abs(y_over_x)); */
/* 		int64_t const unrotated  = FixedMul(q15_from_double(0.25 + 0.273 * M_1_PI) + correction, y_over_x); */
/* 		if(x > 0) { // octants 1, 8 */
/* 			return (uint64_t)unrotated; */
/* 		} */
/* 		else { // octants 4, 5 */
/* 			return (uint64_t)(32768LL + unrotated); */
/* 		} */
/* 	} */
/* 	else { // octants 2, 3, 6, 7 */
/* 		int64_t const x_over_y   = FixedDiv(x, y); */
/* 		int64_t const correction = FixedMul(q15_from_double(0.273 * M_1_PI), -int64_abs(x_over_y)); */
/* 		int64_t const unrotated  = FixedMul(q15_from_double(0.25 + 0.273 * M_1_PI) + correction, x_over_y); */
/* 		if(y > 0) { // octants 2, 3 */
/* 			return (uint64_t)(16384LL - unrotated); */
/* 		} */
/* 		else { // octants 6, 7 */
/* 			return (uint64_t)(49152LL - unrotated); */
/* 		} */
/* 	} */
/* } */
