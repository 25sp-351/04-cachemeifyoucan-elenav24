#ifndef CACHE_RANDOM_H
#define CACHE_RANDOM_H

#include "rod_cut.h"

typedef struct {
    int rod_length;
    int total_value;
    int remainder;
} RandomCacheEntry;

typedef struct {
    RandomCacheEntry* entries;
    int capacity;
    int size;
} RandomCache;

void init_random_cache(RandomCache* cache, int capacity);
void free_random_cache(RandomCache* cache);
int random_cut_rod(RandomCache* cache, PriceTable* table, int rod_length, int* remainder);

#endif