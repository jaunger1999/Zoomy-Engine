typedef enum EventType {
	NONE          = -1,
	ANIMATION_END =  0,
	PLAYER_MOVE   =  1
} EventType;

typedef int (*EventFunction)(char const * const args, unsigned int const id, void* out);

typedef struct Event {
	EventType type;
	EventFunction function;
	char* args;
} Event;

Event* E_GetNext(unsigned int id);

int E_AddObj(unsigned int id);

int E_Init();
int E_Register(EventFunction function, EventType type, unsigned int const id, unsigned const int n, ...);
