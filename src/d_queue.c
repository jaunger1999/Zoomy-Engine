#include <stdio.h>
#define INIT_Q_SIZE 64

#include "d_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Queue* Q_Create(unsigned int const cellSize)
{
	Queue* q = malloc(sizeof(Queue));

	if(q == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Queue));
		return NULL;
	}

	q->cellSize = cellSize;
	q->size     = cellSize * INIT_Q_SIZE;
	q->data     = malloc(q->size);

	if(q->data == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Queue));
		return NULL;
	}

	q->count = 0;

	q->head = 0;
	q->tail = 0;

	return q;
}

void Q_Destroy(Queue* const q)
{
	free(q->data);
	free(q);
}

int Enqueue(Queue* const q, void const* const data)
{
	memcpy(&q->data[q->tail], data, q->cellSize);
	q->count++;

	unsigned int oldTail = q->tail;
	q->tail              = (q->tail + q->cellSize) % q->size;

	if(q->tail == q->head) {
		q->size *= 2;
		realloc(q->data, q->size);

		if(!q->data) {
			fprintf(stderr, "Failed to reallocate queue.");
			return 0;
		}

		q->tail = (oldTail + q->cellSize) % q->size;
	}

	return 1;
}

int Dequeue(Queue* q, void* buf)
{
	if(q->count == 0) {
		return 0;
	}

	// copy our data into the caller's buffer and zero out the memory
	void* head = q->data + q->head;
	memcpy(buf, head, q->cellSize);

	q->count--;
	q->head = (q->head + q->cellSize) % q->size;

	return 1;
}
