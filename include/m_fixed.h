#include <stdint.h>

#define FRACBITS 32
#define FRACUNIT (1<<FRACBITS)

typedef int64_t fixed_t;

//
// Fixed Point Multiplication
//
inline static fixed_t FixedMul(fixed_t a, fixed_t b)
{
   return ((int64_t) a*b >> FRACBITS);
}
