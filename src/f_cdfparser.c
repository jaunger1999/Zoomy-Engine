/// f_cdfparser.c
///
/// There's a small chance of user defined terms to collide with cdf keywords and symbols. Not sure if that's worth addressing.

#include "hash.h"

#include <stdio.h>

unsigned long object;
unsigned long openBrace;
unsigned long closedBrace;
unsigned long events;
unsigned long a_events;
unsigned long transitions;

Dict_S* objTemplates;

int CDF_Init() {
	objTemplates = Dict_S_Create();

	if(objTemplates == NULL) {
		return -1;
	}

	// init our hash values for our string switch statements.
	object      = hash_s("object");
	openBrace   = hash_s("{");
	closedBrace = hash_s("}");
	events      = hash_s("events");
	a_events    = hash_s("a_events");
	transitions = hash_s("transitions");

	return 1;
}

int ParseCDF(char const* const fileName) {
	char const * const delimit =" \t\r\n\v\f";
	char* fileText = LoadFileText(fileName);

	char* currToken = strtok_r(fileText, delimit);

	while(currToken) {
		if(strcmp(currToken, "") == 0) {
			currToken = strtok(fileText, delimit);
			continue;
		}

		switch(hash(currToken)) {
			case object:
				ParseObject(fileText, currToken);
				break;
			case openBrace:
				break;
			case closedBrace:
				break;
			case events:
				break;
			case a_events:
				break;
			case transitions:
				break;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				return -1;
		}


		currToken = strtok(fileText, delimit);
	}
}

int ParseObject(char* fileText, char* currToken char const * const delimit[]) {
	Object* obj  = malloc(sizeof(Object));
	char*   name = NULL;

	#define RETURN_ERROR free(obj); free(name); return -1;

	// The name is expected to be in the same line as the object keyword.
	while(name == NULL && currToken) {
		switch(hash(currToken)) {
			case object:
			case openBrace:
			case closedBrace:
			case events:
			case a_events:
			case transitions:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				RETURN_ERROR
			default:
				name = malloc(sizeof(char) * (strlen(currToken) + 1));

				if(name == NULL) {
					fprintf(stderr, "Malloc failed to allocate a string.\n");
					RETURN_ERROR
				}

				strdup(name, currToken);
				break;
		}

		currToken = strtok(fileText, delimit);
	}

	// We need a name to store this object in our dict_s
	if(name == NULL) {
		RETURN_ERROR
	}

	// check for an open brace.
	switch(hash(currToken)) {
		case openBrace:
			break;
		default:
			fprintf(stderr, "Expected open brace { after object definition.");
			RETURN_ERROR
	}

	// parse the rest of the obj definition.
	while(currToken) {
		currToken = strtok(fileText, delimit);

		switch(hash(currToken)) {
			case object:
				fprintf(stderr, "Can't define an object within an object");
				RETURN_ERROR
			case openBrace:
				fprintf(stderr, "Unexpected brace {");
				RETURN_ERROR
			case closedBrace:
				break;
			case events:
				ParseEvents(fileText, delimit);
				continue;
			case a_events:
				ParseA_Events(fileText, delimit);
				continue;
			case transitions:
				ParseTransitions(fileText, delimit);
				continue;
			default:
				ParseVariable(fileText, delimit);
				continue;
		}

	}

	Dict_S_Add(objTemplates, name, obj);

	return obj;
}

int ParseEvents(char* fileText, char* currToken char const * const delimit[]) {

}

int ParseA_Events(char* fileText, char* currToken char const * const delimit[]) {

}

int ParseTransitions(char* fileText, char* currToken char const * const delimit[]) {

}

int ParseVariable(char* fileText, char* currToken char const * const delimit[]) {

}
