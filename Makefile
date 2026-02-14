NAME = nexuscoin
VERSION = 0.1.0

# Directories
SRC_DIR = src
OUT_DIR = out

# Compiler
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

# Automatically add all src subdirectories to include path
INC_DIRS := $(shell find $(SRC_DIR) -type d)
CFLAGS += $(addprefix -I,$(INC_DIRS))

# Libraries
LDFLAGS = -lsecp256k1 -lcrypto

# Find all .c files recursively
SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Map src/... -> out/... (preserve structure)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

# Output binary
TARGET = $(OUT_DIR)/$(NAME)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile rule (handles subdirectories)
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OUT_DIR)

# Rebuild
re: clean all

.PHONY: all clean re
