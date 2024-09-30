#ifndef CACHE_H
#define CACHE_H

typedef enum {
    LRU,
    MRU
} CacheMethod;

typedef struct CacheNode {
    unsigned long long key;
    unsigned long long value;
    unsigned long long frequency;
    unsigned long long node_order;
} CacheNode;

typedef struct Cache {
    CacheNode *nodes;
    unsigned long long size;
    unsigned long long cache_hits;
    unsigned long long cache_misses;
    unsigned long long current_node_order;
    CacheMethod method;
} Cache;

Cache *init_cache(CacheMethod method, unsigned long long size);
unsigned long long get_from_cache(Cache *cache, unsigned long long key);
void add_to_cache(Cache *cache, unsigned long long key, unsigned long long value);
void free_cache(Cache *cache);

#endif 
