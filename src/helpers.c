#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <core.h>

/**
 * @brief Prompts the user to provide input from the standard io stream
 *
 * The input is fetched from the standard input stream and storing it inside
 * a allocated buffer with the given size
 *
 * @param msg The message to display as a label for the input
 * @param size The size of the input buffer
 *
 * @return The input buffer filled with the user's input
 */
char *input(char *msg, size_t size) {
    char *buffer = (char *)malloc(size);

    if (buffer == NULL) {
        free(buffer);
        return NULL;
    }

    printf("%s", msg);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

/**
 * Clears the current console stream
 */
void clear_console() {
    printf("\033[2J");

#ifdef _WIN32
    system("cls"); // NOLINT
#else
    system("clear"); // NOLINT
#endif
}

/**
 * @brief Concatenate two strings into one
 *
 * The function allocates enough memory for both strings and copy both of them
 * into the new region.
 *
 * @param str1 The first string to be concatenated
 * @param str2 The second string to be concatenated
 *
 * @return The resulting combined string
 */
char *concat(char *str1, char *str2) {
    char *result = (char *)malloc(strlen(str1) + strlen(str2) + 1);

    if (result == NULL) {
        return NULL;
    }

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

status_codes_t x_strtol(char *src, long *dst, int base) {
    // Set errno to 0, because any lib can set the errno value to any value
    // except 0
    errno = 0;
    char *end;

    long result = strtol(src, &end, base);

    if (end == src) {
        return ERROR_CONVERSION_FAILED;
    }

    if (errno == ERANGE) {
        return ERROR_OUT_OF_RANGE;
    }

    *dst = result;

    return SUCCESS;
}