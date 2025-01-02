typedef struct Queue {
	char* data;

	unsigned int size;
	unsigned int cellSize;
	unsigned int count;
	unsigned int head;
	unsigned int tail;
} Queue;

Queue* Q_Create(unsigned int const cellSize);
void   Q_Destroy(Queue* q);

int Enqueue(Queue* const q, void const* const data);
int Dequeue(Queue* const q, void* const buf);
