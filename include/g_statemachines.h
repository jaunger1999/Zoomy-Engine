typedef void (*TickerFunction)(unsigned int const id, float const delta);

typedef struct StateMachine {
	unsigned int   state;
	unsigned int** transitions;

	TickerFunction* tickers;
	TickerFunction* entrances;
	TickerFunction* exits;

	float* stateDurations;
	float  timeToNextState;

	unsigned int id;
	unsigned int totalStates;
	unsigned int totalTransitions;
} StateMachine;

void Tick(StateMachine* const fsm, float const delta);
