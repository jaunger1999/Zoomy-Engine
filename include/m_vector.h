#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif

typedef struct OptionVector3 {
	bool    const valid;
	Vector3 const vector;
} OptionVector3;

Quaternion QuaternionFromGravityVector(Vector3 *g);
OptionVector3 WrapVector3(Vector3 const* const vector);
