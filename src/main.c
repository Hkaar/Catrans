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

    main_menu(items, 5);
    return 0;
}