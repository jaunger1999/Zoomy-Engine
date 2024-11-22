typedef void (*TickerFunction)(float);

typedef struct StateMachine {
	int              state;
	int**            transitions;
	TickerFunction** tickers;
} StateMachine;

void Tick(StateMachine* fsm, float delta);
