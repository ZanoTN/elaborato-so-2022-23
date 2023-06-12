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
	$(CC) $(CFLAGS) -o bin/F4Server \
	src/F4Server.c \
	src/server.c \
	src/error_exit.c \
	src/message_queue.c \
	src/shared_memory.c \
	src/semaphore.c \
	src/forza4.c

F4client: create_bin_dir
	@echo -e "> \033[0;32mCOMPILE CLIENT\033[0m"
	$(CC) $(CFLAGS) -o bin/F4Client \
	src/F4Client.c \
	src/client.c \
	src/error_exit.c \
	src/message_queue.c \
	src/shared_memory.c \
	src/semaphore.c \
	src/forza4.c

# Only with kitty work
test:
	@kitty -e bin/F4Server 6 5 0 X &
	@kitty -e bin/F4Client Tony &
	@kitty -e bin/F4Client Max &

clean: create_bin_dir
	rm -f $(BIN_DIR)/$(TARGET)

.PHONY: all clean create_bin_dir test	