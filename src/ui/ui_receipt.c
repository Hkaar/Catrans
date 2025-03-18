#include <stdio.h>

#include <catrans.h>
#include <ui_helpers.h>

void receipt_menu(const cart_t *cart) {
    separator('=', 72);

    align_center("TOKO SKENSA", 72);
    align_center("Jl. HOS Cokroaminoto No. 84 Denpasar", 72);
    align_center("Bali", 72);
    align_center("Telp: 0816285791", 72);

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
}