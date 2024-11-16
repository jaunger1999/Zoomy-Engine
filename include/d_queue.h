typedef struct Node {
	void* data;
	struct Node* prev;
} Node;

typedef struct Queue {
	Node* front;
	Node* back;
	unsigned int count;
} Queue;

Queue* Q_Create();
void Q_Destroy(Queue* q);

int   Enqueue(Queue* q, void* data);
void* Dequeue(Queue* q);
