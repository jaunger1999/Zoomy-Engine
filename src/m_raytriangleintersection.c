#include <xmmintrin.h>
#include <smmintrin.h>
#include "m_raytriangleintersection.h"
#include <assert.h>

Vector3 VectorComponentAlongPlane(Vector3 * vector, Vector3 * normal) {
	float dot = Vector3DotProduct(*vector, *normal);
	Vector3 dotNormal = Vector3Scale(*normal, dot);

	return Vector3Subtract(*vector, dotNormal);
}

//reformatted
/*bool Intersection(CollisionRay const r, PrecomputedTriangle const p, Hit h) {
	__m128 const int_coef = _mm_set_ps(-1, -1, -1, 1); //This can be a parameter: it's a constant.
	__m128 const o        = _mm_load_ps(&r.ox);
	__m128 const d        = _mm_load_ps(&r.dx);
	__m128 const n        = _mm_load_ps(&p.nx);
	__m128 const det      = _mm_dp_ps(n, d, 0x7f);
	__m128 const dett     = _mm_dp_ps(_mm_mul_ps(int_coef, n), o, 0xff);
	__m128 const oldt     = _mm_load_ss(&h.t);
	
	if((_mm_movemask_ps(_mm_xor_ps(dett, _mm_sub_ss(_mm_mul_ss(oldt, det), dett)))&1) == 0) {
		__m128 const detp = _mm_add_ps(_mm_mul_ps(o, det), _mm_mul_ps(dett, d));
		__m128 const detu = _mm_dp_ps(detp, _mm_load_ps(&p.ux), 0xf1);
		
		if((_mm_movemask_ps(_mm_xor_ps(detu, _mm_sub_ss(det, detu)))&1) == 0) {
			__m128 const on   = _mm_dp_ps(o, n, 0x77);
			__m128 const tp   = _mm_sub_ps(d, on);
			__m128 const detv = _mm_dp_ps(tp, _mm_load_ps(&p.vx), 0xf1);
			
			if((_mm_movemask_ps(_mm_xor_ps(detv, _mm_sub_ss(det, _mm_add_ss(detu, detv))))&1) == 0) {
				//I can't find the function used in the paper but this seems to be the equivalent?
				__m128 const inv_det = _mm_rsqrt_ss(det);
				
				_mm_store_ss(&h.t,  _mm_mul_ss(dett, inv_det));
				_mm_store_ss(&h.u,  _mm_mul_ss(detu, inv_det));
				_mm_store_ss(&h.v,  _mm_mul_ss(detv, inv_det));
				_mm_store_ps(&h.px, _mm_mul_ps(detp, 
					_mm_shuffle_ps(inv_det, inv_det, 0)));
				
				return true;
			}
		}
	}

	return false;
}*/

OptionHit Intersect(Ray const * const ray, Vector3 const * const a, Vector3 const * const b, Vector3 const * const c) {
	Vector3 const edge1      = Vector3Subtract(*b, *a);
	Vector3 const edge2      = Vector3Subtract(*c, *a);
	Vector3 const rayCrossE2 = Vector3CrossProduct(ray->direction, edge2);
	float const det          = Vector3DotProduct(edge1, rayCrossE2);

	assert(!isnan(det));

	if (det > -EPSILON && det < EPSILON) {
		return (OptionHit){ false };
	}
	
	Vector3 const s    = Vector3Subtract(ray->position, *a);
	float const invDet = 1.0f / det;
	float const u      = invDet * Vector3DotProduct(s, rayCrossE2);
	
	assert(!isnan(invDet));
	assert(!isnan(u));

	if (u < 0.0f || u > 1) {
		return (OptionHit){ false };
	}
	
	Vector3 const sCrossE1 = Vector3CrossProduct(s, edge1);
	float const v          = invDet * Vector3DotProduct(edge2, sCrossE1);

	assert(!isnan(v));

	if (v < 0.0f || u + v > 1) {
		return (OptionHit){ false };
	}
	
	float const t = invDet * Vector3DotProduct(edge2, sCrossE1);
	
	assert(!isnan(t));

	if (t > EPSILON) { // The online code implementations compare to EPSILON but idk why.
		Vector3 const intersectionPoint = Vector3Add(ray->position, Vector3Scale(ray->direction, t));
		return (OptionHit){ true, intersectionPoint, t, u, v };
	}
	
	// This means that there is a line intersection but not a ray intersection.
	return (OptionHit){ false };
}


/*float const int_coef_arr[4] = { -1, -1, -1, 1 };
__m128 const int_coef = _mm_load_ps(helper);

bool Intersect(const CollisionRay &r,
const PrecomputedTriangle &p, Hit &h) {
	const __m128 o = _mm_load_ps(&r.ox);
	const __m128 d = _mm_load_ps(&r.dx);
	const __m128 n = _mm_load_ps(&p.nx);
	const __m128 det = _mm_dp_ps(n, d, 0x7f);
	const __m128 dett = _mm_dp_ps(_mm_mul_ps(int_coef, n), o, 0xff);
	const __m128 oldt = _mm_load_ss(&h.t);
	
	if((_mm_movemask_ps(_mm_xor_ps(dett, _mm_sub_ss(_mm_mul_ss(oldt, det), dett)))&1) == 0) {
		const __m128 detp = _mm_add_ps(_mm_mul_ps(o, det), _mm_mul_ps(dett, d));
		const __m128 detu = _mm_dp_ps(detp, _mm_load_ps(&p.ux), 0xf1);
		
		if((_mm_movemask_ps(_mm_xor_ps(detu, _mm_sub_ss(det, detu)))&1) == 0) {
			const __m128 detv = _mm_dp_ps(pt, _mm_load_ps(&p.vx), 0xf1));
			if((_mm_movemask_ps(_mm_xor_ps(detv, _mm_sub_ss(det, _mm_add_ss(detu, detv))))&1) == 0) {
				const __m128 inv_det = inv_ss(det);
				_mm_store_ss(&h.t, _mm_mul_ss(dett, inv_det));
				_mm_store_ss(&h.u, _mm_mul_ss(detu, inv_det));
				_mm_store_ss(&h.v, _mm_mul_ss(detv, inv_det));
				_mm_store_ps(&h.px, _mm_mul_ps(detp,
				_mm_shuffle_ps(inv_det, inv_det, 0)));
				return true;
			}
		}
	}
	return false;
}
//reformatted
bool Intersect(CollisionRay const r, PrecomputedTriangle const p, Hit h) {
	__m128 const int_coef = _mm_set_ps(-1, -1, -1, 1); //This can be a parameter: it's a constant.
	__m128 const o        = _mm_load_ps(&r.ox);
	__m128 const d        = _mm_load_ps(&r.dx);
	__m128 const n        = _mm_load_ps(&p.nx);
	__m128 const det      = _mm_dp_ps(n, d, 0x7f);
	__m128 const dett     = _mm_dp_ps(_mm_mul_ps(int_coef, n), o, 0xff);
	__m128 const oldt     = _mm_load_ss(&h.t);
	
	if((_mm_movemask_ps(_mm_xor_ps(dett, _mm_sub_ss(_mm_mul_ss(oldt, det), dett)))&1) == 0) {
		__m128 const detp = _mm_add_ps(_mm_mul_ps(o, det), _mm_mul_ps(dett, d));
		__m128 const detu = _mm_dp_ps(detp, _mm_load_ps(&p.ux), 0xf1);
		
		if((_mm_movemask_ps(_mm_xor_ps(detu, _mm_sub_ss(det, detu)))&1) == 0) {
			__m128 const on   = _mm_dp_ps(o, n, 0x77);
			__m128 const tp   = _mm_sub_ps(d, on);
			__m128 const detv = _mm_dp_ps(tp, _mm_load_ps(&p.vx), 0xf1);
			
			if((_mm_movemask_ps(_mm_xor_ps(detv, _mm_sub_ss(det, _mm_add_ss(detu, detv))))&1) == 0) {
				//I can't find the function used in the paper but this seems to be the equivalent?
				__m128 const inv_det = _mm_rsqrt_ss(det);
				
				_mm_store_ss(&h.t,  _mm_mul_ss(dett, inv_det));
				_mm_store_ss(&h.u,  _mm_mul_ss(detu, inv_det));
				_mm_store_ss(&h.v,  _mm_mul_ss(detv, inv_det));
				_mm_store_ps(&h.px, _mm_mul_ps(detp, 
					_mm_shuffle_ps(inv_det, inv_det, 0)));
				
				return true;
			}
		}
	}

	return false;
}

*/
