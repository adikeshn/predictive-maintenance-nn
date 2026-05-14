CC = gcc
CFLAGS = -Wall -Werror -g

SRC_DIR = src
BUILD_DIR = src/build

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/evaluate.c $(SRC_DIR)/free_struct.c \
      $(SRC_DIR)/cost.c $(SRC_DIR)/activations.c $(SRC_DIR)/util.c $(SRC_DIR)/train.c $(SRC_DIR)/python_facing.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = machine_failure_net

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Isrc/headers -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)