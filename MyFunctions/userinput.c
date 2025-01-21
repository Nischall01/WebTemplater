#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function Declarations
bool valid_char_input(char *);
char *get_user_input_text(char *, size_t);
char *get_user_input_text_single_char(char *, size_t);
char *get_user_input_text_alphabet_only(char *, size_t);

// Function Definations
bool valid_char_input(char *input) {
  size_t len = strlen(input);
  if (len != 1)
    return false;
  return true;
}

char *get_user_input_text(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL;
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL;
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
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

  return buffer;
}

char *get_user_input_text_single_char(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL;
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL;
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
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

  if (!valid_char_input(buffer)) {
    return NULL;
  }

  return buffer;
}

char *get_user_input_text_alphabet_only(char *buffer, size_t buffer_size) {
  if (!buffer || buffer_size == 0) {
    return NULL;
  }

  // Read the input into buffer
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    return NULL;
  }

  // Remove trailing newline if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
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

  // Validate only alphabetic characters
  for (size_t i = 0; i < len; i++) {
    if (!isalpha((unsigned char)buffer[i])) {
      return NULL; // Non-alphabetic character found
    }
  }

  return buffer;
}
