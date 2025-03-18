#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <catrans.h>
#include <helpers.h>

void input_menu(cart_t *cart, item_t items[], int amount) {
    do {
        clear_console();

        long product_id;
        long product_amount;

        char *raw_product_id = input("Masukkan nomer barang: ", 12);
        char *raw_product_amount = input("Masukkan jumlah barang: ", 12);

        if (x_strtol(raw_product_id, &product_id, 10) != SUCCESS) {
            printf("Produk id bukan nomer!\n");

            free((void *)raw_product_id);
            raw_product_id = NULL;

            free((void *)raw_product_amount);
            raw_product_amount = NULL;
        }

        if (x_strtol(raw_product_amount, &product_amount, 10) != SUCCESS) {
            printf("Jumlah produk yang diberikan bukan nomer!\n");

            free((void *)raw_product_id);
            raw_product_id = NULL;

            free((void *)raw_product_amount);
            raw_product_amount = NULL;
        }

        free((void *)raw_product_id);
        raw_product_id = NULL;

        free((void *)raw_product_amount);
        raw_product_amount = NULL;

        if (product_id <= amount && product_id > 0) {
            status_codes_t result_code =
                cart_push(cart, items[product_id - 1], (int)product_amount);

            if (result_code != SUCCESS) {
                printf("%s\n", err_msg(result_code));
            } else {
                printf("Berhasil menambahkan barang!\n");
            }
        } else {
            printf("Mohon maaf barang yang Anda inginkan tidak ada!\n");
        }

        char *confirmation = input("\nLanjut memasukkan barang[Y/N]? ", 12);

        if (strncmp(confirmation, "n", strlen("n")) == 0) {
            break;
        }

        free(confirmation);
        confirmation = NULL;
    } while (true);
}