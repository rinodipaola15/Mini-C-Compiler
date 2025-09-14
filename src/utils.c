#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

/**
 * Reads the content of a text file into a dynamically allocated string.
 * The caller is responsible for freeing the returned buffer.
 */
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t read_size = fread(buffer, 1, length, file);
    buffer[read_size] = '\0';

    fclose(file);
    return buffer;
}
