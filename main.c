#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cache.h"


unsigned long long collatz_cache_wrapper(Cache *cache, unsigned long long num);

unsigned long long generate_random_numbers(unsigned long long min, unsigned long long max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <N> <MIN> <MAX> <Cache Method> <CACHE_SIZE>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    unsigned long long MIN = strtoull(argv[2], NULL, 10);
    unsigned long long MAX = strtoull(argv[3], NULL, 10);
    char *cache_method_str = argv[4];
    int CACHE_SIZE = atoi(argv[5]);

    CacheMethod method;
    if (strcmp(cache_method_str, "MRU") == 0) {
        method = MRU;
    } else {
        method = LRU;
    }

    if (N <= 0 || MIN > MAX || CACHE_SIZE <= 0) {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    Cache *cache = init_cache(method, CACHE_SIZE);

    FILE *file = fopen("collatz_results_with_cache.csv", "w");
    if (!file) {
        perror("Failed to open file");
        free_cache(cache);
        return 1;
    }
    fprintf(file, "Number,Steps,Cache Method,Time (ms),Cache Hit Rate (%%)\n");

    srand(time(NULL));

    for (int iter = 0; iter < N; iter++) {
        unsigned long long random_num = generate_random_numbers(MIN, MAX);
        
        clock_t start_time = clock(); 
        unsigned long long steps = collatz_cache_wrapper(cache, random_num);
        clock_t end_time = clock(); 
        
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; 
        float hit_rate = (float)cache->cache_hits / (cache->cache_hits + cache->cache_misses) * 100; 
        
        fprintf(file, "%llu,%llu,%s,%.2f,%.2f%%\n", random_num, steps, cache_method_str, time_taken, hit_rate);
    }

    fclose(file);

    float overall_hit_rate = (float)cache->cache_hits / (cache->cache_hits + cache->cache_misses) * 100;
    printf("Overall cache hit rate: %.2f%%\n", overall_hit_rate);

    free_cache(cache);

    return 0;
}