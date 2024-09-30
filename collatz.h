#ifndef COLLATZ_H
#define COLLATZ_H
#include "cache.h"

unsigned long long collatz(unsigned long long num);
unsigned long long collatz_cache_wrapper(Cache *cache, unsigned long long num);

#endif
