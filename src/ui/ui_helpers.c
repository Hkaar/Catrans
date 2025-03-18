#include <stdio.h>
#include <string.h>

/**
 * @brief Prints a character by n amount of times to create a separator
 * 
 * @param repeat_char The character to be used
 * @param count Amount of times for the character to be printed
 */
void separator(const char repeat_char, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c", repeat_char);
    };

    printf("\n");
}

/**
 * @brief Prints a line of text by aligning it to the center of the console
 * 
 * @param text The text to be printed
 * @param width The width to be used for aligning the given text
 */
void align_center(const char *text, int width) {
    int text_length = (int)strlen(text);
    int padding = (width - text_length - 2) / 2;

    printf("|"); 
    printf("%*s%s%*s", padding, "", text, padding + (text_length % 2), "");
    printf("|\n");
}

/**
 * @brief Prints a line of text by aligning it to the left of the console
 * 
 * @param text The text to be printed
 * @param width The width to be used for aligning the given text
 */
void align_left(const char *text, int width) {
    int text_length = (int)strlen(text);
    int padding = (width - text_length - 2) / 2;

    printf("| ");
    printf("%s%*s%*s", text, (padding - 1), "", padding + (text_length % 2),
           "");
    printf("|\n");
}