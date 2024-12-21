#include <stdint.h>
#include <stdbool.h>
#include "m_vector4.h"

#ifndef VECTOR3_TYPE
typedef struct Vector3 {
	int64_t x;
	int64_t y;
	int64_t z;
} Vector3;
#define VECTOR3_TYPE
#endif

typedef struct OptionVector3 {
	bool    const valid;
	Vector3 const vector;
} OptionVector3;

Quaternion QuaternionFromGravityVector(Vector3* g);
OptionVector3 WrapVector3(Vector3 const* const vector);
