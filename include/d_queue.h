typedef struct Node {
	void* data;
	Node* prev;
} Node;

typedef struct Queue {
	Node* front;
	Node* back;
	int count;
} Queue;

Queue* CreateQueue();
void DestroyQueue(Queue* q);

void Enqueue(Queue* q, void* data);
void* Dequeue(Queue* q);
