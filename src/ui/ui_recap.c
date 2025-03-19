#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <catrans.h>
#include <core.h>
#include <helpers.h>

#include <ui_helpers.h>
#include <ui_receipt.h>

void recap_menu(cart_t *cart) {
    if (cart->amount <= 0) {
        printf("Anda tidak memiliki barang di keranjang!\n");
        return;
    }

    cart_sort(cart);
    
    long final_price;
    cart_total_price(cart, &final_price, true);

    long total_discounts = 0;
    long total_price = 0;

    printf("Rekap Pesanan Barang\n");

    separator('=', 94, stdout);

    printf("| %-3s | %-6s | %-19s | %-13s | %-18s | %-16s |\n", "No.", "Jumlah",
           "Nama Barang", "Harga", "Total Harga", "Diskon");

    separator('-', 94, stdout);

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        long item_price;
        calc_price(cart_item, &item_price, true);

        long discount;
        calc_discount(cart_item, &discount);

        total_discounts += discount;
        total_price += (long) cart_item->item.price * cart_item->amount;

        printf(
            "| %-3d | %-6d | %-19s | Rp. %-9d | Rp. %-14ld | Rp. %-12ld |\n",
            i + 1, cart_item->amount, cart_item->item.name,
            cart_item->item.price, item_price, discount);
    }

    separator('=', 94, stdout);

    printf("\nTotal Harga = Rp. %ld\n", total_price);
    printf("Total Diskon = Rp. %ld\n", total_discounts);
    printf("Total Bayar = Rp. %ld\n\n", final_price);

    separator('=', 94, stdout);

    char *raw_payout = input("\nMasukkan uang bayar: ", 64);

    long payout;

    if (x_strtol(raw_payout, &payout, 10) != SUCCESS) {
        free((void *)raw_payout);
        raw_payout = NULL;
        return;
    }

    free((void *)raw_payout);
    raw_payout = NULL;

    if (final_price > payout) {
        clear_console();
        printf("Uang bayar kurang dari Rp. %ld yang diperlukan!\n", final_price);
        return;
    }

    long cash_change = payout - final_price;

    printf("Kembalian = Rp. %ld\n", cash_change);

    char *confirmation = input("\nApakah Anda ingin print struk [Y/N]? ", 3);

    if (strncmp(confirmation, "y", strlen("y")) == 0) {
        printf("\n");
        receipt_menu(cart, payout);
    } else {
        clear_console();
        printf("Membatalkan print struk!\n");
    }

    free((void *)confirmation);
    confirmation = NULL;
}