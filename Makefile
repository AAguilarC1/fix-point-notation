# TODO: Add multiple OS support

NAME := fix_point

BIN_DIR := bin
OBJ_DIR := obj
DATA_DIR := data
TESTS_DIR := tests
TABLE_DIR := lib/table
SCRIPTS := scripts

DIRS := $(BIN_DIR) $(OBJ_DIR) $(BUILD_DIR) $(DATA_DIR) 

CC := clang
CFLAGS := -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -Wall -Wextra -pedantic
LDFLAGS := -lm

dbg ?= 0
ifeq ($(dbg), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(SRC:src/%.c=obj/%.o)
TARGET := $(BIN_DIR)/$(NAME).out
TEST := $(BIN_DIR)/$(NAME)_test.out

$(DIRS):
	mkdir -p $@

$(OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(TEST): $(OBJ)
	$(CC) $(CFLAGS) $(filter-out obj/main.o, $(OBJ)) $(TESTS_DIR)/*.c -lcunit -o $@ $(LDFLAGS) 

all: build $(TARGET)

build: $(DIRS)

run: all
	@./$(TARGET)

check: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(TARGET)

test: build $(TEST)
	@./$(TEST)

setup:
	@sudo apt install -y valgrind
	@sudo apt install -y build-essential
	@sudo apt install -y libcunit1 libcunit1-doc libcunit1-dev
	@sudo apt update
	@sudo apt upgrade -y
	@sudo apt autoremove -y
	@sudo apt autoclean -y

clean:
	rm -rf  $(DIRS)

.PHONY: all setup build run clean