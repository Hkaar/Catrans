#include <stdio.h>
#include <string.h>

#include <core.h>
#include <helpers.h>

static void seperator(char character, int amount);

static void receipt_menu(CartItem cart[], int amount);
static void recap_menu(CartItem cart[], int amount);

void main_menu(char *name, Item items[], int amount)
{
    CartItem cart[99] = {0};

    clear_console();

    printf("Selamat datang di Toko %s\n", name);
    printf("Silakan pilih barang yang Anda inginkan:\n\n");

    int running = 1;

    while (running == 1)
    {
        seperator('=', 48);
        printf("| %-3s | %-20s | %-15s |\n", "No.", "Barang", "Harga");
        seperator('-', 48);

        for (int i = 0; i < amount; i++)
        {
            printf("| %-3d | %-20s | Rp. %-11d |\n",
                   i + 1, items[i].name, items[i].price);
        }

        seperator('=', 48);

        printf("\n99. Struk pembelian\n");
        printf("55. Reset pembelian\n");
        printf("00. Keluar\n");

        char *raw_cmd = input("\nInput pilihan yang Anda inginkan: ", 64);
        char cmd[64] = {0};

        strncpy(cmd, raw_cmd, strlen(raw_cmd) - 1);
        cmd[strlen(raw_cmd) - 1] = '\0';

        free(raw_cmd);
        raw_cmd = NULL;

        clear_console();

        if (strncmp(cmd, "99", strlen("99")) == 0)
        {
            recap_menu(cart, 99);
        }
        else if (strncmp(cmd, "55", strlen("55")) == 0)
        {
            printf("Hello\n");
        }
        else if (strncmp(cmd, "00", strlen("00")) == 0)
        {
            printf("\nSelamat tinggal!\n");
            running = 0;
        }
        else
        {
            printf("Mohon maaf pilihan %s tidak tersedia\n", cmd);
        }
    }
}

static void seperator(char character, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        printf("%c", character);
    }

    printf("\n");
}

static void receipt_menu(CartItem cart[], int amount)
{
    //
}

static void recap_menu(CartItem cart[], int amount)
{
    //
}