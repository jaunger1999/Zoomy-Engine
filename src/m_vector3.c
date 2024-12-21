#include "m_vector3.h"
#include "m_fixed.h"
#include "m_matrix.h"

// Vector with components value 0LL
Vector3 Vector3Zero(void)
{
	Vector3 result = {0LL, 0LL, 0LL};

	return result;
}

// Vector with components value 1LL
Vector3 Vector3One(void)
{
	Vector3 result = {1LL, 1LL, 1LL};

	return result;
}

// Add two vectors
Vector3 Vector3Add(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};

	return result;
}

// Add vector and fixed_t value
Vector3 Vector3AddValue(Vector3 const* const v, fixed_t add)
{
	Vector3 result = {v->x + add, v->y + add, v->z + add};

	return result;
}

// Subtract two vectors
Vector3 Vector3Subtract(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};

	return result;
}

// Subtract vector by fixed_t value
Vector3 Vector3SubtractValue(Vector3 const* const v, fixed_t const sub)
{
	Vector3 result = {v->x - sub, v->y - sub, v->z - sub};

	return result;
}

// Multiply vector by scalar
Vector3 Vector3Scale(Vector3 const* const v, fixed_t const scalar)
{
	Vector3 result = {v->x * scalar, v->y * scalar, v->z * scalar};

	return result;
}

// Multiply vector by vector
Vector3 Vector3Multiply(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {v1->x * v2->x, v1->y * v2->y, v1->z * v2->z};

	return result;
}

// Calculate two vectors cross product
Vector3 Vector3CrossProduct(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {v1->y * v2->z - v1->z * v2->y, v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x};

	return result;
}

// Calculate one vector perpendicular vector
Vector3 Vector3Perpendicular(Vector3 const* const v)
{
	Vector3 result = {0};

	fixed_t min          = fabsf(v->x);
	Vector3 cardinalAxis = {1LL, 0LL, 0LL};

	if(fabsf(v->y) < min) {
		min          = fabsf(v->y);
		Vector3 tmp  = {0LL, 1LL, 0LL};
		cardinalAxis = tmp;
	}

	if(fabsf(v->z) < min) {
		Vector3 tmp  = {0LL, 0LL, 1LL};
		cardinalAxis = tmp;
	}

	// Cross product between vectors
	result.x = v->y * cardinalAxis.z - v->z * cardinalAxis.y;
	result.y = v->z * cardinalAxis.x - v->x * cardinalAxis.z;
	result.z = v->x * cardinalAxis.y - v->y * cardinalAxis.x;

	return result;
}

// Calculate vector length
fixed_t Vector3Length(Vector3 const* const v)
{
	fixed_t result = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);

	return result;
}

// Calculate vector square length
fixed_t Vector3LengthSqr(Vector3 const* const v)
{
	fixed_t result = v->x * v->x + v->y * v->y + v->z * v->z;

	return result;
}

// Calculate two vectors dot product
fixed_t Vector3DotProduct(Vector3 const* const v1, Vector3 const* const v2)
{
	fixed_t result = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);

	return result;
}

// Calculate distance between two vectors
fixed_t Vector3Distance(Vector3 const* const v1, Vector3 const* const v2)
{
	fixed_t result = 0LL;

	fixed_t dx = v2->x - v1->x;
	fixed_t dy = v2->y - v1->y;
	fixed_t dz = v2->z - v1->z;
	result     = sqrtf(dx * dx + dy * dy + dz * dz);

	return result;
}

// Calculate square distance between two vectors
fixed_t Vector3DistanceSqr(Vector3 const* const v1, Vector3 const* const v2)
{
	fixed_t result = 0LL;

	fixed_t dx = v2->x - v1->x;
	fixed_t dy = v2->y - v1->y;
	fixed_t dz = v2->z - v1->z;
	result     = dx * dx + dy * dy + dz * dz;

	return result;
}

// Calculate angle between two vectors
fixed_t Vector3Angle(Vector3 const* const v1, Vector3 const* const v2)
{
	fixed_t result = 0LL;

	Vector3 cross = {v1->y * v2->z - v1->z * v2->y, v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x};
	fixed_t len   = sqrtf(cross->x * cross.x + cross.y * cross.y + cross.z * cross.z);
	fixed_t dot   = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
	result        = atan2f(len, dot);

	return result;
}

// Negate provided vector (invert direction)
Vector3 Vector3Negate(Vector3 const* const v)
{
	Vector3 result = {-v->x, -v->y, -v->z};

	return result;
}

// Divide vector by vector
Vector3 Vector3Divide(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {v1->x / v2->x, v1->y / v2->y, v1->z / v2->z};

	return result;
}

// Normalize provided vector
Vector3 Vector3Normalize(Vector3 const* const v)
{
	Vector3 result = *v;

	fixed_t length = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
	if(length != 0LL) {
		fixed_t ilength = 1LL / length;

		result.x *= ilength;
		result.y *= ilength;
		result.z *= ilength;
	}

	return result;
}

// Calculate the projection of the vector v1 on to v2
Vector3 Vector3Project(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {0};

	fixed_t v1dv2 = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
	fixed_t v2dv2 = (v2->x * v2->x + v2->y * v2->y + v2->z * v2->z);

	fixed_t mag = v1dv2 / v2dv2;

	result.x = v2->x * mag;
	result.y = v2->y * mag;
	result.z = v2->z * mag;

	return result;
}

// Calculate the rejection of the vector v1 on to v2
Vector3 Vector3Reject(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {0};

	fixed_t v1dv2 = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
	fixed_t v2dv2 = (v2->x * v2->x + v2->y * v2->y + v2->z * v2->z);

	fixed_t mag = v1dv2 / v2dv2;

	result.x = v1->x - (v2->x * mag);
	result.y = v1->y - (v2->y * mag);
	result.z = v1->z - (v2->z * mag);

	return result;
}

// Orthonormalize provided vectors
// Makes vectors normalized and orthogonal to each other
// Gram-Schmidt function implementation
void Vector3OrthoNormalize(Vector3* v1, Vector3* v2)
{
	fixed_t length  = 0LL;
	fixed_t ilength = 0LL;

	// Vector3Normalize(*v1);
	Vector3 v = *v1;
	length    = sqrtf(v->x * v.x + v.y * v.y + v.z * v.z);
	if(length == 0LL)
		length = 1LL;
	ilength  = 1LL / length;
	v1->x   *= ilength;
	v1->y   *= ilength;
	v1->z   *= ilength;

	// Vector3CrossProduct(*v1, *v2)
	Vector3 vn1 = {v1->y * v2->z - v1->z * v2->y, v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x};

	// Vector3Normalize(vn1);
	v      = vn1;
	length = sqrtf(v->x * v.x + v.y * v.y + v.z * v.z);
	if(length == 0LL)
		length = 1LL;
	ilength  = 1LL / length;
	vn1.x   *= ilength;
	vn1.y   *= ilength;
	vn1.z   *= ilength;

	// Vector3CrossProduct(vn1, *v1)
	Vector3 vn2 = {vn1.y * v1->z - vn1.z * v1->y, vn1.z * v1->x - vn1.x * v1->z, vn1.x * v1->y - vn1.y * v1->x};

	*v2 = vn2;
}

// Transforms a Vector3 by a given Matrix
Vector3 Vector3Transform(Vector3 const* const v, Matrix const* const mat)
{
	Vector3 result = {0};

	fixed_t x = v->x;
	fixed_t y = v->y;
	fixed_t z = v->z;

	result.x = mat->m0 * x + mat->m4 * y + mat->m8 * z + mat->m12;
	result.y = mat->m1 * x + mat->m5 * y + mat->m9 * z + mat->m13;
	result.z = mat->m2 * x + mat->m6 * y + mat->m10 * z + mat->m14;

	return result;
}

// Transform a vector by quaternion rotation
Vector3 Vector3RotateByQuaternion(Vector3 const* const v, Quaternion const* const q)
{
	Vector3 result = {0};

	result.x = v->x * (q->x * q->x + q->w * q->w - q->y * q->y - q->z * q->z) +
	           v->y * (2 * q->x * q->y - 2 * q->w * q->z) + v->z * (2 * q->x * q->z + 2 * q->w * q->y);
	result.y = v->x * (2 * q->w * q->z + 2 * q->x * q->y) +
	           v->y * (q->w * q->w - q->x * q->x + q->y * q->y - q->z * q->z) +
	           v->z * (-2 * q->w * q->x + 2 * q->y * q->z);
	result.z = v->x * (-2 * q->w * q->y + 2 * q->x * q->z) + v->y * (2 * q->w * q->x + 2 * q->y * q->z) +
	           v->z * (q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z);

	return result;
}

// Rotates a vector around an axis
Vector3 Vector3RotateByAxisAngle(Vector3 const* const v, Vector3 const* const axis, fixed_t const angle)
{
	// Using Euler-Rodrigues Formula
	// Ref->: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

	Vector3 result = *v;

	// Vector3Normalize(axis);
	fixed_t length = sqrtf(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
	if(length == 0LL) {
		length = 1LL;
	}

	fixed_t ilength = 1LL / length;

	Vector3 axisCopy  = *axis;
	axisCopy.x       *= ilength;
	axisCopy.y       *= ilength;
	axisCopy.z       *= ilength;

	fixed_t halfAngle = angle / 2LL;
	fixed_t a         = sinf(halfAngle);
	fixed_t b         = axis->x * a;
	fixed_t c         = axis->y * a;
	fixed_t d         = axis->z * a;
	a                 = cosf(halfAngle);
	Vector3 w         = {b, c, d};

	// Vector3CrossProduct(w, v)
	Vector3 wv = {w.y * v->z - w.z * v->y, w.z * v->x - w.x * v->z, w.x * v->y - w.y * v->x};

	// Vector3CrossProduct(w, wv)
	Vector3 wwv = {w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z, w.x * wv.y - w.y * wv.x};

	// Vector3Scale(wv, 2*a)
	a    *= 2;
	wv.x *= a;
	wv.y *= a;
	wv.z *= a;

	// Vector3Scale(wwv, 2)
	wwv.x *= 2;
	wwv.y *= 2;
	wwv.z *= 2;

	result.x += wv.x;
	result.y += wv.y;
	result.z += wv.z;

	result.x += wwv.x;
	result.y += wwv.y;
	result.z += wwv.z;

	return result;
}

// Move Vector towards target
Vector3 Vector3MoveTowards(Vector3 const* const v, Vector3 const* const target, fixed_t maxDistance)
{
	Vector3 result = {0};

	fixed_t dx    = target->x - v->x;
	fixed_t dy    = target->y - v->y;
	fixed_t dz    = target->z - v->z;
	fixed_t value = (dx * dx) + (dy * dy) + (dz * dz);

	if((value == 0) || ((maxDistance >= 0) && (value <= maxDistance * maxDistance)))
		return *target;

	fixed_t dist = sqrtf(value);

	result.x = v->x + dx / dist * maxDistance;
	result.y = v->y + dy / dist * maxDistance;
	result.z = v->z + dz / dist * maxDistance;

	return result;
}

// Calculate linear interpolation between two vectors
Vector3 Vector3Lerp(Vector3 v1, Vector3 v2, fixed_t amount)
{
	Vector3 result = {0};

	result.x = v1.x + amount * (v2.x - v1.x);
	result.y = v1.y + amount * (v2.y - v1.y);
	result.z = v1.z + amount * (v2.z - v1.z);

	return result;
}

// Calculate cubic hermite interpolation between two vectors and their tangents
// as described in the GLTF 2->0 specification:
// https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
Vector3 Vector3CubicHermite(Vector3 v1, Vector3 tangent1, Vector3 v2, Vector3 tangent2, fixed_t amount)
{
	Vector3 result = {0};

	fixed_t amountPow2 = amount * amount;
	fixed_t amountPow3 = amount * amount * amount;

	result.x = (2 * amountPow3 - 3 * amountPow2 + 1) * v1.x + (amountPow3 - 2 * amountPow2 + amount) * tangent1.x +
	           (-2 * amountPow3 + 3 * amountPow2) * v2.x + (amountPow3 - amountPow2) * tangent2.x;
	result.y = (2 * amountPow3 - 3 * amountPow2 + 1) * v1.y + (amountPow3 - 2 * amountPow2 + amount) * tangent1.y +
	           (-2 * amountPow3 + 3 * amountPow2) * v2.y + (amountPow3 - amountPow2) * tangent2.y;
	result.z = (2 * amountPow3 - 3 * amountPow2 + 1) * v1.z + (amountPow3 - 2 * amountPow2 + amount) * tangent1.z +
	           (-2 * amountPow3 + 3 * amountPow2) * v2.z + (amountPow3 - amountPow2) * tangent2.z;

	return result;
}

// Calculate reflected vector to normal
Vector3 Vector3Reflect(Vector3 const* const v, Vector3 const* const normal)
{
	Vector3 result = {0};

	// I is the original vector
	// N is the normal of the incident plane
	// R = I - (2*N*(DotProduct[I, N]))

	fixed_t dotProduct = (v->x * normal->x + v->y * normal->y + v->z * normal->z);

	result.x = v->x - (2LL * normal->x) * dotProduct;
	result.y = v->y - (2LL * normal->y) * dotProduct;
	result.z = v->z - (2LL * normal->z) * dotProduct;

	return result;
}

// Get min value for each pair of components
Vector3 Vector3Min(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {0};

	result.x = fminf(v1->x, v2->x);
	result.y = fminf(v1->y, v2->y);
	result.z = fminf(v1->z, v2->z);

	return result;
}

// Get max value for each pair of components
Vector3 Vector3Max(Vector3 const* const v1, Vector3 const* const v2)
{
	Vector3 result = {0};

	result.x = fmaxf(v1->x, v2->x);
	result.y = fmaxf(v1->y, v2->y);
	result.z = fmaxf(v1->z, v2->z);

	return result;
}

// Compute barycenter coordinates (u, v, w) for point p with respect to triangle (a, b, c)
// NOTE: Assumes P is on the plane of the triangle
Vector3
Vector3Barycenter(Vector3 const* const p, Vector3 const* const a, Vector3 const* const b, Vector3 const* const c)
{
	Vector3 result = {0};

	Vector3 v0  = {b->x - a->x, b->y - a->y, b->z - a->z};   // Vector3Subtract(b, a)
	Vector3 v1  = {c->x - a->x, c->y - a->y, c->z - a->z};   // Vector3Subtract(c, a)
	Vector3 v2  = {p->x - a->x, p->y - a->y, p->z - a->z};   // Vector3Subtract(p, a)
	fixed_t d00 = (v0.x * v0.x + v0.y * v0.y + v0.z * v0.z); // Vector3DotProduct(v0, v0)
	fixed_t d01 = (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z); // Vector3DotProduct(v0, v1)
	fixed_t d11 = (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z); // Vector3DotProduct(v1, v1)
	fixed_t d20 = (v2.x * v0.x + v2.y * v0.y + v2.z * v0.z); // Vector3DotProduct(v2, v0)
	fixed_t d21 = (v2.x * v1.x + v2.y * v1.y + v2.z * v1.z); // Vector3DotProduct(v2, v1)

	fixed_t denom = d00 * d11 - d01 * d01;

	result.y = (d11 * d20 - d01 * d21) / denom;
	result.z = (d00 * d21 - d01 * d20) / denom;
	result.x = 1LL - (result.z + result.y);

	return result;
}

// Projects a Vector3 from screen space into object space
// NOTE: We are avoiding calling other raymath functions despite available
Vector3 Vector3Unproject(Vector3 const* const source, Matrix const* const projection, Matrix const* const view)
{
	Vector3 result = {0};

	// Calculate unprojected matrix (multiply view matrix by projection matrix) and invert it
	Matrix matViewProj = {
		// MatrixMultiply(view, projection);
		view->m0 * projection->m0 + view->m1 * projection->m4 + view->m2 * projection->m8 + view->m3 * projection->m12,
		view->m0 * projection->m1 + view->m1 * projection->m5 + view->m2 * projection->m9 + view->m3 * projection->m13,
		view->m0 * projection->m2 + view->m1 * projection->m6 + view->m2 * projection->m10 + view->m3 * projection->m14,
		view->m0 * projection->m3 + view->m1 * projection->m7 + view->m2 * projection->m11 + view->m3 * projection->m15,
		view->m4 * projection->m0 + view->m5 * projection->m4 + view->m6 * projection->m8 + view->m7 * projection->m12,
		view->m4 * projection->m1 + view->m5 * projection->m5 + view->m6 * projection->m9 + view->m7 * projection->m13,
		view->m4 * projection->m2 + view->m5 * projection->m6 + view->m6 * projection->m10 + view->m7 * projection->m14,
		view->m4 * projection->m3 + view->m5 * projection->m7 + view->m6 * projection->m11 + view->m7 * projection->m15,
		view->m8 * projection->m0 + view->m9 * projection->m4 + view->m10 * projection->m8 + view->m11 * projection->m12,
		view->m8 * projection->m1 + view->m9 * projection->m5 + view->m10 * projection->m9 + view->m11 * projection->m13,
		view->m8 * projection->m2 + view->m9 * projection->m6 + view->m10 * projection->m10 + view->m11 * projection->m14,
		view->m8 * projection->m3 + view->m9 * projection->m7 + view->m10 * projection->m11 + view->m11 * projection->m15,
		view->m12 * projection->m0 + view->m13 * projection->m4 + view->m14 * projection->m8 + view->m15 * projection->m12,
		view->m12 * projection->m1 + view->m13 * projection->m5 + view->m14 * projection->m9 + view->m15 * projection->m13,
		view->m12 * projection->m2 + view->m13 * projection->m6 + view->m14 * projection->m10 + view->m15 * projection->m14,
		view->m12 * projection->m3 + view->m13 * projection->m7 + view->m14 * projection->m11 + view->m15 * projection->m15};

	// Calculate inverted matrix -> MatrixInvert(matViewProj);
	// Cache the matrix values (speed optimization)
	fixed_t a00 = matViewProj.m0, a01 = matViewProj.m1, a02 = matViewProj.m2, a03 = matViewProj.m3;
	fixed_t a10 = matViewProj.m4, a11 = matViewProj.m5, a12 = matViewProj.m6, a13 = matViewProj.m7;
	fixed_t a20 = matViewProj.m8, a21 = matViewProj.m9, a22 = matViewProj.m10, a23 = matViewProj.m11;
	fixed_t a30 = matViewProj.m12, a31 = matViewProj.m13, a32 = matViewProj.m14, a33 = matViewProj.m15;

	fixed_t b00 = a00 * a11 - a01 * a10;
	fixed_t b01 = a00 * a12 - a02 * a10;
	fixed_t b02 = a00 * a13 - a03 * a10;
	fixed_t b03 = a01 * a12 - a02 * a11;
	fixed_t b04 = a01 * a13 - a03 * a11;
	fixed_t b05 = a02 * a13 - a03 * a12;
	fixed_t b06 = a20 * a31 - a21 * a30;
	fixed_t b07 = a20 * a32 - a22 * a30;
	fixed_t b08 = a20 * a33 - a23 * a30;
	fixed_t b09 = a21 * a32 - a22 * a31;
	fixed_t b10 = a21 * a33 - a23 * a31;
	fixed_t b11 = a22 * a33 - a23 * a32;

	// Calculate the invert determinant (inlined to avoid double-caching)
	fixed_t invDet = 1LL / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

	Matrix matViewProjInv = {(a11 * b11 - a12 * b10 + a13 * b09) * invDet,
	                         (-a01 * b11 + a02 * b10 - a03 * b09) * invDet,
	                         (a31 * b05 - a32 * b04 + a33 * b03) * invDet,
	                         (-a21 * b05 + a22 * b04 - a23 * b03) * invDet,
	                         (-a10 * b11 + a12 * b08 - a13 * b07) * invDet,
	                         (a00 * b11 - a02 * b08 + a03 * b07) * invDet,
	                         (-a30 * b05 + a32 * b02 - a33 * b01) * invDet,
	                         (a20 * b05 - a22 * b02 + a23 * b01) * invDet,
	                         (a10 * b10 - a11 * b08 + a13 * b06) * invDet,
	                         (-a00 * b10 + a01 * b08 - a03 * b06) * invDet,
	                         (a30 * b04 - a31 * b02 + a33 * b00) * invDet,
	                         (-a20 * b04 + a21 * b02 - a23 * b00) * invDet,
	                         (-a10 * b09 + a11 * b07 - a12 * b06) * invDet,
	                         (a00 * b09 - a01 * b07 + a02 * b06) * invDet,
	                         (-a30 * b03 + a31 * b01 - a32 * b00) * invDet,
	                         (a20 * b03 - a21 * b01 + a22 * b00) * invDet};

	// Create quaternion from source point
	Quaternion quat = {source->x, source->y, source->z, 1LL};

	// Multiply quat point by unprojecte matrix
	Quaternion qtransformed = {// QuaternionTransform(quat, matViewProjInv)
	                           matViewProjInv.m0 * quat.x + matViewProjInv.m4 * quat.y + matViewProjInv.m8 * quat.z +
	                              matViewProjInv.m12 * quat.w,
	                           matViewProjInv.m1 * quat.x + matViewProjInv.m5 * quat.y + matViewProjInv.m9 * quat.z +
	                              matViewProjInv.m13 * quat.w,
	                           matViewProjInv.m2 * quat.x + matViewProjInv.m6 * quat.y + matViewProjInv.m10 * quat.z +
	                              matViewProjInv.m14 * quat.w,
	                           matViewProjInv.m3 * quat.x + matViewProjInv.m7 * quat.y + matViewProjInv.m11 * quat.z +
	                              matViewProjInv.m15 * quat.w};

	// Normalized world points in vectors
	result.x = qtransformed.x / qtransformed.w;
	result.y = qtransformed.y / qtransformed.w;
	result.z = qtransformed.z / qtransformed.w;

	return result;
}

// Invert the given vector
Vector3 Vector3Invert(Vector3 const* const v)
{
	Vector3 result = {1LL / v->x, 1LL / v->y, 1LL / v->z};

	return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
Vector3 Vector3Clamp(Vector3 const* const v, Vector3 const* const min, Vector3 const* const max)
{
	Vector3 result = {0};

	result.x = fminf(max->x, fmaxf(min->x, v->x));
	result.y = fminf(max->y, fmaxf(min->y, v->y));
	result.z = fminf(max->z, fmaxf(min->z, v->z));

	return result;
}

// Clamp the magnitude of the vector between two values
Vector3 Vector3ClampValue(Vector3 const* const v, fixed_t const min, fixed_t const max)
{
	Vector3 result = *v;

	fixed_t length = (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
	if(length > 0LL) {
		length = sqrtf(length);

		fixed_t scale = 1; // By default, 1 as the neutral element->
		if(length < min) {
			scale = min / length;
		}
		else if(length > max) {
			scale = max / length;
		}

		result.x = v->x * scale;
		result.y = v->y * scale;
		result.z = v->z * scale;
	}

	return result;
}

// Check whether two given vectors are almost equal
int Vector3Equals(Vector3 const* const p, Vector3 const* const q)
{
	int result = ((fabsf(p->x - q->x)) <= fmaxf(1LL, fmaxf(fabsf(p->x), fabsf(q->x)))) &&
	             ((fabsf(p->y - q->y)) <= fmaxf(1LL, fmaxf(fabsf(p->y), fabsf(q->y)))) &&
	             ((fabsf(p->z - q->z)) <= fmaxf(1LL, fmaxf(fabsf(p->z), fabsf(q->z))));

	return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
Vector3 Vector3Refract(Vector3 const* const v, Vector3 const* const n, fixed_t const r)
{
	Vector3 result = {0};

	fixed_t dot = v->x * n->x + v->y * n->y + v->z * n->z;
	fixed_t d   = 1LL - r * r * (1LL - dot * dot);

	if(d >= 0LL) {
		d    = sqrtf(d);
		
		result.x = r * v->x - (r * dot + d) * n->x;
		result.y = r * v->y - (r * dot + d) * n->y;
		result.z = r * v->z - (r * dot + d) * n->z;
	}

	return result;
}
