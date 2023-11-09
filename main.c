#include "random_source.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    RandomSource *(*factory)(const char *) = NULL;
    if (strcmp(argv[1], "linear") == 0) {
        factory = random_linear_factory;
    } else if (strcmp(argv[1], "random") == 0) {
        factory = random_random_factory;
    } else {
        return 1;
    }
    char *p;
    int count = strtoll(argv[2], &p, 10);
    RandomSource *source = factory(argv[3]);
    for (int i = 0; i < count; i++) {
        printf("%.10g\n", source->ops->next(source));
    }
    source->ops->destroy(source);
    return 0;
}
