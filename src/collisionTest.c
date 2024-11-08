#define RAYLIB
#include "raylib.h"
#include "raytriangleintersection.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void printValid(OptionHit const * const h) {
	if (h->valid) {
		printf("Success!\n");
	}
	else {
		printf("Failure :(\n");
	}
}

int main(void) {
	Ray ray = { (Vector3){ 0.0f, 1.0f, 0.0f }, (Vector3){ 0.1f, -2.0f, 0.0f } };
	Ray ray2 = { (Vector3){ 0.0f, 1.0f, 0.5f }, (Vector3){ 0.0f, -2.0f, 0.0f } };
	Vector3 a = { -0.5f, 0.0f,  0.5f };
	Vector3 b = {  0.5f, 0.0f,  0.5f };
	Vector3 c = {  0.0f, 0.0f, -0.5f };

	printf("\nTest if an angled ray intersects with our triangle\n");
	OptionHit h = Intersect(&ray, &a, &b, &c);
	
	printValid(&h);	

	printf("\nTest if a ray intersects with the exact edge of a triangle\n");
	OptionHit h2 = Intersect(&ray2, &a, &b, &c);

	printValid(&h2);
	return 0;
}
