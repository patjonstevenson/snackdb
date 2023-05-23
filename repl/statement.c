#include "statement.h"
#include <string.h>
#include <stdio.h>

PrepareResult prepare_statement(InputBuffer* input_buffer,
        Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("Inserting...\n");
            break;
        case (STATEMENT_SELECT):
            printf("Selecting...\n");
            break;
    }
}

