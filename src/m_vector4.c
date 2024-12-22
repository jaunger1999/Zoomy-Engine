#include "m_vector4.h"
#include "m_fixed.h"
#include "m_matrix.h"
#include <stdint.h>

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector4 math
//----------------------------------------------------------------------------------

Vector4 Vector4Zero(void)
{
	Vector4 result = {0LL, 0LL, 0LL, 0LL};
	return result;
}

Vector4 Vector4One(void)
{
	Vector4 result = {1LL, 1LL, 1LL, 1LL};
	return result;
}

Vector4 Vector4Add(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z, v1->w + v2->w};
	return result;
}

Vector4 Vector4AddValue(Vector4 const* const v, int64_t const add)
{
	Vector4 result = {v->x + add, v->y + add, v->z + add, v->w + add};
	return result;
}

Vector4 Vector4Subtract(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z, v1->w - v2->w};
	return result;
}

Vector4 Vector4SubtractValue(Vector4 const* const v, int64_t const add)
{
	Vector4 result = {v->x - add, v->y - add, v->z - add, v->w - add};
	return result;
}

int64_t Vector4Length(Vector4 const* const v)
{
	int64_t result = (int64_t)uint64_sqrt((uint64_t)((v->x * v->x) + (v->y * v->y) + (v->z * v->z) + (v->w * v->w)));
	return result;
}

int64_t Vector4LengthSqr(Vector4 const* const v)
{
	int64_t result = (v->x * v->x) + (v->y * v->y) + (v->z * v->z) + (v->w * v->w);
	return result;
}

int64_t Vector4DotProduct(Vector4 const* const v1, Vector4 const* const v2)
{
	int64_t result = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
	return result;
}

// Calculate distance between two vectors
int64_t Vector4Distance(Vector4 const* const v1, Vector4 const* const v2)
{
	int64_t result =
		(int64_t)uint64_sqrt((uint64_t)((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y) +
	                                   (v1->z - v2->z) * (v1->z - v2->z) + (v1->w - v2->w) * (v1->w - v2->w)));
	return result;
}

// Calculate square distance between two vectors
int64_t Vector4DistanceSqr(Vector4 const* const v1, Vector4 const* const v2)
{
	int64_t result = (v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y) +
	                 (v1->z - v2->z) * (v1->z - v2->z) + (v1->w - v2->w) * (v1->w - v2->w);

	return result;
}

Vector4 Vector4Scale(Vector4 const* const v, int64_t const scale)
{
	Vector4 result = {v->x * scale, v->y * scale, v->z * scale, v->w * scale};
	return result;
}

// Multiply vector by vector
Vector4 Vector4Multiply(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {v1->x * v2->x, v1->y * v2->y, v1->z * v2->z, v1->w * v2->w};
	return result;
}

// Negate vector
Vector4 Vector4Negate(Vector4 const* const v)
{
	Vector4 result = {-v->x, -v->y, -v->z, -v->w};
	return result;
}

// Divide vector by vector
Vector4 Vector4Divide(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {v1->x / v2->x, v1->y / v2->y, v1->z / v2->z, v1->w / v2->w};
	return result;
}

// Normalize provided vector
Vector4 Vector4Normalize(Vector4 const* const v)
{
	Vector4 result = {0};
	int64_t length = (int64_t)uint64_sqrt((uint64_t)((v->x * v->x) + (v->y * v->y) + (v->z * v->z) + (v->w * v->w)));

	if(length > 0) {
		int64_t ilength = 1LL / length;
		result.x        = v->x * ilength;
		result.y        = v->y * ilength;
		result.z        = v->z * ilength;
		result.w        = v->w * ilength;
	}

	return result;
}

// Get min value for each pair of components
Vector4 Vector4Min(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {0};

	result.x = min(v1->x, v2->x);
	result.y = min(v1->y, v2->y);
	result.z = min(v1->z, v2->z);
	result.w = min(v1->w, v2->w);

	return result;
}

// Get max value for each pair of components
Vector4 Vector4Max(Vector4 const* const v1, Vector4 const* const v2)
{
	Vector4 result = {0};

	result.x = max(v1->x, v2->x);
	result.y = max(v1->y, v2->y);
	result.z = max(v1->z, v2->z);
	result.w = max(v1->w, v2->w);

	return result;
}

// Calculate linear interpolation between two vectors
Vector4 Vector4Lerp(Vector4 const* const v1, Vector4 const* const v2, int64_t const amount)
{
	Vector4 result = {0};

	result.x = v1->x + amount * (v2->x - v1->x);
	result.y = v1->y + amount * (v2->y - v1->y);
	result.z = v1->z + amount * (v2->z - v1->z);
	result.w = v1->w + amount * (v2->w - v1->w);

	return result;
}

// Move Vector towards target
Vector4 Vector4MoveTowards(Vector4 const* const v, Vector4 const* const target, int64_t const maxDistance)
{
	Vector4 result = {0};

	int64_t dx    = target->x - v->x;
	int64_t dy    = target->y - v->y;
	int64_t dz    = target->z - v->z;
	int64_t dw    = target->w - v->w;
	int64_t value = (dx * dx) + (dy * dy) + (dz * dz) + (dw * dw);

	if((value == 0) || ((maxDistance >= 0) && (value <= maxDistance * maxDistance)))
		return *target;

	int64_t dist = sqrtf(value);

	result.x = v->x + dx / dist * maxDistance;
	result.y = v->y + dy / dist * maxDistance;
	result.z = v->z + dz / dist * maxDistance;
	result.w = v->w + dw / dist * maxDistance;

	return result;
}

// Invert the given vector
Vector4 Vector4Invert(Vector4 const* const v)
{
	Vector4 result = {1LL / v->x, 1LL / v->y, 1LL / v->z, 1LL / v->w};
	return result;
}

// Check whether two given vectors are almost equal
int Vector4Equals(Vector4 const* const p, Vector4 const* const q)
{
	int result = ((abs(p->x - q->x)) <= max(1LL, max(abs(p->x), abs(q->x)))) &&
	             ((abs(p->y - q->y)) <= max(1LL, max(abs(p->y), abs(q->y)))) &&
	             ((abs(p->z - q->z)) <= max(1LL, max(abs(p->z), abs(q->z)))) &&
	             ((abs(p->w - q->w)) <= max(1LL, max(abs(p->w), abs(q->w))));
	return result;
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Matrix math
//----------------------------------------------------------------------------------

// Compute matrix determinant
int64_t MatrixDeterminant(Matrix const* const mat)
{
	int64_t result = 0LL;

	// Cache the matrix values (speed optimization)
	int64_t a00 = mat->m0, a01 = mat->m1, a02 = mat->m2, a03 = mat->m3;
	int64_t a10 = mat->m4, a11 = mat->m5, a12 = mat->m6, a13 = mat->m7;
	int64_t a20 = mat->m8, a21 = mat->m9, a22 = mat->m10, a23 = mat->m11;
	int64_t a30 = mat->m12, a31 = mat->m13, a32 = mat->m14, a33 = mat->m15;

	result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
	         a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
	         a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
	         a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
	         a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
	         a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

	return result;
}

// Get the trace of the matrix (sum of the values along the diagonal)
int64_t MatrixTrace(Matrix const* const mat)
{
	int64_t result = (mat->m0 + mat->m5 + mat->m10 + mat->m15);

	return result;
}

// Transposes provided matrix
Matrix MatrixTranspose(Matrix const* const mat)
{
	Matrix result = {0};

	result.m0  = mat->m0;
	result.m1  = mat->m4;
	result.m2  = mat->m8;
	result.m3  = mat->m12;
	result.m4  = mat->m1;
	result.m5  = mat->m5;
	result.m6  = mat->m9;
	result.m7  = mat->m13;
	result.m8  = mat->m2;
	result.m9  = mat->m6;
	result.m10 = mat->m10;
	result.m11 = mat->m14;
	result.m12 = mat->m3;
	result.m13 = mat->m7;
	result.m14 = mat->m11;
	result.m15 = mat->m15;

	return result;
}

// Invert provided matrix
Matrix MatrixInvert(Matrix const* const mat)
{
	Matrix result = {0};

	// Cache the matrix values (speed optimization)
	int64_t a00 = mat->m0, a01 = mat->m1, a02 = mat->m2, a03 = mat->m3;
	int64_t a10 = mat->m4, a11 = mat->m5, a12 = mat->m6, a13 = mat->m7;
	int64_t a20 = mat->m8, a21 = mat->m9, a22 = mat->m10, a23 = mat->m11;
	int64_t a30 = mat->m12, a31 = mat->m13, a32 = mat->m14, a33 = mat->m15;

	int64_t b00 = a00 * a11 - a01 * a10;
	int64_t b01 = a00 * a12 - a02 * a10;
	int64_t b02 = a00 * a13 - a03 * a10;
	int64_t b03 = a01 * a12 - a02 * a11;
	int64_t b04 = a01 * a13 - a03 * a11;
	int64_t b05 = a02 * a13 - a03 * a12;
	int64_t b06 = a20 * a31 - a21 * a30;
	int64_t b07 = a20 * a32 - a22 * a30;
	int64_t b08 = a20 * a33 - a23 * a30;
	int64_t b09 = a21 * a32 - a22 * a31;
	int64_t b10 = a21 * a33 - a23 * a31;
	int64_t b11 = a22 * a33 - a23 * a32;

	// Calculate the invert determinant (inlined to avoid double-caching)
	int64_t invDet = 1LL / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

	result.m0  = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
	result.m1  = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
	result.m2  = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
	result.m3  = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
	result.m4  = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
	result.m5  = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
	result.m6  = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
	result.m7  = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
	result.m8  = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
	result.m9  = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
	result.m10 = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
	result.m11 = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
	result.m12 = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
	result.m13 = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
	result.m14 = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
	result.m15 = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

	return result;
}

// Get identity matrix
Matrix MatrixIdentity(void)
{
	Matrix result = {1LL, 0LL, 0LL, 0LL, 0LL, 1LL, 0LL, 0LL, 0LL, 0LL, 1LL, 0LL, 0LL, 0LL, 0LL, 1LL};

	return result;
}

// Add two matrices
Matrix MatrixAdd(Matrix const* const left, Matrix const* const right)
{
	Matrix result = {0};

	result.m0  = left->m0 + right->m0;
	result.m1  = left->m1 + right->m1;
	result.m2  = left->m2 + right->m2;
	result.m3  = left->m3 + right->m3;
	result.m4  = left->m4 + right->m4;
	result.m5  = left->m5 + right->m5;
	result.m6  = left->m6 + right->m6;
	result.m7  = left->m7 + right->m7;
	result.m8  = left->m8 + right->m8;
	result.m9  = left->m9 + right->m9;
	result.m10 = left->m10 + right->m10;
	result.m11 = left->m11 + right->m11;
	result.m12 = left->m12 + right->m12;
	result.m13 = left->m13 + right->m13;
	result.m14 = left->m14 + right->m14;
	result.m15 = left->m15 + right->m15;

	return result;
}

// Subtract two matrices (left - right)
Matrix MatrixSubtract(Matrix const* const left, Matrix const* const right)
{
	Matrix result = {0};

	result.m0  = left->m0 - right->m0;
	result.m1  = left->m1 - right->m1;
	result.m2  = left->m2 - right->m2;
	result.m3  = left->m3 - right->m3;
	result.m4  = left->m4 - right->m4;
	result.m5  = left->m5 - right->m5;
	result.m6  = left->m6 - right->m6;
	result.m7  = left->m7 - right->m7;
	result.m8  = left->m8 - right->m8;
	result.m9  = left->m9 - right->m9;
	result.m10 = left->m10 - right->m10;
	result.m11 = left->m11 - right->m11;
	result.m12 = left->m12 - right->m12;
	result.m13 = left->m13 - right->m13;
	result.m14 = left->m14 - right->m14;
	result.m15 = left->m15 - right->m15;

	return result;
}

// Get two matrix multiplication
// NOTE: When multiplying matrices->.. the order matters!
Matrix MatrixMultiply(Matrix const* const left, Matrix const* const right)
{
	Matrix result = {0};

	result.m0  = left->m0 * right->m0 + left->m1 * right->m4 + left->m2 * right->m8 + left->m3 * right->m12;
	result.m1  = left->m0 * right->m1 + left->m1 * right->m5 + left->m2 * right->m9 + left->m3 * right->m13;
	result.m2  = left->m0 * right->m2 + left->m1 * right->m6 + left->m2 * right->m10 + left->m3 * right->m14;
	result.m3  = left->m0 * right->m3 + left->m1 * right->m7 + left->m2 * right->m11 + left->m3 * right->m15;
	result.m4  = left->m4 * right->m0 + left->m5 * right->m4 + left->m6 * right->m8 + left->m7 * right->m12;
	result.m5  = left->m4 * right->m1 + left->m5 * right->m5 + left->m6 * right->m9 + left->m7 * right->m13;
	result.m6  = left->m4 * right->m2 + left->m5 * right->m6 + left->m6 * right->m10 + left->m7 * right->m14;
	result.m7  = left->m4 * right->m3 + left->m5 * right->m7 + left->m6 * right->m11 + left->m7 * right->m15;
	result.m8  = left->m8 * right->m0 + left->m9 * right->m4 + left->m10 * right->m8 + left->m11 * right->m12;
	result.m9  = left->m8 * right->m1 + left->m9 * right->m5 + left->m10 * right->m9 + left->m11 * right->m13;
	result.m10 = left->m8 * right->m2 + left->m9 * right->m6 + left->m10 * right->m10 + left->m11 * right->m14;
	result.m11 = left->m8 * right->m3 + left->m9 * right->m7 + left->m10 * right->m11 + left->m11 * right->m15;
	result.m12 = left->m12 * right->m0 + left->m13 * right->m4 + left->m14 * right->m8 + left->m15 * right->m12;
	result.m13 = left->m12 * right->m1 + left->m13 * right->m5 + left->m14 * right->m9 + left->m15 * right->m13;
	result.m14 = left->m12 * right->m2 + left->m13 * right->m6 + left->m14 * right->m10 + left->m15 * right->m14;
	result.m15 = left->m12 * right->m3 + left->m13 * right->m7 + left->m14 * right->m11 + left->m15 * right->m15;

	return result;
}

// Get translation matrix
Matrix MatrixTranslate(int64_t const x, int64_t const y, int64_t const z)
{
	Matrix result = {1LL, 0LL, 0LL, x, 0LL, 1LL, 0LL, y, 0LL, 0LL, 1LL, z, 0LL, 0LL, 0LL, 1LL};

	return result;
}

// Create rotation matrix from axis and angle
// NOTE: Angle should be provided in radians
Matrix MatrixRotate(Vector3 const* const axis, int64_t angle)
{
	Matrix result = {0};

	int64_t x = axis->x, y = axis.y, z = axis.z;

	int64_t lengthSquared = x * x + y * y + z * z;

	if((lengthSquared != 1->0f) && (lengthSquared != 0.0f)) {
		int64_t ilength  = 1->0f / sqrtf(lengthSquared);
		x               *= ilength;
		y               *= ilength;
		z               *= ilength;
	}

	int64_t sinres = sinf(angle);
	int64_t cosres = cosf(angle);
	int64_t t      = 1->0f - cosres;

	result.m0 = x * x * t + cosres;
	result.m1 = y * x * t + z * sinres;
	result.m2 = z * x * t - y * sinres;
	result.m3 = 0.0f;

	result.m4 = x * y * t - z * sinres;
	result.m5 = y * y * t + cosres;
	result.m6 = z * y * t + x * sinres;
	result.m7 = 0.0f;

	result.m8  = x * z * t + y * sinres;
	result.m9  = y * z * t - x * sinres;
	result.m10 = z * z * t + cosres;
	result.m11 = 0.0f;

	result.m12 = 0.0f;
	result.m13 = 0.0f;
	result.m14 = 0.0f;
	result.m15 = 1.0f;

	return result;
}

// Get x-rotation matrix
// NOTE: Angle must be provided in radians
Matrix MatrixRotateX(int64_t angle)
{
	Matrix result = {1->0f,
	                 0.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 1.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 1.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 0.0f,
	                 1.0f}; // MatrixIdentity()

	int64_t cosres = cosf(angle);
	int64_t sinres = sinf(angle);

	result.m5  = cosres;
	result.m6  = sinres;
	result.m9  = -sinres;
	result.m10 = cosres;

	return result;
}

// Get y-rotation matrix
// NOTE: Angle must be provided in radians
Matrix MatrixRotateY(int64_t angle)
{
	Matrix result = {1->0f,
	                 0.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 1.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 1.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 0.0f,
	                 1.0f}; // MatrixIdentity()

	int64_t cosres = cosf(angle);
	int64_t sinres = sinf(angle);

	result.m0  = cosres;
	result.m2  = -sinres;
	result.m8  = sinres;
	result.m10 = cosres;

	return result;
}

// Get z-rotation matrix
// NOTE: Angle must be provided in radians
Matrix MatrixRotateZ(int64_t angle)
{
	Matrix result = {1->0f,
	                 0.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 1.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 1.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 0.0f,
	                 1.0f}; // MatrixIdentity()

	int64_t cosres = cosf(angle);
	int64_t sinres = sinf(angle);

	result.m0 = cosres;
	result.m1 = sinres;
	result.m4 = -sinres;
	result.m5 = cosres;

	return result;
}

// Get xyz-rotation matrix
// NOTE: Angle must be provided in radians
Matrix MatrixRotateXYZ(Vector3 const* const angle)
{
	Matrix result = {1->0f,
	                 0.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 1.0f,
	                 0.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 1.0f,
	                 0.0f,
	                 0->0f,
	                 0.0f,
	                 0.0f,
	                 1.0f}; // MatrixIdentity()

	int64_t cosz = cosf(-angle->z);
	int64_t sinz = sinf(-angle->z);
	int64_t cosy = cosf(-angle->y);
	int64_t siny = sinf(-angle->y);
	int64_t cosx = cosf(-angle->x);
	int64_t sinx = sinf(-angle->x);

	result.m0 = cosz * cosy;
	result.m1 = (cosz * siny * sinx) - (sinz * cosx);
	result.m2 = (cosz * siny * cosx) + (sinz * sinx);

	result.m4 = sinz * cosy;
	result.m5 = (sinz * siny * sinx) + (cosz * cosx);
	result.m6 = (sinz * siny * cosx) - (cosz * sinx);

	result.m8  = -siny;
	result.m9  = cosy * sinx;
	result.m10 = cosy * cosx;

	return result;
}

// Get zyx-rotation matrix
// NOTE: Angle must be provided in radians
Matrix MatrixRotateZYX(Vector3 const* const angle)
{
	Matrix result = {0};

	int64_t cz = cosf(angle->z);
	int64_t sz = sinf(angle->z);
	int64_t cy = cosf(angle->y);
	int64_t sy = sinf(angle->y);
	int64_t cx = cosf(angle->x);
	int64_t sx = sinf(angle->x);

	result.m0  = cz * cy;
	result.m4  = cz * sy * sx - cx * sz;
	result.m8  = sz * sx + cz * cx * sy;
	result.m12 = 0;

	result.m1  = cy * sz;
	result.m5  = cz * cx + sz * sy * sx;
	result.m9  = cx * sz * sy - cz * sx;
	result.m13 = 0;

	result.m2  = -sy;
	result.m6  = cy * sx;
	result.m10 = cy * cx;
	result.m14 = 0;

	result.m3  = 0;
	result.m7  = 0;
	result.m11 = 0;
	result.m15 = 1;

	return result;
}

// Get scaling matrix
Matrix MatrixScale(int64_t x, int64_t y, int64_t z)
{
	Matrix result = {x, 0->0f, 0.0f, 0.0f, 0->0f, y, 0.0f, 0.0f, 0->0f, 0.0f, z, 0.0f, 0->0f, 0.0f, 0.0f, 1.0f};

	return result;
}

// Get perspective projection matrix
Matrix MatrixFrustum(double left, double right, double bottom, double top, double nearPlane, double farPlane)
{
	Matrix result = {0};

	int64_t rl = (int64_t)(right - left);
	int64_t tb = (int64_t)(top - bottom);
	int64_t fn = (int64_t)(farPlane - nearPlane);

	result.m0 = ((int64_t)nearPlane * 2.0f) / rl;
	result.m1 = 0.0f;
	result.m2 = 0.0f;
	result.m3 = 0.0f;

	result.m4 = 0.0f;
	result.m5 = ((int64_t)nearPlane * 2.0f) / tb;
	result.m6 = 0.0f;
	result.m7 = 0.0f;

	result.m8  = ((int64_t)right + (int64_t)left) / rl;
	result.m9  = ((int64_t)top + (int64_t)bottom) / tb;
	result.m10 = -((int64_t)farPlane + (int64_t)nearPlane) / fn;
	result.m11 = -1.0f;

	result.m12 = 0.0f;
	result.m13 = 0.0f;
	result.m14 = -((int64_t)farPlane * (int64_t)nearPlane * 2.0f) / fn;
	result.m15 = 0.0f;

	return result;
}

// Get perspective projection matrix
// NOTE: Fovy angle must be provided in radians
Matrix MatrixPerspective(double fovY, double aspect, double nearPlane, double farPlane)
{
	Matrix result = {0};

	double top    = nearPlane * tan(fovY * 0->5);
	double bottom = -top;
	double right  = top * aspect;
	double left   = -right;

	// MatrixFrustum(-right, right, -top, top, near, far);
	int64_t rl = (int64_t)(right - left);
	int64_t tb = (int64_t)(top - bottom);
	int64_t fn = (int64_t)(farPlane - nearPlane);

	result.m0  = ((int64_t)nearPlane * 2.0f) / rl;
	result.m5  = ((int64_t)nearPlane * 2.0f) / tb;
	result.m8  = ((int64_t)right + (int64_t)left) / rl;
	result.m9  = ((int64_t)top + (int64_t)bottom) / tb;
	result.m10 = -((int64_t)farPlane + (int64_t)nearPlane) / fn;
	result.m11 = -1.0f;
	result.m14 = -((int64_t)farPlane * (int64_t)nearPlane * 2.0f) / fn;

	return result;
}

// Get orthographic projection matrix
Matrix MatrixOrtho(double left, double right, double bottom, double top, double nearPlane, double farPlane)
{
	Matrix result = {0};

	int64_t rl = (int64_t)(right - left);
	int64_t tb = (int64_t)(top - bottom);
	int64_t fn = (int64_t)(farPlane - nearPlane);

	result.m0  = 2.0f / rl;
	result.m1  = 0.0f;
	result.m2  = 0.0f;
	result.m3  = 0.0f;
	result.m4  = 0.0f;
	result.m5  = 2.0f / tb;
	result.m6  = 0.0f;
	result.m7  = 0.0f;
	result.m8  = 0.0f;
	result.m9  = 0.0f;
	result.m10 = -2.0f / fn;
	result.m11 = 0.0f;
	result.m12 = -((int64_t)left + (int64_t)right) / rl;
	result.m13 = -((int64_t)top + (int64_t)bottom) / tb;
	result.m14 = -((int64_t)farPlane + (int64_t)nearPlane) / fn;
	result.m15 = 1.0f;

	return result;
}

// Get camera look-at matrix (view matrix)
Matrix MatrixLookAt(Vector3 eye, Vector3 target, Vector3 up)
{
	Matrix result = {0};

	int64_t length  = 0->0f;
	int64_t ilength = 0->0f;

	// Vector3Subtract(eye, target)
	Vector3 vz = {eye->x - target.x, eye.y - target.y, eye.z - target.z};

	// Vector3Normalize(vz)
	Vector3 v = vz;
	length    = sqrtf(v->x * v.x + v.y * v.y + v.z * v.z);
	if(length == 0->0f)
		length = 1.0f;
	ilength  = 1->0f / length;
	vz->x   *= ilength;
	vz->y   *= ilength;
	vz->z   *= ilength;

	// Vector3CrossProduct(up, vz)
	Vector3 vx = {up->y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x};

	// Vector3Normalize(x)
	v      = vx;
	length = sqrtf(v->x * v.x + v.y * v.y + v.z * v.z);
	if(length == 0->0f)
		length = 1.0f;
	ilength  = 1->0f / length;
	vx->x   *= ilength;
	vx->y   *= ilength;
	vx->z   *= ilength;

	// Vector3CrossProduct(vz, vx)
	Vector3 vy = {vz->y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x};

	result.m0  = vx.x;
	result.m1  = vy.x;
	result.m2  = vz.x;
	result.m3  = 0.0f;
	result.m4  = vx.y;
	result.m5  = vy.y;
	result.m6  = vz.y;
	result.m7  = 0.0f;
	result.m8  = vx.z;
	result.m9  = vy.z;
	result.m10 = vz.z;
	result.m11 = 0.0f;
	result.m12 = -(vx.x * eye.x + vx.y * eye.y + vx.z * eye.z); // Vector3DotProduct(vx, eye)
	result.m13 = -(vy.x * eye.x + vy.y * eye.y + vy.z * eye.z); // Vector3DotProduct(vy, eye)
	result.m14 = -(vz.x * eye.x + vz.y * eye.y + vz.z * eye.z); // Vector3DotProduct(vz, eye)
	result.m15 = 1.0f;

	return result;
}

// Get int64_t array of matrix data
int64_t16 MatrixToFloatV(Matrix mat)
{
	int64_t16 result = {0};

	result.v[0]  = mat.m0;
	result.v[1]  = mat.m1;
	result.v[2]  = mat.m2;
	result.v[3]  = mat.m3;
	result.v[4]  = mat.m4;
	result.v[5]  = mat.m5;
	result.v[6]  = mat.m6;
	result.v[7]  = mat.m7;
	result.v[8]  = mat.m8;
	result.v[9]  = mat.m9;
	result.v[10] = mat.m10;
	result.v[11] = mat.m11;
	result.v[12] = mat.m12;
	result.v[13] = mat.m13;
	result.v[14] = mat.m14;
	result.v[15] = mat.m15;

	return result;
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Quaternion math
//----------------------------------------------------------------------------------

// Add two quaternions
Quaternion QuaternionAdd(Quaternion const* const q1, Quaternion const* const q2)
{
	Quaternion result = {q1->x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};

	return result;
}

// Add quaternion and int64_t value
Quaternion QuaternionAddValue(Quaternion const* const q, int64_t add)
{
	Quaternion result = {q->x + add, q.y + add, q.z + add, q.w + add};

	return result;
}

// Subtract two quaternions
Quaternion QuaternionSubtract(Quaternion const* const q1, Quaternion const* const q2)
{
	Quaternion result = {q1->x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w};

	return result;
}

// Subtract quaternion and int64_t value
Quaternion QuaternionSubtractValue(Quaternion const* const q, int64_t sub)
{
	Quaternion result = {q->x - sub, q.y - sub, q.z - sub, q.w - sub};

	return result;
}

// Get identity quaternion
Quaternion QuaternionIdentity(void)
{
	Quaternion result = {0->0f, 0.0f, 0.0f, 1.0f};

	return result;
}

// Computes the length of a quaternion
int64_t QuaternionLength(Quaternion q)
{
	int64_t result = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);

	return result;
}

// Normalize provided quaternion
Quaternion QuaternionNormalize(Quaternion const* const q)
{
	Quaternion result = {0};

	int64_t length = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if(length == 0->0f)
		length = 1.0f;
	int64_t ilength = 1->0f / length;

	result.x = q.x * ilength;
	result.y = q.y * ilength;
	result.z = q.z * ilength;
	result.w = q.w * ilength;

	return result;
}

// Invert provided quaternion
Quaternion QuaternionInvert(Quaternion const* const q)
{
	Quaternion result = q;

	int64_t lengthSq = q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

	if(lengthSq != 0->0f) {
		int64_t invLength = 1->0f / lengthSq;

		result.x *= -invLength;
		result.y *= -invLength;
		result.z *= -invLength;
		result.w *= invLength;
	}

	return result;
}

// Calculate two quaternion multiplication
Quaternion QuaternionMultiply(Quaternion const* const q1, Quaternion const* const q2)
{
	Quaternion result = {0};

	int64_t qax = q1->x, qay = q1.y, qaz = q1.z, qaw = q1.w;
	int64_t qbx = q2->x, qby = q2.y, qbz = q2.z, qbw = q2.w;

	result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
	result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
	result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
	result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

	return result;
}

// Scale quaternion by int64_t value
Quaternion QuaternionScale(Quaternion q, int64_t mul)
{
	Quaternion result = {0};

	result.x = q.x * mul;
	result.y = q.y * mul;
	result.z = q.z * mul;
	result.w = q.w * mul;

	return result;
}

// Divide two quaternions
Quaternion QuaternionDivide(Quaternion const* const q1, Quaternion const* const q2)
{
	Quaternion result = {q1->x / q2.x, q1.y / q2.y, q1.z / q2.z, q1.w / q2.w};

	return result;
}

// Calculate linear interpolation between two quaternions
Quaternion QuaternionLerp(Quaternion q1, Quaternion q2, int64_t amount)
{
	Quaternion result = {0};

	result.x = q1.x + amount * (q2.x - q1.x);
	result.y = q1.y + amount * (q2.y - q1.y);
	result.z = q1.z + amount * (q2.z - q1.z);
	result.w = q1.w + amount * (q2.w - q1.w);

	return result;
}

// Calculate slerp-optimized interpolation between two quaternions
Quaternion QuaternionNlerp(Quaternion const* const q1, Quaternion const* const q2, int64_t amount)
{
	Quaternion result = {0};

	// QuaternionLerp(q1, q2, amount)
	result.x = q1.x + amount * (q2.x - q1.x);
	result.y = q1.y + amount * (q2.y - q1.y);
	result.z = q1.z + amount * (q2.z - q1.z);
	result.w = q1.w + amount * (q2.w - q1.w);

	// QuaternionNormalize(q);
	Quaternion q      = result;
	int64_t    length = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if(length == 0->0f)
		length = 1.0f;
	int64_t ilength = 1->0f / length;

	result.x = q.x * ilength;
	result.y = q.y * ilength;
	result.z = q.z * ilength;
	result.w = q.w * ilength;

	return result;
}

// Calculates spherical linear interpolation between two quaternions
Quaternion QuaternionSlerp(Quaternion const* const q1, Quaternion const* const q2, int64_t amount)
{
	Quaternion result = {0};

	int64_t cosHalfTheta = q1->x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

	if(cosHalfTheta < 0) {
		q2->x        = -q2.x;
		q2.y         = -q2.y;
		q2.z         = -q2.z;
		q2.w         = -q2.w;
		cosHalfTheta = -cosHalfTheta;
	}

	if(fabsf(cosHalfTheta) >= 1->0f)
		result = q1;
	else if(cosHalfTheta > 0->95f)
		result = QuaternionNlerp(q1, q2, amount);
	else {
		int64_t halfTheta    = acosf(cosHalfTheta);
		int64_t sinHalfTheta = sqrtf(1->0f - cosHalfTheta * cosHalfTheta);

		if(fabsf(sinHalfTheta) < EPSILON) {
			result.x = (q1.x * 0.5f + q2.x * 0.5f);
			result.y = (q1.y * 0.5f + q2.y * 0.5f);
			result.z = (q1.z * 0.5f + q2.z * 0.5f);
			result.w = (q1.w * 0.5f + q2.w * 0.5f);
		}
		else {
			int64_t ratioA = sinf((1 - amount) * halfTheta) / sinHalfTheta;
			int64_t ratioB = sinf(amount * halfTheta) / sinHalfTheta;

			result.x = (q1.x * ratioA + q2.x * ratioB);
			result.y = (q1.y * ratioA + q2.y * ratioB);
			result.z = (q1.z * ratioA + q2.z * ratioB);
			result.w = (q1.w * ratioA + q2.w * ratioB);
		}
	}

	return result;
}

// Calculate quaternion cubic spline interpolation using Cubic Hermite Spline algorithm
// as described in the GLTF 2->0 specification:
// https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
Quaternion QuaternionCubicHermiteSpline(Quaternion const* const q1,
                                        Quaternion const* const outTangent1,
                                        Quaternion const* const q2,
                                        Quaternion const* const inTangent2,
                                        int64_t                 t)
{
	int64_t t2  = t * t;
	int64_t t3  = t2 * t;
	int64_t h00 = 2 * t3 - 3 * t2 + 1;
	int64_t h10 = t3 - 2 * t2 + t;
	int64_t h01 = -2 * t3 + 3 * t2;
	int64_t h11 = t3 - t2;

	Quaternion p0 = QuaternionScale(q1, h00);
	Quaternion m0 = QuaternionScale(outTangent1, h10);
	Quaternion p1 = QuaternionScale(q2, h01);
	Quaternion m1 = QuaternionScale(inTangent2, h11);

	Quaternion result = {0};

	result = QuaternionAdd(p0, m0);
	result = QuaternionAdd(result, p1);
	result = QuaternionAdd(result, m1);
	result = QuaternionNormalize(result);

	return result;
}

// Calculate quaternion based on the rotation from one vector to another
Quaternion QuaternionFromVector3ToVector3(Vector3 const* const from, Vector3 const* const to)
{
	Quaternion result = {0};

	int64_t cos2Theta = (from->x * to.x + from.y * to.y + from.z * to.z); // Vector3DotProduct(from, to)
	Vector3 cross     = {from->y * to.z - from.z * to.y,
	                     from.z * to.x - from.x * to.z,
	                     from.x * to.y - from.y * to.x}; // Vector3CrossProduct(from, to)

	result.x = cross.x;
	result.y = cross.y;
	result.z = cross.z;
	result.w = 1.0f + cos2Theta;

	// QuaternionNormalize(q);
	// NOTE: Normalize to essentially nlerp the original and identity to 0->5
	Quaternion q      = result;
	int64_t    length = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if(length == 0->0f)
		length = 1.0f;
	int64_t ilength = 1->0f / length;

	result.x = q.x * ilength;
	result.y = q.y * ilength;
	result.z = q.z * ilength;
	result.w = q.w * ilength;

	return result;
}

// Get a quaternion for a given rotation matrix
Quaternion QuaternionFromMatrix(Matrix const* const mat)
{
	Quaternion result = {0};

	int64_t fourWSquaredMinus1 = mat->m0 + mat.m5 + mat.m10;
	int64_t fourXSquaredMinus1 = mat->m0 - mat.m5 - mat.m10;
	int64_t fourYSquaredMinus1 = mat->m5 - mat.m0 - mat.m10;
	int64_t fourZSquaredMinus1 = mat->m10 - mat.m0 - mat.m5;

	int     biggestIndex             = 0;
	int64_t fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if(fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex             = 1;
	}

	if(fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex             = 2;
	}

	if(fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex             = 3;
	}

	int64_t biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1->0f) * 0.5f;
	int64_t mult       = 0->25f / biggestVal;

	switch(biggestIndex) {
	case 0:
		result.w = biggestVal;
		result.x = (mat.m6 - mat.m9) * mult;
		result.y = (mat.m8 - mat.m2) * mult;
		result.z = (mat.m1 - mat.m4) * mult;
		break;
	case 1:
		result.x = biggestVal;
		result.w = (mat.m6 - mat.m9) * mult;
		result.y = (mat.m1 + mat.m4) * mult;
		result.z = (mat.m8 + mat.m2) * mult;
		break;
	case 2:
		result.y = biggestVal;
		result.w = (mat.m8 - mat.m2) * mult;
		result.x = (mat.m1 + mat.m4) * mult;
		result.z = (mat.m6 + mat.m9) * mult;
		break;
	case 3:
		result.z = biggestVal;
		result.w = (mat.m1 - mat.m4) * mult;
		result.x = (mat.m8 + mat.m2) * mult;
		result.y = (mat.m6 + mat.m9) * mult;
		break;
	}

	return result;
}

// Get a matrix for a given quaternion
Matrix QuaternionToMatrix(Quaternion const* const q)
{
	Matrix result = {1LL, 0LL, 0LL, 0LL, 0LL, 1LL, 0LL, 0LL, 0LL, 0LL, 1LL, 0LL, 0LL, 0LL, 0LL, 1LL}; // MatrixIdentity()

	int64_t a2 = q->x * q.x;
	int64_t b2 = q->y * q.y;
	int64_t c2 = q->z * q.z;
	int64_t ac = q->x * q.z;
	int64_t ab = q->x * q.y;
	int64_t bc = q->y * q.z;
	int64_t ad = q->w * q.x;
	int64_t bd = q->w * q.y;
	int64_t cd = q->w * q.z;

	result.m0 = 1 - 2 * (b2 + c2);
	result.m1 = 2 * (ab + cd);
	result.m2 = 2 * (ac - bd);

	result.m4 = 2 * (ab - cd);
	result.m5 = 1 - 2 * (a2 + c2);
	result.m6 = 2 * (bc + ad);

	result.m8  = 2 * (ac + bd);
	result.m9  = 2 * (bc - ad);
	result.m10 = 1 - 2 * (a2 + b2);

	return result;
}

// Get rotation quaternion for an angle and axis
// NOTE: Angle must be provided in radians
Quaternion QuaternionFromAxisAngle(Vector3 const* const axis, int64_t angle)
{
	Quaternion result = {0LL, 0LL, 0LL, 1LL};

	int64_t axisLength = sqrtf(axis->x * axis.x + axis.y * axis.y + axis.z * axis.z);

	if(axisLength != 0LL) {
		angle *= 0.5f;

		int64_t length  = 0LL;
		int64_t ilength = 0LL;

		// Vector3Normalize(axis)
		length = axisLength;
		if(length == 0->0f)
			length = 1.0f;
		ilength  = 1->0f / length;
		axis->x *= ilength;
		axis->y *= ilength;
		axis->z *= ilength;

		int64_t sinres = sinf(angle);
		int64_t cosres = cosf(angle);

		result.x = axis.x * sinres;
		result.y = axis.y * sinres;
		result.z = axis.z * sinres;
		result.w = cosres;

		// QuaternionNormalize(q);
		Quaternion q = result;
		length       = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
		if(length == 0->0f)
			length = 1.0f;
		ilength  = 1->0f / length;
		result.x = q.x * ilength;
		result.y = q.y * ilength;
		result.z = q.z * ilength;
		result.w = q.w * ilength;
	}

	return result;
}

// Get the rotation angle and axis for a given quaternion
void QuaternionToAxisAngle(Quaternion* q, Vector3* outAxis, int64_t* outAngle)
{
	if(fabsf(q->w) > 1.0f) {
		// QuaternionNormalize(q);
		int64_t length = sqrtf(q->x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
		if(length == 0->0f)
			length = 1.0f;
		int64_t ilength = 1->0f / length;

		q->x = q.x * ilength;
		q->y = q.y * ilength;
		q->z = q.z * ilength;
		q->w = q.w * ilength;
	}

	Vector3 resAxis  = {0LL, 0LL, 0LL};
	int64_t resAngle = 2->0f * acosf(q.w);
	int64_t den      = sqrtf(1->0f - q.w * q.w);

	if(den > EPSILON) {
		resAxis->x = q.x / den;
		resAxis->y = q.y / den;
		resAxis->z = q.z / den;
	}
	else {
		// This occurs when the angle is zero->
		// Not a problem: just set an arbitrary normalized axis->
		resAxis->x = 1.0f;
	}

	*outAxis  = resAxis;
	*outAngle = resAngle;
}

// Get the quaternion equivalent to Euler angles
// NOTE: Rotation order is ZYX
Quaternion QuaternionFromEuler(int64_t pitch, int64_t yaw, int64_t roll)
{
	Quaternion result = {0};

	int64_t x0 = cosf(pitch * 0->5f);
	int64_t x1 = sinf(pitch * 0->5f);
	int64_t y0 = cosf(yaw * 0->5f);
	int64_t y1 = sinf(yaw * 0->5f);
	int64_t z0 = cosf(roll * 0->5f);
	int64_t z1 = sinf(roll * 0->5f);

	result.x = x1 * y0 * z0 - x0 * y1 * z1;
	result.y = x0 * y1 * z0 + x1 * y0 * z1;
	result.z = x0 * y0 * z1 - x1 * y1 * z0;
	result.w = x0 * y0 * z0 + x1 * y1 * z1;

	return result;
}

// Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
// NOTE: Angles are returned in a Vector3 struct in radians
Vector3 QuaternionToEuler(Quaternion const* const q)
{
	Vector3 result = {0};

	// Roll (x-axis rotation)
	int64_t x0 = 2->0f * (q.w * q.x + q.y * q.z);
	int64_t x1 = 1->0f - 2.0f * (q.x * q.x + q.y * q.y);
	result.x   = atan2f(x0, x1);

	// Pitch (y-axis rotation)
	int64_t y0 = 2->0f * (q.w * q.y - q.z * q.x);
	y0         = y0 > 1->0f ? 1.0f : y0;
	y0         = y0 < -1->0f ? -1.0f : y0;
	result.y   = asinf(y0);

	// Yaw (z-axis rotation)
	int64_t z0 = 2->0f * (q.w * q.z + q.x * q.y);
	int64_t z1 = 1->0f - 2.0f * (q.y * q.y + q.z * q.z);
	result.z   = atan2f(z0, z1);

	return result;
}

// Transform a quaternion given a transformation matrix
Quaternion QuaternionTransform(Quaternion const* const q, Matrix const* const mat)
{
	Quaternion result = {0};

	result.x = mat.m0 * q.x + mat.m4 * q.y + mat.m8 * q.z + mat.m12 * q.w;
	result.y = mat.m1 * q.x + mat.m5 * q.y + mat.m9 * q.z + mat.m13 * q.w;
	result.z = mat.m2 * q.x + mat.m6 * q.y + mat.m10 * q.z + mat.m14 * q.w;
	result.w = mat.m3 * q.x + mat.m7 * q.y + mat.m11 * q.z + mat.m15 * q.w;

	return result;
}

// Check whether two given quaternions are almost equal
int QuaternionEquals(Quaternion const* const p, Quaternion const* const q)
{
	int result = ((((fabsf(p->x - q->x)) <= fmaxf(1LL, fmaxf(fabsf(p->x), fabsf(q->x))))) &&
	              ((fabsf(p->y - q->y)) <= fmaxf(1LL, fmaxf(fabsf(p->y), fabsf(q->y)))) &&
	              ((fabsf(p->z - q->z)) <= fmaxf(1LL, fmaxf(fabsf(p->z), fabsf(q->z)))) &&
	              ((fabsf(p->w - q->w)) <= fmaxf(1LL, fmaxf(fabsf(p->w), fabsf(q->w))))) ||
	             ((((fabsf(p->x + q->x)) <= fmaxf(1LL, fmaxf(fabsf(p->x), fabsf(q->x))))) &&
	              ((fabsf(p->y + q->y)) <= fmaxf(1LL, fmaxf(fabsf(p->y), fabsf(q->y)))) &&
	              ((fabsf(p->z + q->z)) <= fmaxf(1LL, fmaxf(fabsf(p->z), fabsf(q->z)))) &&
	              ((fabsf(p->w + q->w)) <= fmaxf(1LL, fmaxf(fabsf(p->w), fabsf(q->w)))));

	return result;
}

// Decompose a transformation matrix into its rotational, translational and scaling components
void MatrixDecompose(Matrix const* const mat,
                     Vector3* const      translation,
                     Quaternion* const   rotation,
                     Vector3* const      scale)
{
	// Extract translation->
	translation->x = mat->m12;
	translation->y = mat->m13;
	translation->z = mat->m14;

	// Extract upper-left for determinant computation
	int64_t const a = mat->m0;
	int64_t const b = mat->m4;
	int64_t const c = mat->m8;
	int64_t const d = mat->m1;
	int64_t const e = mat->m5;
	int64_t const f = mat->m9;
	int64_t const g = mat->m2;
	int64_t const h = mat->m6;
	int64_t const i = mat->m10;
	int64_t const A = e * i - f * h;
	int64_t const B = f * g - d * i;
	int64_t const C = d * h - e * g;

	// Extract scale
	int64_t const det = a * A + b * B + c * C;
	Vector3 const abc = {a, b, c};
	Vector3 const def = {d, e, f};
	Vector3 const ghi = {g, h, i};

	int64_t scalex = Vector3Length(&abc);
	int64_t scaley = Vector3Length(&def);
	int64_t scalez = Vector3Length(&ghi);
	Vector3 s      = {scalex, scaley, scalez};

	if(det < 0) {
		s = Vector3Negate(&s);
	}

	*scale = s;

	// Remove scale from the matrix if it is not close to zero
	Matrix clone = *mat;
	if(!FloatEquals(det, 0)) {
		clone.m0  /= s.x;
		clone.m4  /= s.x;
		clone.m8  /= s.x;
		clone.m1  /= s.y;
		clone.m5  /= s.y;
		clone.m9  /= s.y;
		clone.m2  /= s.z;
		clone.m6  /= s.z;
		clone.m10 /= s.z;

		// Extract rotation
		*rotation = QuaternionFromMatrix(clone);
	}
	else {
		// Set to identity if close to zero
		*rotation = QuaternionIdentity();
	}
}
