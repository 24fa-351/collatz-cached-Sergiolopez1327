#include <stdlib.h>
#include <string.h>
#include "cache.h"

Cache *init_cache(CacheMethod method, unsigned long long size) {
    Cache *cache = malloc(sizeof(Cache));
    cache->nodes = malloc(size * sizeof(CacheNode));
    cache->size = size;
    cache->cache_hits = 0;
    cache->cache_misses = 0;
    cache->method = method;
    cache->current_node_order = 0;

    for (unsigned long long iter = 0; iter < size; iter++) {
        cache->nodes[iter].key = 0;
        cache->nodes[iter].value = 0;
        cache->nodes[iter].frequency = 0;
        cache->nodes[iter].node_order = 0;
    }

    return cache;
}

unsigned long long get_from_cache(Cache *cache, unsigned long long key) {
    for (unsigned long long iter = 0; iter < cache->size; iter++) {
        if (cache->nodes[iter].key == key) {
            cache->nodes[iter].node_order = cache->current_node_order++;  
            cache->cache_hits++;
            return cache->nodes[iter].value;
        }
    }
    cache->cache_misses++;
    return 0;  
}

void add_to_cache(Cache *cache, unsigned long long key, unsigned long long value) {
    unsigned long long most_recent_index = 0;

   
    for (unsigned long long iter = 1; iter < cache->size; iter++) {
        if (cache->nodes[iter].node_order > cache->nodes[most_recent_index].node_order) {
            most_recent_index = iter;
        }
    }

    if (cache->method == MRU) {
        cache->nodes[most_recent_index].key = key;
        cache->nodes[most_recent_index].value = value;
        cache->nodes[most_recent_index].node_order = cache->current_node_order++; 
    } else {
        unsigned long long min_freq_index = 0;
        for (unsigned long long iter = 1; iter < cache->size; iter++) {
            if (cache->nodes[iter].frequency < cache->nodes[min_freq_index].frequency) {
                min_freq_index = iter;
            }
        }
        cache->nodes[min_freq_index].key = key;
        cache->nodes[min_freq_index].value = value;
        cache->nodes[min_freq_index].frequency = 1;
        cache->nodes[min_freq_index].node_order = cache->current_node_order++;
    }
}

void free_cache(Cache *cache) {
    free(cache->nodes);
    free(cache);
}
