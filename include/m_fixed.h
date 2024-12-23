#include <stdint.h>

#define FRACBITS 32
#define FRACUNIT (1 << FRACBITS)

typedef int64_t fixed_t;

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

int64_t fpsin(int64_t i);

// Cos(x) = sin(x + pi/2)
#define fpcos(i) fpsin((int16_t)(((uint16_t)(i)) + 8192U))
