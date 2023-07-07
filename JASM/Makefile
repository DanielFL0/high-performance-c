CC = gcc
CFLAGS = -g -Wall
TARGET = jasm

DEPS = error.c file_handler.c string_builder.c

CFLAGS = -Wall -Wextra -std=c99

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(DEPS)