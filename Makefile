CC = gcc
FLAGS = -Wall -Wextra -I$(INCLUDE_DIR)
BUILD_DIR = build
OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/javaMaker

all:$(TARGET)

.PHONY: all clean

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)