# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Igrep/include -g

# Directories
SRC_DIR = grep/src
INC_DIR = grep/include
BUILD_DIR = build
TEST_DIR = tests

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
TARGET = $(BUILD_DIR)/grep

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test target
test: all
	@echo "Running test cases..."
	@mkdir -p $(TEST_DIR)/outputs
	@bash $(TEST_DIR)/run_tests.sh

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_DIR)/outputs

# PHONY targets
.PHONY: all clean test
