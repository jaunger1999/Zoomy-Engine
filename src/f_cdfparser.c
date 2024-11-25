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

int CDF_ParseRoot(char const* const rootPath) {
	CDF_Init();

	char const* const delimit =" \t\r\n\v\f";

	char const* const cdfDir = "/cdf/";
	char const* const cdfRootFile = "root.cdf";

	// init our cdfPath. We're gonna use it a lot.
	char cdfPath[strlen(rootPath) + strlen(cdfDir)];

	strcpy(cdfPath, rootPath);
	strcat(cdfPath, cdfDir);

	// Create a path to our cdf root file.
	char cdfRootPath[strlen(cdfPath) + strlen(cdfRootFile)];

	strcpy(cdfRootPath, cdfPath);
	strcat(cdfRootPath, cdfRootFile);

	char* fileText = LoadFileText(cdfRootPath);
	char* currToken = strtok(fileText, delimit);

	while(currToken) {
		char cdfFilePath[strlen(cdfPath) + strlen(currToken)];

		strcpy(cdfFilePath, cdfPath);
		strcat(cdfFilePath, currToken);

		CDF_Parse(cdfFilePath);

		currToken = strtok(NULL, delimit);
	}

	return 1;
}

int ParseObject(char* currToken, char const * const delimit);

int CDF_Parse(char const* const fileName) {
	char const* const delimit =" \t\r\n\v\f";
	char* fileText = LoadFileText(fileName);

	char* currToken = strtok(fileText, delimit);

	while(currToken) {
		if(strcmp(currToken, "") == 0) {
			currToken = strtok(NULL, delimit);
			continue;
		}

		switch(hash_s(currToken, MAX_STR_LEN)) {
			case OBJECT:
				ParseObject(currToken, delimit);
				currToken = strtok(NULL, delimit);
				break;
			case OPEN_BRACE:
				currToken = strtok(NULL, delimit);
				break;
			case CLOSED_BRACE:
				currToken = strtok(NULL, delimit);
				break;
			case EVENTS:
				currToken = strtok(NULL, delimit);
				break;
			case A_EVENTS:
				currToken = strtok(NULL, delimit);
				break;
			case TRANSITIONS:
				currToken = strtok(NULL, delimit);
				break;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				return -1;
		}
	}

	return 1;
}

typedef struct Object {
	Dict_S* floats;
	Dict_S* ints;
} Object;

int ParseEvents     (char* currToken, char const * const delimit);
int ParseA_Events   (char* currToken, char const * const delimit);
int ParseTransitions(char* currToken, char const * const delimit);

int ParseObject(char* currToken, char const * const delimit) {
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
		currToken = strtok(NULL, delimit);\
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
				goto loopExit;
			case EVENTS:
				ParseEvents(currToken, delimit);
				currToken = strtok(NULL, delimit);
				break;
			case A_EVENTS:
				ParseA_Events(currToken, delimit);
				currToken = strtok(NULL, delimit);
				break;
			case TRANSITIONS:
				ParseTransitions(currToken, delimit);
				currToken = strtok(NULL, delimit);
				break;
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
				currToken = strtok(NULL, delimit);
				break;
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
				currToken = strtok(NULL, delimit);
				break;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				RETURN_ERROR
		}
	}

	loopExit: ;
	Dict_S_Add(objTemplates, objName, obj);

	return 1;
}

int ParseEvents(char* currToken, char const * const delimit) {

	return 1;
}

int ParseA_Events(char* currToken, char const * const delimit) {

	return 1;
}

int ParseTransitions(char* currToken, char const * const delimit) {

	return 1;
}
