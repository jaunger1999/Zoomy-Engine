
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "m_fixed.h"

#define TESTS 0xFFFF

int main(void)
{
	int64_t max = 0, min = 0;
	
	printf("%ld\n", fpsin(0));

	/* for(uint64_t i = 0; i <= TESTS; ++i) { */
	/* 	int64_t s   = (int64_t)lround((1ULL << 60) * sin(2 * M_PI * (double)i / (1ULL << 63))); */
	/* 	int64_t s5d = fpsin((int64_t)i); */
	/* 	int64_t err = s - s5d; */
	/* 	if(err > max) */
	/* 		max = err; */
	/* 	if(err < min) */
	/* 		min = err; */
	/* 	//printf("The value of %ul is %ld - compare %ld, diff : %ld\n", i, s5d, s, err); */
	/* } */
	/**/
	/* printf("min: %ld max: %ld\n", min, max); */

	return 0;
}
