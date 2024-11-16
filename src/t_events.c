#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raymath.h"

#include "g_events.h"

// These are our values we're going to store in a char array.
int a = 1234;
Vector3 b = { 0.1f, 0.2f, 0.3f };

void Test(char const * args, unsigned int id, void* out) {
	// These are the values that our char array are going to extract to.
	int i = 0;
	Vector3 j = (Vector3) { };

	memcpy(&i, args, sizeof(int));
	memcpy(&j, args + sizeof(int), sizeof(Vector3));

	printf("Our first value should be %i: %i\n", a, i);
	printf("Our Vector3 should be (%f, %f, %f): (%f, %f, %f)\n", b.x, b.y, b.z, j.x, j.y, j.z);
}

int main(void) {
	unsigned int id1 = 300;
	unsigned int id2 = 23;
	
	char* args = malloc(sizeof(int) + sizeof(Vector3));
	
	memcpy(args, &a, sizeof(a));
	memcpy(args + sizeof(a), &b, sizeof(b));

	E_Init();
	E_AddObj(id1);
	E_AddObj(id2);

	// Test function, event type, 2 parameters, id, ... parameters for test function.
	E_Register(Test, TEST, id1, 2, a, b);
	E_Register(Test, TEST, id2, 2, a, b);
	
	Event* e = E_GetNext(id1);

	if (!e) {
		printf("Didn't find an event when we should have. :(\n");
	}

	if (!e->function) {
		printf("Why doesn't this event have a function???\n");
	}

	if (!e->args) {
		printf("Why doesn't this event have arguments???\n");
	}

	void* out = NULL;
	e->function(e->args, id1, out);

	e = E_GetNext(id1);

	if (e) {
		printf("We shouldn't be getting a non NULL value with no events remaining. :(\n");
	}

	printf("End of processing\n");
	return 0;
}

// args == Input const * const input, Attributes const * const attributes, CollisionMesh const * const mesh, PhysicalProperties const * const currState, float const delta
void PhysProp_GetNextPlayerState(char const * const args, unsigned int const id, void* ppOut) {
	// Our parameters for this function.
	Input*              input      = NULL;
	Attributes*         attributes = NULL;
	CollisionMesh*      mesh       = NULL;
	PhysicalProperties* currState  = NULL;
	float               delta      = 0.0f;

	// Set our parameters stored in args.
	memcpy(&input,      args,  sizeof(input));
	memcpy(&attributes, args + sizeof(input),  sizeof(attributes));
	memcpy(&mesh,       args + sizeof(input) + sizeof(attributes),  sizeof(mesh));
	memcpy(&currState,  args + sizeof(input) + sizeof(attributes) + sizeof(mesh),  sizeof(mesh));
	memcpy(&delta,      args + sizeof(input) + sizeof(attributes) + sizeof(mesh) + sizeof(mesh), sizeof(delta));

	Vector3 newVelocity;
	Vector3 const gravity = (Vector3){ 0, -attributes->gravity * delta, 0 };
	Vector3 const toVelocity = (Vector3){ attributes->speed * input->movement.x, 0, attributes->speed * input->movement.y };

	if (1 - Vector2LengthSqr(input->movement) < EPSILON && Vector2LengthSqr(input->oldMovement) < STICK_SMASH_THRESHOLD && abs(Vector3LengthSqr(currState->velocity)) < EPSILON) {
		newVelocity = Vector3Add(toVelocity, gravity);
	}
	else {
		/*Vector3 const diff = Vector3Subtract(toVelocity, currState->velocity);
		Vector3 const acceleration = 
			Vector3Scale(
				Vector3Normalize(diff),          // direction between our desired and current velocity.
				attributes->acceleration * delta
			);*/

		// We don't want to go past our target velocity so check if we'll go past by adding acceleration.
		//if (Vector3LengthSqr(diff) > Vector3LengthSqr(acceleration)) {
		//	newVelocity = Vector3Add(currState->velocity, acceleration); 
		//}
		//else {
			newVelocity = Vector3Add(toVelocity, gravity);
		//}
	}
	
	newVelocity = Vector3Add(newVelocity, currState->velocity);

	bool collision = false;
	Vector3 toTryVelocity = Vector3Scale(newVelocity, delta);

	for (int i = 0; i < mesh->faceCount && !collision; i++) {
		// check if we're hitting the outside of a surface
		if (Vector3Angle(toTryVelocity, mesh->surfaceNormals[i]) < PI_OVER_2) {
			continue;
		}

		Vector3 const a = mesh->vertices[mesh->faces[i].a];
		Vector3 const b = mesh->vertices[mesh->faces[i].b];
		Vector3 const c = mesh->vertices[mesh->faces[i].c];

		Ray const r = (Ray){ currState->position, Vector3Normalize(toTryVelocity) };
		OptionHit hit = Intersect(&r, &a, &b, &c); 
		collision = hit.valid && hit.t * hit.t < Vector3LengthSqr(toTryVelocity);

		if (collision) {
			Vector3 planeVector = VectorComponentAlongPlane(&newVelocity, &mesh->surfaceNormals[i]);
			//printf("Plane Vector: %f %f %f\n\n", planeVector.x, planeVector.y, planeVector.z);
			//printf("Surface Normal: %f %f %f\n\n", mesh->surfaceNormals[i].x, mesh->surfaceNormals[i].y, mesh->surfaceNormals[i].z);
			newVelocity = planeVector;
			toTryVelocity = Vector3Scale(newVelocity, delta);
		}
	}

	Vector3 const newPosition = Vector3Add(currState->position, toTryVelocity);

	*(PhysicalProperties*)ppOut = (PhysicalProperties) {
		newPosition,
		newVelocity,
		currState->acceleration
	};
}
