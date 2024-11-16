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

void* Dict_Get(Dict* dict, unsigned int id);

int  Dict_Add(Dict* dict, void* item, unsigned int id);
void Dict_Destroy(Dict* dict);
