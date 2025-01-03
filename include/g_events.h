typedef enum EventType {
	NONE          = 0,
	ANIMATION_END = 1,
	PLAYER_MOVE   = 2, 
} EventType;

typedef unsigned int (*EventFunction)(char const * const args, unsigned int const id, void* out);

typedef struct Event {
	EventType type;
	EventFunction function;
	char* args;
} Event;

int E_GetNext(unsigned int id, Event* e);

int E_AddObj(unsigned int id);

int E_Init(void);
int E_Register(EventFunction function, EventType type, unsigned int const id, unsigned const int n, ...);
