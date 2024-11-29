typedef void (*TickerFunction)(int const id, float const delta);

typedef struct StateMachine {
	int             state;
	int**           transitions;
	TickerFunction* tickers;

	float* stateDurations;
	float  timeToNextState;

	int id;
	int totalStates;
	int totalTransitions;
} StateMachine;

void Tick(StateMachine* const fsm, float const delta);
