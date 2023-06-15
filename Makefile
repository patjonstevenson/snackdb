CC=gcc

# REPL

input_buffer: repl/input_buffer.c repl/input_buffer.h
	gcc -c repl/input_buffer.c

metacommand: repl/metacommand.c repl/metacommand.h
	gcc -c repl/metacommand.c

statement: repl/statement.c repl/statement.h
	gcc -c repl/statement.c

# DATA STORE
row: store/row.c store/row.h
	gcc -c store/row.c

table: store/table.c store/table.h
	gcc -c store/table.c

# MAIN

main: input_buffer metacommand statement row table main.c
	gcc -c main.c
	gcc input_buffer.o metacommand.o statement.o row.o table.o main.o -o snackdb
	rm *.o

debug: input_buffer metacommand statement row table main.c
	gcc -c main.c
	gcc input_buffer.o metacommand.o statement.o row.o table.o main.o -g -o snackdb
	rm *.o


