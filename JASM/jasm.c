#include <stdio.h>
#include "common.h"
#include "error.h"
#include "file_handler.h"
#include "string_builder.h"

/** 8086 data
 * dec  | bin   | hex
 * 0      0000    0
 * 1      0001    1
 * 2      0010    2
 * 3      0011    3
 * 4      0100    4
 * 5      0101    5
 * 6      0110    6
 * 7      0111    7
 * 8      1000    8
 * 9      1001    9
 * 10     1010    A
 * 11     1011    B
 * 12     1100    C
 * 13     1101    D
 * 14     1110    E 
 * 15     1111    F
 */

#define OPCODE_MASK 0b11111100
#define D_MASK      0b00000010
#define W_MASK      0b00000001
#define MOD_MASK    0b11000000
#define REG_MASK    0b00111000
#define RM_MASK     0b00000111

char byte_registers[8][3] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};
char word_registers[8][3] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
char eac_table[24][20] = {
  "(bx) + (si)", 
  "(bx) + (di)", 
  "(bp) + (si)", 
  "(bp) + (di)", 
  "(si)", "(di)", 
  "direct address", 
  "(bx)", 
  "(bx) + (si) + d8", 
  "(bx) + (di) + d8", 
  "(bp) + (si) + d8", 
  "(bp) + (di) + d8", 
  "(si) + d8", 
  "(di) + d8", 
  "(bp) + d8", 
  "(bx) + d8", 
  "(bx) + (si) + d16", 
  "(bx) + (di) + d16", 
  "(bp) + (si) + d16", 
  "(bp) + (di) + d16", 
  "(si) + d16", 
  "(di) + d16", 
  "(bp) + d16", 
  "(bx) + d16"
};
char output[STRING_SIZE];
uint32_t byte_count;
uint8_t bytecode[BUFFER_SIZE + 1];


void display_bits(uint8_t byte);
void dump_buffer(uint8_t *bytecode_buffer, uint32_t byte_count);
void disassemble_8086(uint8_t byte_1, uint8_t byte_2);

int main(void) {
  uint8_t error_code;
  error_code = load_binary_file("test", bytecode, &byte_count);
  dump_buffer(bytecode, byte_count);
  dump_error_code(error_code);
  return 0;
}

void display_bits(uint8_t byte) {
  /** Display bits
   * Prints the binary content of a byte
   */
  for (uint8_t idx = 8; idx > 0; --idx) {
    putchar(byte & (1u << (idx - 1)) ? '1' : '0');
  }
}

void dump_buffer(uint8_t *bytecode_buffer, uint32_t byte_count) {
  /** Dump buffer
   * Prints the binary contents of every byte in a buffer
   */
  puts("=======<DISASSEMBLY OUTPUT>=======");
  for (uint32_t idx = 0; idx < byte_count; idx += 2) {
    printf("%04d ", idx); /* Missing error handling case */
    display_bits(bytecode_buffer[idx]);
    putchar(' ');
    display_bits(bytecode_buffer[idx + 1]);
    putchar(' ');
    disassemble_8086(bytecode_buffer[idx], bytecode_buffer[idx + 1]);
    putchar('\n');
  }
}

void disassemble_8086(uint8_t byte_1, uint8_t byte_2) {
  uint8_t opcode = (byte_1 & OPCODE_MASK) >> 2;
  uint8_t d_bit = (byte_1 & D_MASK) >> 1;
  uint8_t w_bit = (byte_1 & W_MASK) >> 0;
  uint8_t mod = (byte_2 & MOD_MASK) >> 6;
  uint8_t reg = (byte_2 & REG_MASK) >> 3;
  uint8_t rm = (byte_2 & RM_MASK) >> 0;
  uint8_t eacidx = (mod << 3) | rm;
  string_t string;
  init_string(&string, STRING_SIZE, output);
  switch (opcode) {
    case 0b100010:
      append_string(&string,  4, "mov");
      if (d_bit == 0b00) {
        if (w_bit == 0b00) {
          if (mod == 0b11) {
            append_string(&string, 3, byte_registers[rm]);
          } else {
            append_string(&string, 20, eac_table[eacidx]);
          }
          append_string(&string, 3, byte_registers[reg]);
        }
        else {
          if (mod == 0b11) {
            append_string(&string, 3, word_registers[rm]);
          } else {
            append_string(&string, 20, eac_table[eacidx]);
          }
          append_string(&string, 3, word_registers[reg]);
        }
      }
      else {
        if (w_bit == 0b00) {
          append_string(&string, 3, byte_registers[reg]);
          if (mod == 0b11) {
            append_string(&string, 3, byte_registers[rm]);
          } 
          else {
            append_string(&string, 20, eac_table[eacidx]);
          }
        }
        else {
          append_string(&string, 3, word_registers[reg]);
          if (mod == 0b11) {
            append_string(&string, 3, word_registers[rm]);
          }
          else {
            append_string(&string, 20, eac_table[eacidx]);
          }
        }
      }
      break;
    case 0b11111000: /* Processor control instructions */
      /* Clear carry */
      append_string(&string, 4, "clc");
      break;
    case 0b11110101:
      /* Complement carry */
      append_string(&string, 4, "cwc")
      break;
    case 0b11111001:
      /* Set carry */
      append_string(&string, 4, "stc");
      break;
    case 0b11111100:
      /* Clear direction */
      append_string(&string, 4, "std");
      break;
    case 0b11111010:
      /* Clear interrupt */
      append_string(&string, 4, "cli");
      break;
    case 0b11111011:
      /* Set interrupt */
      append_string(&string, 4, "sti");
      break;
    case 0b11110100:
      /* Halt */
      append_string(&string, 4, "hlt");
      break;
    case 0b10011011:
      /* Wait */
      append_string(&string, 5, "wait");
      break;
    case 0b11110000:
      /* Bus lock prefix */
      append_string(&string, 5, "lock");
      break;
    default:
      append_string(&string, 15, "UNKNOWN OPCODE");
  }
  print_string(&string);
} 
