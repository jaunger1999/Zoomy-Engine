typedef void (*TickerFunction)(float);

typedef struct StateMachine {
	int** transitions;

	int state;
	TickerFunction* ticker;
} StateMachine;

void Tick(StateMachine* fsm, float delta);
