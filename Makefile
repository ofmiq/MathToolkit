CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined
LDFLAGS = -lm

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
BIN = math_toolkit

all: $(BIN)

$(BIN):
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

clean:
	rm -f $(BIN)
