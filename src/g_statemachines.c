#include "g_statemachines.h"
#include "g_events.h"

#include <assert.h>
#include <stdlib.h>

int StateMachine_Destroy(StateMachine* sm) {
	// check for NULL so we don't seg fault.
	if(sm == NULL) {
		return 1;
	}

	for(unsigned int i = 0; i < sm->totalStates; i++) {
		free(sm->transitions[i]);
	}

	free(sm->stateDurations);
	free(sm->transitions);
	free(sm->tickers);
	free(sm->entrances);
	free(sm->exits);

	free(sm);

	return 1;
}

StateMachine* StateMachine_Init(unsigned int const totalStates, unsigned int const totalTransitions) {
#define RETURN_ERROR         \
	StateMachine_Destroy(sm); \
	return NULL;

#define CALLOC_ARRAY(type, name, size) \
	name = calloc(size, sizeof(type));  \
                                       \
	if(name == NULL) {                  \
		RETURN_ERROR                     \
	}

	StateMachine* sm = malloc(sizeof(StateMachine));

	if(sm == NULL) {
		return NULL;
	}

	sm->totalStates      = totalStates;
	sm->totalTransitions = totalTransitions;

	CALLOC_ARRAY(int, sm->transitions, totalStates)

	// calloc so we can check for NULL.
	CALLOC_ARRAY(TickerFunction*, sm->tickers, totalStates)
	CALLOC_ARRAY(TickerFunction*, sm->entrances, totalStates)
	CALLOC_ARRAY(TickerFunction*, sm->exits, totalStates)

	// init all but the last state and its transitions.
	for(unsigned int i = 0; i < totalStates - 1; i++) {
		CALLOC_ARRAY(int, sm->transitions[i], totalTransitions)

		// The 0 index is reserved for an animation ending,
		// in which the state machine progresses to the next state.
		sm->transitions[i][0] = i + 1;
	}

	// init the last states transitions.
	CALLOC_ARRAY(int, sm->transitions[totalStates - 1], totalTransitions)

	return sm;
}

void Tick(StateMachine* const sm, float const delta) {
	assert(delta > 0);
	assert(sm != NULL);

	// loop through as many states within delta time as we can.
	float timeRemaining;

	for(timeRemaining = delta;
	    (timeRemaining < sm->timeToNextState && sm->timeToNextState > 0) || sm->stateDurations[sm->state] == -1;
	    timeRemaining -= sm->timeToNextState) {
		sm->tickers[sm->state](sm->id, sm->timeToNextState);

		if(sm->exits[sm->state] != NULL) {
			sm->exits[sm->state](sm->id, delta);
		}

		// set up our next state.
		// 0 index reserved for state timer ending.
		sm->state           = sm->transitions[sm->state][0];
		sm->timeToNextState = sm->stateDurations[sm->state];

		if(sm->entrances[sm->state] != NULL) {
			sm->entrances[sm->state](sm->id, delta);
		}
	}

	// tick the remaining time
	sm->tickers[sm->state](sm->id, timeRemaining);
	sm->timeToNextState -= timeRemaining;

	// Process registered events for this machine.
	for(Event* e = E_GetNext(sm->id); e != NULL; e = E_GetNext(sm->id)) {
		void* out = NULL;

		unsigned int const eventType = e->function(e->args, sm->id, out);

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

		unsigned int const nextState = sm->transitions[sm->state][eventType];

		if(nextState != NONE) {
			assert(nextState >= 0 && nextState < sm->totalTransitions);

			sm->state = nextState;
		}
	}
}
