#include <stdint.h>

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
