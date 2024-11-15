#include "d_queue.h"

#include <stdlib.h>

Queue* Q_Create() {
	Queue* q = malloc(sizeof(Queue));
	q->count = 0;

	// init to NULL so we don't seg fault lol.
	q->front = NULL;
	q->back  = NULL;

	return q;
}

void Q_Destroy(Queue* q) {
	while (q-> count > 0) {
		free(Dequeue(q));
	}

	free(q);
}

void Enqueue(Queue* q, void* data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;

	if (q->back != NULL) { // adding data to a queue with at least one item.
		q->back->prev = node;
	}
	else { // adding data to an empty queue.
		q->front = node;
	}

	q->back = node;
	q->count++;
}

void* Dequeue(Queue* q) {
	if (q->count == 0) {
		return NULL;
	}

	Node* front = q->front;
	void* data = front->data;

	q->front = front->prev;

	free(front);
	q->count--;

	return data;
}
