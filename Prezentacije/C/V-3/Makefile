# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -std=c11

# Source files
SRC = main.c

# Object files (automatically generated from SRC)
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = main

# Default rule: build the target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)