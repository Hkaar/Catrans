#include <stdio.h>

#include <catrans.h>
#include <helpers.h>

#include <ui_helpers.h>
#include <ui.h>

void receipt_menu(const cart_t *cart) {
    separator('=', 72);

    char *store_name = concat("TOKO ", STORE_NAME);
    char *store_phone = concat("Telp: ", STORE_PHONE);

    align_center(store_name, 72);
    align_center(STORE_ADDRESS, 72);
    align_center(store_phone, 72);

    align_left("ID Struk: 1700807978", 72);

    separator('=', 72);

    printf("| %-20s | %-12s | %-13s | %-14s |\n", "Nama Barang", "Harga",
           "Total", "Diskon");

    separator('-', 72);

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        double discount;
        calc_discount(cart_item, &discount);

        printf("| %d x %-15s  | Rp. %-8d | Rp. %-9d | Rp. %-10.2f |\n",
               cart_item->amount, cart_item->item.name, cart_item->item.price,
               cart_item->amount * cart_item->item.price, discount);
    }

    separator('=', 72);

    align_left("  ", 72);
    align_left("Total harga = Rp. 12000.00", 72);
    align_left("Total harga = Rp. 12000.00", 72);
    align_left("Total harga = Rp. 12000.00", 72);
    align_left("Total harga = Rp. 12000.00", 72);
    align_left("  ", 72);
    align_left("Waktu/Hari : Fri Nov 24 14:29:33 2024", 72);
    align_left("  ", 72);

    separator('=', 72);

    getchar();
}