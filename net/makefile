CC = gcc
CFLAGS = -Wall -Werror -g

BUILD_DIR = build

SRC = main.c init.c evaluate.c free_struct.c cost.c activations.c matrix_ops.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

TARGET = activitynet

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)