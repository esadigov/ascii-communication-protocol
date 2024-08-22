# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TEST_DIR = tests
EXAMPLE_DIR = examples

# Files
SRC_FILES = $(SRC_DIR)/serial_com.c
OBJ_FILES = $(OBJ_DIR)/serial_com.o
TEST_FILES = $(TEST_DIR)/test_comm_protocol.c
EXAMPLE_FILES = $(EXAMPLE_DIR)/example_usage.c

# Targets
LIB_TARGET = libcommprotocol.a
TEST_TARGET = test_comm_protocol
EXAMPLE_TARGET = example_usage

# Default target
all: $(LIB_TARGET) $(EXAMPLE_TARGET)

# Build the library
$(LIB_TARGET): $(OBJ_FILES)
	@echo "Creating library $@"
	ar rcs $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build the test
$(TEST_TARGET): $(TEST_FILES) $(LIB_TARGET)
	$(CC) $(CFLAGS) $^ -o $@

# Build the example
$(EXAMPLE_TARGET): $(EXAMPLE_FILES) $(LIB_TARGET)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(LIB_TARGET) $(TEST_TARGET) $(EXAMPLE_TARGET)

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run the example
run_example: $(EXAMPLE_TARGET)
	./$(EXAMPLE_TARGET)

.PHONY: all clean test run_example
