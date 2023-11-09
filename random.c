#include "random_source.h"
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct URandomSource {
    RandomSource base;
    int fd;
} URandomSource;

static double
next(URandomSource *src)
{
    uint64_t value;
    read(src->fd, &value, sizeof(value));
    return (double) value / (double) UINT64_MAX;
}

static RandomSource *
destroy(URandomSource *src)
{
    close(src->fd);
    free(src);
    return NULL;
}

static RandomSourceOperations random_ops = {.destroy = (void *) destroy, .next = (void *) next};

RandomSource *
random_random_factory(const char *params)
{
    URandomSource *src = malloc(sizeof(URandomSource));
    src->base.ops = &random_ops;
    src->fd = open("/dev/urandom", O_RDONLY);
    return (RandomSource *) src;
}
