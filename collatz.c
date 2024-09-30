#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"
#include "collatz.h"

unsigned long long collatz(unsigned long long num) {
    unsigned long long steps = 0;
    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
        } else {
            num = 3 * num + 1;
        }
        steps++;
    }
    return steps;
}

unsigned long long collatz_cache_wrapper(Cache *cache, unsigned long long num) {
    unsigned long long result = get_from_cache(cache, num);
    if (result == 0) {
        result = collatz(num);
        add_to_cache(cache, num, result);
        return result;
    } else {
        return result;
    }
}