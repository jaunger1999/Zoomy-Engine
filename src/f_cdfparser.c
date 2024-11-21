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
unsigned long floatHash;
unsigned long intHash;

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
	floatHash   = hash_s("float");
	intHash     = hash_s("int");

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

char* StringCopy(char const * const src) {
	char* dest = malloc(sizeof(char) * (strlen(src) + 1));
	
	if(dest == NULL) {
		fprintf(stderr, "Malloc failed to allocate a string.\n");
		return NULL;
	}
	
	strdup(dest, src);

	return dest;
}

int ParseEvents(char* fileText, char* currToken char const * const delimit[]);
int ParseA_Events(char* fileText, char* currToken char const * const delimit[]);
int ParseTransitions(char* fileText, char* currToken char const * const delimit[]);

int ParseObject(char* fileText, char* currToken char const * const delimit[]) {
	// Macros so I don't have to copy-paste my ass off.
	#define RETURN_ERROR\
		Dict_S_Destroy(obj->floats);\
		Dict_S_Destroy(obj->ints);\
		free(obj);\
		free(name);\
		return -1;

	#define TOKEN_COPY(name)\
		char* name;\
		\
		if((name = StringCopy(currToken)) == NULL) {\
			RETURN_ERROR\
		}

	#define GET_NEXT_TOKEN\
		currToken = strtok(fileText, delimit);\
		\
		if(currToken == NULL) {\
			fprintf(stderr, "Expected token");\
			RETURN_ERROR\
		}
	
	// Allocate our object.
	Object* obj = malloc(sizeof(Object));

	if(obj == NULL) {
		fprintf(stderr, "Malloc failed to allocate an object.\n");
		RETURN_ERROR
	}

	// Init our dicts.
	obj->floats = Dict_S_Create();
	obj->ints   = Dict_S_Create();

	if(obj->floats == NULL || obj->ints == NULL) {
		RETURN_ERROR
	}

	GET_NEXT_TOKEN

	char* objName = NULL;

	// The name is expected to be in the same line as the object keyword.
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
			if((objName = StringCopy(currToken)) == NULL) {
				RETURN_ERROR
			}
			break;
	}

	GET_NEXT_TOKEN

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
			case closedBrace: // means we're done
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
			case floatHash:
				GET_NEXT_TOKEN
				TOKEN_COPY(name)

				GET_NEXT_TOKEN
				float variable = atof(currToken);
				Dict_S_Add(obj->floats, name, variable);
				continue;
			case intHash:
				GET_NEXT_TOKEN
				TOKEN_COPY(name)

				GET_NEXT_TOKEN
				int variable = atol(currToken);
				Dict_S_Add(obj->ints, name, variable);
				continue;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				RETURN_ERROR
		}
	}

	Dict_S_Add(objTemplates, name, obj);

	return 1;
}

int ParseEvents(char* fileText, char* currToken char const * const delimit[]) {

}

int ParseA_Events(char* fileText, char* currToken char const * const delimit[]) {

}

int ParseTransitions(char* fileText, char* currToken char const * const delimit[]) {

}
