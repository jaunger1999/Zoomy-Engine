#include "hash.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 32

int main(void) {
	unsigned long const object      = hash_s("object",      MAX_STR_LEN);
	unsigned long const openBrace   = hash_s("{",           MAX_STR_LEN);
	unsigned long const closedBrace = hash_s("}",           MAX_STR_LEN);
	unsigned long const events      = hash_s("events",      MAX_STR_LEN);
	unsigned long const a_events    = hash_s("a_events",    MAX_STR_LEN);
	unsigned long const transitions = hash_s("transitions", MAX_STR_LEN);
	unsigned long const floatHash   = hash_s("float",       MAX_STR_LEN);
	unsigned long const intHash     = hash_s("int",         MAX_STR_LEN);
	unsigned long const states      = hash_s("states",      MAX_STR_LEN);

	printf("%lu\n", object);
	printf("%lu\n", openBrace);
	printf("%lu\n", closedBrace);
	printf("%lu\n", events);
	printf("%lu\n", a_events);
	printf("%lu\n", transitions);
	printf("%lu\n", floatHash);
	printf("%lu\n", intHash);
	printf("%lu\n", states);


	return 1;
}
