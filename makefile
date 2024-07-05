NAME := fix-point

BIN_DIR := bin
OBJ_DIR := obj
BUILD_DIR := build
DATA_DIR := data
TESTS_DIR := tests

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

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
BIN := 	bin/$(NAME)
MAIN := src/main.c

$(DIRS):
	mkdir -p $@

$(OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

all: build run

build: $(DIRS) $(BIN)

run: $(BIN)
	@ ./$(BIN)

check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN_DIR)/$(NAME)

$(NAME)_test:
	@$(CC) $(CFLAGS) -lcunit -o $(BIN_DIR)/$@ $(TESTS_DIR)/*.c

test: $(NAME)_test
	@$(BIN_DIR)/$(NAME)_test

setup:
	@sudo apt install -y valgrind clang-format clang-tidy
	@sudo apt install -y build-essential
	@sudo apt install -y libcunit1 libcunit1-doc libcunit1-dev
	@sudo apt update
	@sudo apt upgrade -y
	@sudo apt autoremove -y

clean:
	rm -rf $(DIRS)

.PHONY: all build run clean