#include "cache_random.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void init_random_cache(RandomCache* cache, int capacity) {
    cache->entries = malloc(capacity * sizeof(RandomCacheEntry));
    if (!cache->entries) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    cache->capacity = capacity;
    cache->size = 0;
    srand(time(NULL));
}

int random_cut_rod(RandomCache* cache, PriceTable* table, int rod_length, int* remainder) {
    // check cache first
    for (int i = 0; i < cache->size; i++) {
        if (cache->entries[i].rod_length == rod_length) {
            *remainder = cache->entries[i].remainder;
            return cache->entries[i].total_value;
        }
    }
    
    int total_value = 0;
    *remainder = rod_length;
    
    for (int i = 0; i < table->count; i++) {
        int cut_length = 0;
        int n = 0;
        
        while (cut_length + table->items[i].length <= *remainder) {
            cut_length += table->items[i].length;
            n++;
        }
        
        if (cut_length != 0) {
            total_value += n * table->items[i].value;
            *remainder -= cut_length;
        }
    }
    
    if (cache->size < cache->capacity) {
        cache->entries[cache->size].rod_length = rod_length;
        cache->entries[cache->size].total_value = total_value;
        cache->entries[cache->size].remainder = *remainder;
        cache->size++;
    } else {
        int index = rand() % cache->capacity;
        cache->entries[index].rod_length = rod_length;
        cache->entries[index].total_value = total_value;
        cache->entries[index].remainder = *remainder;
    }
    
    return total_value;
}

void free_random_cache(RandomCache* cache) {
    free(cache->entries);
    cache->entries = NULL;
    cache->size = 0;
    cache->capacity = 0;
}