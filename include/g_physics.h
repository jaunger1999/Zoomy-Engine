#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif

typedef struct PhysicalProperties {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
} PhysicalProperties;

//Vector3 ApplyForce(Object const * const obj, Vector3 const * const dir, const float n);
//Vector3 Accelerate(Object const * const obj, Vector3 const * const a);

//SetVelocityX(Object const * const obj, const float x);
//SetVelocityY(Object const * const obj, const float y);
//SetVelocityZ(Object const * const obj, const float z);
