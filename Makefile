CC=gcc

SRC_DIR=./src
TEST_DIR=./test
BIN_DIR=./bin

# REPL
repl=$(SRC_DIR)/repl

input_buffer: $(repl)/input_buffer.c $(repl)/input_buffer.h
	$(CC) -c $(repl)/input_buffer.c

metacommand: $(repl)/metacommand.c $(repl)/metacommand.h
	$(CC) -c $(repl)/metacommand.c

statement: $(repl)/statement.c $(repl)/statement.h
	$(CC) -c $(repl)/statement.c

# DATA STORE
store=$(SRC_DIR)/store

row: $(store)/row.c $(store)/row.h
	$(CC) -c $(store)/row.c

table: $(store)/table.c $(store)/table.h
	$(CC) -c $(store)/table.c

# MAIN
main: input_buffer metacommand statement row table $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c
	$(CC) input_buffer.o metacommand.o statement.o row.o table.o main.o -o snackdb
	rm *.o

debug: input_buffer metacommand statement row table $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c
	$(CC) input_buffer.o metacommand.o statement.o row.o table.o main.o -g -o snackdb
	rm *.o

# TEST
TESTS=$(TEST_DIR)/*.c
test: $(TESTS)
	$(CC) -c $(TESTS)
	$(CC) *.o -g -o run_test
	rm *.o
	./run_test

