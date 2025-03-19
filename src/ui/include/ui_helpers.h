#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include <stdio.h>

void separator(char separator_char, int count, FILE *stream);

void align_center(const char *text, int width, FILE *stream);

void align_left(const char *text, int width, FILE *stream);

#endif