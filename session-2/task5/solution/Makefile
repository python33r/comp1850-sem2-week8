# File locations
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Target executable
TARGET = pgm_tools

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link object files to create executable
$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
