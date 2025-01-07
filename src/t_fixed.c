
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "m_fixed.h"

int main(void)
{
	int64_t fixedSin = fpsin(FIXED_UNIT);

	printf("\nFloat: sin(1) == %f\n", sin(1));
	printf("Fixed: sin(%lldl) == %ldl\n", FIXED_UNIT, fixedSin);
	printf("Fixed result as integer: %ldl\n", fixedSin >> 32);
	printf("End of processing\n");
	return 0;
}
