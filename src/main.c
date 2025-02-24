#include <stdio.h>

#include <catrans.h>
#include <ui.h>

int main() {
    item_t items[] = {
        {
            "Buku Tulis",
            5000,
        },
        {
            "Pensil",
            2000,
        },
        {
            "Penghapus",
            1000,
        },
        {
            "Penggaris",
            1000,
        },
        {
            "Bujur Sangkar",
            500,
        },
    };

    // cart_t cart = {NULL, 0};

    // printf("Hello world\n");

    // push_to_cart(&cart, items[0], 3);
    // push_to_cart(&cart, items[4], 3);
    // push_to_cart(&cart, items[1], 4);

    // for (int i = 0; i < cart.amount; i++) {
    //     printf("%s | %d\n", cart.items[i]->item.name, cart.items[i]->amount);
    // }

    // double total;
    // cart_total_price(&cart, &total);

    // printf("total: %.2f\n\n", total);

    // pop_from_cart(&cart);
    // pop_from_cart(&cart);

    // cart_total_price(&cart, &total);

    // for (int i = 0; i < cart.amount; i++) {
    //     printf("%s | %d\n", cart.items[i]->item.name, cart.items[i]->amount);
    // }

    // printf("total: %.2f\n", total);

    // push_to_cart(&cart, items[0], 3);
    // push_to_cart(&cart, items[0], 3);

    // cart_total_price(&cart, &total);

    // for (int i = 0; i < cart.amount; i++) {
    //     printf("%s | %d\n", cart.items[i]->item.name, cart.items[i]->amount);
    // }

    // printf("total: %.2f\n", total);

    // reset_cart(&cart);

    // printf("amount of items after reset: %d\n", cart.amount);

    main_menu("SKENSA", items, 5);
    return 0;
}