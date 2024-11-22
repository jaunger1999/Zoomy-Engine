#define INIT_DICT_SIZE 64

#include "d_dict.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>

Dict* Dict_Create() {
	Dict* d = malloc(sizeof(Dict));

	if (d == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Dict));
		return NULL;
	}

	// init with calloc so we have null terminated linked lists for each bucket.
	d->size = INIT_DICT_SIZE;
	d->buckets = calloc(d->size, sizeof(DictEntry*));
	
	return d;
}

void Dict_Destroy(Dict *d) {
	for (unsigned int i = 0; i < d->size; i++) {
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
	unsigned long i = hash(id) % dict->size;

	for (DictEntry* entry = dict->buckets[i]; entry != NULL; entry = entry->next) {
		if (entry->id == id) {
			return entry->item;
		}
	}

	return NULL;
}

int Dict_Add_String(Dict* const dict, void* item, char const * const key) {

	return 1;
}

int Dict_Add(Dict* const dict, unsigned int id, void* const item) {
	unsigned long i = hash(id) % dict->size;

	// Init the entry
	DictEntry* entry = malloc(sizeof(DictEntry));

	if (entry == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(DictEntry));
		return 0;
	}

	entry->id = id;
	entry->item = item;

	// add the entry to hashed bucket
	entry->next = dict->buckets[i];
	dict->buckets[i] = entry;

	return 1;
}
