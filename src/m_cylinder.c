#include "m_raytriangleintersection.h"

struct Cylinder {
	float radius;
	float height;
} typedef Cylinder;

// Cylinder cylinder collision where c1 wants to move from r.position to r.position + r.direction.
OptionHit RayCylinderCollision(Ray const * const r, Vector3 const * const p, Cylinder const * const c) {
	// d = L - E ( Direction vector of ray, from start to end )
	// f = E - C ( Vector from center sphere to ray start )
	
	/*float a = d.Dot(d);
	float b = 2*f.Dot(d);
	float c = f.Dot(f) - r*r;

	float discriminant = b*b - 4*a*c;
	
	if (discriminant < 0) {
		// no intersection
		return (OptionHit) { false };
	}
	
	// ray didn't totally miss sphere,
	// so there is a solution to
	// the equation.
	discriminant = sqrt(discriminant);

	// either solution may be on or off the ray so need to test both
	// t1 is always the smaller value, because BOTH discriminant and
	// a are nonnegative.
	float t1 = (-b - discriminant) / (2*a);
	float t2 = (-b + discriminant) / (2*a);

	// 3x HIT cases:
	// -o->                   --|--> |           | --|->
	// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

	// 3x MISS cases:
	// ->o                    o ->              | -> |
	// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

	if(t1 >= 0 && t1 <= 1) {
		// t1 is the intersection, and it's closer than t2
		// (since t1 uses -b - discriminant)
		// Impale, Poke
		return (OptionHit) { true };
	}

	// here t1 didn't intersect so we are either started
	// inside the sphere or completely past it
	if(t2 >= 0 && t2 <= 1) {
		// ExitWound
		return (OptionHit) { true };
	}
*/
	// no intn: FallShort, Past, CompletelyInside	
	return (OptionHit) { false };
}
