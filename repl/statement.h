#include "input_buffer.h"
#include <stdint.h>

/*
 * Macro Consts
 */
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

/*
 * Types
 */

typedef enum {
    STATEMENT_INSERT, 
    STATEMENT_SELECT
} StatementType;

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
    StatementType type;
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

