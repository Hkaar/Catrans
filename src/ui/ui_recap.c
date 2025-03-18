#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <catrans.h>
#include <core.h>
#include <helpers.h>

#include <ui_helpers.h>
#include <ui_receipt.h>

void recap_menu(const cart_t *cart) {
    if (cart->amount <= 0) {
        return;
    }
    
    double final_price;
    cart_total_price(cart, &final_price);

    double total_discounts = 0;
    double total_price = 0;

    printf("Rekap Pesanan Barang\n");

    separator('=', 94);

    printf("| %-3s | %-6s | %-19s | %-13s | %-18s | %-16s |\n", "No.", "Jumlah",
           "Nama Barang", "Harga", "Total Harga", "Diskon");

    separator('-', 94);

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        double item_price;
        calc_price(cart_item, &item_price, true);

        double discount;
        calc_discount(cart_item, &discount);

        total_discounts += discount;
        total_price += cart_item->item.price * cart_item->amount;

        printf(
            "| %-3d | %-6d | %-19s | Rp. %-9d | Rp. %-14.2f | Rp. %-12.2f |\n",
            i + 1, cart_item->amount, cart_item->item.name,
            cart_item->item.price, item_price, discount);
    }

    separator('=', 94);

    printf("\nTotal Harga = Rp. %.2f\n", total_price);
    printf("Total Diskon = Rp. %.2f\n", total_discounts);
    printf("Total Bayar = Rp. %.2f\n", final_price);

    separator('=', 94);

    char *raw_payout = input("\nMasukkan uang bayar: ", 64);

    long payout;

    if (x_strtol(raw_payout, &payout, 10) != SUCCESS) {
        free((void *)raw_payout);
        raw_payout = NULL;
        return;
    }

    free((void *)raw_payout);
    raw_payout = NULL;

    if (final_price > (int)payout) {
        printf("Uang bayar kurang dari %.2f yang diperlukan!", final_price);
        clear_console();
        return;
    }

    double cash_change = (double)payout - final_price;

    printf("Kembalian = Rp. %.2f\n", cash_change);

    char *confirmation = input("Apakah Anda ingin print struk [Y/N]? ", 3);

    if (strncmp(confirmation, "y", strlen("y")) == 0) {
        receipt_menu(cart);
    } else {
        printf("Membatalkan print struk!\n");
    }

    free((void *)confirmation);
    confirmation = NULL;

    clear_console();
}