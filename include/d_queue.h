typedef struct Queue {
	char* data;

	unsigned int size;
	unsigned int cellSize;
	unsigned int count;
	unsigned int head;
	unsigned int tail;
} Queue;

Queue* Q_Create(void);
void   Q_Destroy(Queue* q);

int Enqueue(Queue* q, void* data);
int Dequeue(Queue* q, void* buf);
