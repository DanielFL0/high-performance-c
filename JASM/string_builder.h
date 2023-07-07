#ifndef STRING_BUILDERH_H
#define STRING_BUILDER_H

typedef struct string_t {
  uint8_t   idx;
  uint8_t   cnt;
  char      *buffer;
} string_t;

error_t init_string(string_t *string, uint8_t size, char *input);
error_t push_char(string_t *string, char c);
error_t append_string(string_t *string, uint8_t size, char *input);
error_t print_string(string_t *string);

#endif