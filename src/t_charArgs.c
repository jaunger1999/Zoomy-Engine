#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raymath.h"

int main(void) {
	// These are our values we're going to store in a char array.
	int a = 1234;
	Vector3 b = { 0.1f, 0.2f, 0.3f };

	char* args = malloc(sizeof(int) + sizeof(Vector3));
	
	memcpy(args, &a, sizeof(a));
	memcpy(args + sizeof(a), &b, sizeof(b));

	// These are the values that our char array are going to extract to.
	int i = 0;
	Vector3 j = (Vector3) { };

	memcpy(&i, args, sizeof(int));
	memcpy(&j, args + sizeof(int), sizeof(Vector3));

	printf("Our first value should be %i: %i\n", a, i);
	printf("Our Vector3 should be (%f, %f, %f): (%f, %f, %f)\n", b.x, b.y, b.z, j.x, j.y, j.z);

	printf("End of processing\n");
	return 0;
}
