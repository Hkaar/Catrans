#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include <core.h>
#include <catrans.h>
#include <helpers.h>

#include <ui_receipt.h>
#include <ui_helpers.h>

#include <config.h>

static char *get_receipt_date();
static long long int gen_receipt_id();

void init_receipt_data(receipt_data_t *receipt_data);
void destroy_receipt_data(receipt_data_t *receipt_data);

void receipt_menu(const cart_t *cart, long payed) {
    receipt_data_t receipt_data;
    init_receipt_data(&receipt_data);
    
    receipt_data.file_path = concat(EXPORT_DIR, "\\receipt.txt");

    if (receipt_data.file_path == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating file path!\n");
        return;
    }
    
    receipt_data.file = fopen(receipt_data.file_path, "w");

    if (receipt_data.file == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed opening file!\n");
        return;
    }

    receipt_data.receipt_id = x_snprintf(48, "%lld", gen_receipt_id());

    if (receipt_data.receipt_id == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed making receipt id!\n");
        return;
    }

    receipt_data.store_name = concat("TOKO ", STORE_NAME);

    if (receipt_data.store_name == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating store name!\n");
        return;
    }
    
    receipt_data.store_phone = concat("Telp: ", STORE_PHONE);

    if (receipt_data.store_phone == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating store phone!\n");
        return;
    }
    
    receipt_data.store_receipt_id = concat("ID Struk: ", receipt_data.receipt_id);

    if (receipt_data.store_receipt_id == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating receipt id!\n");
        return;
    }

    long total_price = 0;
    long total_discount = 0;
    long bill = 0;

    cart_total_price(cart, &total_price, false);
    cart_total_price(cart, &bill, true);

    receipt_data.total_price_line = concat("Total Harga = Rp. ", x_snprintf(32, "%ld", total_price));

    if (receipt_data.total_price_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating total price line!\n");
        return;
    }

    receipt_data.bill_line = concat("Tagihan = Rp. ", x_snprintf(32, "%ld", bill));

    if (receipt_data.bill_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating total bill line!\n");
        return;
    }
    
    receipt_data.payed_line = concat("Pembayaran = Rp. ", x_snprintf(32, "%ld", payed));

    if (receipt_data.payed_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating total cash payed line!\n");
        return;
    }
    
    receipt_data.cashback_line = concat("Kembalian = Rp. ", x_snprintf(32, "%ld", payed-bill));

    if (receipt_data.cashback_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating total cash back line!\n");
        return;
    }

    char *current_date = get_receipt_date();

    if (current_date == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed to get current date!\n");
        return;
    }

    receipt_data.date_line = concat("Waktu/Hari: ", current_date);

    free(current_date);
    current_date = NULL;

    if (receipt_data.date_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating receipt date line!\n");
        return;
    }

    separator('=', 72, receipt_data.file);
    
    align_center(receipt_data.store_name, 72, receipt_data.file);
    align_center(STORE_ADDRESS, 72, receipt_data.file);
    align_center(receipt_data.store_phone, 72, receipt_data.file);

    align_left("  ", 72, receipt_data.file);

    align_left(receipt_data.store_receipt_id, 72, receipt_data.file);

    separator('=', 72, receipt_data.file);

    if (x_fprintf(receipt_data.file, "| %-20s | %-12s | %-13s | %-14s |\n", "Nama Barang", 
        "Harga", "Total", "Diskon") != SUCCESS) {

        destroy_receipt_data(&receipt_data);
        printf("Failed writing to file!");
        return;
    }

    separator('-', 72, receipt_data.file);

    for (int i = 0; i < cart->amount; i++) {
        cart_item_t *cart_item = cart->items[i];

        long discount;
        calc_discount(cart_item, &discount);

        total_discount += discount;

        if (x_fprintf(receipt_data.file, "| %-2d x %-15s | Rp. %-8d | Rp. %-9d | Rp. %-10ld |\n",
            cart_item->amount, cart_item->item.name, cart_item->item.price,
            cart_item->amount * cart_item->item.price, discount) != SUCCESS) {

            destroy_receipt_data(&receipt_data);
            printf("Failed writing to file!");
            return;
        }
    }

    // TODO: CREATE A SEPERATE FUNCTION TO CALCULATE TOTAL DISCOUNTS
    receipt_data.total_discount_line = concat("Total Diskon = Rp. ", x_snprintf(32, "%ld", total_discount));

    if (receipt_data.total_discount_line == NULL) {
        destroy_receipt_data(&receipt_data);
        printf("Failed creating total discount line!\n");
        return;
    }

    separator('=', 72, receipt_data.file);

    align_left("  ", 72, receipt_data.file);
    align_left(receipt_data.total_price_line, 72, receipt_data.file);
    align_left(receipt_data.total_discount_line, 72, receipt_data.file);
    align_left(receipt_data.bill_line, 72, receipt_data.file);
    align_left(receipt_data.payed_line, 72, receipt_data.file);
    align_left(receipt_data.cashback_line, 72, receipt_data.file);
    align_left("  ", 72, receipt_data.file);
    align_left(receipt_data.date_line, 72, receipt_data.file);
    align_left("  ", 72, receipt_data.file);

    separator('=', 72, receipt_data.file);

    destroy_receipt_data(&receipt_data);

    clear_console();
    printf("Berhasil print struk!\n");
}

/**
 * @brief Generates the current date for the receipt
 */
static char *get_receipt_date() {
    time_t rawtime;
    struct tm * timeinfo;

    char *buffer = (char *)malloc(64);

    if (buffer == NULL) {
        return NULL;
    }
    
    if (time(&rawtime) < 0) {
        free(buffer);
        printf("Failed to generate id!\n");
        return NULL;
    }
    
    timeinfo = localtime(&rawtime);

    if (strftime(buffer, 64, "%c", timeinfo) == 0) {
        free(buffer);

        printf("Failed to generate id!\n");
        return NULL;
    }
    
    return buffer;
}

/**
 * @brief Generates a random unique id for the receipt
 */
static long long int gen_receipt_id() {
    return time(NULL);
}

/**
 * @brief Initializes the receipt data object
 */
void init_receipt_data(receipt_data_t *receipt_data) {
    memset(receipt_data, 0, sizeof(receipt_data_t));
}

/**
 * @brief Destroys the receipt data object from memory
 */
void destroy_receipt_data(receipt_data_t *receipt_data) {
    if (receipt_data->file_path) {
        free(receipt_data->file_path);
        receipt_data->file_path = NULL;
    }

    if (receipt_data->file) {
        if (fclose(receipt_data->file) < 0) {
            printf("Failed closing file!\n");
        }

        receipt_data->file = NULL;
    }

    if (receipt_data->receipt_id){
        free(receipt_data->receipt_id);
        receipt_data->receipt_id = NULL;
    }

    if (receipt_data->store_name){
        free(receipt_data->store_name);
        receipt_data->store_name = NULL;
    }

    if (receipt_data->store_phone){
        free(receipt_data->store_phone);
        receipt_data->store_phone = NULL;
    }
    
    if (receipt_data->store_receipt_id){
        free(receipt_data->store_receipt_id);
        receipt_data->store_receipt_id = NULL;
    }

    if (receipt_data->total_price_line){
        free(receipt_data->total_price_line);
        receipt_data->total_price_line = NULL;
    }

    if (receipt_data->total_discount_line){
        free(receipt_data->total_discount_line);
        receipt_data->total_discount_line = NULL;
    }

    if (receipt_data->bill_line){
        free(receipt_data->bill_line);
        receipt_data->bill_line = NULL;
    }

    if (receipt_data->payed_line){
        free(receipt_data->payed_line);
        receipt_data->payed_line = NULL;
    }

    if (receipt_data->cashback_line){
        free(receipt_data->cashback_line);
        receipt_data->cashback_line = NULL;
    }

    if (receipt_data->date_line){
        free(receipt_data->date_line);
        receipt_data->date_line = NULL;
    }
}