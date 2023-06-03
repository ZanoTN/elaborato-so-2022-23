# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -g

all: F4server F4client

# Directories
SRC_DIR := src
BIN_DIR := bin

# Color
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

create_bin_dir:
	@mkdir -p $(BIN_DIR)

F4server: create_bin_dir
	@echo -e "> \033[0;31mCOMPILE SERVER\033[0m"
	$(CC) $(CFLAGS) -o bin/F4Server $(SRC_DIR)/server.c $(SRC_DIR)/error_exit.c $(SRC_DIR)/my_own_library_max_dim.c $(SRC_DIR)/fifo.c

F4client: create_bin_dir
	@echo -e "> \033[0;32mCOMPILE CLIENT\033[0m"
	$(CC) $(CFLAGS) -o bin/F4Client $(SRC_DIR)/client.c $(SRC_DIR)/error_exit.c $(SRC_DIR)/my_own_library_max_dim.c $(SRC_DIR)/fifo.c


clean: create_bin_dir
	rm -f $(BIN_DIR)/$(TARGET)

.PHONY: all clean create_bin_dir	