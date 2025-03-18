#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <catrans.h>
#include <core.h>
#include <helpers.h>

#include <ui_helpers.h>
#include <ui_input.h>
#include <ui_recap.h>
#include <ui.h>

void main_menu(item_t items[], int amount) {
    cart_t cart = {NULL, 0};

    clear_console();

    printf("Selamat datang di Toko %s\n", STORE_NAME);
    printf("Silakan pilih barang yang Anda inginkan:\n\n");

    while (true) {
        separator('=', 48);

        printf("| %-3s | %-20s | %-15s |\n", "No.", "Barang", "Harga");
        separator('-', 48);

        for (int i = 0; i < amount; i++) {
            printf("| %-3d | %-20s | Rp. %-11d |\n", i + 1, items[i].name,
                   items[i].price);
        }

        separator('=', 48);

        printf("\n99. Struk pembelian\n");
        printf("55. Reset pembelian\n");
        printf("11. Input barang\n");
        printf("00. Keluar\n");

        char *raw_cmd = input("\nInput pilihan yang Anda inginkan: ", 64);

        if (raw_cmd == NULL) {
            printf("%s\n", err_msg(ERROR_MEMORY_ALLOCATION));
            continue;
        }

        char cmd[64] = {0};

        strncpy(cmd, raw_cmd, strlen(raw_cmd) - 1);
        cmd[strlen(raw_cmd) - 1] = '\0';

        free(raw_cmd);
        raw_cmd = NULL;

        clear_console();

        if (strncmp(cmd, "99", strlen("99")) == 0) {
            recap_menu(&cart);
        } else if (strncmp(cmd, "55", strlen("55")) == 0) {
            cart_reset(&cart);
            printf("Berhasil reset pembelian!\n");
        } else if (strncmp(cmd, "11", strlen("11")) == 0) {
            input_menu(&cart, items, amount);
        } else if (strncmp(cmd, "00", strlen("00")) == 0) {
            printf("\nSelamat tinggal!\n");
            break;
        } else {
            printf("Mohon maaf pilihan %s tidak tersedia\n", cmd);
        }
    }

    cart_reset(&cart);
}