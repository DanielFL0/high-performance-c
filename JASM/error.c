#include <stdio.h>
#include "common.h"
#include "error.h"

void dump_error_code(uint8_t error_code) {
  switch (error_code) {
    case 0x00:
    puts("JASM SUCCESS: Program ran successfully.");
    break;
    case 0x01:
    puts("JASM FILE OPEN ERROR: Couldn't open file.");
    break;
    case 0x02:
    puts("JASM FILE READ ERROR: Couldn't read from file.");
    break;
    case 0x03:
    puts("JASM FILE WRITE ERROR: Couldn't write to file.");
    break;
    case 0x04:
    puts("JASM FILE CLOSE ERROR: Couldn't close file.");
    break;
    case 0x05:
    puts("JASM PRINTF STDOUT ERROR: Couldn't print to stdout.");
    break;
    case 0x06:
    puts("JASM UNKNOWN INSTRUCTION ERROR: Couldn't decode current instruction.");
    break;
  }
}