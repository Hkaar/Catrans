#ifndef CATRANS_H
#define CATRANS_H

#include <core.h>
#include <stdbool.h>

typedef struct Item {
    char *name;
    int price;
} item_t;

typedef struct CartItem {
    item_t item;
    int amount;
} cart_item_t;

typedef struct Cart {
    cart_item_t **items;
    int amount;
} cart_t;

status_codes_t calc_discount(const cart_item_t *item, double *discount_out);

status_codes_t calc_price(const cart_item_t *item, double *price_out,
                          bool include_discount);

status_codes_t cart_push(cart_t *cart, item_t item, int amount);

status_codes_t cart_pop(cart_t *cart);

status_codes_t cart_total_price(const cart_t *cart, double *price_out);

status_codes_t cart_reset(cart_t *cart);

#endif