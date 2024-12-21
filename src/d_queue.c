#include "d_queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue* Q_Create(void)
{
	Queue* q = malloc(sizeof(Queue));

	if(q == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Queue));
		return NULL;
	}

	q->count = 0;

	// init to NULL so we don't seg fault lol.
	q->front = NULL;
	q->back  = NULL;

	return q;
}

void Q_Destroy(Queue* q)
{
	while(q->count > 0) {
		free(Dequeue(q));
	}

	free(q);
}

int Enqueue(Queue* q, void* data)
{
	Node* node = malloc(sizeof(Node));

	if(node == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Node));
		return 0;
	}

	node->data = data;
	node->prev = NULL;

	if(q->back != NULL) { // adding data to a queue with at least one item.
		q->back->prev = node;
	}
	else { // adding data to an empty queue.
		q->front = node;
	}

	q->back = node;
	q->count++;

	return 1;
}

void* Dequeue(Queue* q)
{
	if(q->count == 0) {
		return NULL;
	}

	Node* front = q->front;
	void* data  = front->data;

	q->front = front->prev;

	free(front);
	q->count--;

	// Set front and back to null so we don't check freed pointers.
	if(q->count == 0) {
		q->front = NULL;
		q->back  = NULL;
	}

	return data;
}
