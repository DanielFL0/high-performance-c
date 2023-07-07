#ifndef ERROR_H
#define ERROR_H

typedef enum error_t {
  JASM_SUCCESS = 0x00,
  JASM_FILE_OPEN_ERROR = 0x01,
  JASM_FILE_READ_ERROR = 0x02,
  JASM_FILE_WRITE_ERROR = 0x03,
  JASM_FILE_CLOSE_ERROR = 0x04,
  JASM_PRINT_STDOUT_ERROR = 0x05,
  JASM_UNKNOWN_INSTRUCTION_ERROR = 0x06,
} error_t;

void dump_error_code(uint8_t error_code);

#endif