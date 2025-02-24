#ifndef CATRANS_H
#define CATRANS_H

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

int calc_discount(const cart_item_t *item, double *discount_out);

int calc_price(const cart_item_t *item, double *price_out);

int push_to_cart(cart_t *cart, item_t item, int amount);

int pop_from_cart(cart_t *cart);

int cart_total_price(const cart_t *cart, double *price_out);

int reset_cart(cart_t *cart);

#endif