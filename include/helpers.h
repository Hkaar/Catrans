#ifndef HELPERS_H
#define HELPERS_H

#define SIZE_T unsigned long long

#include <core.h>

char *input(char *msg, SIZE_T size);

void clear_console();

char *concat(char *str1, char *str2);

status_codes_t x_strtol(char *src, long *dst, int base);

#endif