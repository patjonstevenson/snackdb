#include "../../src/repl/statement.h"
#include "../../src/repl/input_buffer.h"

#include <assert.h>


int prepare_statement_prepares_valid_select() {
    // given
    InputBuffer* input_buffer = new_input_buffer();
    input_buffer->buffer = "select";
    input_buffer->buffer_length = 12;
    input_buffer->input_length = 6;

    Statement statement;
    statement.type = STATEMENT_SELECT;

    PrepareResult expected_result = PREPARE_SUCCESS;

    // when
    PrepareResult actual_result = prepare_statement(input_buffer, &statement);

    // then
    assert(expected_result == actual_result);

    return 0;
}
