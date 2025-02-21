#include <stdio.h>

#include <helpers.h>
#include <ui.h>
#include <core.h>

int main()
{
    Item items[] = {
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

    main_menu("SKENSA", items, 5);
    return 0;
}