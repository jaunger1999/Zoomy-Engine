#include "g_statemachines.h"

#include <stdlib.h>

StateMachine* StateMachine_Init() {
	StateMachine* sm = malloc(sizeof(StateMachine));

	sm->transitions = malloc(sizeof(int) * totalStates);
	sm->tickers     = calloc(totalStates, sizeof(TickerFunction*));

	for(int i = 0; i < totalStates; i++) {
		sm->transitions[i] = malloc(sizeof(int) * totalStates);

		for(int j = 0; j < totalStates; j++) {
			sm->transitions[j] = -1;
		}
	}

	return sm;
}
