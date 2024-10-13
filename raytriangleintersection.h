#ifndef RAYLIB
#define RAYLIB
#include "Raylib.h"
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

OptionVector3 Intersect(Ray const ray, Triangle const triangle);

CollisionMesh GetCollisionMesh(char const *fileDir);
