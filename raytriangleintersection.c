#include <xmmintrin.h>
#include "raytriangleintersection.h"

const float int_coef_arr[4] = { -1, -1, -1, 1 };
const __m128 int_coef = _mm_load_ps(helper);

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