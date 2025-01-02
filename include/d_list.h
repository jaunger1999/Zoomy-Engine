typedef struct List {
	char* data;
	unsigned int count;
	unsigned int cellSize;
} List;

#define LIST_GET(type, list, i) (type)data[i * cellSize]
