#ifndef CORE_H
#define CORE_H

typedef struct
{
    char *name;
    int price;
} Item;

typedef struct
{
    Item item;
    int amount;
} CartItem;

int calc_discount(CartItem *item);

int calc_price(CartItem *item);

#endif