#define INIT_LIST_SIZE 8 

typedef struct List {
	void** items;
	int size;
	int count;
} List;

List* CreateList();
void DestroyList(List* list);
void Append(List* const list, void* item);
