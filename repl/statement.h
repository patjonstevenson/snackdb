#ifndef STATEMENT_H
#define STATEMENT_H

#include "input_buffer.h"
#include "../store/row.h"

#include <stdint.h>


/*
 * Types
 */
typedef enum {
    STATEMENT_INSERT, 
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    // TODO: Create interface for Row
    Row row_to_insert; // only used by insert statement
} Statement;

typedef enum {
    PREPARE_SUCCESS, 
    PREPARE_UNRECOGNIZED_STATEMENT, 
    PREPARE_SYNTAX_ERROR
} PrepareResult;

/*
 * Function Declarations
 */

PrepareResult prepare_statement(InputBuffer* input_buffer, 
                                Statement* statement);

void execute_statement(Statement* statement);

#endif
