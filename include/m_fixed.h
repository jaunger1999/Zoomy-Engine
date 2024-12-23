#include <stdint.h>

#define FRACBITS 32
#define FRACUNIT (1 << FRACBITS)

typedef int64_t fixed_t;

inline static fixed_t  FixedMul(fixed_t const a, fixed_t const b);
inline static uint64_t uint64_sqrt(uint64_t const val);
inline static int64_t  min(int64_t const a, int64_t const b);
inline static int64_t  max(int64_t const a, int64_t const b);
inline static int64_t int64_abs(int64_t x);
