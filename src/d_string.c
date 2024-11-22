#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* StringCopy(char const * const src) {
	char* dest = malloc(sizeof(char) * (strlen(src) + 1));
	
	if(dest == NULL) {
		fprintf(stderr, "Malloc failed to allocate a string.\n");
		return NULL;
	}
	
	strcpy(dest, src);

	return dest;
}
