CC=gcc

input_buffer: repl/input_buffer.c repl/input_buffer.h
	gcc -c repl/input_buffer.c

metacommand: repl/metacommand.c repl/metacommand.h
	gcc -c repl/metacommand.c

statement: repl/statement.c repl/statement.h
	gcc -c repl/statement.c

main: input_buffer metacommand statement main.c
	gcc -c main.c
	gcc input_buffer.o metacommand.o statement.o main.o -o snackdb
	rm *.o

