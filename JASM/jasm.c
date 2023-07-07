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
    case 0b00000000:
      /* ADD
       * Register/memory with register to either
       */
      break;
    case 0b00000001:
      /* ADD
       * Register/memory with register to either
       */
      break;
    case 0b00000010:
      /* ADD
       * Register/memory with register to either
       */
      break;
    case 0b00000011:
      /* ADD
       * Register/memory with register to either
       */
      break;
    case 0b00000100:
      /* ADD
       * Immediate to accumulator
       */
      break;
    case 0b00000101:
      /* ADD
       * Immediate to accumulator
       */
      break;
    case 0b00000110:
      /** PUSH
       * Segment register 
       */
      break;
    case 0b00000111:
      /** POP
       * Segment register
       */
      break;
    case 0b00001000:
      /** OR
       * Register/memory and register to either
       */
      break;
    case 0b00001001:
      /** OR
       * Register/memory and register to either
       */
      break;
    case 0b00001010:
      /** OR
       * Register/memory and register to either
       */
      break;
    case 0b00001011:
      /** OR
       * Register/memory and register to either
       */
      break;
    case 0b00001100:
      /** OR
       * Immediate to accumulator
       */
      break;
    case 0b00001101:
      /** OR
       * Immediate to accumulator
       */
      break;
    case 0b00001110:
      /** PUSH
       * Segment register 
       */
      break;
    case 0b00001111:
      /** POP
       * Segment register
       */
      break;
    case 0b00010000:
      /** ADC
       * Add with carry
       * Register/memory with register to either
       */
      /** TEST
       * And function to flags no result
       * Register/memory and register
       */
      break;
    case 0b00010001:
      /** ADC
       * Add with carry
       * Register/memory with register to either
       */
      /** TEST
       * And function to flags no result
       * Register/memory and register
       */
      break;
    case 0b00010010:
      /** ADC
       * Add with carry
       * Register/memory with register to either
       */
      /** TEST
       * And function to flags no result
       * Register/memory and register
       */
      break;
    case 0b00010011:
      /** ADC
       * Add with carry
       * Register/memory with register to either
       */
      /** TEST
       * And function to flags no result
       * Register/memory and register
       */
      break;
    case 0b00010100:
      /** ADC
       * Add with carry
       * Immediate to ccumulator
       */
      break;
    case 0b00010101:
      /** ADC
       * Add with carry
       * Immediate to ccumulator
       */
      break;
    case 0b00010110:
      /** PUSH
       * Segment register 
       */
      break;
    case 0b00010111:
      /** POP
       * Segment register
       */
      break;
    case 0b00011000:
      /** SBB
       * Subtract with borrow
       * Register/memory and register to either
       */
      break;
    case 0b00011001:
      /** SBB
       * Subtract with borrow
       * Register/memory and register to either
       */
      break;
    case 0b00011010:
      /** SBB
       * Subtract with borrow
       * Register/memory and register to either
       */
      break;
    case 0b00011011:
      /** SBB
       * Subtract with borrow
       * Register/memory and register to either
       */
      break;
    case 0b00011100:
      /** SBB
       * Subtract with borrow
       * Immediate from accumulator
       */
      break;
    case 0b00011101:
      /** SBB
       * Subtract with borrow
       * Immediate from accumulator
       */
      break;
    case 0b00011110:
      /** PUSH
       * Segment register 
       */
      break;
    case 0b00011111:
      /** POP
       * Segment register
       */
      break;
    case 0b00100000:
      /** AND
       * Register/memory with register to either
       */
      break;
    case 0b00100001:
      /** AND
       * Register/memory with register to either
       */
      break;
    case 0b00100010:
      /** AND
       * Register/memory with register to either
       */
      break;
    case 0b00100011:
      /** AND
       * Register/memory with register to either
       */
      break;
    case 0b00100100:
      /** AND
       * Immediate to accumulator
       */
      break;
    case 0b00100101:
      /** AND
       * Immediate to accumulator
       */
      break;
    case 0b00100110:
      /** SEGMENT
       * Override prefix
       */
      break;
    case 0b00100111:
      /** DAA
       * Decimal adjust for add
       */
      break;
    case 0b00101000:
      /** SUB
       * Subtract
       * Register/memory and register to either
       */
      break;
    case 0b00101001:
      /** SUB
       * Subtract
       * Register/memory and register to either
       */
      break;
    case 0b00101010:
      /** SUB
       * Subtract
       * Register/memory and register to either
       */
      break;
    case 0b00101011:
      /** SUB
       * Subtract
       * Register/memory and register to either
       */
      break;
    case 0b00101100:
      /** SUB
       * Subtract
       * Immediate from accumulator
       */
      break;
    case 0b00101101:
      /** SUB
       * Subtract
       * Immediate from accumulator
       */
      break;
    case 0b00101110:
      /** SEGMENT
       * Override prefix
       */
      break;
    case 0b00101111:
      /** DAS
       * Decimal adjust for subtract
       */
      break;
    case 0b00110000:
      /** XOR
       * Exclusive or
       * Register/memory and register to either
       */
      break;
    case 0b00110001:
      /** XOR
       * Exclusive or
       * Register/memory and register to either
       */
      break;
    case 0b00110010:
      /** XOR
       * Exclusive or
       * Register/memory and register to either
       */
      break;
    case 0b00110011:
      /** XOR
       * Exclusive or
       * Register/memory and register to either
       */
      break;
    case 0b00110100:
      /** XOR
       * Exclusive or
       * Immediate to register/memory
       */
      /** XOR
       * Exclusive or
       * Immediate to accumulator
       */
      break;
    case 0b00110101:
      /** XOR
       * Exclusive or
       * Immediate to register/memory
       */
      /** XOR
       * Exclusive or
       * Immediate to accumulator
       */
      break;
    case 0b00110110:
      /** SEGMENT
       * Override prefix
       */
      break;
    case 0b00110111:
      /** AAA
       * ASCII adjust for add
       */
      break;
    case 0b00111000:
      /** CMP
       * Compare
       * Register/memory and register
       */
      break;
    case 0b00111001:
      /** CMP
       * Compare
       * Register/memory and register
       */
      break;
    case 0b00111010:
      /** CMP
       * Compare
       * Register/memory and register
       */
      break;
    case 0b00111011:
      /** CMP
       * Compare
       * Register/memory and register
       */
      break;
    case 0b00111100:
      /** CMP
       * Compare
       * Immediate with accumulator
       */
      break;
    case 0b00111101:
      /** CMP
       * Compare
       * Immediate with accumulator
       */
      break;
    case 0b00111110:
      /** SEGMENT
       * Override prefix
       */
      break;
    case 0b00111111:
      /** AAS
       * ASCII adjust for subtract
       */
      break;
    case 0b01000000:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000001:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000010:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000011:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000100:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000101:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000110:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01000111:
      /** INC
       * Increment
       * Register
       */
      break;
    case 0b01001000:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001001:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001010:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001011:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001100:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001101:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001110:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01001111:
      /** DEC
       * Decrement
       * Register
       */
      break;
    case 0b01010000:
      /** PUSH
       * Register 
       */
      break;
    case 0b01010001:
      /* Register */
      break;
    case 0b01010010:
      /* Register */
      break;
    case 0b01010011:
      /* Register */
      break;
    case 0b01010100:
      /* Register */
      break;
    case 0b01010101:
      /* Register */
      break;
    case 0b01010110:
      /* Register */
      break;
    case 0b01010111:
      /* Register */
      break;
    case 0b01011000:
      /** POP
       * Register
       */
      break;
    case 0b01011001:
      /** POP
       * Register
       */
      break;
    case 0b01011010:
      /** POP
       * Register
       */
      break;
    case 0b01011011:
      /** POP
       * Register
       */
      break;
    case 0b01011100:
      /** POP
       * Register
       */
      break;
    case 0b01011101:
      /** POP
       * Register
       */
      break;
    case 0b01011110:
      /** POP
       * Register
       */
      break;
    case 0b01011111:
      /** POP
       * Register
       */
      break;
    case 0b01100000:
      break;
    case 0b01100001:
      break;
    case 0b01100010:
      break;
    case 0b01100011:
      break;
    case 0b01100100:
      break;
    case 0b01100101:
      break;
    case 0b01100110:
      break;
    case 0b01100111:
      break;
    case 0b01101000:
      break;
    case 0b01101001:
      break;
    case 0b01101010:
      break;
    case 0b01101011:
      break;
    case 0b01101100:
      break;
    case 0b01101101:
      break;
    case 0b01101110:
      break;
    case 0b01101111:
      break;
    case 0b01110000:
      /** JO
       * Jump on overflow
       */
      break;
    case 0b01110001:
      /** JNO
       * Jump on not overflow
       */
      break;
    case 0b01110010:
      /** JB/JNAE
       * Jump on below/not above or equal
       */
      break;
    case 0b01110011:
      /** JNB/JAE
       * Jump on not below/above or equal
       */
      break;
    case 0b01110100:
      /** JE/JZ
       * Jump on equal/zero
       */
      break;
    case 0b01110101:
      /** JNE/JNZ
       * Jump on not equal/not zero
       */
      break;
    case 0b01110110:
      /** JBE/JNA
       * Jump on below or equal/not above
      */
      break;
    case 0b01110111:
      /** JNBE/JA
       * Jump on not below or equal/above
       */
      break;
    case 0b01111000:
      /** JS
       * Jump on sign
       */
      break;
    case 0b01111001:
      /** JNS
       * Jump on not sign
       */
      break;
    case 0b01111010:
      /** JP/JPE
       * Jump on parity/parity even
       */
      break;
    case 0b01111011:
      /** JNP/JPO
       * Jump on not par/par odd
       */
      break;
    case 0b01111100:
      /** JL/JNGE 
       * Jump on less/not greater or equal
       */
      break;
    case 0b01111101:
      /** JNL/JGE 
       * Jump on not less/greater or equal
       */
      break;
    case 0b01111110:
      /** JLE/JNG 
       * Jump on less or equal/not greater
      */
      break;
    case 0b01111111:
      /** JNLE/JG
       * Jump on not less or equal/greater
       */
      break;
    case 0b10000000:
      /* ADD
       * Immediate to register/memory
       */
      /* ADC
       * Add with carry
       * Immediate to register/memory
       */
      /** SUB
       * Subtract
       * Immediate from register/memory
       */
      /** SBB
       * Subtract with borrow
       * Immediate from register/memory
       */
      /** CMP
       * Compare
       * Immediate with register/memory
       */
      /** AND
       * Immediate to register/memory
       */
      /** OR
       * Immediate to register/memory
       */
      break;
    case 0b10000001:
      /* ADD
       * Immediate to register/memory
       */
      /* ADC
       * Add with carry
       * Immediate to register/memory
       */
      /** SUB
       * Subtract
       * Immediate from register/memory
       */
      /** SBB
       * Subtract with borrow
       * Immediate from register/memory
       */
      /** CMP
       * Compare
       * Immediate with register/memory
       */
      /** AND
       * Immediate to register/memory
       */
      /** OR
       * Immediate to register/memory
       */
      break;
    case 0b10000010:
      /* ADD
       * Immediate to register/memory
       */
      /* ADC
       * Add with carry
       * Immediate to register/memory
       */
      /** SUB
       * Subtract
       * Immediate from register/memory
       */
      /** SBB
       * Subtract with borrow
       * Immediate from register/memory
       */
      /** CMP
       * Compare
       * Immediate with register/memory
       */
      break;
    case 0b10000011:
      /* ADD
       * Immediate to register/memory
       */
      /* ADC
       * Add with carry
       * Immediate to register/memory
       */
      /** SUB
       * Subtract
       * Immediate from register/memory
       */
      /** SBB
       * Subtract with borrow
       * Immediate from register/memory
       */
      /** CMP
       * Compare
       * Immediate with register/memory
       */
      break;
    case 0b10000100:
      break;
    case 0b10000101:
      break;
    case 0b10000110:
      /** XCHG
       * Register/memory with register
       */
      break;
    case 0b10000111:
      /** XCHG
       * Register/memory with register
       */
      break;
    case 0b10001000:
      /** MOV
       * Register/memory to/from register 
       */
      break;
    case 0b10001001:
      /** MOV
       * Register/memory to/from register 
       */
      break;
    case 0b10001010:
      /* Immediate to register/memory */
      break;
    case 0b10001011:
      /* Immediate to register/memory */
      break;
    case 0b10001100:
      /* Segment register to register/memory */
      break;
    case 0b10001101:
      /** LEA
       * Load EA to register
       */
      break;
    case 0b10001110:
      /** MOV
       * Register/memory to segment register 
       */
      break;
    case 0b10001111:
      /** POP
       * Register/memory 
       */
      break;
    case 0b10010000:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010001:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010010:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010011:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010100:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010101:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010110:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10010111:
      /** XCHG
       * Register with accumulator
       */
      break;
    case 0b10011000:
      /** CBW
       * Convert byte to word
       */
      break;
    case 0b10011001:
      /** CWD
       * Convert word to double word
       */
      break;
    case 0b10011010:
      /** CALL
       * Direct intersegment
       */
      break;
    case 0b10011011:
      /** WAIT
       * Wait 
       */
      append_string(&string, 5, "wait");
      break;
    case 0b10011100:
      /** PUSHF
       * Push flags
       */
      break;
    case 0b10011101:
      /** POPF
       * Pop flags
       */
      break;
    case 0b10011110:
      /** SAHF
       * Store AH into flags
       */
      break;
    case 0b10011111:
      /** LAHF
       * Load AH with flags
       */
      break;
    case 0b10100000:
      /* Memory to accumulator */
      break;
    case 0b10100001:
      /* Memory to accumulator */
      break;
    case 0b10100010:
      /* Accumulator to memory */
      break;
    case 0b10100011:
      /* Accumulator to memory */
      break;
    case 0b10100100:
      /** MOVS
       * Move byte/word
       */
      break;
    case 0b10100101:
      /** MOVS
       * Move byte/word
       */
      break;
    case 0b10100110:
      /** CMPS
       * Compare byte/word
       */
      break;
    case 0b10100111:
      /** CMPS
       * Compare byte/word
       */
      break;
    case 0b10101000:
      /** TEST
       * And function to flags no result
       * Immediate data and accumulator
       */
      break;
    case 0b10101001:
      /** TEST
       * And function to flags no result
       * Immediate data and accumulator
       */
      break;
    case 0b10101010:
      /** STDS
       * Store byte/word from AL/AX
       */
      break;
    case 0b10101011:
      /** STDS
       * Store byte/word from AL/AX
       */
      break;
    case 0b10101100:
      /** LODS
       * Load byte/word to AL/AX
       */
      break;
    case 0b10101101:
      /** LODS
       * Load byte/word to AL/AX
       */
      break;
    case 0b10101110:
      /** SCAS
       * Scan byte/word
       */
      break;
    case 0b10101111:
      /** SCAS
       * Scan byte/word
       */
      break;
    case 0b10110000:
      /* Immediate to register */
      break;
    case 0b10110001:
      /* Immediate to register */
      break;
    case 0b10110010:
      /* Immediate to register */
      break;
    case 0b10110011:
      /* Immediate to register */
      break;
    case 0b10110100:
      /* Immediate to register */
      break;
    case 0b10110101:
      /* Immediate to register */
      break;
    case 0b10110110:
      /* Immediate to register */
      break;
    case 0b10110111:
      /* Immediate to register */
      break;
    case 0b10111000:
      /* Immediate to register */
      break;
    case 0b10111001:
      /* Immediate to register */
      break;
    case 0b10111010:
      /* Immediate to register */
      break;
    case 0b10111011:
      /* Immediate to register */
      break;
    case 0b10111100:
      /* Immediate to register */
      break;
    case 0b10111101:
      /* Immediate to register */
      break;
    case 0b10111110:
      /* Immediate to register */
      break;
    case 0b10111111:
      /* Immediate to register */
      break;
    case 0b11000000:
      break;
    case 0b11000001:
      break;
    case 0b11000010:
      /** RET
       * Return from call
       * Within segment adding immediate to SP
       */
      break;
    case 0b11000011:
      /** RET
       * Return from call
       * Within segment
       */
      break;
    case 0b11000100:
      /** LES
       * Load pointer to ES
       */
      break;
    case 0b11000101:
      /** LDS
       * Load pointer to DS
       */
      break;
    case 0b11000110:
      break;
    case 0b11000111:
      break;
    case 0b11001000:
      break;
    case 0b11001001:
      break;
    case 0b11001010:
      /** RET
       * Return from call
       * Intersegment adding immediate to SP
       */
      break;
    case 0b11001011:
      /** RET
       * Return from call
       * Intersegment
       */
      break;
    case 0b11001100:
      /** INT
       * Interrupt
       * Type 3
       */
      break;
    case 0b11001101:
      /** INT
       * Interrupt
       * Type specified
       */
      break;
    case 0b11001110:
      /** INTO
       * Interrupt on overflow
       */
      break;
    case 0b11001111:
      /** IRET
       * Interrupt return
       */
      break;
    case 0b11010000:
      /** SHL/SAL
       * Shift logical/arithmetic left
       */
      /** SHR
       * Shift logical right
       */
      /** SAR
       * Shift arithmetic right
       */
      /** ROL
       * Rotate left
       */
      /** ROR
       * Rotate right
       */
      /** RCL
       * Rotate through carry flag left
       */
      /** RCR
       * Rotate through carry right
       */
      break;
    case 0b11010001:
      /** SHL/SAL
       * Shift logical/arithmetic left
       */
      /** SHR
       * Shift logical right
       */
      /** SAR
       * Shift arithmetic right
       */
      /** ROL
       * Rotate left
       */
      /** ROR
       * Rotate right
       */
      /** RCL
       * Rotate through carry flag left
       */
      /** RCR
       * Rotate through carry right
       */
      break;
    case 0b11010010:
      /** SHL/SAL
       * Shift logical/arithmetic left
       */
      /** SHR
       * Shift logical right
       */
      /** SAR
       * Shift arithmetic right
       */
      /** ROL
       * Rotate left
       */
      /** ROR
       * Rotate right
       */
      /** RCL
       * Rotate through carry flag left
       */
      /** RCR
       * Rotate through carry right
       */
      break;
    case 0b11010011:
      /** SHL/SAL
       * Shift logical/arithmetic left
       */
      /** SHR
       * Shift logical right
       */
      /** SAR
       * Shift arithmetic right
       */
      /** ROL
       * Rotate left
       */
      /** ROR
       * Rotate right
       */
      /** RCL
       * Rotate through carry flag left
       */
      /** RCR
       * Rotate through carry right
       */
      break;
    case 0b11010100:
      /** AAM
       * ASCII adjust for multiply
       */
      break;
    case 0b11010101:
      /** AAD
       * ASCII adjust for divide
       */
      break;
    case 0b11010110:
      break;
    case 0b11010111:
      /** XLAT
       * Translate byte to AL
       */
      break;
    case 0b11011000:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011001:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011010:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011011:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011100:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011101:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011110:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11011111:
      /** ESC
       * Escape (to external device)
       */
      break;
    case 0b11100000:
      /** LOOPNZ/LOOPNE
       * Loop while not zero/equal
       */
      break;
    case 0b11100001:
      /** LOOPZ/LOOPE
       * loop while zero/equal
       */
      break;
    case 0b11100010:
      /** LOOP
       * Loop CX times
       */
      break;
    case 0b11100011:
      /** JCXZ
       * Jump on CX zero
       */
      break;
    case 0b11100100:
      /** IN
       * Fixed port
       */
      break;
    case 0b11100101:
      /** IN
       * Fixed port
       */
      break;
    case 0b11100110:
      /** OUT
       * Fixed port
       */
      break;
    case 0b11100111:
      /** OUT
       * Fixed port
       */
      break;
    case 0b11101000:
      /** CALL
       * Direct within segment
       */
      break;
    case 0b11101001:
      /** JMP
       * Unconditional jump
       * Direct within segment
       */
      break;
    case 0b11101010:
      /** JMP
       * Unconditional jump
       * Direct intersegment
       */
      break;
    case 0b11101011:
      /** JMP
       * Unconditional jump
       * Direct within segment-short
       */
      break;
    case 0b11101100:
      /** IN
       * Variable port
       */
      break;
    case 0b11101101:
      /** IN
       * Fixed port
       */
      break;
    case 0b11101110:
      /** OUT
       * Variable port
       */
      break;
    case 0b11101111:
      /** OUT
       * Variable port
       */
      break;
    case 0b11110000:
      /** LOCK
       * Bus lock prefix 
       */
      append_string(&string, 5, "lock");
      break;
    case 0b11110001:
      break;
    case 0b11110010:
      /** REP
       * Repeat
       */
      break;
    case 0b11110011:
      /** REP
       * Repeat
       */
      break;
    case 0b11110100:
      /** HLT
       * Halt 
       */
      append_string(&string, 4, "hlt");
      break;
    case 0b11110101:
      /** CMC
       * Complement carry 
       */
      append_string(&string, 4, "cwc");
      break;
    case 0b11110110:
      /** NEG
       * Change sign
       */
      /** MUL
       * Multiply (unsigned)
       */
      /** IMUL
       * Integer multiply (signed)
       */
      /** DIV
       * Divide (unsigned)
       */
      /** IDIV
       * Integer divide (signed)
       */
      /** NOT
       * Invert
       */
      /** TEST
       * And function to flags no result
       * Immediate data and register/memory
       */
      break;
    case 0b11110111:
      /** NEG
       * Change sign
       */
      /** MUL
       * Multiply (unsigned)
       */
      /** IMUL
       * Integer multiply (signed)
       */
      /** DIV
       * Divide (unsigned)
       */
      /** IDIV
       * Integer divide (signed)
       */
      /** NOT
       * Invert
       */
      /** TEST
       * And function to flags no result
       * Immediate data and register/memory
       */
      break;
    case 0b11111000:
      /** CLC
       * Clear carry 
       */
      append_string(&string, 4, "clc");
      break;
    case 0b11111001:
      /** STC
       * Set carry 
       */
      append_string(&string, 4, "stc");
      break;
    case 0b11111010:
      /** CLI
       * Clear interrupt 
       */
      append_string(&string, 4, "cli");
      break;
    case 0b11111011:
      /** STI
       * Set interrupt 
       */
      append_string(&string, 4, "sti");
      break;
    case 0b11111100:
      /** CLD
       * Clear direction 
       */
      append_string(&string, 4, "std");
      break;
    case 0b11111101:
      /** STD
       * Set direction
       */
      break;
    case 0b11111110:
      /** INC
       * Increment
       * Register/memory
       */
      /** DEC
       * Decrement
       * Register/memory
       */
      break;
    case 0b11111111:
      /** PUSH
       * Register/memory 
       */
      /** INC
       * Increment
       * Register/memory
       */
      /** DEC
       * Decrement
       * Register/memory
       */
      /** CALL
       * Indirect within segment
       */
      /** CALL
       * Indirect intersegment
       */
      /** JMP
       * Unconditional jump
       * Indirect within segment
       */
      /** JMP
       * Unconditional jump
       * Indirect intersegment
       */
      break;
    default:
      append_string(&string, 15, "UNKNOWN OPCODE");
  }
  print_string(&string);
} 
