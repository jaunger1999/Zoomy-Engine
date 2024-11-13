typedef void (*TickerFunction)(float);

typedef struct StateMachine {
	int** transitions;

	int state;
	TickerFunction* ticker;
	Attributes* attributes;
} StateMachine;

void Tick(StateMachine* fsm, float delta);
