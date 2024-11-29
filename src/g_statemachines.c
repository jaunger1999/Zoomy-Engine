#include "g_events.h"
#include "g_statemachines.h"

#include <assert.h>
#include <stdlib.h>

int StateMachine_Destroy(StateMachine* sm) {
	for(int i = 0; i < sm->totalStates; i++) {
		for(int j = 0; j < sm->totalStates; j++) {
			free(sm->transitions[i]);
		}
	}

	free(sm);
	sm = NULL;

	return 1;
}

StateMachine* StateMachine_Init(int const totalStates, int const totalTransitions) {
	#define RETURN_ERROR\
		StateMachine_Destroy(sm);
		return NULL;

	#define MALLOC_INT_ARRAY(name, size)\
		name = malloc(sizeof(int) * size);\
		\
		if(name == NULL) {\
			RETURN_ERROR\
		}
	
	StateMachine* sm = malloc(sizeof(StateMachine));

	if(sm == NULL) {
		RETURN_ERROR
	}

	sm->totalStates      = totalStates;
	sm->totalTransitions = totalTransitions;

	MALLOC_INT_ARRAY(sm->transitions, totalStates)
	sm->tickers = calloc(totalStates, sizeof(TickerFunction*));

	if(sm->tickers == NULL) {
		RETURN_ERROR
	}

	// init all but the last state and its transitions.
	for(int i = 0; i < totalStates - 1; i++) {
		MALLOC_INT_ARRAY(sm->transitions[i], totalTransitions)

		// The 0 index is reserved for an animation ending, 
		// in which the state machine progresses to the next state.
		sm->transitions[i][0] = i + 1;

		//The rest of the states have unset transitions by default.
		for(int j = 1; j < totalTransitions; j++) {
			sm->transitions[i][j] = -1;
		}
	}

	// init the last states transitions.
	for(int k = 0; k < totalTransitions; k++) {
		MALLOC_INT_ARRAY(sm->transitions[totalStates - 1], totalTransitions)

		// By default the final state in our table has no defined transition.
		sm->transitions[totalStates - 1][k] = -1;
	}

	return sm;
}

void Tick(StateMachine* const sm, float const delta) {
	// our exit condition is in the loop.
	// our condition variable is signed so we don't underflow.
	for(float timeRemaining = delta; ; timeRemaining -= sm->timeToNextState) {
		// if we aren't moving to another state, tick and exit the loop.
		// we don't want to exit if we have states with no time length.
		if(timeRemaining < sm->timeToNextState && sm->timeToNextState > 0) {
			sm->tickers[sm->state](sm->id, timeRemaining);
			sm->timeToNextState -= timeRemaining;
			break;
		}

		sm->tickers[sm->state](sm->id, sm->timeToNextState);
	
		// set up our next state.
		// 0 index reserved for state timer ending.
		// TODO: call state exit and state entrance function.
		sm->state = sm->transitions[sm->state][0];
		sm->timeToNextState = sm->stateDurations[sm->state];
	}

	// Process registered events for this machine.
	for(Event* e = E_GetNext(sm->id); e != NULL; e = E_GetNext(sm->id)) {
		void* out = NULL;

		int const eventType = e->function(e->args, sm->id, out);

		// skip out processing if it's NULL
		if(out == NULL) {
			goto after_out_processing;
		}

		// process out

		after_out_processing:
		if(eventType == NONE) {
			continue;
		}

		assert(eventType >= 0 && eventType < sm->totalTransitions);

		int const nextState = sm->transitions[sm->state][eventType];

		if(nextState != NONE) {
			assert(nextState >= 0 && nextState < sm->totalTransitions);

			sm->state = nextState;
		}
	}
}
