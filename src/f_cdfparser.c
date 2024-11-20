#include "hash.h"

#include <stdio.h>

unsigned long object;
unsigned long openBrace;
unsigned long closedBrace;
unsigned long events;
unsigned long a_events;
unsigned long transitions;

Dict_S* objTemplates;

int InitHashValues() {
	object      = hash_s("object");
	openBrace   = hash_s("{");
	closedBrace = hash_s("}");
	events      = hash_s("events");
	a_events    = hash_s("a_events");
	transitions = hash_s("transitions");

	return 1;
}

int CDF_Init() {
	objTemplates = Dict_S_Create();

	if(objTemplates == NULL) {
		return -1;
	}

}

int ParseCDF(char const* const fileName) {
	char const * const delimit = " \n";
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
				return -1;
			default:
				name = malloc(sizeof(char) * (strlen(currToken) + 1));

				if(name == NULL) {
					fprintf(stderr, "Malloc failed to allocate a string.\n");
					return -1;
				}
				strdup(name, currToken);
				break;
		}

		currToken = strtok(fileText, delimit);
	}

	if(name == NULL) {
		return -1;
	}

	// check for an open brace.
	switch(hash(currToken)) {
		case openBrace:
			break;
		default:
			fprintf(stderr, "Expected open brace { after object definition.");
			return -1;
	}

	while(currToken) {
		currToken = strtok(fileText, delimit);
	}

	Dict_S_Add(objTemplates, name, obj);

	return obj;
}
