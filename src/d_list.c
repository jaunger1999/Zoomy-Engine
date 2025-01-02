#define INIT_LIST_SIZE 64

#include "d_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* List_Create(unsigned int const itemSize) {
	List* l = malloc(sizeof(List));	

	if(!l) {
		fprintf(stderr, "Failed to allocate list");
		return NULL;
	}

	l->data = malloc(itemSize * INIT_LIST_SIZE);

	if(!l->data) {
		fprintf(stderr, "Failed to allocate list");
		return NULL;
	}

	l->itemSize = itemSize;
	l->size = INIT_LIST_SIZE;

	return l;
}

int List_Get(List const* const l, unsigned int const i, void* buf) {
	memcpy(buf, &l->data[i * l->itemSize], l->itemSize);

	return 1;
}

int List_Insert(List* const l, unsigned int const i, void const* const data) {
	unsigned int oldSize = l->size;

	while(i > l->size) {
		l->size *= 2;
	}

	if(oldSize != l->size) {
		realloc(l, l->size);
	}

	memcpy(&l->data[i * l->itemSize], data, l->itemSize);

	return 1;
}
