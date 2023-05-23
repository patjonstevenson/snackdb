#include "input_buffer.h"

/*
 * Types
 */

typedef enum {
    STATEMENT_INSERT, STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
} Statement;

typedef enum {
    PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

/*
 * Function Declarations
 */

PrepareResult prepare_statement(InputBuffer* input_buffer, 
                                Statement* statement);

void execute_statement(Statement* statement);

