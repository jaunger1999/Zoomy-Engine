#include "d_queue.h"

Queue* CreateQueue() {
	Queue* q = malloc(sizeof(Queue));
	q->count = 0;

	return q;
}

void DestroyQueue(Queue* q) {
	while (q-> count > 0) {
		free(Dequeue(q);
	}

	free(q);
}

void Enqueue(Queue* q, void* data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;

	q->back->prev = node;
	q->back       = node;
}

void* Dequeue(Queue* q) {
	if (q->count == 0) {
		return;
	}

	Node* front = q->front;
	void* data = front->data;

	q->front = front->prev;

	free(front);
}
