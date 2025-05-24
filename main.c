#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rod_cut.h"

#ifdef USE_LRU
#include "cache_lru.h"
#else
#include "cache_random.h"
#endif

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <rod_length>\n", argv[0]);
        return 1;
    }

    PriceTable table;
    init_price_table(&table);
    sort_by_value(&table);

    int rod_length = atoi(argv[1]);
    int remainder;
    int total_value;

#ifdef USE_LRU
    LRUCache cache;
    init_lru_cache(&cache, 100);
    total_value = lru_cut_rod(&cache, &table, rod_length, &remainder);
    free_lru_cache(&cache);
#elif defined(USE_RANDOM)
    RandomCache cache;
    init_random_cache(&cache, 100);
    total_value = random_cut_rod(&cache, &table, rod_length, &remainder);
    free_random_cache(&cache);
#endif

    int current_length = rod_length - remainder;
    for (int i = 0; i < table.count; i++) {
        if (table.items[i].length > current_length) continue;
        
        int n = current_length / table.items[i].length;
        if (n > 0) {
            printf("%d @ %d = %d\n", n, table.items[i].value, n * table.items[i].value);
            current_length -= n * table.items[i].length;
        }
    }
    
    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", total_value);

    free_price_table(&table);
    return 0;
}