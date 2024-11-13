#include "g_events.h"
#include "d_queue.h"
#include "d_list.h"

#include <stdarg.h>

List* eventQs;

/*
 * TODO: Free the previously existing event handler if it exists.
 */
void E_Init() {
	eventQs = CreateList();
}

/*
 * Creates a new Event Queue and returns the id/index in which it's stored in the array.
 */
int E_AddObj() {
	Queue* newEventQ = CreateQueue();
	int id = eventQs->count;

	Append(eventQs, newEventQ);

	return id;
}

Event* E_GetNext(int id) {
	assert(id >= 0);
	assert(id < eventQs->count);
	
	return (Event*)Dequeue(eventQs[id]);
}

void E_Register(EventFunction function, EventType type, int n, int id, ...) {
	assert(id >= 0);
	assert(id < eventQs->count);
	assert(function != NULL);

	void** args = malloc(sizeof(void*) * n);
	
	// iterate through the variable number of arguments.
	va_list ptr;
	va_start(ptr, n);

	for (int i = 0; i < n; i++) {
		args[i] = va_arg(ptr, (void*));
	}
	
	va_end(ptr);

	// Construct the event and append it to its corresponding queue.
	Event* event    = malloc(sizeof(Event));
	event->type     = type
	event->function = function;
	event->args     = args;

	Enqueue(eventQs[id], event);
}
