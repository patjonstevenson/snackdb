#ifndef STATEMENT_H
#define STATEMENT_H

#include "input_buffer.h"
#include "../store/row.h"
#include "../store/table.h"

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

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_FAILURE_UNKNOWN
} ExecuteResult;

/*
 * Function Declarations
 */

PrepareResult prepare_statement(InputBuffer* input_buffer, 
                                Statement* statement);

ExecuteResult execute_insert(Statement* statement, Table* table);

ExecuteResult execute_select(Statement* statement, Table* table);

ExecuteResult execute_statement(Statement* statement, Table* table);

#endif
