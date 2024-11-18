typedef struct DictEntry_S {
	unsigned char* id;
	void* item;
	struct DictEntry_S* next;
} DictEntry;

typedef struct Dict_S {
	DictEntry_S** buckets; // an array of linked lists.
	unsigned int size;
} Dict_S;

Dict_S* Dict_S_Create();

void* Dict_S_Get(Dict* dict, unsigned int id);

int  Dict_S_Add(Dict_S* dict, void* item, unsigned int id);
void Dict_S_Destroy(Dict_S* dict);
