#define INIT_DICT_SIZE 64

#include "d_dict.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>

Dict* Dict_Create(void)
{
	Dict* d = malloc(sizeof(Dict));

	if(d == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(Dict));
		return NULL;
	}

	// init with calloc so we have null terminated linked lists for each bucket.
	d->size    = INIT_DICT_SIZE;
	d->buckets = calloc(d->size, sizeof(DictEntry));

	return d;
}

void Dict_Destroy(Dict* d)
{
	for(unsigned int i = 0; i < d->size; i++) {
		for(DictEntry* e = d->buckets[i].next; e != NULL;) {
			DictEntry* old = e;

			e = e->next;
			free(old);
		}
	}

	free(d->buckets);
	free(d);
}

void* Dict_Get(Dict const* const dict, unsigned int const id)
{
	unsigned long i = hash(id) % dict->size;

	for(DictEntry* entry = &dict->buckets[i]; entry != NULL; entry = entry->next) {
		if(entry->id == id) {
			return entry->item;
		}
	}

	return NULL;
}

int Dict_Add(Dict* const dict, unsigned int id, void* const item)
{
	unsigned long i = hash(id) % dict->size;
	DictEntry* entry = NULL;

	// If there's a collision, make a new entry
	if(dict->buckets[i].id != 0) {
		entry = malloc(sizeof(DictEntry));

		if(entry == NULL) {
			fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(DictEntry));
			return 0;
		}

		// our current first entry in the bucket will become the second
		*entry = dict->buckets[i];
	}

	// make the new entry the head of our linked list.
	dict->buckets[i].id   = id;
	dict->buckets[i].item = item;
	dict->buckets[i].next = entry;

	return 1;
}
