CC=gcc

input_buffer: input_buffer.c input_buffer.h
	gcc -c input_buffer.c

metacommand: metacommand.c metacommand.h
	gcc -c metacommand.c

statement: statement.c statement.h
	gcc -c statement.c

repl: input_buffer metacommand statement repl.c
	gcc -c repl.c
	gcc input_buffer.o metacommand.o statement.o repl.o -o repl
	rm *.o

