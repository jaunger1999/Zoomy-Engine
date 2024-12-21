#include <stdint.h>

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
#ifndef VECTOR2_TYPE
typedef struct Vector2 {
	int64_t x;
	int64_t y;
} Vector2;
#define VECTOR2_TYPE
#endif

#ifndef VECTOR3_TYPE
typedef struct Vector3 {
	int64_t x;
	int64_t y;
	int64_t z;
} Vector3;
#define VECTOR3_TYPE
#endif

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

#ifndef MATRIX_TYPE
// Matrix type OpenGL style 4x4 - right handed, column major
typedef struct Matrix {
	int64_t m0, m4, m8, m12;  // Matrix first row 4 components
	int64_t m1, m5, m9, m13;  // Matrix second row 4 components
	int64_t m2, m6, m10, m14; // Matrix third row 4 components
	int64_t m3, m7, m11, m15; // Matrix fourth row 4 components
} Matrix;
#define MATRIX_TYPE
#endif
