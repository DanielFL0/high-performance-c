#include <stdio.h>
#include "common.h"
#include "error.h"
#include "file_handler.h"

error_t load_file(char *file_name, uint8_t *char_buffer, uint32_t *byte_count) {
  /** load_file
   * Writes the file contents into a buffer
   */
  int8_t return_code; /* fclose error code */
  FILE *file_pointer; /* fopen file pointer */
  file_pointer = fopen(file_name, "r");
  if (file_pointer == NULL) {
    return JASM_FILE_OPEN_ERROR;
  }
  return_code = fread(char_buffer, sizeof(uint8_t), BUFFER_SIZE, file_pointer);
  if (return_code > 0) {
    *byte_count = return_code;
  } else {
    return JASM_FILE_READ_ERROR;
  }
  return_code = fclose(file_pointer);
  if (return_code != 0) {
    return JASM_FILE_CLOSE_ERROR;
  }
  return JASM_SUCCESS;
}

error_t load_binary_file(char *file_name, uint8_t *bytecode_buffer, uint32_t *byte_count) {
  /** load_binary_file
   * Writes the binary file contents into a buffer
   */
  int8_t return_code; /* error code */
  FILE *file_pointer; /* fopen file pointer */
  file_pointer = fopen(file_name, "rb");
  if (file_pointer == NULL) {
    return JASM_FILE_OPEN_ERROR;
  }
  return_code = fread(bytecode_buffer, sizeof(uint8_t), BUFFER_SIZE, file_pointer);
  if (return_code > 0) {
    *byte_count = return_code;
  } else {
    return JASM_FILE_READ_ERROR;
  }
  return_code = fclose(file_pointer);
  if (return_code != 0) {
    return JASM_FILE_CLOSE_ERROR;
  }
  return JASM_SUCCESS;
}