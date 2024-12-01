/// f_cdfparser.c
///
/// Content Definition Format (CDF), inspired by the Eternity Engine's edf.
/// It's a file format for defining game objects.
///
/// There's a small chance of hashed user defined terms to collide with hashed cdf keywords and symbols. Not sure if that's worth addressing.
/// I added padding to each string so there shouldn't be any collisions I think.
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
#define STATES       3457781689 

// padding constant so we can avoid hash collisions.
#define MAX_STR_LEN 32

Dict_S* objTemplates;

int CDF_Init() {
	objTemplates = Dict_S_Create();

	if(objTemplates == NULL) {
		return 0;
	}
	
	return 1;
}

int CDF_Parse(char const* const fileName, char const* const delimit);

int CDF_ParseRoot(char const* const rootPath) {
	CDF_Init();

	// white space characters to divide our cdf files.
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

	// Open each file listed in the root file and parse them
	for(char* currToken = strtok(fileText, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		// Create a path to our file.
		char cdfFilePath[strlen(cdfPath) + strlen(currToken)];

		strcpy(cdfFilePath, cdfPath);
		strcat(cdfFilePath, currToken);

		CDF_Parse(cdfFilePath, delimit);

		currToken = strtok(NULL, delimit);
	}

	return 1;
}

// Parse an object from within a cdf file.
int ParseObject(char* currToken, char const* const delimit);

// Parse an individual cdf file.
int CDF_Parse(char const* const fileName, char const* const delimit) {
	char* fileText = LoadFileText(fileName);

	for(char* currToken = strtok(fileText, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		if(strcmp(currToken, "") == 0) {
			continue;
		}

		switch(hash_s(currToken, MAX_STR_LEN)) {
			case OBJECT:
				ParseObject(currToken, delimit);
				break;
			case OPEN_BRACE:
				break;
			case CLOSED_BRACE:
				break;
			case EVENTS:
				break;
			case A_EVENTS:
				break;
			case TRANSITIONS:
				break;
			case STATES:
				break;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				return -1;
		}
	}

	return 1;
}

// Template struct for now.
typedef struct Object {
	Dict_S* floats;
	Dict_S* ints;
} Object;

int ParseStates     (char* currToken, char const* const delimit);
int ParseEvents     (char* currToken, char const* const delimit);
int ParseA_Events   (char* currToken, char const* const delimit);
int ParseTransitions(char* currToken, char const* const delimit);

int ParseObject(char* currToken, char const* const delimit) {
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
	for(currToken = strtok(NULL, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
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
				break;
			case A_EVENTS:
				ParseA_Events(currToken, delimit);
				break;
			case TRANSITIONS:
				ParseTransitions(currToken, delimit);
				break;
			case STATES:
				ParseStates(currToken, delimit);
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
				break;
			default:
				fprintf(stderr, "Unexpected token: %s\n", currToken);
				RETURN_ERROR
		}
	}

	// Needed for when we find our closing brace.
	loopExit:
	Dict_S_Add(objTemplates, objName, obj);

	return 1;
}

int ParseStates(char* currToken, char const * const delimit) {
	currToken = strtok(NULL, delimit);

	if(strcmp(currToken, "{") != 0) {
		return 0;
	}

	for(currToken = strtok(NULL, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		switch(hash_s(currToken, MAX_STR_LEN)) {
			case CLOSED_BRACE:
				goto loopExit;
		}
	}

	// Needed for when we find our closing brace.
	loopExit:
	return 1;
}

int ParseEvents(char* currToken, char const * const delimit) {
	currToken = strtok(NULL, delimit);

	if(strcmp(currToken, "{") != 0) {
		return 0;
	}

	for(currToken = strtok(NULL, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		switch(hash_s(currToken, MAX_STR_LEN)) {
			case CLOSED_BRACE:
				goto loopExit;
		}
	}

	// Needed for when we find our closing brace.
	loopExit: ;
	return 1;
}

// Action Events
int ParseA_Events(char* currToken, char const* const delimit) {
	currToken = strtok(NULL, delimit);

	if(strcmp(currToken, "{") != 0) {
		return 0;
	}

	for(currToken = strtok(NULL, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		switch(hash_s(currToken, MAX_STR_LEN)) {
			case CLOSED_BRACE:
				goto loopExit;
		}
	}

	// Needed for when we find our closing brace.
	loopExit: ;
	return 1;
}

int ParseTransitions(char* currToken, char const* const delimit) {
	currToken = strtok(NULL, delimit);

	if(strcmp(currToken, "{") != 0) {
		return 0;
	}

	for(currToken = strtok(NULL, delimit); currToken != NULL; currToken = strtok(NULL, delimit)) {
		switch(hash_s(currToken, MAX_STR_LEN)) {
			case CLOSED_BRACE:
				goto loopExit;
		}
	}

	loopExit: ;
	return 1;
}
