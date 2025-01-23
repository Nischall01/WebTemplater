#include "../include/userinput.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Validates if the input is a single character.
bool valid_char_input(char *input) {
  size_t len = strlen(input);
  if (len != 1)
    return false;
  return true;
}

// Reads a line of user input text into the provided buffer.
char *get_user_input_text(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL; // Return NULL if buffer is NULL or size is zero
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL; // Return NULL if reading fails
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0'; // Replace newline with null terminator
    len--;
  }
  // Check for potential buffer overflow
  else if (len == buffer_size - 1) {
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    return NULL; // Return NULL to indicate error
  }

  return buffer; // Return the buffer containing the input text
}

// Reads a single character of user input into the provided buffer.
char *get_user_input_text_single_char(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL; // Return NULL if buffer is NULL or size is zero
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL; // Return NULL if reading fails
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0'; // Replace newline with null terminator
    len--;
  }
  // Check for potential buffer overflow
  else if (len == buffer_size - 1) {
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    return NULL; // Return NULL to indicate error
  }

  // Validate that the input is a single character
  if (!valid_char_input(buffer)) {
    return NULL; // Return NULL if input is not a single character
  }

  return buffer; // Return the buffer containing the valid input character
}

// Reads user input text that contains only alphabetic characters into the
// provided buffer.
char *get_user_input_text_alphabet_only(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL; // Return NULL if buffer is NULL or size is zero
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL; // Return NULL if reading fails
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0'; // Replace newline with null terminator
    len--;
  }
  // Check for potential buffer overflow
  else if (len == buffer_size - 1) {
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    return NULL; // Return NULL to indicate error
  }

  // Validate that all characters are alphabetic
  for (size_t i = 0; i < len; i++) {
    if (!isalpha((unsigned char)buffer[i])) {
      return NULL; // Return NULL if a non-alphabetic character is found
    }
  }

  return buffer; // Return the buffer containing the valid alphabetic input
}
