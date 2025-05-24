#ifndef ROD_CUT_H
#define ROD_CUT_H

typedef struct {
    int length;
    int value;
} PriceItem;

typedef struct {
    PriceItem* items;
    int count;
} PriceTable;

void init_price_table(PriceTable* table);
void sort_by_value(PriceTable* table);
void free_price_table(PriceTable* table);

#endif