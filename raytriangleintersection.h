#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif

struct CollisionRay {
	float ox, oy, oz, ow;
	float dx, dy, dz, dw;
} __declspec(aligned(16));

typedef struct CollisionRay CollisionRay;

struct PrecomputedTriangle {
	float nx, ny, nz, nd;
	float ux, uy, uz, ud;
	float vx, vy, vz, vd;
} __declspec(aligned(16));

typedef struct PrecomputedTriangle PrecomputedTriangle;

struct Hit {
	float px, py, pz, pw;
	float t, u, v;
} __declspec(aligned(16));

typedef struct Hit Hit;


typedef struct Triangle {
	Vector3 n;
	Vector3 a;
	Vector3 b;
	Vector3 c;
} Triangle;

typedef struct Face {
	// These are all indices in our vertex and normal arrays
	int a;
	int b;
	int c;

	int nA;
	int nB;
	int nC;

} Face;

typedef struct CollisionMesh {
	int faceCount;
	Vector3 *vertices;
	Vector3 *normals;
	Face *faces;
} CollisionMesh;

typedef struct OptionVector3 {
	bool const valid;
	Vector3 const vector;
} OptionVector3;


OptionVector3 Intersect(Ray const ray, Vector3 const a, Vector3 const b, Vector3 const c);

CollisionMesh GetCollisionMesh(char const *fileDir);
