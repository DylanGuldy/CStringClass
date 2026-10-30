# Basic Flags
CC = gcc
CFLAGS = -Wall -std=c11 -g
INCLUDE_FLAGS = -I
INCLUDE = include/
SRC = src
BUILD = build

# Library Flags
AR = ar
LDFLAGS = -Lbuild/bin/
LDLIBS = -lcstring

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
EXAMPLE_DIR = examples

# Building library
LIB_SRCS = $(wildcard $(SRC)/*.c)
# mmmmm maybe edit this and move it into the compile
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB = $(BIN_DIR)/libcstring.a

# Example main
EXAMPLE = $(BUILD_DIR)/main_example

all: $(EXAMPLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "**********"
	@echo "**********"
	@echo "**********"
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
# TODO probably have different rules for each
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(LIB): $(LIB_OBJS)
	$(AR) rcs $@ $^

$(EXAMPLE): $(EXAMPLE_DIR)/main_example.c $(LIB)
	$(CC) $(CFLAGS) $< $(INCLUDE_FLAGS) $(INCLUDE) $(LDFLAGS) $(LDLIBS) -o $@



clean:
	rm -rf build

.PHONY: all clean