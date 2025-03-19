#ifndef UI_RECEIPT_H
#define UI_RECEIPT_H

#include <catrans.h>

typedef struct ReceiptData {
    char *file_path;
    FILE *file;
    char *receipt_id;
    char *store_name;
    char *store_phone;
    char *store_receipt_id;
    char *total_price_line;
    char *total_discount_line;
    char *bill_line;
    char *payed_line;
    char *cashback_line;
    char *date_line;
} receipt_data_t;

void receipt_menu(const cart_t *cart, long cash_payed);

#endif