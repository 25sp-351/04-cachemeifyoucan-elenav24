#ifndef CACHE_LRU_H
#define CACHE_LRU_H

#include "rod_cut.h"

typedef struct CacheEntry {
    int rod_length;
    int total_value;
    int remainder;
    struct CacheEntry* next;
    struct CacheEntry* prev;
} CacheEntry;

typedef struct {
    CacheEntry* head;
    CacheEntry* tail;
    int capacity;
    int size;
} LRUCache;

void init_lru_cache(LRUCache* cache, int capacity);
void free_lru_cache(LRUCache* cache);
int lru_cut_rod(LRUCache* cache, PriceTable* table, int rod_length, int* remainder);

#endif