#include "cache_lru.h"
#include <stdlib.h>
#include <stdio.h>

static void move_to_front(LRUCache* cache, CacheEntry* entry) {
    if (entry == cache->head) return;
    
    // remove from current position
    if (entry->prev) entry->prev->next = entry->next;
    if (entry->next) entry->next->prev = entry->prev;
    
    // update tail if needed
    if (entry == cache->tail && entry->prev) {
        cache->tail = entry->prev;
    }
    
    // add to front
    entry->prev = NULL;
    entry->next = cache->head;
    if (cache->head) cache->head->prev = entry;
    cache->head = entry;
    if (!cache->tail) cache->tail = entry;
}

void init_lru_cache(LRUCache* cache, int capacity) {
    cache->head = NULL;
    cache->tail = NULL;
    cache->capacity = capacity;
    cache->size = 0;
}

int lru_cut_rod(LRUCache* cache, PriceTable* table, int rod_length, int* remainder) {
    // check cache first
    CacheEntry* current = cache->head;
    while (current) {
        if (current->rod_length == rod_length) {
            *remainder = current->remainder;
            move_to_front(cache, current);
            return current->total_value;
        }
        current = current->next;
    }
    
    // not in cache, compute
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
    
    // add to cache
    if (cache->size >= cache->capacity && cache->tail) {
        // evict least recently used
        CacheEntry* to_evict = cache->tail;
        if (to_evict->prev) {
            to_evict->prev->next = NULL;
            cache->tail = to_evict->prev;
        } else {
            cache->head = cache->tail = NULL;
        }
        free(to_evict);
        cache->size--;
    }
    
    // create new entry
    CacheEntry* new_entry = malloc(sizeof(CacheEntry));
    if (!new_entry) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    
    new_entry->rod_length = rod_length;
    new_entry->total_value = total_value;
    new_entry->remainder = *remainder;
    new_entry->next = cache->head;
    new_entry->prev = NULL;
    
    if (cache->head) {
        cache->head->prev = new_entry;
    }
    cache->head = new_entry;
    if (!cache->tail) {
        cache->tail = new_entry;
    }
    cache->size++;
    
    return total_value;
}

void free_lru_cache(LRUCache* cache) {
    CacheEntry* current = cache->head;
    while (current) {
        CacheEntry* next = current->next;
        free(current);
        current = next;
    }
    cache->head = cache->tail = NULL;
    cache->size = 0;
}