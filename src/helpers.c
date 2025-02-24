#include <stdio.h>
#include <stdlib.h>

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
        return NULL;
    }

    printf("%s", msg);
    fgets(buffer, size, stdin);

    return buffer;
}

/**
 * Clears the current console stream
 */
void clear_console() {
    printf("\033[2J");

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}