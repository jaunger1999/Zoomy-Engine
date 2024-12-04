typedef struct DictEntry {
	unsigned int id;
	void* item;
	struct DictEntry* next;
} DictEntry;

typedef struct Dict {
	DictEntry** buckets; // an array of linked lists.
	unsigned int size;
} Dict;

Dict* Dict_Create();

void* Dict_Get(Dict const* const dict, unsigned int const id);

int  Dict_Add(Dict* const dict, unsigned int const id, void* item);
void Dict_Destroy(Dict* dict);
