#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raymath.h"
#include "d_queue.h"

int main(void) {
	Queue* q = Q_Create(sizeof(int));

	// These are our values we're going to store in our queue.
	int a = 1234;
	int b = 4321;
	// Vector3 b = { 0.1f, 0.2f, 0.3f };
	
	Enqueue(q, &a);
	Enqueue(q, &b);

	int i;
	int j;
	Dequeue(q, &i);
	Dequeue(q, &j);

	printf("Our first value should be %i: %i\n", a, i);
	printf("Our second value should be %i: %i\n", b, j);

	// printf("Our Vector3 should be (%f, %f, %f): (%f, %f, %f)\n", b.x, b.y, b.z, j.x, j.y, j.z);

	void* k = NULL;
	Dequeue(q, k);

	if (k) {
		printf("Our empty queue shouldn't have returned a non NULL value. :(\n");
	}

	Q_Destroy(q);

	printf("End of processing\n");
	return 0;
}
