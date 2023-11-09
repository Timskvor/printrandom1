#include "random_source.h"
#include <stdlib.h>
#include <stdint.h>

enum
{
    MASK = 0x7FFFFFFF,
    MOD = 0x80000000
};

typedef struct LinearRandomSource {
    RandomSource base;
    uint32_t state;
} LinearRandomSource;

static double
next(LinearRandomSource *src)
{
    src->state = 1103515245 * src->state + 12345;
    return (double) (src->state & MASK) / (double) MOD;
}

static RandomSource *
destroy(LinearRandomSource *src)
{
    free(src);
    return NULL;
}

static RandomSourceOperations linear_ops = {.destroy = (void *) destroy, .next = (void *) next};

RandomSource *
random_linear_factory(const char *params)
{
    LinearRandomSource *src = malloc(sizeof(LinearRandomSource));
    src->base.ops = &linear_ops;
    char *p;
    src->state = strtol(params, &p, 10) & MASK;
    return (RandomSource *) src;
}
