#include <stdio.h>
#include <string.h>
#include <time.h>

#include <helpers.h>

/**
 * @brief Prints a character by n amount of times to create a separator
 * 
 * @param separator_char The character to be repeated
 * @param count Amount of times for the character to be printed
 * @param stream The output stream to be used
 */
void separator(const char separator_char, int count, FILE *stream) {
    for (int i = 0; i < count; i++) {
        x_fprintf(stream, "%c", separator_char);
    }

    x_fprintf(stream, "\n");
}

/**
 * @brief Prints a line of text by aligning it to the center of the console
 * 
 * @param text The text to be printed
 * @param width The width to be used for aligning the given text
 * @param stream The output stream to be used
 */
void align_center(const char *text, int width, FILE *stream) {
    int text_length = (int)strlen(text);
    int padding = (width - text_length - 2) / 2;

    x_fprintf(stream, "|"); 
    x_fprintf(stream, "%*s%s%*s", padding, "", text, padding + (text_length % 2), "");
    x_fprintf(stream, "|\n");
}

/**
 * @brief Prints a line of text by aligning it to the left of the console
 * 
 * @param text The text to be printed
 * @param width The width to be used for aligning the given text
 * @param stream The output stream to be used
 */
void align_left(const char *text, int width, FILE *stream) {
    int text_length = (int)strlen(text);
    int padding = (width - text_length - 2) / 2;

    x_fprintf(stream, "| ");
    x_fprintf(stream, "%s%*s%*s", text, (padding - 1), "", padding + (text_length % 2),
           "");
    x_fprintf(stream, "|\n");
}