#define RAYLIB
#include "raylib.h"
#include "raytriangleintersection.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(void) {
	Ray ray = { (Vector3){ 0.0f, 1.0f, 0.0f }, (Vector3){ 0.0f, -2.0f, 0.0f } };
	Vector3 a = { -0.5f, 0.0f,  0.5f };
	Vector3 b = {  0.5f, 0.0f,  0.5f };
	Vector3 c = {  0.0f, 0.0f, -0.5f };

	OptionVector3 v = Intersect(&ray, &a, &b, &c);

	if (v.valid) {
		printf("Success!");
	}
	else {
		printf("Failure :(");
	}

	return 0;
}
