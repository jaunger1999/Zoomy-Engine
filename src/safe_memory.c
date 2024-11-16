#include "safe_memory.h"

#include <stdio.h>
#include <stdlib.h>

void *safe_malloc(size_t n) {
    void *p = malloc(n);

    if(p == NULL) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
    }

    return p;
}
