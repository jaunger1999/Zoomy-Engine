#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif

/*struct CollisionRay {
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

typedef struct Hit Hit;*/

typedef struct OptionHit {
	bool valid;
	Vector3 intersection;
	float t, u, v;
} OptionHit;

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
	Vector3 *vertices;
	Vector3 *vertexNormals;
	Vector3 *surfaceNormals;

	Face *faces;

	int faceCount;
} CollisionMesh;



OptionHit Intersect(Ray const * const ray, Vector3 const * const a, Vector3 const * const b, Vector3 const * const c);

CollisionMesh GetCollisionMesh(char const * const fileDir);

Vector3 VectorComponentAlongPlane(Vector3 * vector, Vector3 * normal);
