#include <core.h>

/**
 * @brief This function calculates the discount for an item in a shopping cart.
 *
 * The discount is applied based on the number of items purchased. If more than 5 items
 * are bought, a 15% discount is applied. If between 4 and 5 items are bought, a 10% discount
 * is applied. The discount is calculated per item.
 *
 * @param item A pointer to a CartItem structure that contains item details and quantity.
 * @return The total discount applied to the items.
 */
int calc_discount(CartItem *item)
{
    int discount = 0;

    if (item->amount > 5)
    {
        discount = (0.15 * item->item.price) * item->amount;
    }
    else if (item->amount > 3)
    {
        discount = (0.1 * item->item.price) * item->amount;
    }

    return discount;
}

/**
 * @brief This function calculates the total price of an item including discounts
 *
 * The price is calculated by multiplying the base item price by the quantity
 * bought and subtracting it by the discount provided.
 *
 * @param item A pointer to a CartItem structure that contains item details and quantity.
 * @return The total price of the item
 */
int calc_price(CartItem *item)
{
    int total = (item->amount * item->item.price) - calc_discount(item);

    return total;
}