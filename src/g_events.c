#include "g_events.h"
#include "d_queue.h"
#include "d_dict.h"

#include "raymath.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
typedef char* (*EventParameters)(unsigned int const n, va_list* args); 

Dict* eventQs;

/*
 * TODO: Free the previously existing event handler if it exists.
 */
void E_Init() {
	eventQs = Dict_Create();
}

/*
 * Creates a new Event Queue and returns the id/index in which it's stored in the array.
 */
int E_AddObj(unsigned int const id) {
	Queue* newEventQ = Q_Create();
	
	Dict_Add(eventQs, newEventQ, id);

	return 1;
}

Event* E_GetNext(unsigned int const id) {
	Queue* q = (Queue*)Dict_Get(eventQs, id);

	return (Event*)Dequeue(q);
}

EventParameters GetParameterFunction(EventType type);

void E_Register(EventFunction function, EventType type, unsigned int const id, unsigned int const n, ...) {
	assert(function != NULL);

	va_list ptr;
	va_start(ptr, n);

	EventParameters parameterFunction = GetParameterFunction(type);
	char* args = parameterFunction(n, &ptr);
	
	va_end(ptr);

	// Construct the event and append it to its corresponding queue.
	Event* event    = calloc(1, sizeof(Event));
	event->type     = type;
	event->function = function;
	event->args     = args;

	Queue* q = Dict_Get(eventQs, id);
	Enqueue(q, event);
}

char* TestParameters(unsigned int const n, va_list* args);

EventParameters GetParameterFunction(EventType type) {
	switch (type) {
		case TEST:
			return TestParameters;
		case DAMAGE:
			return NULL;
	}

	return NULL;
}

char* TestParameters(unsigned int const n, va_list* args) {
	char* packedArgs = calloc(sizeof(int) + sizeof(Vector3), sizeof(char));
	
	int     a = va_arg(*args, int);
	Vector3 b = va_arg(*args, Vector3);

	memcpy(packedArgs,             &a, sizeof(a));
	memcpy(packedArgs + sizeof(a), &b, sizeof(b));

	return packedArgs;
}
