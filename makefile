DIRS := bin obj build data
CC := gcc 
CFLAGS := -Wall -Wextra -Werror -Wpedantic -std=c99 -g
LDFLAGS := -lm

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
BIN := 	bin/main.elf
MAIN := src/main.c

$(DIRS):
	mkdir -p $@

$(OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

all: $(DIRS) build

build: $(DIRS) $(BIN)

run: $(BIN)
	@ ./$(BIN)

clean:
	rm -rf $(DIRS)

.PHONY: all build run clean