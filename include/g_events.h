typedef EventReturn (*EventFunction)(char*);

typedef enum EventType {
	DAMAGE = 0
} EventType;

typedef struct EventReturn {
	EventType type;
	char* returnValues;
} EventReturn;

typedef struct Event {
	EventType type;
	EventFunction function;
	char* args;
} Event;

Event* E_GetNext(int id);

int E_AddObj();

void E_Init();
void E_Register(EventFunction function, EventType type, int n, int id, ...);
