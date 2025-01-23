#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdbool.h> // For bool type
#include <stddef.h>  // For size_t type

// Function Prototypes

/**
 * Checks if the input character is valid.
 *
 * @param input Pointer to the character input.
 * @return true if valid, false otherwise.
 */
bool valid_char_input(char *input);

/**
 * Reads a line of user input text.
 *
 * @param buffer Pointer to the buffer where input will be stored.
 * @param size Size of the buffer.
 * @return Pointer to the buffer containing the input text.
 */
char *get_user_input_text(char *buffer, size_t size);

/**
 * Reads a single character of user input.
 *
 * @param buffer Pointer to the buffer where input will be stored.
 * @param size Size of the buffer.
 * @return Pointer to the buffer containing the input character.
 */
char *get_user_input_text_single_char(char *buffer, size_t size);

/**
 * Reads user input text that contains only alphabetic characters.
 *
 * @param buffer Pointer to the buffer where input will be stored.
 * @param size Size of the buffer.
 * @return Pointer to the buffer containing the input text.
 */
char *get_user_input_text_alphabet_only(char *buffer, size_t size);

#endif //
