#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

error_t load_file(char *file_name, uint8_t *char_buffer, uint32_t *byte_count);
error_t load_binary_file(char *file_name, uint8_t *bytecode_buffer, uint32_t *byte_count);

#endif