#include <stdint.h>

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

#ifndef VECTOR4_TYPE
typedef struct Vector4 {
	int64_t x;
	int64_t y;
	int64_t z;
	int64_t w;
} Vector4;
#define VECTOR4_TYPE
#endif

#ifndef QUATERNION_TYPE
typedef Vector4 Quaternion;
#define QUATERNION_TYPE
#endif
