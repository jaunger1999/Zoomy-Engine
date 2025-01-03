typedef struct List {
	char* data;
	unsigned int itemSize;
	unsigned int size;
} List;

List* List_Create(unsigned int const itemSize);
int List_Get(List const* const list, unsigned int const i, void* buf);
int List_Insert(List* const list, unsigned int const i, void const* const data); 
