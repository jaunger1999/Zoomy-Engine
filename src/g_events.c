#include "g_attributes.h"
#include "g_physics.h"
#include "g_events.h"
#include "g_health.h"
#include "g_statemachines.h"

#include "m_raytriangleintersection.h"

#include "gamestate.h"

#include "d_queue.h"
#include "d_dict.h"

#include "raymath.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

typedef char* (*EventParameters)(unsigned int const n, va_list args); 

Dict* eventQs;

/*
 * TODO: Free the previously existing event handler if it exists.
 */
int E_Init() {
	eventQs = Dict_Create();

	return eventQs != NULL;
}

/*
 * Creates a new Event Queue and returns the id/index in which it's stored in the array.
 */
int E_AddObj(unsigned int const id) {
	Queue* newEventQ = Q_Create();
	
	Dict_Add(eventQs, id, newEventQ);

	return 1;
}

Event* E_GetNext(unsigned int const id) {
	Queue* q = (Queue*)Dict_Get(eventQs, id);

	return (Event*)Dequeue(q);
}

EventParameters GetParameterFunction(EventType type);

int E_Register(EventFunction function, EventType type, unsigned int const id, unsigned int const n, ...) {
	assert(function != NULL);

	va_list ptr;
	va_start(ptr, n);

	EventParameters parameterFunction = GetParameterFunction(type);
	char* args = parameterFunction(n, ptr);
	
	va_end(ptr);

	// Construct the event and append it to its corresponding queue.
	Event* event    = malloc(sizeof(Event));

	if (event == NULL) {
		fprintf(stderr, "Fatal: failed to allocate memory on the heap.");
		return 0;
	}

	event->type     = type;
	event->function = function;
	event->args     = args;

	Queue* q = Dict_Get(eventQs, id);
	Enqueue(q, event);

	return 1;
}

char* TestParameters      (unsigned int const n, va_list args);
char* PlayerMoveParameters(unsigned int const n, va_list args);

EventParameters GetParameterFunction(EventType type) {
	switch (type) {
		case NONE:
			return TestParameters;
		case ANIMATION_END:
			return NULL;
		case PLAYER_MOVE:
			return PlayerMoveParameters;
	}

	return NULL;
}

char* PlayerMoveParameters(unsigned int const n, va_list args) {
	char* packedArgs = malloc(sizeof(Input*) + sizeof(Attributes*) + sizeof(CollisionMesh*) + sizeof(PhysicalProperties*) + sizeof(float));

	if (packedArgs == NULL) {
		fprintf(stderr, "Fatal: failed to allocate memory on the heap.\n");
		return NULL;
	}

	Input*              i     = va_arg(args, Input*);
	Attributes*         a     = va_arg(args, Attributes*);
	CollisionMesh*      m     = va_arg(args, CollisionMesh*);
	PhysicalProperties* p     = va_arg(args, PhysicalProperties*);
	float               delta = va_arg(args, double);

	memcpy(packedArgs,                                                 &i,     sizeof(i));
	memcpy(packedArgs + sizeof(i),                                     &a,     sizeof(a));
	memcpy(packedArgs + sizeof(i) + sizeof(a),                         &m,     sizeof(m));
	memcpy(packedArgs + sizeof(i) + sizeof(a) + sizeof(m),             &p,     sizeof(p));
	memcpy(packedArgs + sizeof(i) + sizeof(a) + sizeof(m) + sizeof(p), &delta, sizeof(delta));

	return packedArgs;
}

char* TestParameters(unsigned int const n, va_list args) {
	char* packedArgs = malloc(sizeof(int) + sizeof(Vector3));
	
	if (packedArgs == NULL) {
		fprintf(stderr, "Fatal: failed to allocate memory on the heap.\n");
		return NULL;
	}

	int     a = va_arg(args, int);
	Vector3 b = va_arg(args, Vector3);

	memcpy(packedArgs,             &a, sizeof(a));
	memcpy(packedArgs + sizeof(a), &b, sizeof(b));

	return packedArgs;
}
