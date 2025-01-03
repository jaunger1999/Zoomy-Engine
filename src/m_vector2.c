#include "m_vector2.h"
#include "m_fixed.h"
#include "m_matrix.h"
#include <stdint.h>

// Vector with components value 0->0f
Vector2 Vector2Zero(void)
{
	Vector2 result = {0LL, 0LL};

	return result;
}

// Vector with components value 1->0f
Vector2 Vector2One(void)
{
	Vector2 result = {1LL, 1LL};

	return result;
}

// Add two vectors (v1 + v2)
Vector2 Vector2Add(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {v1->x + v2->x, v1->y + v2->y};

	return result;
}

// Add vector and fixed_t value
Vector2 Vector2AddValue(Vector2 const* const v, fixed_t add)
{
	Vector2 result = {v->x + add, v->y + add};

	return result;
}

// Subtract two vectors (v1 - v2)
Vector2 Vector2Subtract(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {v1->x - v2->x, v1->y - v2->y};

	return result;
}

// Subtract vector by fixed_t value
Vector2 Vector2SubtractValue(Vector2 const* const v, fixed_t sub)
{
	Vector2 result = (Vector2){v->x - sub, v->y - sub};

	return result;
}

// Calculate vector length
fixed_t Vector2Length(Vector2 const* const v) { return (fixed_t)uint64_sqrt((uint64_t)((v->x * v->x) + (v->y * v->y))); }

// Calculate vector square length
fixed_t Vector2LengthSqr(Vector2 const* const v) { return (v->x * v->x) + (v->y * v->y); }

// Calculate two vectors dot product
fixed_t Vector2DotProduct(Vector2 const* const v1, Vector2 const* const v2)
{
	fixed_t result = (v1->x * v2->x + v1->y * v2->y);

	return result;
}

// Calculate distance between two vectors
fixed_t Vector2Distance(Vector2 const* const v1, Vector2 const* const v2)
{
	fixed_t result = (int64_t)uint64_sqrt((uint64_t)((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y)));

	return result;
}

// Calculate square distance between two vectors
fixed_t Vector2DistanceSqr(Vector2 const* const v1, Vector2 const* const v2)
{
	fixed_t result = ((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y));

	return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
fixed_t Vector2Angle(Vector2 const* const v1, Vector2 const* const v2)
{
	fixed_t result = 0LL;

	fixed_t dot = v1->x * v2->x + v1->y * v2->y;
	fixed_t det = v1->x * v2->y - v1->y * v2->x;

	result = atan2f(det, dot);

	return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
fixed_t Vector2LineAngle(Vector2 const* const start, Vector2 const* const end)
{
	fixed_t result = 0LL;

	// TODO(10/9/2023): Currently angles move clockwise, determine if this is wanted behavior
	result = -atan2f(end->y - start->y, end->x - start->x);

	return result;
}

// Scale vector (multiply by value)
Vector2 Vector2Scale(Vector2 const* const v, fixed_t scale)
{
	Vector2 result = {v->x * scale, v->y * scale};

	return result;
}

// Multiply vector by vector
Vector2 Vector2Multiply(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {v1->x * v2->x, v1->y * v2->y};

	return result;
}

// Negate vector
Vector2 Vector2Negate(Vector2 const* const v)
{
	Vector2 result = {-v->x, -v->y};

	return result;
}

// Divide vector by vector
Vector2 Vector2Divide(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {v1->x / v2->x, v1->y / v2->y};

	return result;
}

// Normalize provided vector
Vector2 Vector2Normalize(Vector2 const* const v)
{
	Vector2 result = {0};
	fixed_t length = (int64_t)uint64_sqrt((uint64_t)((v->x * v->x) + (v->y * v->y)));

	if(length > 0) {
		fixed_t ilength = 1LL / length;
		result.x        = v->x * ilength;
		result.y        = v->y * ilength;
	}

	return result;
}

// Transforms a Vector2 by a given Matrix
Vector2 Vector2Transform(Vector2 const* const v, Matrix const* const mat)
{
	Vector2 result = {0};

	fixed_t x = v->x;
	fixed_t y = v->y;
	fixed_t z = 0;

	result.x = mat->m0 * x + mat->m4 * y + mat->m8 * z + mat->m12;
	result.y = mat->m1 * x + mat->m5 * y + mat->m9 * z + mat->m13;

	return result;
}

// Calculate linear interpolation between two vectors
Vector2 Vector2Lerp(Vector2 const* const v1, Vector2 const* const v2, fixed_t amount)
{
	Vector2 result = {0};

	result.x = v1->x + amount * (v2->x - v1->x);
	result.y = v1->y + amount * (v2->y - v1->y);

	return result;
}

// Calculate reflected vector to normal
Vector2 Vector2Reflect(Vector2 const* const v, Vector2 const* const normal)
{
	Vector2 result = {0};

	fixed_t dotProduct = (v->x * normal->x + v->y * normal->y);

	result.x = v->x - (2LL * normal->x) * dotProduct;
	result.y = v->y - (2LL * normal->y) * dotProduct;

	return result;
}

// Get min value for each pair of components
Vector2 Vector2Min(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {0};

	result.x = min(v1->x, v2->x);
	result.y = min(v1->y, v2->y);

	return result;
}

// Get max value for each pair of components
Vector2 Vector2Max(Vector2 const* const v1, Vector2 const* const v2)
{
	Vector2 result = {0};

	result.x = max(v1->x, v2->x);
	result.y = max(v1->y, v2->y);

	return result;
}

// Rotate vector by angle
Vector2 Vector2Rotate(Vector2 const* const v, fixed_t const angle)
{
	Vector2 result = {0};

	fixed_t cosres = cosf(angle);
	fixed_t sinres = sinf(angle);

	result.x = v->x * cosres - v->y * sinres;
	result.y = v->x * sinres + v->y * cosres;

	return result;
}

// Move Vector towards target
Vector2 Vector2MoveTowards(Vector2 const* const v, Vector2 const* const target, fixed_t maxDistance)
{
	Vector2 result = {0};

	fixed_t dx    = target->x - v->x;
	fixed_t dy    = target->y - v->y;
	fixed_t value = (dx * dx) + (dy * dy);

	if((value == 0) || ((maxDistance >= 0) && (value <= maxDistance * maxDistance))) {
		return *target;
	}

	fixed_t dist = (int64_t)uint64_sqrt((uint64_t)value);

	result.x = v->x + dx / dist * maxDistance;
	result.y = v->y + dy / dist * maxDistance;

	return result;
}

// Invert the given vector
Vector2 Vector2Invert(Vector2 const* const v)
{
	Vector2 result = {1LL / v->x, 1LL / v->y};

	return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
Vector2 Vector2Clamp(Vector2 const* const v, Vector2 const* const min, Vector2 const* const max)
{
	Vector2 result = {0};

	result.x = fminf(max->x, fmaxf(min->x, v->x));
	result.y = fminf(max->y, fmaxf(min->y, v->y));

	return result;
}

// Clamp the magnitude of the vector between two min and max values
Vector2 Vector2ClampValue(Vector2 const* const v, fixed_t min, fixed_t max)
{
	Vector2 result = *v;

	fixed_t length = (v->x * v->x) + (v->y * v->y);

	if(length > 0LL) {
		length = (int64_t)uint64_sqrt(length);

		fixed_t scale = 1; // By default, 1 as the neutral element->
		if(length < min) {
			scale = min / length;
		}
		else if(length > max) {
			scale = max / length;
		}

		result.x = v->x * scale;
		result.y = v->y * scale;
	}

	return result;
}

// Check whether two given vectors are almost equal
int Vector2Equals(Vector2 const* const p, Vector2 const* const q)
{
	int result = (fabsf(p->x - q->x) <= max(1LL, max(abs(p->x), abs(q->x)))) &&
	             (fabsf(p->y - q->y) <= max(1LL, max(abs(p->y), abs(q->y))));

	return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
Vector2 Vector2Refract(Vector2 const* const v, Vector2 const* const n, fixed_t r)
{
	Vector2 result = {0};

	fixed_t dot = v->x * n->x + v->y * n->y;
	fixed_t d   = 1LL - r * r * (1LL - dot * dot);

	if(d >= 0LL) {
		d    = (int64_t)uint64_sqrt((uint64_t)d);
		result.x = r * v->x - (r * dot + d) * n->x;
		result.y = r * v->y - (r * dot + d) * n->y;
	}

	return result;
}
