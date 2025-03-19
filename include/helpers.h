#ifndef HELPERS_H
#define HELPERS_H

#define SIZE_T unsigned long long

#include <stdio.h>

#include <core.h>

char *input(char *msg, size_t size);

void clear_console();

char *concat(char *str1, char *str2);

status_codes_t x_strtol(char *src, long *dst, int base);

status_codes_t x_fprintf(FILE *stream, char *format, ...);

char *x_snprintf(char *format, size_t size, ...);

#endif