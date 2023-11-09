#ifndef RANDOM_SOURCE_H
#define RANDOM_SOURCE_H

typedef struct RandomSource RandomSource;

typedef struct RandomSourceOperations {
    RandomSource *(*destroy)(RandomSource *src);
    double (*next)(RandomSource *src);
} RandomSourceOperations;

struct RandomSource {
    RandomSourceOperations *ops;
};

RandomSource *random_linear_factory(const char *params);
RandomSource *random_random_factory(const char *params);

#endif
