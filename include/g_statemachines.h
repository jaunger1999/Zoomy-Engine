typedef void (*TickerFunction)(float);

typedef struct StateMachine {
	int              state;
	int**            transitions;
	TickerFunction** tickers;
	Attributes**     attributes;
} StateMachine;

void Tick(StateMachine* fsm, float delta);
