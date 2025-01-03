#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "g_events.h"

// These are our values we're going to store in a char array.
int     a = 1234;
Vector3 b = {0.1f, 0.2f, 0.3f};

unsigned int Test(char const* args, unsigned int id, void* out)
{
	// These are the values that our char array are going to extract to.
	int     i = 0;
	Vector3 j = (Vector3){0};

	memcpy(&i, args, sizeof(int));
	memcpy(&j, args + sizeof(int), sizeof(Vector3));

	printf("Our first value should be %i: %i\n", a, i);
	printf("Our Vector3 should be (%f, %f, %f): (%f, %f, %f)\n", b.x, b.y, b.z, j.x, j.y, j.z);

	return 1;
}

int main(void)
{
	unsigned int id1 = 0;
	unsigned int id2 = 23;

	char* args = malloc(sizeof(int) + sizeof(Vector3));

	memcpy(args, &a, sizeof(a));
	memcpy(args + sizeof(a), &b, sizeof(b));

	E_Init();
	E_AddObj(id1);
	E_AddObj(id2);

	// Test function, event type, 2 parameters, id, ... parameters for test function.
	E_Register(Test, NONE, id1, 2, a, b);
	E_Register(Test, NONE, id2, 2, a, b);

	Event e = {0};
	E_GetNext(id1, &e);

	/* if(e) { */
	/* 	printf("Didn't find an event when we should have. :(\n"); */
	/* } */
	/**/
	/* if(!e->function) { */
	/* 	printf("Why doesn't this event have a function???\n"); */
	/* } */
	/**/
	/* if(!e->args) { */
	/* 	printf("Why doesn't this event have arguments???\n"); */
	/* } */

	void* out = NULL;
	e.function(e.args, id1, out);

	E_GetNext(id1, &e);

	/* if(e) { */
	/* 	printf("We shouldn't be getting a non NULL value with no events remaining. :(\n"); */
	/* } */

	printf("End of processing\n");
	return 0;
}
