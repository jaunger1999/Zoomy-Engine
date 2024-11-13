#include "d_list.h"

List* CreateList() {
	List* list = malloc(sizeof(List));
	list->size = INIT_LIST_SIZE;
	list->count = 0;
	list->items = malloc(sizeof(void*) * list->size);

	return list;
}

void DestroyList(List* list) {
	for (int i = 0; i < list->count; i++) {
		free(list->items[i]);
	}

	free(list->items);
	free(list);
}

void Append(List* const list, void* item) {
	list->items[list->count] = item;

	list->count++;

	if (list->count == list->size) {
		int oldSize = list->size;
		list->size *= 2;

		realloc(list->items, sizeof(void*) * list->size);
	}
}
