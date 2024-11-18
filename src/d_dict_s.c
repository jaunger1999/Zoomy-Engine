#define INIT_DICT_SIZE 64

#include "d_dict_s.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(unsigned char const * const str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

Dict_S* Dict_S_Create() {
	Dict_S* d = malloc(sizeof(Dict_S));

	if (d == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Dict_S));
		return NULL;
	}

	// init with calloc so we have null terminated linked lists for each bucket.
	d->size = INIT_DICT_SIZE;
	d->buckets = calloc(d->size, sizeof(DictEntry_S*));
	
	return d;
}

void Dict_S_Destroy(Dict_S *d) {
	for (unsigned int i = 0; i < d->size; i++) {
		for (DictEntry_S* e = d->buckets[i]; e != NULL;) {
			DictEntry_S* old = e;

			e = e->next;
			free(old);
		}
	}

	free(d->buckets);
	free(d);
}

void* Dict_S_Get(Dict_S* const dict, unsigned char const * const id) {
	unsigned long i = hash(id) % dict->size;

	for (DictEntry_S* entry = dict->buckets[i]; entry != NULL; entry = entry->next) {
		if (strcmp(entry->id, id) == 0) {
			return entry->item;
		}
	}

	return NULL;
}

int Dict_S_Add(Dict_S* const dict, void* const item, unsigned int id) {
	unsigned long i = hash(id) % dict->size;

	// Init the entry
	DictEntry_S* entry = malloc(sizeof(DictEntry_S));

	if (entry == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(DictEntry_S));
		return 0;
	}

	entry->id = id;
	entry->item = item;

	// add the entry to hashed bucket
	entry->next = dict->buckets[i];
	dict->buckets[i] = entry;

	return 1;
}
