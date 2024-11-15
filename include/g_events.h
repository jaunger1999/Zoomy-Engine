typedef enum EventType {
	TEST   = -1,
	DAMAGE =  0
} EventType;

typedef struct EventReturn {
	EventType type;
	char* returnValues;
} EventReturn;

typedef EventReturn (*EventFunction)(char* args, unsigned int const id);

typedef struct Event {
	EventType type;
	EventFunction function;
	char* args;
} Event;

Event* E_GetNext(unsigned int id);

int E_AddObj(unsigned int id);

void E_Init();
void E_Register(EventFunction function, EventType type, unsigned int const n, unsigned const int id, ...);
