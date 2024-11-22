typedef struct DictEntry_S {
	char* id;
	void* item;
	struct DictEntry_S* next;
} DictEntry_S;

typedef struct Dict_S {
	DictEntry_S** buckets; // an array of linked lists.
	unsigned int size;
} Dict_S;

Dict_S* Dict_S_Create();

void* Dict_S_Get(Dict_S* dict, char const * const id);

int  Dict_S_Add(Dict_S* dict, char const * const id, void* item);
void Dict_S_Destroy(Dict_S* dict);
