#define INIT_DICT_SIZE 64

#include "d_dict.h"

#include <stdlib.h>

// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hash(unsigned int x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

Dict* Dict_Create() {
	Dict* d = malloc(sizeof(Dict));

	// init with calloc so we have null terminated linked lists for each bucket.
	d->size = INIT_DICT_SIZE;
	d->buckets = calloc(sizeof(DictEntry*), d->size);
	
	return d;
}

void Dict_Destroy(Dict *d) {
	for (int i = 0; i < d->size; i++) {
		for (DictEntry* e = d->buckets[i]; e != NULL;) {
			DictEntry* old = e;

			e = e->next;
			free(old);
		}
	}

	free(d->buckets);
	free(d);
}

void* Dict_Get(Dict* const dict, unsigned int id) {
	unsigned int i = hash(id) % dict->size;

	for (DictEntry* entry = dict->buckets[i]; entry != NULL; entry = entry->next) {
		if (entry->id == id) {
			return entry->item;
		}
	}

	return NULL;
}

void Dict_Add(Dict* const dict, void* item, unsigned int id) {
	unsigned int i = hash(id) % dict->size;

	// Init the entry
	DictEntry* entry = malloc(sizeof(DictEntry));
	entry->id = id;
	entry->item = item;

	// add the entry to hashed bucket
	entry->next = dict->buckets[i];
	dict->buckets[i] = entry;
}


