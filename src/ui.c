#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <catrans.h>
#include <core.h>
#include <helpers.h>

static void seperator(char character, int amount);

static void receipt_menu(const cart_t *cart, char *name);
static void recap_menu(const cart_t *cart, char *name);
static void input_menu(cart_t *cart, item_t items[], int amount);

void main_menu(char *name, item_t items[], int amount) {
    cart_t cart = {NULL, 0};

    clear_console();

    printf("Selamat datang di Toko %s\n", name);
    printf("Silakan pilih barang yang Anda inginkan:\n\n");

    int running = 1;

    while (running == 1) {
        seperator('=', 48);
        printf("| %-3s | %-20s | %-15s |\n", "No.", "Barang", "Harga");
        seperator('-', 48);

        for (int i = 0; i < amount; i++) {
            printf("| %-3d | %-20s | Rp. %-11d |\n", i + 1, items[i].name,
                   items[i].price);
        }

        seperator('=', 48);

        printf("\n99. Struk pembelian\n");
        printf("55. Reset pembelian\n");
        printf("11. Input barang\n");
        printf("00. Keluar\n");

        char *raw_cmd = input("\nInput pilihan yang Anda inginkan: ", 64);
        char cmd[64] = {0};

        strncpy(cmd, raw_cmd, strlen(raw_cmd) - 1);
        cmd[strlen(raw_cmd) - 1] = '\0';

        free(raw_cmd);
        raw_cmd = NULL;

        clear_console();

        if (strncmp(cmd, "99", strlen("99")) == 0) {
            recap_menu(&cart, name);
        } else if (strncmp(cmd, "55", strlen("55")) == 0) {
            reset_cart(&cart);
            printf("Berhasil reset pembelian!\n");
        } else if (strncmp(cmd, "11", strlen("11")) == 0) {
            input_menu(&cart, items, amount);
        } else if (strncmp(cmd, "00", strlen("00")) == 0) {
            printf("\nSelamat tinggal!\n");
            running = 0;
        } else {
            printf("Mohon maaf pilihan %s tidak tersedia\n", cmd);
        }
    }

    reset_cart(&cart);
}

static void input_menu(cart_t *cart, item_t items[], int amount) {
    int keep_alive = 1;

    do {
        char *raw_product_id = input("Masukkan nomer barang: ", 12);
        char *raw_product_amount = input("Masukkan jumlah barang: ", 12);

        int product_id = atoi(raw_product_id);
        int product_amount = atoi(raw_product_amount);

        free(raw_product_id);
        raw_product_id = NULL;

        free(raw_product_amount);
        raw_product_amount = NULL;

        if (product_id <= amount && product_id > 0) {
            status_codes_t result_code =
                push_to_cart(cart, items[product_id - 1], product_amount);

            if (result_code != SUCCESS) {
                printf("%s\n", err_msg(result_code));
            } else {
                printf("Berhasil menambahkan barang!\n");
            }
        } else {
            printf("Mohon maaf barang yang Anda inginkan tidak ada!\n");
        }

        char *confirmation = input("\nLanjut memasukkan barang[Y/N]? ", 12);

        if (strncmp(strlwr(confirmation), "n", strlen("n")) == 0) {
            keep_alive = 0;
        }

        free(confirmation);
        confirmation = NULL;
    } while (keep_alive);
}

static void receipt_menu(const cart_t *cart, char *name) {
    seperator('=', 64);

    printf("TOKO %s\n", name);
    printf("Jl. HOS Cokroaminoto No. 84 Denpasar\n");
    printf("Bali\n");
    printf("Telp: 0816285791\n");

    printf("ID Struk: 1700807978\n");

    seperator('=', 64);

    printf("| %-20s | %-8s | %-8s | %-8s |\n", "Nama Barang", "Harga", "Total",
           "Diskon");

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        double discount;
        calc_discount(cart_item, &discount);

        printf("| %d x %-15s | %-8d | %-8d | %-12.2f |\n", cart_item->amount,
               cart_item->item.name, cart_item->item.price,
               cart_item->amount * cart_item->item.price, discount);
    }

    seperator('=', 64);
    getchar();
}

static void recap_menu(const cart_t *cart, char *name) {
    double final_price;
    cart_total_price(cart, &final_price);

    double total_discounts = 0;
    double total_price = 0;

    printf("Rekap Pesanan Barang\n");
    seperator('=', 96);

    printf("| %-3s | %-6s | %-19s | %-13s | %-19s | %-17s |\n", "No.", "Jumlah",
           "Nama Barang", "Harga", "Total Harga", "Diskon");

    seperator('-', 96);

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        double item_price;
        calc_price(cart_item, &item_price);

        double discount;
        calc_discount(cart_item, &discount);

        total_discounts += discount;
        total_price += cart_item->item.price * cart_item->amount;

        printf(
            "| %-3d | %-6d | %-19s | Rp. %-9d | Rp. %-15.2f | Rp. %-13.2f |\n",
            i + 1, cart_item->amount, cart_item->item.name,
            cart_item->item.price, item_price, discount);
    }

    seperator('=', 96);

    printf("\nTotal Harga = Rp. %.2f\n", total_price);
    printf("Total Diskon = Rp. %.2f\n", total_discounts);
    printf("Total Bayar = Rp. %.2f\n", final_price);

    seperator('=', 96);

    char *raw_payout = input("\nMasukkan uang bayar: ", 64);

    double payout = atoi(raw_payout);

    free(raw_payout);
    raw_payout = NULL;

    if (final_price > payout) {
        printf("Uang bayar kurang dari %.2f yang diperlukan!", final_price);
        clear_console();
        return;
    }

    double cash_change = payout - final_price;

    printf("Kembalian = Rp. %.2f\n", cash_change);

    char *confirmation = input("Apakah Anda ingin print struk [Y/N]? ", 3);

    if (strncmp(strlwr(confirmation), "y", strlen("y")) == 0) {
        receipt_menu(cart, name);
    } else {
        printf("Membatalkan print struk!\n");
    }

    free(confirmation);
    confirmation = NULL;

    clear_console();
}

static void seperator(char character, int amount) {
    for (int i = 0; i < amount; i++) {
        printf("%c", character);
    }

    printf("\n");
}