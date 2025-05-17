#include "rod_cut.h"
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void init_price_table(PriceTable* table) {
    table->items = NULL;
    table->count = 0;
    
    printf("Enter piece prices in the format <length>, <value> (press Ctrl+D to end input):\n");
    
    int capacity = 10;
    table->items = malloc(capacity * sizeof(PriceItem));
    if (!table->items) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (table->count >= capacity) {
            capacity *= 2;
            PriceItem* new_items = realloc(table->items, capacity * sizeof(PriceItem));
            if (!new_items) {
                fprintf(stderr, "Memory allocation failed.\n");
                free(table->items);
                exit(1);
            }
            table->items = new_items;
        }
        
        if (sscanf(buffer, "%d, %d", &table->items[table->count].length, 
                  &table->items[table->count].value) == 2) {
            table->count++;
        } else {
            fprintf(stderr, "Invalid Input.\n");
        }
    }
    
    if (table->count == 0) {
        fprintf(stderr, "Must have at least one line of input formatted <length>, <value>\n");
        free(table->items);
        exit(1);
    }
}

void sort_by_value(PriceTable* table) {
    for (int i = 0; i < table->count - 1; i++) {
        for (int j = 0; j < table->count - i - 1; j++) {
            if (table->items[j].value < table->items[j + 1].value) {
                swap(&table->items[j].value, &table->items[j + 1].value);
                swap(&table->items[j].length, &table->items[j + 1].length);
            }
        }
    }
}

void free_price_table(PriceTable* table) {
    free(table->items);
    table->items = NULL;
    table->count = 0;
}