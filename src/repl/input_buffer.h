#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>


/*
 * This module provides types and functions for the input buffer.
 * 
 * To read a line of input, use getline():
 * ssize_t getline(char **lineptr, size_t *n, FILE *stream);
 *
 * lineptr : a pointer to the variable we use to point to the buffer containing
 * the read line. If it set to NULL it is mallocatted by getline and should thus
 * be freed by the user, even if the command fails.
 *
 * n : a pointer to the variable we use to save the size of allocated buffer.
 *
 * stream : the input stream to read from. We’ll be reading from standard input.
 *
 * return value : the number of bytes read, which may be less than the size of
 * the buffer.
 *
 * */


typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();

void print_prompt();

void read_input(InputBuffer* input_buffer);

void close_input_buffer(InputBuffer* input_buffer);

#endif
