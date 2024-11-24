/// f_cdfparser.c
///
/// There's a small chance of user defined terms to collide with cdf keywords and symbols. Not sure if that's worth addressing.

#include "d_dict_s.h"
#include "d_string.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

// Precomputed hash values to create a switch statement.
#define OBJECT       3150600508
#define OPEN_BRACE     51624448
#define CLOSED_BRACE 3453045186
#define EVENTS       3847627034
#define A_EVENTS     3587176570
#define TRANSITIONS  2309289059
#define FLOAT         458547227
#define INT          2897414608

#define MAX_STR_LEN 32

Dict_S* objTemplates;

int CDF_Init() {
	objTemplates = Dict_S_Create();

	if(objTemplates == NULL) {
		return 0;
	}
	
	return 1;
}

int CDF_Parse(char const* const fileName);

int CDF_ParseRoot() {
	CDF_Init();

	char const* const delimit =" \t\r\n\v\f";
	char* fileText = LoadFileText("cdf/root.cdf");

	char* currToken = strtok(fileText, delimit);

	while(currToken) {
		CDF_Parse(currToken);
	}

	return 1;
}

int ParseObject(char* fileText, char* currToken, char const * const delimit);

int CDF_Parse(char const* const fileName) {
	char const* const delimit =" \t\r\n\v\f";
	char* fileText = LoadFileText(fileName);

	char* currToken = strtok(fileText, delimit);

	while(currToken) {
		if(strcmp(currToken, "") == 0) {
			currToken = strtok(fileText, delimit);
			continue;
		}

		switch(hash_s(currToken, MAX_STR_LEN)) {
			case OBJECT:
				ParseObject(fileText, currToken, delimit);
				continue;
			case OPEN_BRACE:
				continue;
			case CLOSED_BRACE:
				continue;
			case EVENTS:
				continue;
			case A_EVENTS:
				continue;
			case TRANSITIONS:
				continue;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				return -1;
		}

		currToken = strtok(fileText, delimit);
	}

	return 1;
}

typedef struct Object {
	Dict_S* floats;
	Dict_S* ints;
} Object;

int ParseEvents     (char* fileText, char* currToken, char const * const delimit);
int ParseA_Events   (char* fileText, char* currToken, char const * const delimit);
int ParseTransitions(char* fileText, char* currToken, char const * const delimit);

int ParseObject(char* fileText, char* currToken, char const * const delimit) {
	// Macros so I don't have to copy-paste my ass off.
	#define RETURN_ERROR\
		Dict_S_Destroy(obj->floats);\
		Dict_S_Destroy(obj->ints);\
		free(obj);\
		free(objName);\
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
			fprintf(stderr, "Expected token\n");\
			RETURN_ERROR\
		}
	
	// Allocate our object.
	Object* obj = malloc(sizeof(Object));
	char* objName = NULL;

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

	// The name is expected to be in the same line as the object keyword.
	switch(hash_s(currToken, MAX_STR_LEN)) {
		case OBJECT:
		case OPEN_BRACE:
		case CLOSED_BRACE:
		case EVENTS:
		case A_EVENTS:
		case TRANSITIONS:
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
	switch(hash_s(currToken, MAX_STR_LEN)) {
		case OPEN_BRACE:
			break;
		default:
			fprintf(stderr, "Expected open brace { after object definition.");
			RETURN_ERROR
	}

	GET_NEXT_TOKEN

	// parse the rest of the obj definition.
	while(currToken) {
		switch(hash_s(currToken, MAX_STR_LEN)) {
			case OBJECT:
				fprintf(stderr, "Can't define an object within an object");
				RETURN_ERROR
			case OPEN_BRACE:
				fprintf(stderr, "Unexpected brace {");
				RETURN_ERROR
			case CLOSED_BRACE: // means we're done
				break;
			case EVENTS:
				ParseEvents(fileText, currToken, delimit);
				continue;
			case A_EVENTS:
				ParseA_Events(fileText, currToken, delimit);
				continue;
			case TRANSITIONS:
				ParseTransitions(fileText, currToken, delimit);
				continue;
			case FLOAT:
				GET_NEXT_TOKEN
				TOKEN_COPY(fName)

				GET_NEXT_TOKEN
				float* f = malloc(sizeof(float));

				if(f == NULL) {
					RETURN_ERROR
				}

				*f = atof(currToken);
				Dict_S_Add(obj->floats, fName, f);
				continue;
			case INT:
				GET_NEXT_TOKEN
				TOKEN_COPY(iName)

				GET_NEXT_TOKEN
				int* i = malloc(sizeof(int));

				if(i == NULL) {
					RETURN_ERROR
				}

				*i = atol(currToken);
				Dict_S_Add(obj->ints, iName, i);
				continue;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				RETURN_ERROR
		}

		currToken = strtok(fileText, delimit);
	}

	Dict_S_Add(objTemplates, objName, obj);

	return 1;
}

int ParseEvents(char* fileText, char* currToken, char const * const delimit) {

	return 1;
}

int ParseA_Events(char* fileText, char* currToken, char const * const delimit) {

	return 1;
}

int ParseTransitions(char* fileText, char* currToken, char const * const delimit) {

	return 1;
}
