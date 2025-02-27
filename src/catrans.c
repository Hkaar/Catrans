#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <catrans.h>
#include <core.h>

/**
 * @brief This function calculates the discount for an item in a shopping cart.
 *
 * The discount is applied based on the number of items purchased. If more than
 * 5 items are bought, a 15% discount is applied. If between 4 and 5 items are
 * bought, a 10% discount is applied. The discount is calculated per item.
 *
 * @param item A pointer to a CartItem structure that contains item details and
 * quantity.
 * @param discount_out A pointer to pass in the result
 *
 * @return The status code of the function
 */
int calc_discount(const cart_item_t *item, double *discount_out) {
    if (item == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    double discount = 0;

    if (item->amount > 5) {
        discount = (0.15 * item->item.price) * item->amount;
    } else if (item->amount > 3) {
        discount = (0.1 * item->item.price) * item->amount;
    }

    *discount_out = discount;
    return SUCCESS;
}

/**
 * @brief This function calculates the total price of an item including
 * discounts
 *
 * The price is calculated by multiplying the base item price by the quantity
 * bought and subtracting it by the discount provided.
 *
 * @param item A pointer to a CartItem structure that contains item details and
 * quantity.
 * @param price_out A pointer to pass in the result
 *
 * @return The status code of the function
 */
int calc_price(const cart_item_t *item, double *price_out) {
    if (item == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    double discount;

    if (calc_discount(item, &discount) != SUCCESS) {
        return ERROR_CALCULATION_FAILED;
    }

    double total = (item->amount * item->item.price) - discount;
    *price_out = total;

    return SUCCESS;
}

/**
 * @brief Pushes an item to the given cart
 *
 * Creates a new cart item struct and adds it to the given cart reference.
 * This works by reallocating the memory buffer for cart items in the cart.
 *
 * @param cart The cart for the item to be pushed into
 * @param item The item to be pushed into the cart
 * @param amount The amount of items to be pushed
 *
 * @return The status code of the function
 */
int push_to_cart(cart_t *cart, item_t item, int amount) {
    if (amount <= 0 || cart == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    for (int i = 0; i < cart->amount; i++) {
        if (cart->items[i] == NULL) {
            return ERROR_MEMORY_CORRUPTED;
        }

        if (strncmp(cart->items[i]->item.name, item.name, strlen(item.name)) ==
            0) {
            cart->items[i]->amount += amount;
            return SUCCESS;
        }
    }

    cart_item_t *cart_item = (cart_item_t *)malloc(sizeof(cart_item_t));

    if (cart_item == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    cart_item->item = item;
    cart_item->amount = amount;

    cart_item_t **new_items =
        (cart_item_t **)malloc(sizeof(cart_item_t *) * (cart->amount + 1));

    if (new_items == NULL) {
        free((void *)cart_item);
        cart_item = NULL;

        return ERROR_MEMORY_ALLOCATION;
    }

    if (cart->items != NULL && new_items != NULL) {
        memcpy((void *)new_items, (void *)cart->items,
               sizeof(cart_item_t *) * cart->amount);
    }

    new_items[cart->amount] = cart_item;

    free((void *)cart->items);

    cart->items = new_items;
    cart->amount++;

    return SUCCESS;
}

/**
 * @brief Removes the most recent item from the cart
 *
 * Removes the most recent item by reallocating a new buffer with the size less
 * than the original buffer in the cart.
 *
 * @param cart The cart to be used
 *
 * @return The status code of the function
 */
int pop_from_cart(cart_t *cart) {
    if (cart == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    if (cart->amount <= 0) {
        return ERROR_EMPTY_ARRAY;
    }

    cart_item_t *last_item = cart->items[cart->amount - 1];

    free(last_item);
    last_item = NULL;

    cart_item_t **new_items =
        (cart_item_t **)malloc(sizeof(cart_item_t *) * (cart->amount - 1));

    if (new_items == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    if (cart->items != NULL && new_items != NULL) {
        memcpy((void *)new_items, (void *)cart->items,
               sizeof(cart_item_t *) * (cart->amount - 1));
    }

    free((void *)cart->items);

    cart->amount--;
    cart->items = new_items;

    return SUCCESS;
}

/**
 * Reset the cart to it's initial state
 *
 * @param cart A pointer to the cart to be reset
 *
 * @return The status code of the function
 */
int reset_cart(cart_t *cart) {
    if (cart == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    if (cart->amount > 0 && cart->items == NULL) {
        return ERROR_MEMORY_CORRUPTED;
    }

    for (int i = 0; i < cart->amount; i++) {
        if (cart->items[i] == NULL) {
            return ERROR_MEMORY_CORRUPTED;
        }

        free((void *)cart->items[i]);
        cart->items[i] = NULL;
    }

    free((void *)cart->items);
    cart->items = NULL;

    cart->amount = 0;

    return SUCCESS;
}

/**
 * @brief Get the total price of all the items in the cart
 *
 * Iterates through the cart and calculates the total price (including
 * discounts) and returns the total final price for all items.
 *
 * @param cart The cart to be used
 * @param price_out A pointer to pass the result
 *
 * @return The status code of the function
 */
int cart_total_price(const cart_t *cart, double *price_out) {
    if (cart == NULL) {
        return ERROR_INVALID_PARAMS;
    }

    double item_price = 0;
    double total = 0;

    for (int i = 0; i < cart->amount; i++) {
        if (cart->items[i] == NULL) {
            return ERROR_MEMORY_CORRUPTED;
        }

        if (calc_price(cart->items[i], &item_price) != SUCCESS) {
            return ERROR_CALCULATION_FAILED;
        }

        total += item_price;
    }

    *price_out = total;

    return SUCCESS;
}