#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

/**
 * @brief Reads a line of text from standard input.
 * @param buf Pointer to a buffer where the input string will be stored.
 * @param bufsize Size of the buffer in bytes.
 * @return true if input was successfully read, false otherwise.
 */
bool read_line(char* buf, int bufsize);

/**
 * @brief Prompts the user for an integer and reads it from standard input.
 * @param prompt Prompt message displayed to the user.
 * @param out Pointer to an integer variable where the parsed value will be stored.
 * @return true if a valid integer was entered, false otherwise.
 */
bool read_int(const char* prompt, int* out);

/**
 * @brief Prompts the user for a double and reads it from standard input.
 * @param prompt Prompt message displayed to the user.
 * @param out Pointer to a double variable where the parsed value will be stored.
 * @return true if a valid double was entered, false otherwise.
 */
bool read_double(const char* prompt, double* out);

#endif
