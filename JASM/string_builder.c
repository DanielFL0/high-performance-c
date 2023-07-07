#include <stdio.h>
#include "common.h"
#include "error.h"
#include "string_builder.h"

error_t init_string(string_t *string, uint8_t size, char *input) {
  string->idx = 0;
  string->cnt = size;
  string->buffer = input;
  return JASM_SUCCESS;
}

error_t push_char(string_t *string, char c) {
  if (string->idx >= (string->cnt - 1)) {
    string->idx = 0;
  }
  string->buffer[string->idx] = c;
  string->idx++;
  return JASM_SUCCESS;
}

error_t append_string(string_t *string, uint8_t size, char *input) {
  for (uint8_t jdx = 0; jdx < size; ++jdx) {
    if (input[jdx] == '\0') {
      push_char(string, ' ');
    }
    else {
      push_char(string, input[jdx]);
    }
  }
  return JASM_SUCCESS;
}

error_t print_string(string_t *string) {
  for (uint8_t jdx = 0; jdx < string->idx; ++jdx) {
    putchar(string->buffer[jdx]);
  }
  return JASM_SUCCESS;
}